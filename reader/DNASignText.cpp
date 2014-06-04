#include "DNASignText.h"

DNASignText::DNASignText(string name) : DNANode(name) {}
DNASignText::~DNASignText(void) {}

void DNASignText::make_from_dgi(DatagramIterator &dgi, DNAStorage *store)
{
	DNANode::make_from_dgi(dgi, store);
	m_letters = dgi_extract_string8(dgi);
};
