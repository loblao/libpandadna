#include "SuitLegList.h"

SuitLegList::SuitLegList(DNASuitPath* path, DNAStorage* store, double suit_walk_speed): m_path(path),
                         m_store(store), m_suit_walk_speed(suit_walk_speed)
{
    // Create first leg
    DNASuitPoint* start_point = path->get_point(0);
    DNASuitPoint* heading_point = path->get_point(1);
    add_leg(start_point, heading_point,
            start_point->get_point_type() == DNASuitPoint::SIDE_DOOR_POINT
            ? SuitLeg::T_from_suit_building : SuitLeg::T_from_sky, -1);

    // Create mid legs
    for (size_t i = 1; i < path->get_num_points(); i++)
    {
        DNASuitPoint* point_a = path->get_point(i - 1);
        DNASuitPoint* point_b = path->get_point(i);
        block_number_t landmark_building_index = point_a->get_landmark_building_index();
        if (landmark_building_index == -1)
            landmark_building_index = point_b->get_landmark_building_index();
        
        add_leg(point_a, point_b, get_next_leg_type(i - 1), landmark_building_index);
    }

    // Create last leg
    DNASuitPoint* end_point;
    
    size_t end_index = path->get_num_points() - 1;
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

size_t SuitLegList::get_num_legs()
{
    return m_legs.size();
}

SuitLeg* SuitLegList::get_leg(size_t index)
{
    nassertd(index < get_num_legs())
    {
    }
    return m_legs.at(index);
}

SuitLeg::LegType SuitLegList::get_type(size_t index)
{
    return get_leg(index)->get_type();
}

double SuitLegList::get_leg_time(size_t index)
{
    return get_leg(index)->get_leg_time();
}

zone_id_t SuitLegList::get_zone_id(size_t index)
{
    return get_leg(index)->get_zone_id();
}

block_number_t SuitLegList::get_block_number(size_t index)
{
    return get_leg(index)->get_block_number();
}

DNASuitPoint* SuitLegList::get_point_a(size_t index)
{
    return get_leg(index)->get_point_a();
}

DNASuitPoint* SuitLegList::get_point_b(size_t index)
{
    return get_leg(index)->get_point_b();
}

double SuitLegList::get_start_time(size_t index)
{
    if (index < get_num_legs())
        return get_leg(index)->get_start_time();
        
    double start_time = 0;
    for (size_t i = 0; i < get_num_legs(); i++)
    {
        if (i == index)
            break;
            
        start_time += get_leg_time(i);
    }
    
    return start_time;
}

size_t SuitLegList::get_leg_index_at_time(double time, size_t start_leg)
{
    (void*)start_leg; // TO DO: Figure out how to use start_leg
    double end_time = 0;
    size_t i;
    for (i = 0; i < get_num_legs(); i++)
    {
        end_time += get_leg_time(i);
        if (end_time > time)
            break;
    }
    
    return i;
}

bool SuitLegList::is_point_in_range(DNASuitPoint* point, double low_time, double high_time)
{
    point_index_t point_index = point->get_index();
    size_t start_leg_index = get_leg_index_at_time(low_time, 0);
    size_t end_leg_index = get_leg_index_at_time(high_time, point_index);
    
    for (size_t i = start_leg_index; i <= end_leg_index; i++)
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

SuitLeg::LegType SuitLegList::get_next_leg_type(size_t index)
{
    return get_suit_leg_type(m_path->get_point(index)->get_point_type(),
                             m_path->get_point(index + 1)->get_point_type());
}

void SuitLegList::add_leg(DNASuitPoint* point_a, DNASuitPoint* point_b,
                          SuitLeg::LegType type, block_number_t landmark_building_index)
{
    zone_id_t zone_id = m_store->get_suit_edge_zone(point_a->get_index(),
                                                    point_b->get_index());
    double start_time = get_start_time(get_num_legs());
    m_legs.push_back(new SuitLeg(start_time, zone_id,
                                 landmark_building_index,
                                 point_a, point_b, type,
                                 m_suit_walk_speed));

    // Handle Cog HQ legs
    start_time = get_start_time(get_num_legs());

    if (point_a->get_point_type() == DNASuitPoint::COGHQ_OUT_POINT)
    {
        landmark_building_index = point_a->get_landmark_building_index();
        m_legs.insert(m_legs.end() - 1, new SuitLeg(start_time, zone_id,
                                                    landmark_building_index,
                                                    point_a, point_b,
                                                    SuitLeg::T_from_cog_HQ,
                                                    m_suit_walk_speed));
    }

    else if (point_b->get_point_type() == DNASuitPoint::COGHQ_IN_POINT)
    {
        block_number_t landmark_building_index = point_b->get_landmark_building_index();
        if (landmark_building_index == -1)
            landmark_building_index = point_a->get_landmark_building_index();
        m_legs.push_back(new SuitLeg(start_time, zone_id,
                                     landmark_building_index,
                                     point_a, point_b,
                                     SuitLeg::T_to_cog_HQ,
                                     m_suit_walk_speed));
    }
}
