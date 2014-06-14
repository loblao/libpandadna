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
		virtual void traverse(NodePath np, DNAStorage* store);

	private:
		string m_code;
		LVector4f* m_color;
		string m_font;
		string m_flags;
		double m_indent;
        double m_kern;
        double m_wiggle;
        double m_stumble;
        double m_stomp;
        double m_width;
        double m_height;
		void curve(NodePath& root, unsigned short num_children);

		static int _index;
};

#endif
