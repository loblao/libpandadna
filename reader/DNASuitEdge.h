#pragma once

#include "dnabase.h"

class EXPCL_PANDASKEL DNASuitEdge
{
	PUBLISHED:
		DNASuitEdge();
		~DNASuitEdge();

		void set_start_point(unsigned short start_point);
		void set_end_point(unsigned short end_point);
		void set_zone_id(unsigned short zone_id);

		unsigned short get_start_point();
		unsigned short get_end_point();
		unsigned short get_zone_id();

	private:
		unsigned short m_start_point;
		unsigned short m_end_point;
		unsigned short m_zone_id;
};