#include "DNALoader.h"
#include <virtualFileSystem.h>

#include <texture.h>
#include <texturePool.h>

#include <textFont.h>
#include <fontPool.h>

#include <modelPool.h>

using namespace std;

VirtualFileSystem *vfs = VirtualFileSystem::get_global_ptr();

DNALoader::DNALoader(void) : m_cur_store(NULL), m_cur_comp(NULL) {};
DNALoader::~DNALoader(void) {};

void DNALoader::show_error(const string& error)
{
	// To do: use notify
	cerr << "DNALoader(error): " << error << endl;
	m_had_error = true;
}

void DNALoader::handle_storage_data(DatagramIterator& dgi)
{
	//catalog codes
	unsigned short num_roots = dgi.get_uint16();
    for (unsigned short i = 0; i < num_roots; i++)
	{
		string root = dgi_extract_string8(dgi);

		unsigned short num_codes = dgi.get_uint8();
		for (unsigned short j = 0; j < num_codes; j++)
		{
			string code = dgi_extract_string8(dgi);
			m_cur_store->store_catalog_code(root, code);
		};
	};

	// textures
	unsigned short num_textures = dgi.get_uint16();
	for (unsigned short i = 0; i < num_textures; i++)
	{
		string code = dgi_extract_string8(dgi);
		string filename = dgi_extract_string8(dgi);
		
		if (!vfs->exists(filename))
		{
			stringstream ss;
			ss << "Cannot find texture " << filename << " in the vfs!";
			show_error(ss.str());
			return;
		};

		PT(Texture) t = TexturePool::load_texture(filename);
		m_cur_store->store_texture(code, t);
	};

	//fonts
	unsigned short num_fonts = dgi.get_uint16();
	for (unsigned short i = 0; i < num_fonts; i++)
	{
		string code = dgi_extract_string8(dgi);
		string filename = dgi_extract_string8(dgi);
		
		if (!vfs->exists(filename))
		{
			stringstream ss;
			ss << "Cannot find font " << filename << " in the vfs!";
			show_error(ss.str());
			return;
		};

		PT(TextFont) f = FontPool::load_font(filename);
		m_cur_store->store_font(code, f);
	};

	// nodes
	unsigned short num_nodes = dgi.get_uint16();
	for (unsigned short i = 0; i < num_nodes; i++)
	{
		string code = dgi_extract_string8(dgi);
		string filename = dgi_extract_string8(dgi);
		string search = dgi_extract_string8(dgi);

		if (!ModelPool::verify_model(filename))
		{
			stringstream ss;
			ss << "Cannot find node filename " << filename << " in the vfs!";
			show_error(ss.str());
			return;
		};

		NodePath* np;

		bool has_search = (strcmp(search.c_str(), "") == 1);
		
		if (!has_search)
		{
			ModelRoot* model = ModelPool::load_model(filename);
			np = new NodePath(model);
		}

		else
		{
			ModelRoot* model = ModelPool::load_model(filename);
			NodePath temp_np = NodePath(model);

			stringstream ss;
			ss << "**/" << search;
			search = ss.str();

			NodePath result = temp_np.find(search);

			if (result.is_empty())
			{
				stringstream ss;
				ss << "Can't find the search (" << search << ") of node " << filename;
				show_error(ss.str());
				return;
			}
			
			else
			{
				np = new NodePath(result);
				temp_np.remove_node();
			}
		};

		m_cur_store->store_node(code, np);
	};

	// hood nodes
	unsigned short num_hood_nodes = dgi.get_uint16();
	for (unsigned short i = 0; i < num_hood_nodes; i++)
	{
		string code = dgi_extract_string8(dgi);
		string filename = dgi_extract_string8(dgi);
		string search = dgi_extract_string8(dgi);

		if (!ModelPool::verify_model(filename))
		{
			stringstream ss;
			ss << "Cannot find hood node filename " << filename << " in the vfs!";
			show_error(ss.str());
			return;
		};

		NodePath* np;

		bool has_search = (strcmp(search.c_str(), "") == 1);
		
		if (!has_search)
		{
			ModelRoot* model = ModelPool::load_model(filename);
			np = new NodePath(model);
		}

		else
		{
			ModelRoot* model = ModelPool::load_model(filename);
			NodePath temp_np = NodePath(model);

			stringstream ss;
			ss << "**/" << search;
			search = ss.str();

			NodePath result = temp_np.find(search);

			if (result.is_empty())
			{
				stringstream ss;
				ss << "Can't find the search (" << search << ") of hood node " << filename;
				show_error(ss.str());
				return;
			}
			
			else
			{
				np = new NodePath(result);
				temp_np.remove_node();
			}
		};

		m_cur_store->store_hood_node(code, np);
	};

	// place nodes
	unsigned short num_place_nodes = dgi.get_uint16();
	for (unsigned short i = 0; i < num_place_nodes; i++)
	{
		string code = dgi_extract_string8(dgi);
		string filename = dgi_extract_string8(dgi);
		string search = dgi_extract_string8(dgi);

		if (!ModelPool::verify_model(filename))
		{
			stringstream ss;
			ss << "Cannot find place node filename " << filename << " in the vfs!";
			show_error(ss.str());
			return;
		};

		NodePath* np;

		bool has_search = (strcmp(search.c_str(), "") == 1);
		
		if (!has_search)
		{
			ModelRoot* model = ModelPool::load_model(filename);
			np = new NodePath(model);
		}

		else
		{
			ModelRoot* model = ModelPool::load_model(filename);
			NodePath temp_np = NodePath(model);

			stringstream ss;
			ss << "**/" << search;
			search = ss.str();

			NodePath result = temp_np.find(search);

			if (result.is_empty())
			{
				stringstream ss;
				ss << "Can't find the search (" << search << ") of place node " << filename;
				show_error(ss.str());
				return;
			}
			
			else
			{
				np = new NodePath(result);
				temp_np.remove_node();
			}
		};

		m_cur_store->store_place_node(code, np);
	};

	// blocks
	unsigned short num_bldgs = dgi.get_uint16();
	for (unsigned short i = 0; i < num_bldgs; i++)
	{
		unsigned char number = dgi.get_uint8();
		unsigned short zone = dgi.get_uint16();
		string title = dgi_extract_string8(dgi);
		string article = dgi_extract_string8(dgi);
		string bldg_type = dgi_extract_string8(dgi);
		m_cur_store->store_block(number, title, article, bldg_type, zone);
	};

	// suit points
	unsigned short num_points = dgi.get_uint16();
	for (unsigned short i = 0; i < num_points; i++)
	{
		unsigned short index = dgi.get_uint16();
		unsigned char point_type = dgi.get_uint8();

		int x = dgi.get_int32();
		int y = dgi.get_int32();
		int z = dgi.get_int32();

		unsigned char graph = dgi.get_uint8();
		char landmark_building_index = dgi.get_int8();

		m_cur_store->store_suit_point(index, point_type, new LVector3f(x / 100.0, y / 100.0, z / 100.0),
									  landmark_building_index);
	};

	// suit edges
	unsigned short num_edges = dgi.get_uint16();
	for (unsigned short i = 0; i < num_edges; i++)
	{
		unsigned short index = dgi.get_uint16();
		unsigned short num_points = dgi.get_uint16();
		for (unsigned short j = 0; j < num_points; j++)
		{
			unsigned short end_point = dgi.get_uint16();
			unsigned short zone_id = dgi.get_uint16();
			m_cur_store->store_suit_edge(index, index, end_point, zone_id);
		};
	};

	// battle cells
	unsigned short num_cells = dgi.get_uint16();
	for (unsigned short i = 0; i < num_cells; i++)
	{
		unsigned char w = dgi.get_uint8();
		unsigned char h = dgi.get_uint8();

		int x = dgi.get_int32();
		int y = dgi.get_int32();
		int z = dgi.get_int32();

		m_cur_store->store_battle_cell(w, h, new LVector3f(x / 100.0, y / 100.0, z / 100.0));
	};
};

