#pragma once

#include "DNAGroup.h"

class EXPCL_DNA DNADoor : public DNAGroup
{
    PUBLISHED:
        DNADoor(const std::string& name);
        ~DNADoor();
        
        static void DNADoor::setup_door(NodePath& door_np, NodePath& parent_np, NodePath& door_origin,
                                        DNAStorage* store, block_number_t block, LVecBase4f& color);

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
    protected:
        std::string m_code;
        LVecBase4f m_color;
        
    // Type handle
    public:
        static TypeHandle get_class_type()
        {
            return _type_handle;
        }
        
        static void init_type()
        {
            DNAGroup::init_type();
            register_type(_type_handle, "DNADoor", DNAGroup::get_class_type());
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
