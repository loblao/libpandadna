#include "DNAWindows.h"
#include "DNAStorage.h"

#include <decalEffect.h>

#define MAX_WINDOWS 4

TypeHandle DNAWindows::_type_handle;

DNAWindows::DNAWindows(const std::string& name): DNAGroup(name), m_code(""),
                                                 m_color(LVecBase4f(1)),
                                                 m_window_count(1)
{
}

DNAWindows::~DNAWindows()
{
}

void DNAWindows::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
    DNAGroup::make_from_dgi(dgi, store);
    m_code = dgi.get_string();
    m_color = DGI_EXTRACT_COLOR;
    m_window_count = dgi.get_uint8();
    m_window_count = m_window_count <= MAX_WINDOWS ? m_window_count : MAX_WINDOWS; 
}

#define MW(x, y, flip) make_windows(offset + x, offset + y, np, m_code, scale, m_color, store, flip);

void DNAWindows::traverse(NodePath& np, DNAStorage* store)
{
    if (!m_window_count)
        return;
        
    float parent_sx = np.get_parent().get_scale().get_x();
    float scale = 0.00375;

    if (parent_sx <= 5)
        scale++;
        
    else if (parent_sx <= 10)
        scale += 1.15;
        
    else
        scale += 1.3;
        
    float offset = 0.00375;
    
    switch (m_window_count)
    {
        case 1:
        {
            MW(.5, .5, false)
        }; break;
        
        case 2:
        {
            MW(.33, .5, false)
            MW(.66, .5, true)
        }; break;
        
        case 3:
        {
            MW(.33, .66, false)
            MW(.66, .66, true)
            MW(.5, .33, false)
        }; break;
        
        case 4:
        {
            MW(.33, .25, false)
            MW(.66, .25, true)
            MW(.33, .66, false)
            MW(.66, .66, true)
        }; break;
        
        default:
        {
            std::cerr << "dna(error): m_window_count invalid: " << m_window_count << std::endl;
        }; break;
    }
}

void DNAWindows::make_windows(float x, float y, NodePath& parent_node,
                              const std::string& code, float scale,
                              LVecBase4f& color, DNAStorage* store,
                              bool flip)
{
    std::stringstream ss;
    ss << code.substr(0, code.size() - 1);
    ss << (flip ? "l" : "r");
    std::string _code = ss.str();
    
    NodePath result = store->find_node(_code);
    if (result.is_empty())
    {
        raise_code_not_found(_code.c_str());
        return;
    }
    
    NodePath window = result.copy_to(parent_node);
    window.set_color(color);
    window.set_scale(NodePath(), scale);
    window.set_pos(x, 0, y);
    window.set_depth_offset(0);
}

