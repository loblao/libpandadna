#ifndef _H_DNA_SIGNBASELINE_
#define _H_DNA_SIGNBASELINE_

#include "DNANode.h"

#define DUMP_IF_NOT_NULL(X) if (m_##X) INDENTED_OUT << #X " [ " << m_##X << " ]" << std::endl;

class EXPCL_DNA DNASignBaseline : public DNANode
{
    PUBLISHED:
        DNASignBaseline(const std::string& name);
        ~DNASignBaseline();

        WRITE_PDNA
        {
            DNANode::write_pdna(dg, false);

            dg.add_string(m_text);
            dg.add_string(m_code);
            PACK_COLOR;
            dg.add_string(m_flags);
            dg.add_float32(m_indent);
            dg.add_float32(m_kern);
            dg.add_float32(m_wiggle);
            dg.add_float32(m_stumble);
            dg.add_float32(m_stomp);
            dg.add_float32(m_width);
            dg.add_float32(m_height);

            if (recursive)
                pack_children_pdna(dg);
        }

        WRITE_DNA
        {
            DNANode::write_dna(out, false, indent);
            indent += 1;

            if (m_code.size())
                INDENTED_OUT << "code [ \"" << m_code << "\" ]" << std::endl;

            if (m_flags.size())
                INDENTED_OUT << "flags [ \"" << m_flags << "\" ]" << std::endl;

            DUMP_IF_NOT_NULL(indent);
            DUMP_IF_NOT_NULL(kern);
            DUMP_IF_NOT_NULL(wiggle);
            DUMP_IF_NOT_NULL(stumble);
            DUMP_IF_NOT_NULL(stomp);
            DUMP_IF_NOT_NULL(width);
            DUMP_IF_NOT_NULL(height);

            for (size_t i = 0; i < m_text.size(); ++i)
                INDENTED_OUT << "text [ letters [ \"" << m_text.at(i) << "\" ] ]" << std::endl;

            if (m_color != LVecBase4f(1, 1, 1, 1))
                INDENTED_OUT << "color [ " << m_color.get_x() << " "
                             << m_color.get_y() << " " << m_color.get_z()
                             << " " << m_color.get_w() << " ]" << std::endl;

            if (recursive)
                pack_children_dna(out, indent - 1);
        }

        COMP_CODE(COMPCODE_SIGN_BASELINE);
        COMP_NAME(baseline);

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);

        std::string m_text;

    private:
        bool is_first_letter_of_word(const char c);
        void line_next_pos_hpr_scale(LVecBase3f& pos, LVecBase3f& hpr, LVecBase3f& scale, LVecBase3f& frame);
        void circle_next_pos_hpr_scale(LVecBase3f& pos, LVecBase3f& hpr, LVecBase3f& scale, LVecBase3f& frame);
        void center(LVecBase3f& pos, LVecBase3f& hpr);
        void reset();

        INLINE void baseline_next_pos_hpr_scale(LVecBase3f& pos, LVecBase3f& hpr, LVecBase3f& scale, LVecBase3f& frame)
        {
            if (0.0 != m_width || 0.0 != m_height)
                circle_next_pos_hpr_scale(pos, hpr, scale, frame);
            else
                line_next_pos_hpr_scale(pos, hpr, scale, frame);
        }

        LVecBase3f m_curr_pos;
        float m_field_252;
        float m_angle;
        bool m_is_space;
        int m_counter;

    PROPERTY_STRING(code);
    PROPERTY_STRING(flags);
    PROPERTY(LVecBase4, color);
    PROPERTY(float, indent);
    PROPERTY(float, kern);
    PROPERTY(float, wiggle);
    PROPERTY(float, stumble);
    PROPERTY(float, stomp);
    PROPERTY(float, width);
    PROPERTY(float, height);

    TYPE_HANDLE(DNASignBaseline, DNANode);
};

#endif
