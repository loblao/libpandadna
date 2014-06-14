#ifndef DNASTREET_H
#define DNASTREET_H

#include "pandabase.h"
#include "DNANode.h"

class EXPCL_PANDASKEL DNAStreet : public DNANode
{
	PUBLISHED:
		DNAStreet(string name);
		~DNAStreet(void);

		void set_code(const string& code);
		string get_code();
		
		void set_street_texture(const string& texture);
		string get_street_texture();

        void set_sidewalk_texture(const string& texture);
		string getSidewalkTexture();

        void set_curb_texture(const string& texture);
		string get_curb_texture();

		void set_street_color(LVector4f* color);
		LVector4f* get_street_color();

		void set_sidewalk_color(LVector4f* color);
		LVector4f* get_sidewalk_color();

		void set_curb_color(LVector4f* color);
		LVector4f* get_curb_color();

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
