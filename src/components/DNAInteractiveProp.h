#ifndef _H_DNA_INTERACTIVEPROP_
#define _H_DNA_INTERACTIVEPROP_

#include "DNAAnimProp.h"

class EXPCL_DNA DNAInteractiveProp : public DNAAnimProp
{
    PUBLISHED:
        DNAInteractiveProp(const std::string& name);
        ~DNAInteractiveProp();
        
        WRITE_PDNA
        {
            DNAAnimProp::write_pdna(dg, false);

            dg.add_int16(m_cell_id);
            
            if (recursive)
                pack_children_pdna(dg);
        }
        
        WRITE_DNA
        {
            DNAAnimProp::write_dna(out, false, indent);
            indent += 1;
            
            if (m_cell_id != -1)
                INDENTED_OUT << "cell_id [ " << m_cell_id << " ]" << std::endl;
            
            if (recursive)
                pack_children_dna(out, indent - 1);
        }
        
        COMP_CODE(COMPCODE_INTERACTIVE_PROP);
        COMP_NAME(interactive_prop);
        
    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
    PROPERTY(short, cell_id);
    
    TYPE_HANDLE(DNAInteractiveProp, DNAAnimProp);
};

#endif
