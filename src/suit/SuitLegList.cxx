#include "SuitLegList.h"

SuitLegList::SuitLegList(PT(DNASuitPath) path, DNAStorage* store, double suit_walk_speed): m_path(path),
                         m_store(store), m_suit_walk_speed(suit_walk_speed)
{
    // Create first leg
    PT(DNASuitPoint) start_point = path->get_point(0);
    PT(DNASuitPoint) heading_point = path->get_point(1);
    add_leg(start_point, heading_point,
            start_point->get_point_type() == DNASuitPoint::SIDE_DOOR_POINT
            ? SuitLeg::T_from_suit_building : SuitLeg::T_from_sky, -1);

    // Create mid legs
    for (int i = 1; i < path->get_num_points(); i++)
    {
        PT(DNASuitPoint) point_a = path->get_point(i - 1);
        PT(DNASuitPoint) point_b = path->get_point(i);
        block_number_t landmark_building_index = point_a->get_landmark_building_index();
        if (landmark_building_index == -1)
            landmark_building_index = point_b->get_landmark_building_index();

        add_leg(point_a, point_b, get_next_leg_type(i - 1), landmark_building_index);
    }

    // Create last leg
    PT(DNASuitPoint) end_point;

    int end_index = path->get_num_points() - 1;
    start_point = path->get_point(end_index - 1);
    end_point = path->get_point(end_index);

    SuitLeg::LegType last_leg_type;
    if (end_point->get_point_type() == DNASuitPoint::FRONT_DOOR_POINT)
        last_leg_type = SuitLeg::T_to_toon_building;

    else if (end_point->get_point_type() == DNASuitPoint::SIDE_DOOR_POINT)
        last_leg_type = SuitLeg::T_to_suit_building;

    else
        last_leg_type = SuitLeg::T_to_sky;

    add_leg(start_point, end_point, last_leg_type,
            end_point->get_landmark_building_index());

    add_leg(start_point, end_point, SuitLeg::T_off, -1);
}

SuitLegList::~SuitLegList()
{
    for (leg_vec_t::iterator it = m_legs.begin(); it != m_legs.end(); it++)
        delete *it;
}

SuitLeg::LegType SuitLegList::get_suit_leg_type(DNASuitPoint::PointType a,
                                                DNASuitPoint::PointType b)
{
    if (a == DNASuitPoint::SIDE_DOOR_POINT)
        return SuitLeg::T_walk_to_street;

    if (b == DNASuitPoint::FRONT_DOOR_POINT || b == DNASuitPoint::SIDE_DOOR_POINT)
        return SuitLeg::T_walk_from_street;

    return SuitLeg::T_walk;
}

int SuitLegList::get_num_legs()
{
    return m_legs.size();
}

SuitLeg* SuitLegList::get_leg(int index)
{
    nassertr(index < get_num_legs(), nullptr);
    return m_legs.at(index);
}

SuitLeg::LegType SuitLegList::get_type(int index)
{
    return get_leg(index)->get_type();
}

double SuitLegList::get_leg_time(int index)
{
    return get_leg(index)->get_leg_time();
}

zone_id_t SuitLegList::get_zone_id(int index)
{
    return get_leg(index)->get_zone_id();
}

block_number_t SuitLegList::get_block_number(int index)
{
    return get_leg(index)->get_block_number();
}

PT(DNASuitPoint) SuitLegList::get_point_a(int index)
{
    return get_leg(index)->get_point_a();
}

PT(DNASuitPoint) SuitLegList::get_point_b(int index)
{
    return get_leg(index)->get_point_b();
}

double SuitLegList::get_start_time(int index)
{
    return get_leg(index)->get_start_time();
}

int SuitLegList::get_leg_index_at_time(double time, int start_leg)
{
    if (start_leg < 0 || start_leg >= m_legs.size() || get_leg_time(start_leg) > time)
        start_leg = 0;

    int num_legs = get_num_legs();
    int next_leg = start_leg + 1;

    while (true)
    {
        if (next_leg >= num_legs || get_start_time(next_leg) > time)
            break;

        next_leg++;
    }

    return next_leg - 1;
}

bool SuitLegList::is_point_in_range(PT(DNASuitPoint) point, double low_time, double high_time)
{
    point_index_t point_index = point->get_index();
    int start_leg_index = get_leg_index_at_time(low_time, 0);
    int end_leg_index = get_leg_index_at_time(high_time, point_index);

    for (int i = start_leg_index; i <= end_leg_index; i++)
    {
        if (i >= get_num_legs())
            return false;

        SuitLeg* leg = get_leg(i);
        if (leg->get_point_a()->get_index() == point_index)
            return true;

        else if (leg->get_point_b()->get_index() == point_index)
            return true;
    }

    return false;
}

SuitLeg::LegType SuitLegList::get_next_leg_type(int index)
{
    return get_suit_leg_type(m_path->get_point(index)->get_point_type(),
                             m_path->get_point(index + 1)->get_point_type());
}

void SuitLegList::add_leg(PT(DNASuitPoint) point_a, PT(DNASuitPoint) point_b,
                          SuitLeg::LegType type, block_number_t landmark_building_index)
{
    zone_id_t zone_id = m_store->get_suit_edge_zone(point_a->get_index(),
                                                    point_b->get_index());

    SuitLeg* last_leg = m_legs.size() ? m_legs[m_legs.size() - 1] : nullptr;
    double start_time = last_leg ? last_leg->get_start_time() + last_leg->get_leg_time() : 0.0;

    if (point_a->get_point_type() == DNASuitPoint::COGHQ_OUT_POINT && type == SuitLeg::T_walk)
    {
        SuitLeg* hq_leg = new SuitLeg(start_time, zone_id,
                                      point_a->get_landmark_building_index(),
                                      point_a, point_b,
                                      SuitLeg::T_from_cog_HQ,
                                      m_suit_walk_speed);
        m_legs.push_back(hq_leg);
        start_time += hq_leg->get_leg_time();
    }

    SuitLeg* leg = new SuitLeg(start_time, zone_id,
                               landmark_building_index,
                               point_a, point_b, type,
                               m_suit_walk_speed);
    m_legs.push_back(leg);

    if (point_b->get_point_type() == DNASuitPoint::COGHQ_IN_POINT && type == SuitLeg::T_walk)
    {
        m_legs.push_back(new SuitLeg(start_time + leg->get_leg_time(), zone_id,
                                     point_b->get_landmark_building_index(),
                                     point_a, point_b,
                                     SuitLeg::T_to_cog_HQ,
                                     m_suit_walk_speed));
    }
}
