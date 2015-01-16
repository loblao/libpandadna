#pragma once
#include "DNADoor.h"

class EXPCL_DNA DNAFlatDoor : public DNADoor
{
    PUBLISHED:
        DNAFlatDoor(const std::string& name);
        ~DNAFlatDoor();

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
            DNADoor::init_type();
            register_type(_type_handle, "DNAFlatDoor", DNADoor::get_class_type());
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
