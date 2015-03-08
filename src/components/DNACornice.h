#pragma once
#include "DNAGroup.h"

class EXPCL_DNA DNACornice : public DNAGroup
{
    PUBLISHED:
        DNACornice(const std::string& name);
        ~DNACornice();

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
    PROPERTY(LVecBase4f, color);
    PROPERTY_STRING(code);
        
    TYPE_HANDLE(DNACornice, DNAGroup);
};
