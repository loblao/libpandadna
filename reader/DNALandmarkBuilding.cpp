#include "DNALandmarkBuilding.h"

DNALandmarkBuilding::DNALandmarkBuilding(string name) : DNANode(name), m_wall_color(new LVector4f(1)) {}
DNALandmarkBuilding::~DNALandmarkBuilding(void) {}

void DNALandmarkBuilding::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
	DNANode::make_from_dgi(dgi, store);
	m_code = dgi_extract_string8(dgi);
	m_wall_color = dgi_extract_color(dgi);
	m_title = dgi_extract_string8(dgi);
	m_article = dgi_extract_string8(dgi);
	m_building_type = dgi_extract_string8(dgi);
};

void DNALandmarkBuilding::traverse(NodePath& np, DNAStorage* store)
{
	NodePath* result = store->find_node(m_code);
	if (result->is_empty())
	{
		stringstream ss;
		ss << "code " << m_code << " not found in storage!";
		cerr << "DNALandmarkBuilding(fatal): " << ss.str() << endl;
		throw ss.str();
	}

	NodePath _np = result->copy_to(np);
	_np.set_name(m_name);

	_np.set_pos(*m_pos);
	_np.set_hpr(*m_hpr);
	_np.set_scale(*m_scale);

	setup_suit_building_origin(np, _np);

	for (comp_vec_t::iterator child = m_children.begin(); child != m_children.end(); child++)
	{
        (*child)->traverse(_np, store);
	};

	_np.flatten_strong();
};

void DNALandmarkBuilding::setup_suit_building_origin(NodePath a, NodePath b)
{
	locale loc;
	bool is_tb = (m_name.substr(0, 2) == "tb");
	bool is_digit = (string(1, m_name.at(2)).find_first_not_of("0123456789") == std::string::npos);
	bool has_colon = (m_name.find(':') != string::npos);
	if (is_tb && is_digit && has_colon)
	{
		stringstream ss;
		ss << "s" << m_name.substr(1);
		string name = ss.str();

		NodePath node = b.find("**/*suit_building_origin");
		if (node.is_empty())
		{
			cout << "DNALandmarkBuilding " << name << " did not find **/*suit_building_origin" << endl;
			node = a.attach_new_node(name);
			node.set_pos(*m_pos);
			node.set_hpr(*m_hpr);
			node.set_scale(*m_scale);
		}

		else
		{
			node.wrt_reparent_to(a);
			node.set_name(name);
		}
	}

	else
	{
		cout << "DNALandmarkBuilding " << m_name << " does not match needed conditions to setup suit origin" << endl;
	};
};

void DNALandmarkBuilding::set_article(const string& article)
{
	m_article = article;
};

string DNALandmarkBuilding::get_article()
{
	return m_article;
};

void DNALandmarkBuilding::set_building_type(const string& building_type)
{
	m_building_type = building_type;
};

string DNALandmarkBuilding::get_building_type()
{
	return m_building_type;
};

void DNALandmarkBuilding::set_title(const string& title)
{
	m_title = title;
};

string DNALandmarkBuilding::get_title()
{
	return m_title;
};

void DNALandmarkBuilding::set_code(const string& code)
{
	m_code = code;
};

string DNALandmarkBuilding::get_code()
{
	return m_code;
};

void DNALandmarkBuilding::set_wall_color(LVector4f* color)
{
	m_wall_color = color;
};

LVector4f* DNALandmarkBuilding::get_wall_color()
{
	return m_wall_color;
};
