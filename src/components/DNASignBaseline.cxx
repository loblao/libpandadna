#include "DNASignBaseline.h"

#include "nodePathCollection.h"

#define _USE_MATH_DEFINES
#include <math.h>

TypeHandle DNASignBaseline::_type_handle;

DNASignBaseline::DNASignBaseline(const std::string& name): DNANode(name),
                                                           m_color(LVecBase4f(1)),
                                                           m_indent(0.0),
                                                           m_kern(0.0),
                                                           m_wiggle(0.0),
                                                           m_stumble(0.0),
                                                           m_stomp(0.0),
                                                           m_width(0.0),
                                                           m_height(0.0),
                                                           m_curr_pos(LVecBase3f(0)),
                                                           m_field_252(0.0),
                                                           m_angle(0.0),
                                                           m_is_space(false),
                                                           m_counter(0)
{
}

DNASignBaseline::~DNASignBaseline()
{
}

void DNASignBaseline::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
    DNANode::make_from_dgi(dgi, store);
    m_code = dgi.get_string();
    dgi_extract_color(dgi, m_color);
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
    reset();

    NodePath _np = np.attach_new_node("baseline");

    if (m_code.size())
    {
        PT(TextFont) font = store->find_font(m_code);
        if (font == nullptr)
        {
            raise_code_not_found(m_code.c_str());
            return;
        }
    }

    traverse_children(_np, store);

    LVecBase3f pos = m_pos;
    LVecBase3f hpr = m_hpr;
    center(pos, hpr);

    _np.set_depth_write(0);
    _np.set_pos(np, pos);
    _np.set_hpr(np, hpr);
}

void DNASignBaseline::line_next_pos_hpr_scale(LVecBase3f& pos, LVecBase3f& hpr,
                                              LVecBase3f& scale, LVecBase3f& frame)
{
    pos[0] = m_curr_pos[0] + m_counter * m_kern + m_stumble * ((m_counter & 1) ? 1 : -1);
    pos[1] = m_curr_pos[1];
    pos[2] = m_curr_pos[2] + m_stomp * ((m_counter & 1) ? 1 : -1);

    scale[0] *= m_scale[0];
    scale[1] *= m_scale[1];
    scale[2] *= m_scale[2];

    hpr[2] -= m_wiggle * ((m_counter & 1) ? 1 : -1);

    m_curr_pos[0] += scale[0] * frame[0];
    m_counter++;
}

void DNASignBaseline::circle_next_pos_hpr_scale(LVecBase3f& pos, LVecBase3f& hpr,
                                                LVecBase3f& scale, LVecBase3f& frame)
{
    // TODO: cleanup this code
    scale[0] *= m_scale[0];
    scale[1] *= m_scale[1];
    scale[2] *= m_scale[2];

    double v39 = m_width * 0.5;
    double v43 = m_height * 0.5;

    double v11 = m_width == 0.0 ? pos[0] : -pos[0];
    double v14 = v11 / v39;

    double v38 = m_width == 0.0 ? m_indent : -m_indent;
    double _posa = m_angle * M_PI / 180.0;
    double v40 = v38 * M_PI / 180.0 + v14 + _posa + M_PI / 2;

    double _scalea = m_stomp * ((m_counter & 1) ? 1 : -1) + pos[2];
    if (m_width < 0.0) _scalea *= -1;

    v39 = (_scalea + v39) * cos(v40);
    double v22 = _scalea + v43;

    pos[0] = v39;
    double _scaleb = v22 * sin(v40);
    pos[2] = _scaleb;

    double v26 = m_wiggle * ((m_counter & 1) ? 1 : -1);
    hpr[2] -= (v26 + m_angle + v38);

    double _scalec = sqrt(_scaleb * _scaleb + v39 * v39);
    if (m_width < 0.0)
        m_field_252 = _posa * 180 / M_PI;

    double _hpra = std::min(1.0, scale[0] * frame[0] / (_scalec + _scalec));
    double _posb = _posa - 2 * asin(_hpra);

    if (m_width >= 0.0)
        m_field_252 = _posb * 180 / M_PI;

    double _hprb = m_stumble * ((m_counter & 1) ? 1 : -1);

    v43 = m_angle;
    double v31 = asin((m_kern - _hprb) / (_scalec + _scalec));
    m_angle = (_posb - (v31 + v31)) * 180 / M_PI;

    if (m_width >= 0.0)
        hpr[2] += (m_angle - v43) * 0.5;

    m_counter++;
}

void DNASignBaseline::center(LVecBase3f& pos, LVecBase3f& hpr)
{
    double angle = -m_hpr[2] * M_PI / 180;
    if ( 0.0 != m_width || 0.0 != m_height )
    {
        pos[0] -= cos(angle + M_PI / 2) * m_width * 0.5;
        pos[2] -= sin(angle + M_PI / 2) * m_height * 0.5;
        hpr[2] += m_field_252 * 0.5;
    }

    else
    {
        m_counter--;
        double stumble =  m_stumble * ((m_counter & 1) ? 1 : -1);
        double scale = (stumble + m_counter * m_kern + m_curr_pos[0]) * 0.5;
        pos[0] -= cos(angle) * scale;
        pos[2] -= sin(angle) * scale;
        m_counter++;
    }

    pos[1] = -0.05;
}

void DNASignBaseline::reset()
{
    m_curr_pos[0] = 0.0;
    m_curr_pos[1] = 0.0;
    m_curr_pos[2] = 0.0;
    m_field_252 = 0.0;
    m_angle = 0.0;
    m_is_space = true;
    m_counter = 0;
}
