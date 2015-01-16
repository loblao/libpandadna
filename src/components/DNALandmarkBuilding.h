#pragma once
#include "DNANode.h"

class EXPCL_DNA DNALandmarkBuilding : public DNANode
{
    PUBLISHED:
        DNALandmarkBuilding(const std::string& name);
        ~DNALandmarkBuilding();

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
    protected:
        void setup_suit_building_origin(NodePath& a, NodePath& b);
        std::string m_code;
        LVecBase4f m_wall_color;
        
    // Type handle
    public:
        static TypeHandle get_class_type()
        {
            return _type_handle;
        }
        
        static void init_type()
        {
            DNANode::init_type();
            register_type(_type_handle, "DNALandmarkBuilding", DNANode::get_class_type());
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
