#pragma once
#include "DNAProp.h"

class EXPCL_DNA DNASign : public DNAProp
{
    PUBLISHED:
        DNASign(const std::string& name);
        ~DNASign();

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
    
    // Type handle
    public:
        static TypeHandle get_class_type()
        {
            return _type_handle;
        }
        
        static void init_type()
        {
            DNAProp::init_type();
            register_type(_type_handle, "DNASign", DNAProp::get_class_type());
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
