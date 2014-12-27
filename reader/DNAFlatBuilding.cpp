#include "DNAFlatBuilding.h"
#include <nodePathCollection.h>
#include <decalEffect.h>

DNAFlatBuilding::DNAFlatBuilding(string name) : DNANode(name), m_has_door(false),
												m_width(0) {}
DNAFlatBuilding::~DNAFlatBuilding(void) {}

int DNAFlatBuilding::current_wall_height = 0;

void DNAFlatBuilding::make_from_dgi(DatagramIterator &dgi, DNAStorage *store)
{
	DNANode::make_from_dgi(dgi, store);
	m_width = dgi.get_uint8();
	m_has_door = dgi.get_bool();
};

void DNAFlatBuilding::traverse(NodePath& np, DNAStorage* store)
{
	DNAFlatBuilding::current_wall_height = 0;
	NodePath node = np.attach_new_node(m_name);
	stringstream ss;
	ss << m_name << "-internal";
	NodePath internal_node = node.attach_new_node(ss.str());
	m_scale->set_x(m_width);
	internal_node.set_scale(*m_scale);
	node.set_pos(*m_pos);
	node.set_hpr(*m_hpr);

	for (comp_vec_t::iterator child = m_children.begin(); child != m_children.end(); child++)
	{
        if ((*child)->is_wall())
		{
			(*child)->traverse(internal_node, store);
		}

		else
		{
			(*child)->traverse(node, store);
		}
	};

	if (DNAFlatBuilding::current_wall_height != 0)
	{
		NodePath* result = store->find_node("wall_camera_barrier");
		if (result->is_empty())
		{
			stringstream ss;
			ss << "DNAFlatBuilding(fatal): " << m_name << " : wall_camera_barrier not in storage!";
			cerr << ss.str() << endl;
			throw ss.str();
		};

		NodePath camera_barrier = result->copy_to(internal_node);
		camera_barrier.set_scale(LVector3f(1, 1, DNAFlatBuilding::current_wall_height));
		
		setup_suit_flat_building(np, store);
		setup_cogdo_flat_building(np, store);

		internal_node.flatten_strong();
		
		NodePath coll_node = node.find("**/door_*/+CollisionNode");
		if (!coll_node.is_empty())
		{
			stringstream ss;
			ss << "KnockKnockDoorSphere_" << store->get_block(m_name);
			coll_node.set_name(ss.str());
		};

		camera_barrier.wrt_reparent_to(np);

		NodePathCollection wall_collection = internal_node.find_all_matches("wall*");
		NodePath wall_holder = node.attach_new_node("wall_holder");
		NodePath wall_decal = node.attach_new_node("wall_decal");
		NodePathCollection window_collection = internal_node.find_all_matches("**/cornice*_d");
		NodePathCollection door_collection = internal_node.find_all_matches("**/door*");
        NodePathCollection cornice_collection = internal_node.find_all_matches("**/cornice*_d");

		wall_collection.reparent_to(wall_holder);
		window_collection.reparent_to(wall_decal);
		door_collection.reparent_to(wall_decal);
		cornice_collection.reparent_to(wall_decal);

		short num_children = wall_holder.get_num_children();
		for (short i = 0; i < num_children; i++)
		{
			NodePath x = wall_holder.get_child(i);
			x.clear_tag("DNACode");
			x.clear_tag("DNARoot");
		};
		
		wall_holder.flatten_strong();
		wall_decal.flatten_strong();

		NodePath holder_child0 = wall_holder.get_child(0);
		wall_decal.get_children().reparent_to(holder_child0);
		holder_child0.reparent_to(internal_node);
		holder_child0.set_effect(DecalEffect::make());

		wall_holder.remove_node();
		wall_decal.remove_node();
	};
};

void DNAFlatBuilding::setup_suit_flat_building(NodePath& np, DNAStorage* store)
{
	string name = m_name;
	if (name.substr(0, 2) != "tb")
	{
		return;
	};

	stringstream ss;
	ss << "sb" << name.substr(2); 
	name = ss.str();

	NodePath node = np.attach_new_node(name);
	
	LVector3f* scale = new LVector3f(*m_scale);
	scale->set_x(m_width);
	scale->set_z(DNAFlatBuilding::current_wall_height);

	node.set_z(DNAFlatBuilding::current_wall_height);
	node.set_scale(*scale);
	node.set_pos_hpr(*m_pos, *m_hpr);

	int num_codes = store->get_num_catalog_codes("suit_wall");
	string code = store->get_catalog_code("suit_wall", rand() % num_codes);
	store->find_node(code)->copy_to(node);

	if (m_has_door)
	{
		NodePath door_np = node.find("wall_*");
		store->find_node("suit_door")->copy_to(door_np).\
			set_pos_hpr_scale(0.5, 0, 0, 0, 0, 0, 1.0 / m_width, 0,
							  1.0 / DNAFlatBuilding::current_wall_height);
		door_np.set_effect(DecalEffect::make());
	};

	node.flatten_medium();
	node.stash();
};

void DNAFlatBuilding::setup_cogdo_flat_building(NodePath& np, DNAStorage* store)
{
	string name = m_name;
	if (name.substr(0, 2) != "tb")
	{
		return;
	};

	stringstream ss;
	ss << "cb" << name.substr(2); 
	name = ss.str();

	NodePath node = np.attach_new_node(name);
	
	LVector3f* scale = new LVector3f(*m_scale);
	scale->set_x(m_width);
	scale->set_z(DNAFlatBuilding::current_wall_height);

	node.set_z(DNAFlatBuilding::current_wall_height);
	node.set_scale(*scale);
	node.set_pos_hpr(*m_pos, *m_hpr);

	int num_codes = store->get_num_catalog_codes("codgo_wall");
	string code = store->get_catalog_code("cogdo_wall", rand() % num_codes);
	NodePath* result = store->find_node(code);
	if (result->is_empty())
	{
		return;
	}
	
	result->copy_to(node);

	if (m_has_door)
	{
		NodePath wall_np = node.find("wall_*");
		NodePath* result = store->find_node("suit_door");

		NodePath door_node = result->copy_to(wall_np);
		door_node.set_scale(NodePath(), 1, 1, 1);
		door_node.set_x(.5);

		wall_np.set_effect(DecalEffect::make());
	};

	node.flatten_medium();
	node.stash();
};

void DNAFlatBuilding::set_width(unsigned char w)
{
	m_width = w;
};

unsigned char DNAFlatBuilding::get_width()
{
	return m_width;
};

int DNAFlatBuilding::get_current_wall_height()
{
	return DNAFlatBuilding::current_wall_height;
};

void DNAFlatBuilding::set_has_door(bool value)
{
	m_has_door = value;
};

bool DNAFlatBuilding::get_has_door()
{
	return m_has_door;
};
