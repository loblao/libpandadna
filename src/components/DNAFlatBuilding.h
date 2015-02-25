#pragma once
#include "DNANode.h"

class EXPCL_DNA DNAFlatBuilding : public DNANode
{
    PUBLISHED:
        DNAFlatBuilding(const std::string& name);
        ~DNAFlatBuilding();

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
        static int current_wall_height;
    
    protected:
        void setup_flat(NodePath& np, DNAStorage* store, const char chr,
                        const std::string& wall_code);
        void setup_suit_flat_building(NodePath& np, DNAStorage* store);
        void setup_cogdo_flat_building(NodePath& np, DNAStorage* store);
        float m_width;
        bool m_has_door;
        
    // Type handle
    public:
        static TypeHandle get_class_type()
        {
            return _type_handle;
        }
        
        static void init_type()
        {
            DNANode::init_type();
            register_type(_type_handle, "DNAFlatBuilding", DNANode::get_class_type());
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
