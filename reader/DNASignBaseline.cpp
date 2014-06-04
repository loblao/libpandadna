#include "DNASignBaseline.h"

DNASignBaseline::DNASignBaseline(string name) : DNANode(name) {}
DNASignBaseline::~DNASignBaseline(void) {}

void DNASignBaseline::make_from_dgi(DatagramIterator &dgi, DNAStorage *store)
{
	DNANode::make_from_dgi(dgi, store);
	m_code = dgi_extract_string8(dgi);
	m_color = dgi_extract_color(dgi);
	m_font = dgi_extract_string8(dgi);
	m_flags = dgi_extract_string8(dgi);
	m_indent = dgi.get_int16() / 100;
    m_kern = dgi.get_int16() / 100;
	m_wiggle = dgi.get_int16() / 100;
	m_stumble = dgi.get_int16() / 100;
	m_stomp = dgi.get_int16() / 100;
	m_width = dgi.get_int16() / 100;
	m_height = dgi.get_int16() / 100;
};
