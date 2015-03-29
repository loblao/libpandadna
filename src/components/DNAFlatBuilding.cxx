#include "DNAFlatBuilding.h"
#include "DNAWall.h"

#include <decalEffect.h>
#include <nodePathCollection.h>

TypeHandle DNAFlatBuilding::_type_handle;
int DNAFlatBuilding::current_wall_height = 0;

DNAFlatBuilding::DNAFlatBuilding(const std::string& name): DNANode(name), m_width(0),
                                                           m_has_door(false)
{
}

DNAFlatBuilding::~DNAFlatBuilding()
{
}
        
void DNAFlatBuilding::setup_flat(NodePath& np, DNAStorage* store, const char chr,
                                 const std::string& wall_code)
                                 
{
    if (m_name.substr(0, 2) != "tb")
        return;
        
    std::stringstream ss;
    ss << chr << 'b' << m_name.substr(2, m_name.size());
    
    NodePath node = np.attach_new_node(ss.str());
    
    LPoint3f scale = LPoint3f(m_scale);
    scale.set_x(m_width);
    scale.set_z(DNAFlatBuilding::current_wall_height);
    
    node.set_z(DNAFlatBuilding::current_wall_height);
    node.set_pos_hpr_scale(m_pos, m_hpr, scale);
    
    unsigned int num_codes = store->get_num_catalog_codes(wall_code);
    if (num_codes == 0)
        return;
        
    srand(time(NULL));
    NodePath wall_node = store->find_node(store->get_catalog_code(wall_code,
                                           rand() % num_codes));
    if (wall_node.is_empty())
        return;
        
    wall_node.copy_to(node);
    if (m_has_door)
    {
        NodePath wall_np, door_np;
        wall_np = node.find("wall_*");
        door_np = store->find_node("suit_door").copy_to(wall_np);
        door_np.set_pos_hpr_scale(.5, 0, 0, 0, 0, 0, 1.0 / m_width, 0,
                                  1.0 / DNAFlatBuilding::current_wall_height);                           
        wall_np.set_effect(DecalEffect::make());
    }
    
    node.flatten_medium();
    node.stash();
}
                                 
void DNAFlatBuilding::setup_suit_flat_building(NodePath& np, DNAStorage* store)
{
    setup_flat(np, store, 's', "suit_wall");
}

void DNAFlatBuilding::setup_cogdo_flat_building(NodePath& np, DNAStorage* store)
{
    setup_flat(np, store, 'c', "cogdo_wall");
}

void DNAFlatBuilding::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
    DNANode::make_from_dgi(dgi, store);
    m_width = dgi.get_uint16() / 10.0;
    m_has_door = dgi.get_bool();
}

void DNAFlatBuilding::traverse(NodePath& np, DNAStorage* store)
{
    DNAFlatBuilding::current_wall_height = 0;
    NodePath node = np.attach_new_node(m_name);
    
    std::stringstream ss;
    ss << m_name.size() << "-internal";

    NodePath internal_node = node.attach_new_node(ss.str());
    
    LPoint3f scale(m_scale);
    scale.set_x(m_width);
    internal_node.set_scale(scale);
    node.set_pos_hpr(m_pos, m_hpr);
    
    for (dna_group_vec_t::iterator it = m_children.begin(); it != m_children.end(); it++)
    {
        DNAGroup* comp = *it;
        comp->traverse(comp->is_of_type(DNAWall::get_class_type()) ? internal_node : node, store);
    }
    
    if (DNAFlatBuilding::current_wall_height)
    {
        NodePath result = store->find_node("wall_camera_barrier");
        if (result.is_empty())
        {
            raise_code_not_found("wall_camera_barrier");
            return;
        }
        
        NodePath camera_barrier = result.copy_to(internal_node);
        camera_barrier.set_scale(1, 1, DNAFlatBuilding::current_wall_height);
        
        setup_suit_flat_building(np, store);
        setup_cogdo_flat_building(np, store);
        
        internal_node.flatten_strong();
        
        NodePath coll_np = node.find("**/door_*/+CollisionNode");
        if (!coll_np.is_empty())
        {
            std::stringstream ss;    
            ss << "KnockKnockDoorSphere_" << store->get_block(m_name);
            coll_np.set_name(ss.str());
        }
        
        camera_barrier.wrt_reparent_to(np);
        
        NodePathCollection wall_collection, door_collection, cornice_collection,
                           window_collection;
        NodePath wall_holder, wall_decal;
        
        wall_collection = internal_node.find_all_matches("wall*");
        door_collection = internal_node.find_all_matches("**/door*");
        cornice_collection = internal_node.find_all_matches("**/cornice*_d");
        window_collection = internal_node.find_all_matches("**/window*");

        wall_holder = node.attach_new_node("wall_holder");
        wall_decal = node.attach_new_node("wall_decal");

        wall_collection.reparent_to(wall_holder);
        door_collection.reparent_to(wall_decal);
        cornice_collection.reparent_to(wall_decal);
        window_collection.reparent_to(wall_decal);

        for (size_t i = 0; i < wall_holder.get_num_children(); i++)
        {
            NodePath child = wall_holder.get_child(i);
            child.clear_tag("DNARoot");
            child.clear_tag("DNACode");
        }

        wall_holder.flatten_strong();
        wall_decal.flatten_strong();

        NodePath holder_child_0 = wall_holder.get_child(0);
        wall_decal.get_children().reparent_to(holder_child_0);
        holder_child_0.reparent_to(internal_node);
        holder_child_0.set_effect(DecalEffect::make());

        wall_holder.remove_node();
        wall_decal.remove_node();
    }
}
