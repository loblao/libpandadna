#pragma once

#include "dnabase.h"
#include <lvector3.h>

using namespace std;

class EXPCL_PANDASKEL DNASuitPoint
{
	PUBLISHED:
		DNASuitPoint(unsigned short, unsigned char, LVector3f*, short);
		~DNASuitPoint();
		
		unsigned short m_index;
        unsigned char m_point_type;
        LVector3f* m_pos;
        short m_landmark_building_index;

		void set_index(unsigned char);
		void set_landmark_building_index(short);
		void set_pos(LVector3f*);
		void set_point_type(unsigned short);
		void set_point_type(const char*);

		unsigned char get_index();
		short get_landmark_building_index();
		LVector3f* get_pos();
		unsigned short get_point_type();
};
