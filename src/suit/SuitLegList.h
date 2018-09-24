#ifndef _H_DNA_SUITLEGLIST_
#define _H_DNA_SUITLEGLIST_

#include "DNASuitPoint.h"
#include "DNASuitPath.h"
#include "DNAStorage.h"
#include "SuitLeg.h"

typedef std::vector<SuitLeg*> leg_vec_t;

class EXPCL_DNA SuitLegList
{
    PUBLISHED:
        SuitLegList(PT(DNASuitPath) path, DNAStorage* store, double suit_walk_speed = 4.8,
                       double from_sky = 6.5, double to_sky = 6.5, double from_suit_building = 2.0,
                       double to_suit_building = 2.5, double to_toon_building = 2.5);
        ~SuitLegList();

        SuitLeg::LegType get_suit_leg_type(DNASuitPoint::PointType a,
                                           DNASuitPoint::PointType b);
        int get_num_legs();
        SuitLeg* get_leg(int index);
        SuitLeg::LegType get_type(int index);
        double get_leg_time(int index);
        zone_id_t get_zone_id(int index);
        block_number_t get_block_number(int index);
        PT(DNASuitPoint) get_point_a(int index);
        PT(DNASuitPoint) get_point_b(int index);
        double get_start_time(int index);
        int get_leg_index_at_time(double time, int start_leg);
        bool is_point_in_range(PT(DNASuitPoint) point, double low_time, double high_time);
        SuitLeg::LegType get_next_leg_type(int index);
        SuitLeg* __getitem__(int index);

    private:
        void add_leg(PT(DNASuitPoint) point_a, PT(DNASuitPoint) point_b,
                     SuitLeg::LegType type, block_number_t landmark_building_index);
        leg_vec_t m_legs;
        PT(DNASuitPath) m_path;
        DNAStorage* m_store;
        double m_suit_walk_speed;

        struct {
            double from_sky;
            double to_sky;
            double from_suit_building;
            double to_suit_building;
            double to_toon_building;
        } m_leg_times;
};

#endif