// handlers
void DNALoader::handle_comp_group(DatagramIterator& dgi)
{
	DNAGroup* new_group = new DNAGroup("group");
	new_group->make_from_dgi(dgi, m_cur_store);
	if (m_cur_comp != NULL) // top group
	{
		new_group->set_parent(m_cur_comp);
	};
	m_cur_comp = new_group;
};

void DNALoader::handle_comp_visgroup(DatagramIterator& dgi)
{
	DNAVisGroup* new_visgroup = new DNAVisGroup("visgroup");
	new_visgroup->make_from_dgi(dgi, m_cur_store);
	new_visgroup->set_parent(m_cur_comp);
	m_cur_comp = new_visgroup;
};

void DNALoader::handle_comp_node(DatagramIterator& dgi)
{
	DNANode* new_node = new DNANode("node");
	new_node->make_from_dgi(dgi, m_cur_store);
	new_node->set_parent(m_cur_comp);
	m_cur_comp = new_node;
};

void DNALoader::handle_comp_prop(DatagramIterator& dgi)
{
	DNAProp* new_prop = new DNAProp("prop");
	new_prop->make_from_dgi(dgi, m_cur_store);
	new_prop->set_parent(m_cur_comp);
	m_cur_comp = new_prop;
};

void DNALoader::handle_comp_sign(DatagramIterator& dgi)
{
	DNASign* new_sign = new DNASign("sign");
	new_sign->make_from_dgi(dgi, m_cur_store);
	new_sign->set_parent(m_cur_comp);
	m_cur_comp = new_sign;
};

