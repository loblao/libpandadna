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
        
    TYPE_HANDLE(DNAFlatDoor, DNADoor);
};
