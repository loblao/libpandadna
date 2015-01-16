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
        std::string m_code;
        std::string m_street_texture;
        std::string m_sidewalk_texture;
        std::string m_curb_texture;
        LVecBase4f m_street_color;
        LVecBase4f m_sidewalk_color;
        LVecBase4f m_curb_color;
        
    // Type handle
    public:
        static TypeHandle get_class_type()
        {
            return _type_handle;
        }
        
        static void init_type()
        {
            DNANode::init_type();
            register_type(_type_handle, "DNAStreet", DNANode::get_class_type());
        }
        
        virtual TypeHandle get_type() const
        {
            return get_class_type();
        }
        
        virtual TypeHandle force_init_type()
        {
            init_type();
            return get_class_type();
        }

    private:
        static TypeHandle _type_handle;
};
