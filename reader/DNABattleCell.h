#pragma once

#include "dnabase.h"
#include <lvector3.h>

class EXPCL_PANDASKEL DNABattleCell
{
	PUBLISHED:
		DNABattleCell();
		~DNABattleCell();

		void set_width(unsigned char width);
		void set_height(unsigned char height);
		void set_width_height(unsigned char width, unsigned char height);
		void set_pos(LVector3f* pos);

		unsigned char get_width();
		unsigned char get_height();
		LVector3f* get_pos();

	private:
		unsigned char m_width;
		unsigned char m_height;
		LVector3f* m_pos;
};
