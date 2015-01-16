#pragma once

#include "DNASuitPoint.h"

#include <typedObject.h>

class EXPCL_DNA DNASuitEdge : public TypedObject
{
    PUBLISHED:
        DNASuitEdge(DNASuitPoint* start_point, DNASuitPoint* end_point, zone_id_t zone_id);
        ~DNASuitEdge();
        
        void set_start_point(DNASuitPoint* point);
        DNASuitPoint* get_start_point();
        
        void set_end_point(DNASuitPoint* point);
        DNASuitPoint* get_end_point();
        
        void set_zone_id(zone_id_t zone_id);
        zone_id_t get_zone_id();
        
    protected:
        DNASuitPoint* m_start_point;
        DNASuitPoint* m_end_point;
        zone_id_t m_zone_id;
        
    // Type handle
    public:
        static TypeHandle get_class_type()
        {
            return _type_handle;
        }
        
        static void init_type()
        {
            TypedObject::init_type();
            register_type(_type_handle, "DNASuitEdge", TypedObject::get_class_type());
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
