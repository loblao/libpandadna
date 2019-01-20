#include "DNADoor.h"
#include "DNAStorage.h"

#include "decalEffect.h"

TypeHandle DNADoor::_type_handle;

DNADoor::DNADoor(const std::string& name): DNAGroup(name), m_code(""),
                                           m_color(LVecBase4f(1))
{
}

DNADoor::~DNADoor()
{
}

void DNADoor::setup_door(NodePath door_np, NodePath parent_np, NodePath door_origin,
                         DNAStorage* store, const std::string& block, LVecBase4f& color)
{
    NodePath left_hole, left_hole_geom, right_hole, right_hole_geom,
             left_door, right_door, door_flat, door_trigger, store_np;
    door_np.set_pos_hpr_scale(door_origin, LVecBase3f(0), LVecBase3f(0), LVecBase3f(1));
    door_np.set_color(color);

    left_hole = door_np.find("door_*_hole_left");
    left_hole.set_name("doorFrameHoleLeft");
    left_hole_geom = left_hole.find("**/+GeomNode");
    left_hole_geom.set_name("doorFrameHoleLeftGeom");

    right_hole = door_np.find("door_*_hole_right");
    right_hole.set_name("doorFrameHoleRight");
    right_hole_geom = right_hole.find("**/+GeomNode");
    right_hole_geom.set_name("doorFrameHoleRightGeom");

    left_door = door_np.find("door_*_left");
    left_door.set_name("leftDoor");

    right_door = door_np.find("door_*_right");
    right_door.set_name("rightDoor");

    door_flat = door_np.find("door_*_flat");
    door_flat.set_effect(DecalEffect::make());

    left_hole.wrt_reparent_to(door_flat, 0);
    right_hole.wrt_reparent_to(door_flat, 0);

    if (!left_hole_geom.get_node(0)->is_geom_node())
        left_hole_geom = left_hole_geom.find("**/+GeomNode");

    if (!right_hole_geom.get_node(0)->is_geom_node())
        right_hole_geom = right_hole_geom.find("**/+GeomNode");

    left_hole_geom.set_effect(DecalEffect::make());
    right_hole_geom.set_effect(DecalEffect::make());

    right_door.wrt_reparent_to(parent_np, 0);
    left_door.wrt_reparent_to(parent_np, 0);

    right_door.set_color(color, 0);
    left_door.set_color(color, 0);

    right_door.hide();
    left_door.hide();

    left_hole.set_color(LVecBase4f(0, 0, 0, 1), 0);
    right_hole.set_color(LVecBase4f(0, 0, 0, 1), 0);

    right_hole.hide();
    left_hole.hide();

    door_trigger = door_np.find("door_*_trigger");
    door_trigger.set_scale(2, 2, 2);
    door_trigger.wrt_reparent_to(parent_np, 0);
    door_trigger.set_name("door_trigger_" + block);
}

void DNADoor::setup_door(NodePath door_np, NodePath parent_np, NodePath door_origin,
                         DNAStorage* store, block_number_t block, LVecBase4f& color)
{
    std::stringstream ss;
    ss << block;
    setup_door(door_np, parent_np, door_origin, store, ss.str(), color);
}

void DNADoor::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
    DNAGroup::make_from_dgi(dgi, store);
    m_code = dgi.get_string();
    dgi_extract_color(dgi, m_color);
}

void DNADoor::traverse(NodePath& np, DNAStorage* store)
{
    NodePath front_node = np.find("**/*_front");
    if (!front_node.get_node(0)->is_geom_node())
        front_node = front_node.find("**/+GeomNode");

    front_node.set_effect(DecalEffect::make());

    NodePath node = store->find_node(m_code);
    if (node.is_empty())
    {
        dna_cat.error() << "Door not found: " << m_code << std::endl;
        return;
    }

    NodePath door_origin = np.find("**/*door_origin");
    std::string block = store->get_block(np.get_name());

    setup_door(node.copy_to(front_node), np, door_origin, store, block, m_color);
    NodePath store_np = NodePath("block_door_pos_hpr-" + block);
    store_np.set_pos_hpr_scale(door_origin, LVecBase3f(0), LVecBase3f(0), LVecBase3f(1));
    store->store_block_door(atoi(block.c_str()), store_np);
}
