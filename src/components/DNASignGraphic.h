#pragma once
#include "DNAProp.h"

class EXPCL_DNA DNASignGraphic : public DNAProp
{
    PUBLISHED:
        DNASignGraphic(const std::string& name);
        ~DNASignGraphic();

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
    PROPERTY(float, width);
    PROPERTY(float, height);
    
    TYPE_HANDLE(DNASignGraphic, DNAProp);
};
