#ifndef _H_DNA_SUITLEG_
#define _H_DNA_SUITLEG_

#include "DNASuitPoint.h"

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
            T_from_coghq,
            T_to_coghq,
            T_off
        };

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

    public:
        SuitLeg(double start_time, zone_id_t zone_id, block_number_t block_number,
                PT(DNASuitPoint) point_a, PT(DNASuitPoint) point_b, LegType leg_type,
                double leg_time);

    protected:
        double m_leg_time;

    PROPERTY(double, start_time);
    PROPERTY(zone_id_t, zone_id);
    PROPERTY(block_number_t, block_number);
    PROPERTY(PT(DNASuitPoint), point_a);
    PROPERTY(PT(DNASuitPoint), point_b);
    PROPERTY(LegType, leg_type);
};

#endif
