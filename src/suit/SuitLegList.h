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
        SuitLegList(DNASuitPath* path, DNAStorage* store, double suit_walk_speed=4.8);
        ~SuitLegList();
        
        SuitLeg::LegType get_suit_leg_type(DNASuitPoint::PointType a,
                                           DNASuitPoint::PointType b);
        size_t get_num_legs();
        SuitLeg* get_leg(size_t index);
        SuitLeg::LegType get_type(size_t index);
        double get_leg_time(size_t index);
        zone_id_t get_zone_id(size_t index);
        block_number_t get_block_number(size_t index);
        DNASuitPoint* get_point_a(size_t index);
        DNASuitPoint* get_point_b(size_t index);
        double get_start_time(size_t index);
        size_t get_leg_index_at_time(double time, size_t start_leg);
        bool is_point_in_range(DNASuitPoint* point, double low_time, double high_time);
        SuitLeg::LegType get_next_leg_type(size_t index);
        
    private:
        void add_leg(DNASuitPoint* point_a, DNASuitPoint* point_b,
                     SuitLeg::LegType type, block_number_t landmark_building_index);
        leg_vec_t m_legs;
        DNASuitPath* m_path;
        DNAStorage* m_store;
        double m_suit_walk_speed;
};

#endif
