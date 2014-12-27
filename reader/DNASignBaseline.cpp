// warning: this is extremely broken atm
// a lot of debug stuff have been left behind

#include "DNASignBaseline.h"
#include <nodePath.h>
#include <textNode.h>
#include <nodePathCollection.h>
#include <compress_string.h>
#include <bamFile.h>

#define M_PI 3.14159265358979323846  /* pi */

#include "DNASignText.h"

DNASignBaseline::DNASignBaseline(string name) : DNANode(name), m_data("") {}
DNASignBaseline::~DNASignBaseline(void) {}

void DNASignBaseline::make_from_dgi(DatagramIterator &dgi, DNAStorage *store)
{
	DNANode::make_from_dgi(dgi, store);

	string comp_string = dgi.get_string();
	if (comp_string.size() > 0)
	{
		m_data = decompress_string(comp_string);
	};
};

void DNASignBaseline::traverse(NodePath& np, DNAStorage* store)
{
	NodePath _np = np.attach_new_node("baseline");
	_np.set_pos(*m_pos);
	_np.set_hpr(*m_hpr);
	_np.set_depth_offset(50);

	stringstream ss;
	ss << m_data;

	if (m_data.size() > 0)
	{
		BamFile bf = BamFile();
		bf.open_read(ss);
		NodePath node = NodePath(bf.read_node());
		node.reparent_to(_np);
	};

	for (comp_vec_t::iterator child = m_children.begin(); child != m_children.end(); child++)
	{
		(*child)->traverse(_np, store);
	};
};
