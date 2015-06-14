#ifndef _H_DNA_SUITLEG_
#define _H_DNA_SUITLEG_

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
        
        double get_leg_time();
        LPoint3f get_pos_at_time(double time);
        
        LPoint3f get_pos_a();
        LPoint3f get_pos_b();

        // Aliases
        INLINE void set_type(LegType type)
        {
            set_leg_type(type);
        }

        INLINE LegType get_type()
        {
            return get_leg_type();
        }
        
        static const std::string get_type_name(LegType leg_type);
      
    protected:
        double m_leg_time;
        
    PROPERTY(double, start_time);
    PROPERTY(zone_id_t, zone_id);
    PROPERTY(block_number_t, block_number);
    PROPERTY(DNASuitPoint*, point_a);
    PROPERTY(DNASuitPoint*, point_b);
    PROPERTY(LegType, leg_type);
};

#endif
