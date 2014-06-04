#include "DNAFlatBuilding.h"

DNAFlatBuilding::DNAFlatBuilding(string name) : DNANode(name), m_has_door(false),
												m_width(0) {}
DNAFlatBuilding::~DNAFlatBuilding(void) {}

void DNAFlatBuilding::make_from_dgi(DatagramIterator &dgi, DNAStorage *store)
{
	DNANode::make_from_dgi(dgi, store);
	m_width = dgi.get_uint8();
	m_has_door = dgi.get_bool();
};