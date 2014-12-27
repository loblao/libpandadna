#include "DNASignText.h"

DNASignText::DNASignText(string name) : DNANode(name) {}
DNASignText::~DNASignText(void) {}

void DNASignText::make_from_dgi(DatagramIterator &dgi, DNAStorage *store)
{
	DNANode::make_from_dgi(dgi, store);
	m_letters = dgi_extract_string8(dgi);
};

bool DNASignText::is_sign_text()
{
	return true;
};

void DNASignText::set_letters(const string& letters)
{
	m_letters = letters;
};

string DNASignText::get_letters()
{
	return m_letters;
};
