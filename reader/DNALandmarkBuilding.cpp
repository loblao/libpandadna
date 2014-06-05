#include "DNALandmarkBuilding.h"

DNALandmarkBuilding::DNALandmarkBuilding(string name) : DNANode(name), m_wall_color(new LVector4f(1)) {}
DNALandmarkBuilding::~DNALandmarkBuilding(void) {}

void DNALandmarkBuilding::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
	DNANode::make_from_dgi(dgi, store);
	m_code = dgi_extract_string8(dgi);
	m_wall_color = dgi_extract_color(dgi);
	m_title = dgi_extract_string8(dgi);
	m_article = dgi_extract_string8(dgi);
	m_building_type = dgi_extract_string8(dgi);
};
