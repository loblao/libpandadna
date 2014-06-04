#ifndef DNASIGNBASELINE_H
#define DNASIGNBASELINE_H

#include "pandabase.h"
#include "DNANode.h"

class EXPCL_PANDASKEL DNASignBaseline : public DNANode
{
	PUBLISHED:
		DNASignBaseline(string name);
		~DNASignBaseline(void);

	public:
		void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);

	private:
		string m_code;
		LVector4f* m_color;
		string m_font;
		string m_flags;
		float m_indent;
        float m_kern;
        float m_wiggle;
        float m_stumble;
        float m_stomp;
        float m_width;
        float m_height;
};

#endif
