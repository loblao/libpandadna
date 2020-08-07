#ifndef _H_DNA_SIGNTEXT_
#define _H_DNA_SIGNTEXT_

#include "DNANode.h"

class EXPCL_DNA DNASignText : public DNANode
{
    PUBLISHED:
        DNASignText(const std::string& name);
        ~DNASignText();

        WRITE_PDNA
        {
            DNANode::write_pdna(dg, false);

            dg.add_string(m_letters);
            dg.add_string(m_code);
            PACK_COLOR;

            if (recursive)
                pack_children_pdna(dg);
        }

        WRITE_DNA
        {
            DNANode::write_dna(out, false, indent);
            indent += 1;

            if (m_code.size())
                INDENTED_OUT << "code [ \"" << m_code << "\" ]" << std::endl;

            for (size_t i = 0; i < m_letters.size(); ++i)
                INDENTED_OUT << "text [ letters [ \"" << m_letters.at(i) << "\" ] ]" << std::endl;

            if (m_color != LVecBase4f(1, 1, 1, 1))
                INDENTED_OUT << "color [ " << m_color.get_x() << " "
                             << m_color.get_y() << " " << m_color.get_z()
                             << " " << m_color.get_w() << " ]" << std::endl;

            if (recursive)
                pack_children_dna(out, indent - 1);
        }

        COMP_CODE(COMPCODE_SIGN_TEXT);
        COMP_NAME(text);

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);

        std::string m_letters;

    private:
        bool m_color_unset;

    PROPERTY_STRING(code);
    PROPERTY(LVecBase4, color);

    TYPE_HANDLE(DNASignText, DNANode);
};

#endif
