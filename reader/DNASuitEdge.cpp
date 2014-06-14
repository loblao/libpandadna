#include "DNASuitEdge.h"

DNASuitEdge::DNASuitEdge() {};
/*DNASuitEdge::DNASuitEdge(unsigned short start_point, unsigned short end_point,
						   unsigned short zone_id) : m_start_point(start_point),
						   m_end_point(end_point), m_zone_id(zone_id);*/

DNASuitEdge::~DNASuitEdge() {};

void DNASuitEdge::set_start_point(unsigned short start_point)
{
	m_start_point = start_point;
};

void DNASuitEdge::set_end_point(unsigned short end_point)
{
	m_end_point = end_point;
};

void DNASuitEdge::set_zone_id(unsigned short zone_id)
{
	m_zone_id = zone_id;
};

unsigned short DNASuitEdge::get_start_point()
{
	return m_start_point;
};

unsigned short DNASuitEdge::get_end_point()
{
	return m_end_point;
};

unsigned short DNASuitEdge::get_zone_id()
{
	return m_zone_id;
};
