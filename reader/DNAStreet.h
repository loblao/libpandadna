#ifndef DNASTREET_H
#define DNASTREET_H

#include "pandabase.h"
#include "DNANode.h"

class EXPCL_PANDASKEL DNAStreet : public DNANode
{
	PUBLISHED:
		DNAStreet(string name);
		~DNAStreet(void);

	public:
		void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
		virtual void traverse(NodePath& np, DNAStorage* store);

	private:
		string m_code;
		string m_street_tex;
        string m_sidewalk_tex;
        string m_curb_tex;
        LVector4f* m_street_color;
        LVector4f* m_sidewalk_color;
        LVector4f* m_curb_color;
};

#endif
