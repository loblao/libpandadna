#pragma once

#include "DNASuitPoint.h"

#include <typedObject.h>
#include <vector>

typedef std::vector<DNASuitPoint*> suit_point_vec_t;

class EXPCL_DNA DNASuitPath : public TypedObject
{
    PUBLISHED:
        DNASuitPath();
        ~DNASuitPath();
        
        void add_point(DNASuitPoint* point);
        DNASuitPoint* get_point(size_t index);
        size_t get_num_points();
        point_index_t get_point_index(size_t index);
        void reverse_path();
        
    protected:
        suit_point_vec_t m_suit_points;
        
    // Type handle
    public:
        static TypeHandle get_class_type()
        {
            return _type_handle;
        }
        
        static void init_type()
        {
            TypedObject::init_type();
            register_type(_type_handle, "DNASuitPath", TypedObject::get_class_type());
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
