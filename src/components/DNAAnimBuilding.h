#pragma once
#include "DNALandmarkBuilding.h"

class EXPCL_DNA DNAAnimBuilding : public DNALandmarkBuilding
{
    PUBLISHED:
        DNAAnimBuilding(const std::string& name);
        ~DNAAnimBuilding();

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
    PROPERTY_STRING(anim_name);
        
    TYPE_HANDLE(DNAAnimBuilding, DNALandmarkBuilding);
};
