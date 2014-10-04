#ifndef DNAWALL_H
#define DNAWALL_H

#include "pandabase.h"
#include "DNANode.h"

class EXPCL_PANDASKEL DNAWall : public DNANode
{
	PUBLISHED:
		DNAWall(string name);
		~DNAWall(void);

		void set_code(const string& code);
		string get_code();

		void set_color(LVector4f* color);
		LVector4f* get_color();
		
		void set_height(float h);
		float get_height();

	public:
		void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
		virtual void traverse(NodePath& np, DNAStorage* store);
		virtual bool is_wall();

	protected:
		string m_code;
		float m_height;
		LVector4f* m_color;
};

#endif
