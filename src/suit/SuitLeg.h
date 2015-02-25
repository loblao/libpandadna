#pragma once

#include "DNASuitPoint.h"

#ifndef CPPPARSER
class SuitTimings
{
    public:
        static double from_sky;
        static double to_sky;
        static double from_suit_building;
        static double to_suit_building;
        static double to_toon_building;
};
#endif

class EXPCL_DNA SuitLeg
{
    PUBLISHED:
        enum LegType
        {
            T_walk_from_street,
            T_walk_to_street,
            T_walk,
            T_from_sky,
            T_to_sky,
            T_from_suit_building,
            T_to_suit_building,
            T_to_toon_building,
            T_from_cog_HQ,
            T_to_cog_HQ,
            T_off
        };
        
        SuitLeg(double start_time, zone_id_t zone_id, block_number_t block_number,
                DNASuitPoint* point_a, DNASuitPoint* point_b, LegType leg_type,
                double suit_walk_speed=4.8);
        ~SuitLeg();
        
        void set_start_time(double start_time);
        double get_start_time();
        
        void set_zone_id(zone_id_t zone_id);
        zone_id_t get_zone_id();
        
        void set_block_number(block_number_t block_number);
        block_number_t get_block_number();
        
        void set_point_a(DNASuitPoint* point_a);
        DNASuitPoint* get_point_a();
        
        void set_point_b(DNASuitPoint* point_b);
        DNASuitPoint* get_point_b();
        
        void set_type(LegType leg_type);
        LegType get_type();
        
        double get_leg_time();
        LPoint3f get_pos_at_time(double time);
        
        LPoint3f get_pos_a();
        LPoint3f get_pos_b();
        
        static const std::string get_type_name(LegType leg_type);
    
    protected:
        double m_start_time;
        zone_id_t m_zone_id;
        block_number_t m_block_number;
        DNASuitPoint* m_point_a;
        DNASuitPoint* m_point_b;
        double m_leg_time;
        LegType m_leg_type;
};
