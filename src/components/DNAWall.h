#pragma once
#include "DNANode.h"

class EXPCL_DNA DNAWall : public DNANode
{
    PUBLISHED:
        DNAWall(const std::string& name);
        ~DNAWall();

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
    PROPERTY(LVecBase4f, color);
    PROPERTY(float, height);
    PROPERTY_STRING(code);
        
    TYPE_HANDLE(DNAWall, DNANode);
};
