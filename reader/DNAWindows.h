#ifndef DNAWINDOWS_H
#define DNAWINDOWS_H

#include "pandabase.h"
#include "DNAGroup.h"

class EXPCL_PANDASKEL DNAWindows : public DNAGroup
{
	PUBLISHED:
		DNAWindows(string name);
		~DNAWindows(void);

		void set_code(const string& code);
		string get_code();

		void set_color(LVector4f* color);
		LVector4f* get_color();
		
		void set_window_count(unsigned short count);
		unsigned short get_window_count();

	public:
		void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
		virtual void traverse(NodePath& np, DNAStorage* store);

	private:
		string m_code;
		LVector4f* m_color;
		unsigned short m_window_count;
		void make_windows(float x, float z, NodePath parent_node, LVector4f* color,
						  float scale, DNAStorage* store, bool flip = false);
};

#endif
