#ifndef _H_DNA_SUITPOINT_
#define _H_DNA_SUITPOINT_

#include "dnabase.h"

#include "luse.h"
#include "typedReferenceCount.h"

class EXPCL_DNA DNASuitPoint : public TypedReferenceCount
{
    PUBLISHED:
        enum PointType
        {
            STREET_POINT,
            FRONT_DOOR_POINT,
            SIDE_DOOR_POINT,
            COGHQ_IN_POINT,
            COGHQ_OUT_POINT
        };

        DNASuitPoint(point_index_t index, PointType point_type, LPoint3f pos,
                     block_number_t landmark_building_index=-1);
        ~DNASuitPoint();

        void set_point_type(const std::string& point_type);

    PROPERTY(point_index_t, index);
    PROPERTY(PointType, point_type);
    PROPERTY(LPoint3f, pos);
    PROPERTY(block_number_t, landmark_building_index);

    TYPE_HANDLE(DNASuitPoint, TypedReferenceCount);
};

#endif