void DNALoader::handle_comp_sign_baseline(DatagramIterator& dgi)
{
	DNASignBaseline* new_sign_baseline = new DNASignBaseline("sign");
	new_sign_baseline->make_from_dgi(dgi, m_cur_store);
	new_sign_baseline->set_parent(m_cur_comp);
	m_cur_comp = new_sign_baseline;
};

void DNALoader::handle_comp_sign_text(DatagramIterator& dgi)
{
	DNASignText* new_sign_text = new DNASignText("sign");
	new_sign_text->make_from_dgi(dgi, m_cur_store);
	new_sign_text->set_parent(m_cur_comp);
};

void DNALoader::handle_comp_sign_graphic(DatagramIterator& dgi)
{
	DNASignGraphic* new_sign_graphic = new DNASignGraphic("sign");
	new_sign_graphic->make_from_dgi(dgi, m_cur_store);
	new_sign_graphic->set_parent(m_cur_comp);
	m_cur_comp = new_sign_graphic;
};

void DNALoader::handle_comp_flatbldg(DatagramIterator& dgi)
{
	DNAFlatBuilding* new_flatbldg = new DNAFlatBuilding("flatbldg");
	new_flatbldg->make_from_dgi(dgi, m_cur_store);
	new_flatbldg->set_parent(m_cur_comp);
	m_cur_comp = new_flatbldg;
};

void DNALoader::handle_comp_wall(DatagramIterator& dgi)
{
	DNAWall* new_wall = new DNAWall("wall");
	new_wall->make_from_dgi(dgi, m_cur_store);
	new_wall->set_parent(m_cur_comp);
	m_cur_comp = new_wall;
};

void DNALoader::handle_comp_windows(DatagramIterator& dgi)
{
	DNAWindows* new_windows = new DNAWindows("windows");
	new_windows->make_from_dgi(dgi, m_cur_store);
	new_windows->set_parent(m_cur_comp);
};

void DNALoader::handle_comp_cornice(DatagramIterator& dgi)
{
	DNACornice* new_cornice = new DNACornice("cornice");
	new_cornice->make_from_dgi(dgi, m_cur_store);
	new_cornice->set_parent(m_cur_comp);
};

void DNALoader::handle_comp_landmark_bldg(DatagramIterator& dgi)
{
	DNALandmarkBuilding* new_bldg = new DNALandmarkBuilding("bldg");
	new_bldg->make_from_dgi(dgi, m_cur_store);
	new_bldg->set_parent(m_cur_comp);
	m_cur_comp = new_bldg;
};

void DNALoader::handle_comp_anim_prop(DatagramIterator& dgi)
{
	DNAAnimProp* new_anim_prop = new DNAAnimProp("anim_prop");
	new_anim_prop->make_from_dgi(dgi, m_cur_store);
	new_anim_prop->set_parent(m_cur_comp);
	m_cur_comp = new_anim_prop;
};

void DNALoader::handle_comp_interactive_prop(DatagramIterator& dgi)
{
	DNAInteractiveProp* new_inter_prop = new DNAInteractiveProp("anim_prop");
	new_inter_prop->make_from_dgi(dgi, m_cur_store);
	new_inter_prop->set_parent(m_cur_comp);
	m_cur_comp = new_inter_prop;
};

void DNALoader::handle_comp_door(DatagramIterator& dgi)
{
	DNADoor* new_door = new DNADoor("door");
	new_door->make_from_dgi(dgi, m_cur_store);
	new_door->set_parent(m_cur_comp);
};

