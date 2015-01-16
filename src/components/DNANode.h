#pragma once

#include "DNAGroup.h"
#include "DNAStorage.h"

class EXPCL_DNA DNANode : public DNAGroup
{
    PUBLISHED:
        DNANode(const std::string& name);
        ~DNANode();
        
        const LVecBase3f get_pos();
        const LVecBase3f get_hpr();
        const LVecBase3f get_scale();

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
    protected:
        LVecBase3f m_pos;
        LVecBase3f m_hpr;
        LVecBase3f m_scale;

     // Type handle
    public:
        static TypeHandle get_class_type()
        {
            return _type_handle;
        }
        
        static void init_type()
        {
            DNAGroup::init_type();
            register_type(_type_handle, "DNANode", DNAGroup::get_class_type());
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
