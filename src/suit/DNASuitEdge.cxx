#include "DNASuitEdge.h"

TypeHandle DNASuitEdge::_type_handle;

DNASuitEdge::DNASuitEdge(DNASuitPoint* start_point, DNASuitPoint* end_point,
                         zone_id_t zone_id): m_start_point(start_point),
                                             m_end_point(end_point),
                                             m_zone_id(zone_id)
{
}

DNASuitEdge::~DNASuitEdge()
{
}

void DNASuitEdge::set_start_point(DNASuitPoint* point)
{
    m_start_point = point;
}

DNASuitPoint* DNASuitEdge::get_start_point()
{
    return m_start_point;
}

void DNASuitEdge::set_end_point(DNASuitPoint* point)
{
    m_end_point = point;
}

DNASuitPoint* DNASuitEdge::get_end_point()
{
    return m_end_point;
}
        
void DNASuitEdge::set_zone_id(zone_id_t zone_id)
{
    m_zone_id = zone_id;
}

zone_id_t DNASuitEdge::get_zone_id()
{
    return m_zone_id;
}
