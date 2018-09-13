#include "DNASignBaseline.h"

#include <nodePathCollection.h>
#include <textNode.h>

#define _USE_MATH_DEFINES
#include <math.h>

TypeHandle DNASignBaseline::_type_handle;

DNASignBaseline::DNASignBaseline(const std::string& name): DNANode(name)
{
}

DNASignBaseline::~DNASignBaseline()
{
}

void DNASignBaseline::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
    DNANode::make_from_dgi(dgi, store);
    m_text = dgi.get_string();
    m_code = dgi.get_string();
    m_color = DGI_EXTRACT_COLOR;
    m_flags = dgi.get_string();
    m_indent = dgi.get_float32();
    m_kern = dgi.get_float32();
    m_wiggle = dgi.get_float32();
    m_stumble = dgi.get_float32();
    m_stomp = dgi.get_float32();
    m_width = dgi.get_float32();
    m_height = dgi.get_float32();
}

void DNASignBaseline::traverse(NodePath& np, DNAStorage* store)
{
    PT(TextNode) tn = new TextNode("text");
    NodePath root("signroot");
    float x = 0;
    for (unsigned int i = 0; i < m_text.size(); ++i)
    {
        tn->set_text(std::string(1, m_text.at(i)));
        tn->set_text_color(m_color);

        PT(TextFont) font = store->find_font(m_code);
        if (font == nullptr)
        {
            raise_code_not_found(m_code.c_str());
            return;
        }

        tn->set_font(font);

        if (i == 0 && m_flags.find('b') != std::string::npos)
            tn->set_text_scale(1.5);

        else
            tn->set_text_scale(1.0);

        NodePath np = root.attach_new_node(tn->generate());
        np.set_scale(m_scale);
        np.set_depth_write(0);
        if (i & 1)
        {
            np.set_pos(x + m_stumble, 0, m_stomp);
            np.set_r(-m_wiggle);
        }

        else
        {
            np.set_pos(x - m_stumble, 0, m_stomp);
            np.set_r(m_wiggle);
        }

        x += tn->get_width() * np.get_sx() + m_kern;
    }

    for (int i = 0; i < root.get_num_children(); ++i)
    {
        NodePath c = root.get_child(i);
        c.set_x(c.get_x() - x / 2.);
    }

    if (m_width != 0 && m_height != 0)
    {
        for (int i = 0; i < root.get_num_children(); ++i)
        {
            NodePath node = root.get_child(i);

            double A = (node.get_x() / (m_height / 2.));
            double B = (m_indent * M_PI / 180.);

            double theta = A + B;
            double d, x, y, radius;
            d = node.get_y();
            x = sin(theta) * (m_width / 2.);
            y = (cos(theta) - 1) * (m_height / 2.);
            radius = hypot(x, y);

            if (radius != 0)
            {
                double j = (radius + d) / radius;
                x *= j;
                y *= j;
            }
            node.set_pos(x, 0, y);
            node.set_r(node, theta * 180. / M_PI);
        }
    }

    NodePath _np = np.attach_new_node(root.node());
    _np.set_pos_hpr(m_pos, m_hpr);
    _np.set_depth_offset(50);

    traverse_children(_np, store);
    _np.flatten_strong();
}
