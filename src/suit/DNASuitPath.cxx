#include "DNASuitPath.h"

#include <algorithm>

TypeHandle DNASuitPath::_type_handle;

DNASuitPath::DNASuitPath()
{
}

DNASuitPath::~DNASuitPath()
{
}

void DNASuitPath::add_point(PT(DNASuitPoint) point)
{
    m_suit_points.push_back(point);
}

PT(DNASuitPoint) DNASuitPath::get_point(int index)
{
    return m_suit_points.at(index);
}

int DNASuitPath::get_num_points()
{
    return m_suit_points.size();
}

point_index_t DNASuitPath::get_point_index(int index)
{
    return get_point(index)->get_index();
}

void DNASuitPath::reverse_path()
{
    std::reverse(m_suit_points.begin(), m_suit_points.end());
}
