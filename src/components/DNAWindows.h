#pragma once
#include "DNAGroup.h"

class EXPCL_DNA DNAWindows : public DNAGroup
{
    PUBLISHED:
        DNAWindows(const std::string& name);
        ~DNAWindows();
        
        void make_windows(float x, float y, NodePath& parent_node,
                          const std::string& code, float scale,
                          LVecBase4f& color, DNAStorage* store,
                          bool flip=false);

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
    PROPERTY(LVecBase4f, color);
    PROPERTY(unsigned char, window_count);
    PROPERTY_STRING(code);
        
    TYPE_HANDLE(DNAWindows, DNAGroup);
};
