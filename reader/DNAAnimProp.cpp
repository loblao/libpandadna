#include "DNAAnimProp.h"

DNAAnimProp::DNAAnimProp(string name) : DNAProp(name) {}
DNAAnimProp::~DNAAnimProp(void) {}

void DNAAnimProp::make_from_dgi(DatagramIterator &dgi, DNAStorage *store)
{
	DNAProp::make_from_dgi(dgi, store);
	m_anim_name = dgi_extract_string8(dgi);
};
