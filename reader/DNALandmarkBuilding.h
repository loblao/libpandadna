#ifndef DNALANDMARKBUILDING_H
#define DNALANDMARKBUILDING_H

#include "pandabase.h"
#include "DNANode.h"

class EXPCL_PANDASKEL DNALandmarkBuilding : public DNANode
{
	PUBLISHED:
		DNALandmarkBuilding(string name);
		~DNALandmarkBuilding(void);

	public:
		void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
		virtual void traverse(NodePath& np, DNAStorage* store);

	private:
		string m_code;
		LVector4f* m_wall_color;
		string m_title;
		string m_article;
		string m_building_type;
		void setup_suit_building_origin(NodePath a, NodePath b);
};

#endif