void DNALoader::handle_comp_flatdoor(DatagramIterator& dgi)
{
	DNAFlatDoor* new_door = new DNAFlatDoor("flatdoor");
	new_door->make_from_dgi(dgi, m_cur_store);
	new_door->set_parent(m_cur_comp);
};

void DNALoader::handle_comp_street(DatagramIterator& dgi)
{
	DNAStreet* new_street = new DNAStreet("street");
	new_street->make_from_dgi(dgi, m_cur_store);
	new_street->set_parent(m_cur_comp);
};

void DNALoader::handle_comp_data(DatagramIterator& dgi)
{
	unsigned char prop_code = dgi.get_uint8();
	switch (prop_code)
	{
		case PROPCODE_GROUP: // 1
			handle_comp_group(dgi);
			break;

		case PROPCODE_VISGROUP: // 2
			handle_comp_visgroup(dgi);
			break;

		case PROPCODE_NODE: // 3
			handle_comp_node(dgi);
			break;

		case PROPCODE_PROP: // 4
			handle_comp_prop(dgi);
			break;

		case PROPCODE_SIGN: // 5
			handle_comp_sign(dgi);
			break;

		case PROPCODE_SIGN_BASELINE: // 6
			handle_comp_sign_baseline(dgi);
			break;

		case PROPCODE_SIGN_TEXT: // 7
			handle_comp_sign_text(dgi);
			break;
		
		case PROPCODE_SIGN_GRAPHIC: // 8
			handle_comp_sign_graphic(dgi);
			break;

		case PROPCODE_FLAT_BUILDING: // 9
			handle_comp_flatbldg(dgi);
			break;

		case PROPCODE_WALL: // 10
			handle_comp_wall(dgi);
			break;

		case PROPCODE_WINDOWS: // 11
			handle_comp_windows(dgi);
			break;

		case PROPCODE_CORNICE: // 12
			handle_comp_cornice(dgi);
			break;

		case PROPCODE_LANDMARK_BUILDING: // 13
			handle_comp_landmark_bldg(dgi);
			break;

		case PROPCODE_ANIM_PROP: // 14
			handle_comp_anim_prop(dgi);
			break;

		case PROPCODE_INTERACTIVE_PROP: // 15
			handle_comp_interactive_prop(dgi);
			break;

		case PROPCODE_DOOR: // 17
			handle_comp_door(dgi);
			break;

		case PROPCODE_FLAT_DOOR: // 18
			handle_comp_flatdoor(dgi);
			break;

		case PROPCODE_STREET: //19
			handle_comp_street(dgi);
			break;

		case PROPCODE_SPECIAL_LEVEL_UP: // 255
			if (m_cur_comp->get_parent() != NULL)
			{
				m_cur_comp = m_cur_comp->get_parent();
			};
			break;

		default:
			stringstream ss;
			ss << "Invalid prop code " << (int)prop_code;
			show_error(ss.str());
			return;
	};

	if (dgi.get_remaining_size())
	{
		handle_comp_data(dgi);
	};
};

// To do: this should return PandaNode
// but interrogate crashes!
NodePath DNALoader::load_DNA_file(DNAStorage& store, const Filename &name)
{
	string temp;
	if (!vfs->read_file(name, temp, true))
	{
		throw new string("failure");
	};

	// Read the data
	m_cur_store = &store;
	m_had_error = false;
	Datagram dg = Datagram(temp);
	DatagramIterator dgi = DatagramIterator(dg, 0);

	// Header
	string header = dgi.extract_bytes(5);

	if (strcmp(header.c_str(), "PDNA\n") != 0)
	{
		stringstream ss;
		ss << "Bad header: " << header;
		show_error(ss.str().c_str());
		throw new string("failure");
	};

	bool compressed = dgi.get_bool();
	if (compressed)
	{
		show_error("Compressed files are not supported yet!");
		throw new string("failure");
	};

	dgi.skip_bytes(1); //ignore extra \n (part of the header)

	// DNAStorage data

	handle_storage_data(dgi);
	if (m_had_error)
	{
		show_error("had error reading storage data");
		throw new string("failure");
	};

	handle_comp_data(dgi);
	if (m_had_error)
	{
		show_error("had error reading component data");
		throw new string("failure");
	};

	if (dgi.get_remaining_bytes().size() > 0)
	{
		show_error("the data was not totally used");
		throw new string("failure");
	};
	
	NodePath np = NodePath("dna");
	m_cur_comp->traverse(np, m_cur_store);

	m_cur_store = NULL;

	return np;
};
