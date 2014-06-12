// warning: this is extremely broken atm
// a lot of debug stuff have been left behind

#include "DNASignBaseline.h"
#include <nodePath.h>
#include <textNode.h>
#include <nodePathCollection.h>

#define M_PI 3.14159265358979323846  /* pi */

#include "DNASignText.h"

DNASignBaseline::DNASignBaseline(string name) : DNANode(name) {}
DNASignBaseline::~DNASignBaseline(void) {}

void DNASignBaseline::make_from_dgi(DatagramIterator &dgi, DNAStorage *store)
{
	DNANode::make_from_dgi(dgi, store);
	m_code = dgi_extract_string8(dgi);
	m_color = dgi_extract_color(dgi);
	m_font = dgi_extract_string8(dgi);
	m_flags = dgi_extract_string8(dgi);
	m_indent = dgi.get_float64();
    m_kern = dgi.get_float64();
	m_wiggle = dgi.get_float64();
	m_stumble = dgi.get_float64();
	m_stomp = dgi.get_float64();
	m_width = dgi.get_float64();
	m_height = dgi.get_float64();
};

void DNASignBaseline::traverse(NodePath np, DNAStorage* store)
{
	NodePath _np = np.attach_new_node("baseline");
	_np.set_pos(*m_pos);
	_np.set_hpr(*m_hpr);
	_np.set_depth_offset(50);

	vector<string> texts;

	for (comp_vec_t::iterator child = m_children.begin(); child != m_children.end(); child++)
	{
		if ((*child)->is_sign_text())
		{
			texts.push_back((reinterpret_cast<DNASignText*>(*child))->get_letters());
		}

		else
		{
			(*child)->traverse(_np, store);
		};
	};

	NodePath root = NodePath("text_root");

	float x = 0.0;
	unsigned int i = 0;
	for (vector<string>::iterator text = texts.begin(); text != texts.end(); text++)
	{
		PT(TextNode) tn = new TextNode("text");
		tn->set_text(*text);
		TextFont* font = store->find_font(m_code);
		tn->set_font(font);

		bool has_big_flag = (i == 0) ? (m_flags.find('b') != string::npos) : false;

		NodePath text_np = root.attach_new_node(tn);
		text_np.set_scale(*m_scale);
        text_np.set_depth_write(false);

		if (has_big_flag)
		{
			text_np.set_scale(text_np, 1.5);
		};

		if (i % 2)
		{
			text_np.set_pos(x + m_stumble, 0, m_stomp);
			text_np.set_r(-m_wiggle);
		}

		else
		{
			text_np.set_pos(x - m_stumble, 0, -m_stomp);
			text_np.set_r(m_wiggle);
		};

		float n = text_np.get_sx() / (has_big_flag ? 1.5 : 1.0);
		x += m_kern + tn->get_width() * n;
		//cout << i << " " << has_big_flag << "! " << x << " @ " << m_kern << << " / " << n << endl;
		i++;
	};

	//cout << i << ": x is " << x << ";" << texts.size() << endl;

	unsigned short num_children = root.get_num_children();
	for (i = 0; i < num_children; i++)
	{
		NodePath c = root.get_child(i);
		c.set_x(c.get_x() - x / 2.0);
	};

	if ((m_width != 0.0) && (m_height != 0.0))
	{
		curve(root, num_children);
	};

	NodePathCollection npc = root.find_all_matches("**/+TextNode");
	num_children = npc.get_num_paths();
	for (i = 0; i < num_children; i++)
	{
		NodePath node = npc.get_path(i);
		PT(TextNode) tn = (TextNode*)node.node();
		NodePath np2 = node.get_parent().attach_new_node(tn->generate());
		np2.set_transform(node.get_transform());
		np2.set_color_scale(*m_color, 1);
		node.remove_node();
	};

	root.flatten_strong();
	if (root.get_num_children() > 0)
	{
		root.get_child(0).reparent_to(_np);
	};
};

void DNASignBaseline::curve(NodePath& root, unsigned short num_children)
{
	// doesnt work
	for (short i = 0; i < num_children; i++)
	{
		NodePath node = root.get_child(i);
		
		float theta = node.get_x() / (m_height / 2.0);
		float deviation = node.get_y();

		theta += m_indent * M_PI / 180.0;

		float x = sin(theta) * (m_width / 2.0);
		float y = (cos(theta) - 1) * (m_height / 2.0);

		float radius = hypot(x, y);

		x *= (radius+deviation) / radius;
		y *= (radius+deviation) / radius;

		if (DNASignBaseline::_index < 0) // do not actually curve (broken!)
		{
			cout << "EL " << DNASignBaseline::_index++ << ": nx=" << node.get_x() << " x=" << x << " y=" << y << " a=" << theta;
			cout << " r=" << radius << " h=" << m_height << " w=" << m_width << endl;

			root.set_pos(x, 0, y);
			root.set_r(root, theta * 180.0 / M_PI);
		};
	};
};

int DNASignBaseline::_index = 0;
