#ifndef _H_DNA_PROP_
#define _H_DNA_PROP_

#include "DNANode.h"

class EXPCL_DNA DNAProp : public DNANode
{
    PUBLISHED:
        DNAProp(const std::string& name);
        ~DNAProp();
        
        WRITE_PDNA
        {
            DNANode::write_pdna(dg, false);
            
            dg.add_string(m_code);
            PACK_COLOR;
            
            if (recursive)
                pack_children_pdna(dg);
        }
        
        WRITE_DNA
        {
            DNANode::write_dna(out, false, indent);
            indent += 1;
            
            if (m_color != LVecBase4f(1, 1, 1, 1))
                INDENTED_OUT << "color [ " << m_color.get_x() << " "
                             << m_color.get_y() << " " << m_color.get_z()
                             << " " << m_color.get_w() << " ]" << std::endl;
                             
            if (m_code.size())
                INDENTED_OUT << "code [ \"" << m_code << "\" ]" << std::endl;
            
            if (recursive)
                pack_children_dna(out, indent - 1);
        }
        
        COMP_CODE(COMPCODE_PROP);
        COMP_NAME(prop);
        
    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
    protected:
        virtual void raise_code_not_found();
    
    PROPERTY(LVecBase4f, color);
    PROPERTY_STRING(code);
        
    TYPE_HANDLE(DNAProp, DNANode);
};

#endif
