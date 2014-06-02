#include "DNASuitPoint.h"

DNASuitPoint::DNASuitPoint(unsigned short index, unsigned char point_type, LVector3f* pos,
						   short landmark_building_index = -1) : m_index(index), m_point_type(point_type),
						   m_landmark_building_index(landmark_building_index), m_graph_id(0),
						   m_pos(pos) {};

DNASuitPoint::~DNASuitPoint() {};

void DNASuitPoint::set_index(unsigned char index)
{
	m_index = index;
};

void DNASuitPoint::set_landmark_building_index(short index)
{
	m_landmark_building_index = index;
};

void DNASuitPoint::set_graph_id(char id)
{
	m_graph_id = id;
};

void DNASuitPoint::set_pos(LVector3f* pos)
{
	m_pos = pos;
};

void DNASuitPoint::set_point_type(const char* point_type)
{

	if (stricmp(point_type, "STREET_POINT") == 0) m_point_type = 0;
	else if (stricmp(point_type, "FRONT_DOOR_POINT") == 0) m_point_type = 1;
	else if (stricmp(point_type, "SIDE_DOOR_POINT") == 0) m_point_type = 2;
	else if (stricmp(point_type, "COGHQ_IN_POINT") == 0) m_point_type = 3;
	else if (stricmp(point_type, "COGHQ_OUT_POINT") == 0) m_point_type = 4;

	else
	{
		stringstream ss;
		ss << "'" << point_type << "' is not a valid point type. Must be:" << endl;
		ss << "   STREET_POINT" << endl;
		ss << "   FRONT_DOOR_POINT" << endl;
		ss << "   SIDE_DOOR_POINT" << endl;
		ss << "   COGHQ_IN_POINT" << endl;
		ss << "   COGHQ_OUT_POINT" << endl;
		PyErr_Format(PyExc_ValueError, ss.str().c_str());
	}
};

void DNASuitPoint::set_point_type(unsigned short value)
{
	m_point_type = value;
};

unsigned char DNASuitPoint::get_index()
{
	return m_index;
};

char DNASuitPoint::get_graph_id()
{
	return m_graph_id;
};

short DNASuitPoint::get_landmark_building_index()
{
	return m_landmark_building_index;
};

LVector3f* DNASuitPoint::get_pos()
{
	return m_pos;
};

unsigned short DNASuitPoint::get_point_type()
{
	return m_point_type;
};
