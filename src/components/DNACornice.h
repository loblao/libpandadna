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
        
    protected:
        std::string m_code;
        LVecBase4f m_color;
        
    // Type handle
    public:
        static TypeHandle get_class_type()
        {
            return _type_handle;
        }
        
        static void init_type()
        {
            DNAGroup::init_type();
            register_type(_type_handle, "DNACornice", DNAGroup::get_class_type());
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
