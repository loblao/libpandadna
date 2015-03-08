#pragma once
#include "DNAProp.h"

class EXPCL_DNA DNAAnimProp : public DNAProp
{
    PUBLISHED:
        DNAAnimProp(const std::string& name);
        ~DNAAnimProp();

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
    PROPERTY_STRING(anim_name);
        
    TYPE_HANDLE(DNAAnimProp, DNAProp);
};
