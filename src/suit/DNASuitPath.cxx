#include "DNASuitPath.h"

#include <algorithm>

TypeHandle DNASuitPath::_type_handle;

DNASuitPath::DNASuitPath()
{
}

DNASuitPath::~DNASuitPath()
{
}

void DNASuitPath::add_point(DNASuitPoint* point)
{
    m_suit_points.push_back(point);
}

DNASuitPoint* DNASuitPath::get_point(size_t index)
{
    return m_suit_points.at(index);
}

size_t DNASuitPath::get_num_points()
{
    return m_suit_points.size();
}

point_index_t DNASuitPath::get_point_index(size_t index)
{
    return get_point(index)->get_index();
}

void DNASuitPath::reverse_path()
{
    std::reverse(m_suit_points.begin(), m_suit_points.end());
}
