#pragma once
#include "DNAProp.h"

class EXPCL_DNA DNASign : public DNAProp
{
    PUBLISHED:
        DNASign(const std::string& name);
        ~DNASign();

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
    
    TYPE_HANDLE(DNASign, DNAProp);
};
