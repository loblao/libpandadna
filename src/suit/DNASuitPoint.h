#pragma once

#include "dnabase.h"

#include <luse.h>
#include <typedObject.h>

class EXPCL_DNA DNASuitPoint : public TypedObject
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

        void set_index(point_index_t index);
        point_index_t get_index();
        
        void set_point_type(PointType point_type);
        void set_point_type(const std::string& point_type);
        PointType get_point_type();
        
        void set_pos(const LPoint3f pos);
        const LPoint3f get_pos();
        
        void set_landmark_building_index(block_number_t landmark_building_index);
        block_number_t get_landmark_building_index();
        
    protected:
        point_index_t m_index;
        PointType m_point_type;
        LPoint3f m_pos;
        short m_landmark_building_index;
        
    // Type handle
    public:
        static TypeHandle get_class_type()
        {
            return _type_handle;
        }
        
        static void init_type()
        {
            TypedObject::init_type();
            register_type(_type_handle, "DNASuitPoint", TypedObject::get_class_type());
        }
        
        virtual TypeHandle get_type() const
        {
            return get_class_type();
        }
        
        virtual TypeHandle force_init_type()
        {
            init_type();
            return get_class_type();
        }

    private:
        static TypeHandle _type_handle;
};
