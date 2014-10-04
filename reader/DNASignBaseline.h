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
		virtual void traverse(NodePath& np, DNAStorage* store);

	private:
		string m_code;
		LVector4f* m_color;
		string m_data;
};

#endif
