#ifndef DNASIGNGRAPHIC_H
#define DNASIGNGRAPHIC_H

#include "pandabase.h"
#include "DNANode.h"

class EXPCL_PANDASKEL DNASignGraphic : public DNANode
{
	PUBLISHED:
		DNASignGraphic(string name);
		~DNASignGraphic(void);

		void set_code(const string& code);
		string get_code();

		void set_color(LVector4f* color);
		LVector4f* get_color();

		void set_width(float w);
		float get_width();

		void set_height(float h);
		float get_height();
	
	public:
		void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
		virtual void traverse(NodePath& np, DNAStorage* store);

	private:
		string m_code;
		LVector4f* m_color;
        float m_width;
        float m_height;
        bool m_b_default_color;
};

#endif
