#pragma once
#include "DNAAnimProp.h"

class EXPCL_DNA DNAInteractiveProp : public DNAAnimProp
{
    PUBLISHED:
        DNAInteractiveProp(const std::string& name);
        ~DNAInteractiveProp();
        
       short get_cell_id();

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
    protected:
        short m_cell_id;
    
    // Type handle
    public:
        static TypeHandle get_class_type()
        {
            return _type_handle;
        }
        
        static void init_type()
        {
            DNAAnimProp::init_type();
            register_type(_type_handle, "DNAInteractiveProp", DNAAnimProp::get_class_type());
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
