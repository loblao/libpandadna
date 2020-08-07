#include "DNASignText.h"
#include "DNASignBaseline.h"

#include "nodePathCollection.h"
#include "decalEffect.h"
#include "textNode.h"

TypeHandle DNASignText::_type_handle;

DNASignText::DNASignText(const std::string& name): DNANode(name),
                                                   m_color(LVecBase4f(1)),
                                                   m_color_unset(true)
{
}

DNASignText::~DNASignText()
{
}

void DNASignText::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
    DNANode::make_from_dgi(dgi, store);
    m_letters = dgi.get_string();
    m_code = dgi.get_string();
    dgi_extract_color(dgi, m_color);
}

void DNASignText::traverse(NodePath& np, DNAStorage* store)
{
    NodePath parent_node = np;
    while (!parent_node.node()->is_geom_node())
    {
        parent_node = parent_node.get_parent();
    }

    parent_node.set_effect(DecalEffect::make());

    PT(DNASignBaseline) parent_group = DCAST(DNASignBaseline, m_parent);
    if (!m_code.size())
    {
        m_code = parent_group->get_code();
    }

    if (m_code.size())
    {
        PT(TextFont) font = store->find_font(m_code);
        if (font == nullptr)
        {
            raise_code_not_found(m_code.c_str());
            return;
        }

        if (m_color_unset)
        {
            set_color(parent_group->get_color());
            m_color_unset = true;
        }

        std::string text = m_letters;
        if (parent_group->get_width() < 0.0 || parent_group->get_height() < 0.0)
            std::reverse(text.begin(), text.end());

        PT(TextNode) textnode;
        for (int i = 0; i < text.size(); i++)
        {
			textnode = new TextNode("text");
            textnode->set_text_color(m_color);
            textnode->set_font(font);

            if (parent_group->get_flags().find("d") != std::string::npos)
            {
                textnode->set_shadow_color(m_color[0] * 0.3, m_color[1] * 0.3, m_color[2] * 0.3, m_color[3] * 0.7);
                textnode->set_shadow(0.03, 0.03);
            }

            textnode->set_text(std::string(1, text[i]));

            LVecBase3f pos(0, 0, 0);
            LVecBase3f hpr(0, 0, 0);
            LVecBase3f scale(1, 1, 1);

            bool is_first_letter = false;
            if (parent_group->get_flags().find("b") != std::string::npos)
            {
                is_first_letter = parent_group->is_first_letter_of_word(text[i]);
            }
            if (is_first_letter)
            {
                scale[0] *= 1.5;
                scale[2] *= 1.5;
            }

            LVecBase3f frame(textnode->get_width(), 0, textnode->get_height());
            parent_group->baseline_next_pos_hpr_scale(pos, hpr, scale, frame);
            NodePath letter_np = np.attach_new_node(textnode->generate());
            letter_np.set_pos_hpr_scale(np, pos, hpr, scale);
            letter_np.set_color_off(0);
            letter_np.set_color(m_color, 0);
        }
    }
}
