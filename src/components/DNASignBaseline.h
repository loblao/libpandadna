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
        
    protected:
        std::string m_data;
        
    // Type handle
    public:
        static TypeHandle get_class_type()
        {
            return _type_handle;
        }
        
        static void init_type()
        {
            DNANode::init_type();
            register_type(_type_handle, "DNASignBaseline", DNANode::get_class_type());
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
