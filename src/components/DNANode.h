#pragma once

#include "DNAGroup.h"
#include "DNAStorage.h"

class EXPCL_DNA DNANode : public DNAGroup
{
    PUBLISHED:
        DNANode(const std::string& name);
        ~DNANode();
        
    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
    PROPERTY(LVecBase3f, pos);
    PROPERTY(LVecBase3f, hpr);
    PROPERTY(LVecBase3f, scale);
    
    TYPE_HANDLE(DNANode, DNAGroup);
};
