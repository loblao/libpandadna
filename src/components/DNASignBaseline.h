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
        
    // N.B. Do not use PROPERTY here, we don't want setter/getter for m_data
    protected:
        std::string m_data;
        
    TYPE_HANDLE(DNASignBaseline, DNANode);
};
