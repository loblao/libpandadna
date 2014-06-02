#include "BlockHandle.h"

BlockHandle::BlockHandle() :  m_zone(0) {};
BlockHandle::~BlockHandle() {};

void BlockHandle::set_title(const string value)
{
	m_title = value;
};

void BlockHandle::set_article(const string value)
{
	m_article = value;
};

void BlockHandle::set_type(const string value)
{
	m_type = value;
};

void BlockHandle::set_zone(unsigned short value)
{
	m_zone = value;
};

string BlockHandle::get_title()
{
	return m_title;
};

string BlockHandle::get_article()
{
	return m_article;
};

string BlockHandle::get_type()
{
	return m_type;
};

unsigned short BlockHandle::get_zone()
{
	return m_zone;
};