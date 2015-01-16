#include "DNASignBaseline.h"

#include <bamFile.h>
#include <stringStream.h>
#include <compress_string.h>

TypeHandle DNASignBaseline::_type_handle;

DNASignBaseline::DNASignBaseline(const std::string& name): DNANode(name), m_data("")
{
}

DNASignBaseline::~DNASignBaseline()
{
}

void DNASignBaseline::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
    DNANode::make_from_dgi(dgi, store);
    m_data = dgi.get_string();
    if (m_data.size())
        m_data = decompress_string(m_data);
}

void DNASignBaseline::traverse(NodePath& np, DNAStorage* store)
{
    NodePath _np = np.attach_new_node("baseline");
    _np.set_pos_hpr(m_pos, m_hpr);
    _np.set_depth_offset(50);
    
    if (m_data.size())
    {
        BamFile bf;
        StringStream ss;
        ss.set_data(m_data);
        bf.open_read(ss);
        
        NodePath(bf.read_node()).reparent_to(_np);
    }
    
    traverse_children(_np, store);
}
