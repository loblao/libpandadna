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
        
    PROPERTY(LVecBase4f, wall_color);
    PROPERTY_STRING(code);
    
    TYPE_HANDLE(DNALandmarkBuilding, DNANode);
};
