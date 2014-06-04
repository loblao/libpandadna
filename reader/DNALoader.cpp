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

		m_cur_store->store_suit_point(index, point_type, new LVector3f(x / 100, y / 100, z / 100), landmark_building_index);
	};

	// suit edges
	unsigned short num_edges = dgi.get_uint16();
	for (unsigned short i = 0; i < num_edges; i++)
	{
		unsigned short index = dgi.get_uint16();
		unsigned num_points = dgi.get_uint16();
		for (unsigned short j = 0; j < num_points; j++)
		{
			unsigned short start_point = dgi.get_uint16();
			unsigned short end_point = dgi.get_uint16();
			unsigned short zone_id = dgi.get_uint16();
			m_cur_store->store_suit_edge(index, start_point, end_point, zone_id);
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

		m_cur_store->store_battle_cell(w, h, new LVector3f(x / 100, y / 100, z / 100));
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

void DNALoader::handle_comp_wall(DatagramIterator& dgi)
{
	DNAWall* new_wall = new DNAWall("wall");
	new_wall->make_from_dgi(dgi, m_cur_store);
	new_wall->set_parent(m_cur_comp);
	m_cur_comp = new_wall;
};


void DNALoader::handle_comp_flatbldg(DatagramIterator& dgi)
{
	DNAFlatBuilding* new_flatbldg = new DNAFlatBuilding("flatbldg");
	new_flatbldg->make_from_dgi(dgi, m_cur_store);
	new_flatbldg->set_parent(m_cur_comp);
	m_cur_comp = new_flatbldg;
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

		case PROPCODE_FLAT_BUILDING: // 9
			handle_comp_flatbldg(dgi);
			break;

		case PROPCODE_WALL: // 10
			handle_comp_wall(dgi);
			break;

		case PROPCODE_STREET: //19
			handle_comp_street(dgi);
			break;

		case PROPCODE_SPECIAL_LEVEL_UP: // 255
			m_cur_comp = m_cur_comp->get_parent();
			break;

		default:
			stringstream ss;
			ss << "Invalid prop code " << (int)prop_code;
			show_error(ss.str());
			return;
	};

	if (dgi.get_remaining_size())
	{
		cout << "recursive call: ";
		cout << m_cur_comp->get_name() << endl;
		handle_comp_data(dgi);
	};
};

// To do: return PandaNode
string DNALoader::load_DNA_file(DNAStorage& store, const Filename &name)
{	
	string temp;
	if (!vfs->read_file(name, temp, true))
	{
		return "failure (unable to read)";
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
		return "failure (bad header)";
	};

	bool compressed = dgi.get_bool();
	if (compressed)
	{
		show_error("Compressed files are not supported yet!");
		return "failure (compressed)";
	};

	dgi.skip_bytes(1); //ignore extra \n (part of the header)

	// DNAStorage data
	dgi.skip_bytes(4);

	handle_storage_data(dgi);
	if (m_had_error)
	{
		return "failure (had error reading storage data)";
	}

	handle_comp_data(dgi);

	return dgi.get_remaining_bytes();
};
