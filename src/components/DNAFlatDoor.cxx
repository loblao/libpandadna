#include "DNAFlatDoor.h"
#include "DNAStorage.h"

#include <decalEffect.h>

TypeHandle DNAFlatDoor::_type_handle;

DNAFlatDoor::DNAFlatDoor(const std::string& name): DNADoor(name)
{
}

DNAFlatDoor::~DNAFlatDoor()
{
}

void DNAFlatDoor::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
    DNADoor::make_from_dgi(dgi, store);
}

void DNAFlatDoor::traverse(NodePath& np, DNAStorage* store)
{
    NodePath result = store->find_node(m_code);
    if (result.is_empty())
    {
        raise_code_not_found();
    }
    
    NodePath _np = result.copy_to(np);
    _np.set_scale(NodePath(), 1);
    _np.set_x(.5);
    _np.set_hpr(_np, 0);
    _np.set_color(m_color);
    _np.node()->set_effect(DecalEffect::make());
}
