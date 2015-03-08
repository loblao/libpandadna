#pragma once
#include "DNAAnimProp.h"

class EXPCL_DNA DNAInteractiveProp : public DNAAnimProp
{
    PUBLISHED:
        DNAInteractiveProp(const std::string& name);
        ~DNAInteractiveProp();
        
    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
    PROPERTY(short, cell_id);
    
    TYPE_HANDLE(DNAInteractiveProp, DNAAnimProp);
};
