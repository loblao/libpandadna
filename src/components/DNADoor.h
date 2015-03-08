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
        
    PROPERTY(LVecBase4f, color);
    PROPERTY_STRING(code);
    
    TYPE_HANDLE(DNADoor, DNAGroup);
};
