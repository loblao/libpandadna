#include "DNAInteractiveProp.h"

DNAInteractiveProp::DNAInteractiveProp(string name) : DNAAnimProp(name) {}
DNAInteractiveProp::~DNAInteractiveProp(void) {}

void DNAInteractiveProp::make_from_dgi(DatagramIterator &dgi, DNAStorage *store)
{
	DNAAnimProp::make_from_dgi(dgi, store);
	m_cell_id = dgi.get_int16();
};
