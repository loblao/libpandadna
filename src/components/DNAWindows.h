#ifndef _H_DNA_WINDOWS_
#define _H_DNA_WINDOWS_

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
                          
        WRITE_PDNA
        {
            DNAGroup::write_pdna(dg, false);            
            dg.add_string(m_code);
            PACK_COLOR;
            dg.add_uint8(m_window_count);
        }
        
        WRITE_DNA
        {
            DNAGroup::write_dna(out, false, indent);
            indent += 1;
            
            if (m_color != LVecBase4f(1, 1, 1, 1))
                INDENTED_OUT << "color [ " << m_color.get_x() << " "
                             << m_color.get_y() << " " << m_color.get_z()
                             << " " << m_color.get_w() << " ]" << std::endl;
                             
            if (m_code.size())
                INDENTED_OUT << "code [ \"" << m_code << "\" ]" << std::endl;
            
            if (m_window_count != 1)
                INDENTED_OUT << "count [ " << (int)m_window_count << " ]" << std::endl;
            
            indent -= 1;
            INDENTED_OUT << "]" << std::endl;
        }
        
        COMP_CODE(COMPCODE_WINDOWS);
        COMP_NAME(windows);

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
    PROPERTY(LVecBase4f, color);
    PROPERTY(unsigned char, window_count);
    PROPERTY_STRING(code);
        
    TYPE_HANDLE(DNAWindows, DNAGroup);
};

#endif
