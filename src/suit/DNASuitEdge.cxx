#include "DNASuitEdge.h"

TypeHandle DNASuitEdge::_type_handle;

DNASuitEdge::DNASuitEdge(PT(DNASuitPoint) start_point, PT(DNASuitPoint) end_point,
                         zone_id_t zone_id): m_start_point(start_point),
                                             m_end_point(end_point),
                                             m_zone_id(zone_id)
{
}

DNASuitEdge::~DNASuitEdge()
{
}
