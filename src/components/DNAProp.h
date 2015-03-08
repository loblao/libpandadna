#pragma once
#include "DNANode.h"

class EXPCL_DNA DNAProp : public DNANode
{
    PUBLISHED:
        DNAProp(const std::string& name);
        ~DNAProp();

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
    protected:
        virtual void raise_code_not_found();
    
    PROPERTY(LVecBase4f, color);
    PROPERTY_STRING(code);
        
    TYPE_HANDLE(DNAProp, DNANode);
};
