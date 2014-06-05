#include "DNADoor.h"

DNADoor::DNADoor(string name) : DNAGroup(name), m_color(new LVector4f(1)) {}
DNADoor::~DNADoor(void) {}

void DNADoor::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
	DNAGroup::make_from_dgi(dgi, store);
	m_code = dgi_extract_string8(dgi);
	m_color = dgi_extract_color(dgi);
};
