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
        
    PROPERTY(float, width);
    PROPERTY(bool, has_door);
        
    TYPE_HANDLE(DNAFlatBuilding, DNANode);
};
