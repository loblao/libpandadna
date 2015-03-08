#include "SuitLeg.h"

double SuitTimings::from_sky = 6.5;
double SuitTimings::to_sky = 6.5;
double SuitTimings::from_suit_building = 2.0;
double SuitTimings::to_suit_building = 2.5;
double SuitTimings::to_toon_building = 2.5;
    
SuitLeg::SuitLeg(double start_time, zone_id_t zone_id, block_number_t block_number,
                 DNASuitPoint* point_a, DNASuitPoint* point_b, LegType leg_type,
                 double suit_walk_speed): m_start_time(start_time), m_zone_id(zone_id),
                                          m_block_number(block_number), m_point_a(point_a),
                                          m_point_b(point_b), m_leg_type(leg_type)
{
    m_leg_time = (get_pos_b() - get_pos_a()).length() / suit_walk_speed;
}

SuitLeg::~SuitLeg()
{
}

double SuitLeg::get_leg_time()
{
    if (get_type() == SuitLeg::T_from_sky)
        return SuitTimings::from_sky;
        
    else if (get_type() == SuitLeg::T_to_sky)
        return SuitTimings::to_sky;
        
    else if (get_type() == SuitLeg::T_from_suit_building)
        return SuitTimings::from_suit_building;
        
    else if (get_type() == SuitLeg::T_to_suit_building)
        return SuitTimings::to_suit_building;
        
    else if (get_type() == SuitLeg::T_to_toon_building)
        return SuitTimings::to_toon_building;

    else if (get_type() == SuitLeg::T_to_cog_HQ || get_type() == SuitLeg::T_from_cog_HQ)
        return SuitTimings::to_toon_building;
        
    return m_leg_time;
}

LPoint3f SuitLeg::get_pos_at_time(double time)
{
    LPoint3f pos_a = get_pos_a();
    LPoint3f pos_b = get_pos_b();
    return pos_a + ((pos_b - pos_a) * (time / get_leg_time()));
}

LPoint3f SuitLeg::get_pos_a()
{
    return m_point_a->get_pos();
}

LPoint3f SuitLeg::get_pos_b()
{
    return m_point_b->get_pos();
}

const std::string SuitLeg::get_type_name(LegType leg_type)
{
    if (leg_type == SuitLeg::T_walk_from_street)
        return "WalkFromStreet";

    else if (leg_type == SuitLeg::T_walk_to_street)
        return "WalkToStreet";

    else if (leg_type == SuitLeg::T_walk)
        return "Walk";

    else if (leg_type == SuitLeg::T_from_sky)
        return "FromSky";

    else if (leg_type == SuitLeg::T_to_sky)
        return "ToSky";

    else if (leg_type == SuitLeg::T_from_suit_building)
        return "FromSuitBuilding";

    else if (leg_type == SuitLeg::T_to_suit_building)
        return "ToSuitBuilding";

    else if (leg_type == SuitLeg::T_to_toon_building)
        return "ToToonBuilding";

    else if (leg_type == SuitLeg::T_from_cog_HQ)
        return "FromCogHQ";

    else if (leg_type == SuitLeg::T_to_cog_HQ)
        return "ToCogHQ";

    else if (leg_type == SuitLeg::T_off)
        return "Off";
        
    dna_cat.error() << "invalid leg type: " << leg_type << std::endl;
    return "**invalid**";
}
