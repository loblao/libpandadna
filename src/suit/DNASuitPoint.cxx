#include "DNASuitPoint.h"

TypeHandle DNASuitPoint::_type_handle;

DNASuitPoint::DNASuitPoint(point_index_t index, PointType point_type, LPoint3f const pos,
                           block_number_t landmark_building_index): m_index(index), m_point_type(point_type), m_pos(pos),
                                                                    m_landmark_building_index(landmark_building_index)
{
}

DNASuitPoint::~DNASuitPoint()
{
}

void DNASuitPoint::set_index(point_index_t index)
{
    m_index = index;
}

point_index_t DNASuitPoint::get_index()
{
    return m_index;
}

void DNASuitPoint::set_point_type(PointType point_type)
{
    m_point_type = point_type;
}

void DNASuitPoint::set_point_type(const std::string& point_type)
{
    if (point_type == "STREET_POINT")
        set_point_type(DNASuitPoint::STREET_POINT);
        
    else if (point_type == "FRONT_DOOR_POINT")
        set_point_type(DNASuitPoint::FRONT_DOOR_POINT);
        
    else if (point_type == "SIDE_DOOR_POINT")
        set_point_type(DNASuitPoint::SIDE_DOOR_POINT);
        
    else if (point_type == "COGHQ_IN_POINT")
        set_point_type(DNASuitPoint::COGHQ_IN_POINT);
        
    else if (point_type == "COGHQ_OUT_POINT")
        set_point_type(DNASuitPoint::COGHQ_OUT_POINT);
        
    else
         dna_cat.error() << "invalid point type: " << point_type << std::endl;
}

DNASuitPoint::PointType DNASuitPoint::get_point_type()
{
    return m_point_type;
}

void DNASuitPoint::set_pos(LPoint3f const pos)
{
    m_pos = pos;
}

const LPoint3f DNASuitPoint::get_pos()
{
    return m_pos;
}

void DNASuitPoint::set_landmark_building_index(block_number_t landmark_building_index)
{
    m_landmark_building_index = landmark_building_index;
}

block_number_t DNASuitPoint::get_landmark_building_index()
{
    return m_landmark_building_index;
}
