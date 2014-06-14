#include "DNAFlatDoor.h"
#include <nodePath.h>
#include <decalEffect.h>

DNAFlatDoor::DNAFlatDoor(string name) : DNADoor(name) {}
DNAFlatDoor::~DNAFlatDoor(void) {}

void DNAFlatDoor::traverse(NodePath& np, DNAStorage* store)
{
	NodePath* result = store->find_node(m_code);
	// to do: check

	NodePath _np = result->copy_to(np);
	_np.set_scale(NodePath(), 1);
	_np.set_pos(.5, 0, 0);
	_np.set_hpr(0);
	_np.set_color(*m_color);
	_np.get_node(0)->set_effect(DecalEffect::make());
};
