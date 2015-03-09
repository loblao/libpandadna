#pragma once
#include "DNANode.h"

class EXPCL_DNA DNASignBaseline : public DNANode
{
    PUBLISHED:
        DNASignBaseline(const std::string& name);
        ~DNASignBaseline();

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
    PROPERTY_STRING(text);
    PROPERTY_STRING(code);
    PROPERTY_STRING(flags);
    PROPERTY(LVecBase4, color);
    PROPERTY(float, indent);
    PROPERTY(float, kern);
    PROPERTY(float, wiggle);
    PROPERTY(float, stumble);
    PROPERTY(float, stomp);
    PROPERTY(float, width);
    PROPERTY(float, height);
        
    TYPE_HANDLE(DNASignBaseline, DNANode);
};
