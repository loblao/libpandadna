#ifndef DNALANDMARKBUILDING_H
#define DNALANDMARKBUILDING_H

#include "pandabase.h"
#include "DNANode.h"

class EXPCL_PANDASKEL DNALandmarkBuilding : public DNANode
{
	PUBLISHED:
		DNALandmarkBuilding(string name);
		~DNALandmarkBuilding(void);

		void set_article(const string& article);
		string get_article();

		void set_building_type(const string& building_type);
		string get_building_type();

		void set_title(const string& title);
		string get_title();

		void set_code(const string& code);
		string get_code();

		void set_wall_color(LVector4f* color);
		LVector4f* get_wall_color();

	public:
		void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
		virtual void traverse(NodePath& np, DNAStorage* store);

	protected:
		string m_code;
		LVector4f* m_wall_color;
		string m_title;
		string m_article;
		string m_building_type;
		void setup_suit_building_origin(NodePath a, NodePath b);
};

#endif
