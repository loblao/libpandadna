#include "DNAWindows.h"

DNAWindows::DNAWindows(string name) : DNAGroup(name), m_color(new LVector4f(1)) {}
DNAWindows::~DNAWindows(void) {}

void DNAWindows::make_from_dgi(DatagramIterator &dgi, DNAStorage *store)
{
	DNAGroup::make_from_dgi(dgi, store);
	m_code = dgi_extract_string8(dgi);
	m_color = dgi_extract_color(dgi);
	m_window_count = dgi.get_uint8();
};

void DNAWindows::traverse(NodePath& np, DNAStorage* store)
{
	if (m_window_count == 0)
	{
		return;
	}

	float parent_x = np.get_parent().get_scale().get_x();
	float scale = fmod(rand(), .0375);

	if (parent_x <= 5.0)
	{
		scale += 1.0;
	}

	else if (parent_x <= 10.0)
	{
		scale += 1.15;
	}

	else
	{
		scale += 1.3;
	}

	float offset = fmod(rand(), .0375);

	if (m_window_count == 1)
	{
		make_windows(offset + .5, offset + .5, np, m_color, scale, store);
	}

	else if (m_window_count == 2)
	{
		make_windows(offset + .33, offset + .5, np, m_color, scale, store);
		make_windows(offset + .66, offset + .5, np, m_color, scale, store, true);
	}

	else if (m_window_count == 3)
	{
		make_windows(offset + .33, offset + .66, np, m_color, scale, store);
		make_windows(offset + .66, offset + .66, np, m_color, scale, store, true);
		make_windows(offset + .5, offset + .66, np, m_color, scale, store);
	}

	else if (m_window_count == 4)
	{
		make_windows(offset + .33, offset + .25, np, m_color, scale, store);
		make_windows(offset + .66, offset + .25, np, m_color, scale, store, true);
		make_windows(offset + .33, offset + .66, np, m_color, scale, store);
		make_windows(offset + .66, offset + .66, np, m_color, scale, store, true);
	}

	else
	{
		cerr << "Invalid window count " << m_window_count << endl;
		throw string("bad window count");
	};
};

void DNAWindows::make_windows(float x, float z, NodePath parent_node, LVector4f* color,
							  float scale, DNAStorage* store, bool flip)

{
	string stripped = m_code.substr(0, m_code.size() - 1);
	stringstream ss;
	ss << stripped;

	NodePath* node;
	if (flip)
	{
		ss << "l";
		node = store->find_node(ss.str());
	}

	else
	{
		ss << "r";
		node = store->find_node(ss.str());
	}

	NodePath window = node->copy_to(parent_node);
	window.set_color(*color);
	window.set_scale(NodePath(), scale);
	window.set_pos(x, 0, z);
};

void DNAWindows::set_code(const string& code)
{
	m_code = code;
};

string DNAWindows::get_code()
{
	return m_code;
};

void DNAWindows::set_color(LVector4f* color)
{
	m_color = color;
};

LVector4f* DNAWindows::get_color()
{
	return m_color;
};

void DNAWindows::set_window_count(unsigned short count)
{
	m_window_count = count;
};

unsigned short DNAWindows::get_window_count()
{
	return m_window_count;
};
