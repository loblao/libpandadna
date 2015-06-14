#ifndef _H_DNA_FLATDOOR_
#define _H_DNA_FLATDOOR_

#include "DNADoor.h"

class EXPCL_DNA DNAFlatDoor : public DNADoor
{
    PUBLISHED:
        DNAFlatDoor(const std::string& name);
        ~DNAFlatDoor();
        
        COMP_CODE(COMPCODE_FLAT_DOOR);
        COMP_NAME(flat_door);

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
    TYPE_HANDLE(DNAFlatDoor, DNADoor);
};

#endif
