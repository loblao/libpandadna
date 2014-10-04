#ifndef DNACORNICE_H
#define DNACORNICE_H

#include "pandabase.h"
#include "DNAGroup.h"

class EXPCL_PANDASKEL DNACornice : public DNAGroup
{
	PUBLISHED:
		DNACornice(string name);
		~DNACornice(void);

		void set_code(const string& code);
		string get_code();

		void set_color(LVector4f* color);
		LVector4f* get_color();

	public:
		void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
		virtual void traverse(NodePath& np, DNAStorage* store);

	private:
		string m_code;
		LVector4f* m_color;
};

#endif
