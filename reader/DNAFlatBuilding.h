#ifndef DNAFLATBUILDING_H
#define DNAFLATBUILDING_H

#include "pandabase.h"
#include "DNANode.h"

class EXPCL_PANDASKEL DNAFlatBuilding : public DNANode
{
	PUBLISHED:
		DNAFlatBuilding(string name);
		~DNAFlatBuilding(void);

		void set_width(unsigned char w);
		unsigned char get_width();

		int get_current_wall_height();

		void set_has_door(bool);
		bool get_has_door();

	public:
		void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
		virtual void traverse(NodePath& np, DNAStorage* store);
		static int current_wall_height;
	
	private:
		unsigned char m_width;
        bool m_has_door;
		void setup_suit_flat_building(NodePath& np, DNAStorage* store);
		void setup_cogdo_flat_building(NodePath& np, DNAStorage* store);
};

#endif
