#ifndef _H_DNA_STREET_
#define _H_DNA_STREET_

#include "DNANode.h"

#define DUMP_COLOR(X) INDENTED_OUT << "color [ " << X.get_x() << " " << X.get_y() << " " << X.get_z() << " " << X.get_w() << " ]" << std::endl;

class EXPCL_DNA DNAStreet : public DNANode
{
    PUBLISHED:
        DNAStreet(const std::string& name);
        ~DNAStreet();

        WRITE_PDNA
        {
            DNANode::write_pdna(dg, false);

            dg.add_string(m_code);

            dg.add_string(m_street_texture);
            dg.add_string(m_sidewalk_texture);
            dg.add_string(m_curb_texture);

            pack_color(dg, m_street_color);
            pack_color(dg, m_sidewalk_color);
            pack_color(dg, m_curb_color);
        }

        WRITE_DNA
        {
            DNANode::write_dna(out, false, indent);
            indent += 1;

            if (m_code.size())
                INDENTED_OUT << "code [ \"" << m_code << "\" ]" << std::endl;

            if (m_street_texture.size())
            {
                INDENTED_OUT << "texture [ \"" << m_street_texture << "\" ]" << std::endl;
                if (m_sidewalk_texture.size())
                {
                    INDENTED_OUT << "texture [ \"" << m_sidewalk_texture << "\" ]" << std::endl;
                    if (m_curb_texture.size())
                    {
                        INDENTED_OUT << "texture [ \"" << m_curb_texture << "\" ]" << std::endl;
                    }
                }
            }

            if (m_street_color != LVecBase4f(1, 1, 1, 1))
            {
                DUMP_COLOR(m_street_color);
                if (m_sidewalk_color != LVecBase4f(1, 1, 1, 1))
                {
                    DUMP_COLOR(m_sidewalk_color);
                    if (m_curb_color != LVecBase4f(1, 1, 1, 1))
                    {
                        DUMP_COLOR(m_curb_color);
                    }
                }
            }

            indent -= 1;
            INDENTED_OUT << "]" << std::endl;
        }

        COMP_CODE(COMPCODE_STREET);
        COMP_NAME(street);

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);

        void set_texture(const std::string& texture);
        void set_color(LVecBase4f color);

    protected:
        PT(Texture) get_texture(const std::string& texture, DNAStorage* store);

    private:
        int m_set_texture_count;
        int m_set_color_count;

    PROPERTY_STRING(code);
    PROPERTY_STRING(street_texture);
    PROPERTY_STRING(sidewalk_texture);
    PROPERTY_STRING(curb_texture);
    PROPERTY(LVecBase4f, street_color);
    PROPERTY(LVecBase4f, sidewalk_color);
    PROPERTY(LVecBase4f, curb_color);

    TYPE_HANDLE(DNAStreet, DNANode);
};

#endif
