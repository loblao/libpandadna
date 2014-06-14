#include "DNADoor.h"
#include <decalEffect.h>

DNADoor::DNADoor(string name) : DNAGroup(name), m_color(new LVector4f(1)) {}
DNADoor::~DNADoor(void) {}

void DNADoor::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
	DNAGroup::make_from_dgi(dgi, store);
	m_code = dgi_extract_string8(dgi);
	m_color = dgi_extract_color(dgi);
};

void DNADoor::traverse(NodePath& np, DNAStorage* store)
{
	NodePath front_node = np.find("**/*_front");
	if (!front_node.get_node(0)->is_geom_node())
	{
		front_node = front_node.find("**/+GeomNode");
	};
	
	if (front_node.is_empty())
	{
		cerr << "EMPTY!\n";
		return;	
	};
	front_node.get_node(0)->set_effect(DecalEffect::make());
	
	NodePath* result = store->find_node(m_code);
	if (result->is_empty())
	{
		stringstream ss;
		ss << "code " << m_code << " of door " << m_name << " not found";
		cout << "DNADoor(fatal): " << ss.str() << endl;
		throw ss.str();
	}

	NodePath door_node = result->copy_to(front_node);

	string block = store->get_block(np.get_name());

	NodePath door_origin = np.find("**/*door_origin");
	if (door_origin.is_empty())
	{
		stringstream ss;
		ss << "door " << m_name << " has no origin!";
		cout << "DNADoor(fatal): " << ss.str() << endl;
		throw ss.str();
	}

	door_node.set_pos(door_origin, 0, 0, 0);
	door_node.set_hpr(door_origin, 0, 0, 0);
	door_node.set_scale(door_origin, 1, 1, 1);
	door_node.set_color(*m_color);

	NodePath left_hole = door_node.find("door_*_hole_left");
	left_hole.set_name("doorFrameHoleLeft");

	NodePath right_hole = door_node.find("door_*_hole_right");
	right_hole.set_name("doorFrameHoleRight");

	NodePath left_door = door_node.find("door_*_left");
	left_door.set_name("leftDoor");
	NodePath right_door = door_node.find("door_*_right");
	right_door.set_name("rightDoor");

	NodePath door_flat = door_node.find("door_*_flat");
	left_hole.wrt_reparent_to(door_flat);
	right_hole.wrt_reparent_to(door_flat);
	door_flat.set_effect(DecalEffect::make());

	right_door.wrt_reparent_to(np);
	left_door.wrt_reparent_to(np);

	right_door.set_color(*m_color);
	left_door.set_color(*m_color);
	right_hole.set_color(0, 0, 0, 1);
	left_hole.set_color(0, 0, 0, 1);

	NodePath door_trigger = door_node.find("door_*_trigger");
	door_trigger.set_scale(2);
	door_trigger.wrt_reparent_to(np);

	stringstream ss;
	ss << "door_trigger_" << block;
	door_trigger.set_name(ss.str());

	int block_num = atoi(ss.str().c_str());

	if (!store->get_door_pos_hpr_from_block_number(block_num))
	{
		NodePath dnp = NodePath("door");
		dnp.set_pos(door_node, 0);
		dnp.set_hpr(door_node, 0);
		dnp.set_scale(door_node, 0);
		store->store_block_door(block_num, dnp);
	};
};

void DNADoor::set_code(const string& code)
{
	m_code = code;
};

string DNADoor::get_code()
{
	return m_code;
};

void DNADoor::set_color(LVector4f* color)
{
	m_color = color;
};

LVector4f* DNADoor::get_color()
{
	return m_color;
};
