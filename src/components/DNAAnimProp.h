#ifndef _H_DNA_ANIMPROP_
#define _H_DNA_ANIMPROP_

#include "DNAProp.h"

class EXPCL_DNA DNAAnimProp : public DNAProp
{
    PUBLISHED:
        DNAAnimProp(const std::string& name);
        ~DNAAnimProp();
        
        WRITE_PDNA
        {
            DNAProp::write_pdna(dg, false);
            
            dg.add_string(m_anim_name);
            
            if (recursive)
                pack_children_pdna(dg);
        }
        
        WRITE_DNA
        {
            DNAProp::write_dna(out, false, indent);
            indent += 1;
            
            if (m_anim_name.size())
                INDENTED_OUT << "anim [ \"" << m_anim_name << "\" ]" << std::endl;
            
            if (recursive)
                pack_children_dna(out, indent - 1);
        }
        
        COMP_CODE(COMPCODE_ANIM_PROP);
        COMP_NAME(anim_prop);

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
    PROPERTY_STRING(anim_name);
        
    TYPE_HANDLE(DNAAnimProp, DNAProp);
};

#endif
