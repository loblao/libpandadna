#pragma once
#include "DNANode.h"

class EXPCL_DNA DNAStreet : public DNANode
{
    PUBLISHED:
        DNAStreet(const std::string& name);
        ~DNAStreet();

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
    protected:
        PT(Texture) get_texture(const std::string& texture, DNAStorage* store);
        
    PROPERTY_STRING(code);
    PROPERTY_STRING(street_texture);
    PROPERTY_STRING(sidewalk_texture);
    PROPERTY_STRING(curb_texture);
    PROPERTY(LVecBase4f, street_color);
    PROPERTY(LVecBase4f, sidewalk_color);
    PROPERTY(LVecBase4f, curb_color);
    
    TYPE_HANDLE(DNAStreet, DNANode);
};
