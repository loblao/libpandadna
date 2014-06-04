#ifndef DNAWINDOWS_H
#define DNAWINDOWS_H

#include "pandabase.h"
#include "DNAGroup.h"

class EXPCL_PANDASKEL DNAWindows : public DNAGroup
{
	PUBLISHED:
		DNAWindows(string name);
		~DNAWindows(void);

	public:
		void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);

	private:
		string m_code;
		LVector4f* m_color;
		unsigned short m_window_count;
};

#endif
