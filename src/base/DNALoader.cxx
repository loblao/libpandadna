#include "DNALoader.h"

#include "DNAVisGroup.h"
#include "DNANode.h"
#include "DNAProp.h"
#include "DNASign.h"
#include "DNASignBaseline.h"
#include "DNASignText.h"
#include "DNASignGraphic.h"
#include "DNAWall.h"
#include "DNAWindows.h"
#include "DNALandmarkBuilding.h"
#include "DNAFlatBuilding.h"
#include "DNAData.h"
#include "DNADoor.h"
#include "DNAFlatDoor.h"
#include "DNAStreet.h"
#include "DNAAnimBuilding.h"
#include "DNAAnimProp.h"
#include "DNAInteractiveProp.h"
#include "DNACornice.h"

#include "dnaLexerDefs.h"
#include "dnaParserDefs.h"

#include "texturePool.h"
#include "fontPool.h"
#include "virtualFileSystem.h"
#include "compress_string.h"

DNALoader::DNALoader(): m_cur_comp(nullptr), m_cur_store(nullptr)
{
}

DNALoader::~DNALoader()
{
}

NodePath DNALoader::load_DNA_file(DNAStorage* store, const Filename& file)
{
    load_DNA_file_base(store, file);
    dna_cat.debug() << "load_DNA_file_base completed" << std::endl;

    if (!m_cur_comp)
        return NodePath(); // Empty NodePath

    NodePath np = NodePath("dna");
    m_cur_comp->traverse(np, m_cur_store);

    m_cur_store = nullptr;
    m_cur_comp = nullptr;

    return np;
}

PT(DNAGroup) DNALoader::load_DNA_file_AI(DNAStorage* store, const Filename& file)
{
    load_DNA_file_base(store, file);
    dna_cat.debug() << "load_DNA_file_base completed" << std::endl;
    m_cur_store = nullptr;
    return m_cur_comp;
}

void DNALoader::handle_storage_data(DatagramIterator& dgi)
{
    unsigned short i;

    // Catalog codes
    unsigned short num_roots = dgi.get_uint16();
    std::string root;
    for (i = 0; i < num_roots; i++)
    {
        root = dgi.get_string();
        unsigned char num_codes = dgi.get_uint8();
        for (unsigned short j = 0; j < num_codes; j++)
            m_cur_store->store_catalog_code(root, dgi.get_string());
    }

    // Textures
    unsigned short num_textures = dgi.get_uint16();
    for (i = 0; i < num_textures; i++)
    {
        std::string code, filename;
        code = dgi.get_string();
        filename = dgi.get_string();
        m_cur_store->store_texture(code, TexturePool::load_texture(filename));
    }

    // Fonts
    unsigned short num_fonts = dgi.get_uint16();
    for (i = 0; i < num_fonts; i++)
    {
        std::string code, filename;
        code = dgi.get_string();
        filename = dgi.get_string();
        m_cur_store->store_font(code, FontPool::load_font(filename), filename);
    }

    // Nodes
    unsigned short num_nodes;

    num_nodes = dgi.get_uint16();
    for (i = 0; i < num_nodes; i++)
    {
        std::string filename, code, search;
        code = dgi.get_string();
        filename = dgi.get_string();
        search = dgi.get_string();
        m_cur_store->store_node(filename, search, code);
    }

    num_nodes = dgi.get_uint16();
    for (i = 0; i < num_nodes; i++)
    {
        std::string filename, code, search;
        code = dgi.get_string();
        filename = dgi.get_string();
        search = dgi.get_string();
        m_cur_store->store_hood_node(filename, search, code);
    }

    num_nodes = dgi.get_uint16();
    for (i = 0; i < num_nodes; i++)
    {
        std::string filename, code, search;
        code = dgi.get_string();
        filename = dgi.get_string();
        search = dgi.get_string();
        m_cur_store->store_place_node(filename, search, code);
    }

    // Blocks
    unsigned short num_blocks = dgi.get_uint16();
    for (i = 0; i < num_blocks; i++)
    {
        block_number_t number = dgi.get_uint8();
        zone_id_t zone = dgi.get_uint16();
        std::string title = dgi.get_string();
        std::string article = dgi.get_string();
        std::string bldg_type = dgi.get_string();

        m_cur_store->store_block(number, title, article, bldg_type, zone);
    }

    // Suit points
    unsigned short num_points = dgi.get_uint16();
    for (i = 0; i < num_points; i++)
    {
        point_index_t index = dgi.get_uint16();
        DNASuitPoint::PointType point_type = (DNASuitPoint::PointType)dgi.get_uint8();

        float x, y, z;
        x = dgi.get_int32() / 100.0;
        y = dgi.get_int32() / 100.0;
        z = dgi.get_int32() / 100.0;
        LPoint3f pos(x, y, z);
        block_number_t landmark_building_index = dgi.get_int16();

        m_cur_store->store_suit_point(new DNASuitPoint(index, point_type, pos,
                                                       landmark_building_index));
    }

    // Suit edges
    unsigned short num_edges = dgi.get_uint16();
    for (i = 0; i < num_edges; i++)
    {
        point_index_t index = dgi.get_uint16();
        point_index_t num_points = dgi.get_uint16();

        for (unsigned short j = 0; j < num_points; j++)
        {
            point_index_t end_point = dgi.get_uint16();
            zone_id_t zone_id = dgi.get_uint16();
            m_cur_store->store_suit_edge(index, end_point, zone_id);
        }
    }
}

#define ADDCASE(CODE, CLASS) case CODE:{new_comp=new CLASS("unnamed_comp");dna_cat.debug()<<#CLASS<<std::endl;};break;

void DNALoader::handle_comp_data(DatagramIterator& dgi)
{
    while(dgi.get_remaining_size())
    {
        unsigned char comp_code = dgi.get_uint8();
        dna_cat.debug() << "code " << (int)comp_code << std::endl;
        PT(DNAGroup) new_comp;
        if (comp_code == COMPCODE_RETURN)
        {
            nassertv(m_cur_comp != nullptr);
            dna_cat.debug() << "COMPCODE_RETURN:" << std::endl;
            PT(DNAGroup) p = m_cur_comp->get_parent();
            dna_cat.debug() << "    current: " << m_cur_comp->get_name()
                            << ", new: " << (p ? p->get_name() : "nullptr") << std::endl;
            if (p != nullptr)
                m_cur_comp = p;

            else
            {
                nassertv(m_cur_comp->get_name() == "root");
            }
        }

        else
        {
            switch (comp_code)
            {
                ADDCASE(COMPCODE_GROUP, DNAGroup)
                case COMPCODE_VISGROUP:
                {
                    new_comp = new DNAVisGroup("unnamed_comp");
                    dna_cat.debug() << "DNAVisGroup" << std::endl;
                    m_cur_store->store_DNA_vis_group(DCAST(DNAVisGroup, new_comp));
                }; break;
                ADDCASE(COMPCODE_NODE, DNANode)
                ADDCASE(COMPCODE_PROP, DNAProp)
                ADDCASE(COMPCODE_SIGN, DNASign)
                ADDCASE(COMPCODE_SIGN_BASELINE, DNASignBaseline)
                ADDCASE(COMPCODE_SIGN_TEXT, DNASignText)
                ADDCASE(COMPCODE_SIGN_GRAPHIC, DNASignGraphic)
                ADDCASE(COMPCODE_FLAT_BUILDING, DNAFlatBuilding)
                ADDCASE(COMPCODE_WALL, DNAWall)
                ADDCASE(COMPCODE_WINDOWS, DNAWindows)
                ADDCASE(COMPCODE_CORNICE, DNACornice)
                ADDCASE(COMPCODE_LANDMARK_BUILDING, DNALandmarkBuilding)
                ADDCASE(COMPCODE_ANIM_PROP, DNAAnimProp)
                ADDCASE(COMPCODE_INTERACTIVE_PROP, DNAInteractiveProp)
                ADDCASE(COMPCODE_ANIM_BUILDING, DNAAnimBuilding)
                ADDCASE(COMPCODE_DOOR, DNADoor)
                ADDCASE(COMPCODE_FLAT_DOOR, DNAFlatDoor)
                ADDCASE(COMPCODE_STREET, DNAStreet)

                default:
                {
                    dna_cat.fatal() << "invalid comp code: " << (int)comp_code << std::endl;
                    return;
                }; break;
            }

            new_comp->make_from_dgi(dgi, m_cur_store);
            dna_cat.debug() << "    new comp name: " << new_comp->get_name() << std::endl;
            dna_cat.debug() << "make_from_dgi completed" << std::endl;

            if (m_cur_comp)
            {
                dna_cat.debug() << "setting parent" << std::endl;
                new_comp->set_parent(m_cur_comp);
                m_cur_comp->add(new_comp);
                dna_cat.debug() << "setting parent done" << std::endl;
            }

            if (!new_comp->is_of_type(DNAWindows::get_class_type())
                && !new_comp->is_of_type(DNACornice::get_class_type())
                && !new_comp->is_of_type(DNADoor::get_class_type())
                && !new_comp->is_of_type(DNAStreet::get_class_type()))
            {
                m_cur_comp = new_comp;
            }
        }
    }
}

void DNALoader::load_DNA_file_base(DNAStorage* store, const Filename& file)
{
    dna_cat.info() << "loading " << file << std::endl;

    static VirtualFileSystem* vfs = VirtualFileSystem::get_global_ptr();
    Filename found(file);
    vfs->resolve_filename(found, get_model_path());

    if (!vfs->exists(found))
    {
        dna_cat.error() << "unable to find " << file << std::endl;
        return;
    }

    m_cur_comp = nullptr;
    m_cur_store = store;

    bool is_pdna = found.get_extension() == "pdna";
    if (is_pdna)
    {
        std::string data;
        vfs->read_file(found, data, true);

        nassertv(data.size() > 7);
        nassertv(data.substr(0, 5) == "PDNA\n");

        bool compressed = (data[5] != 0);
        data = data.substr(7);

        if (compressed)
        {
            dna_cat.debug() << "detected compressed data" << std::endl;
            data = decompress_string(data);
        }

        Datagram dg(data.data(), data.size());
        DatagramIterator dgi(dg);

        handle_storage_data(dgi);
        dna_cat.debug() << "storage data read" << std::endl;
        handle_comp_data(dgi);
        dna_cat.debug() << "components data read" << std::endl;

        PT(DNAGroup) dnaroot = new DNAData("root");
        for (int i = 0; i < m_cur_comp->get_num_children(); i++)
            dnaroot->add(m_cur_comp->at(i));

        m_cur_comp = dnaroot;
    }

    else
    {
        std::istream* in = vfs->open_read_file(found, true);
        if (!in)
        {
            dna_cat.error() << "unable to read " << file << std::endl;
            return;
        }

        m_cur_comp = new DNAData("root");
        dna_init_parser(*in, found, this, m_cur_store, m_cur_comp);
        dnayyparse();
        dna_cleanup_parser();
        vfs->close_read_file(in);

        if (dna_error_count() != 0)
            m_cur_comp = nullptr;
    }
}

PT(PandaNode) load_DNA_file(DNAStorage* store, const Filename& file, CoordinateSystem, int)
{
    DNALoader loader;
    PT(DNAGroup) root = loader.load_DNA_file_AI(store, file);
    if (root == nullptr)
        return nullptr;

    nassertr(root->get_type() == DNAData::get_class_type(), nullptr);

    NodePath np("dna");
    root->traverse(np, store);

    PT(PandaNode) result = np.node();

    // Omit "dna" root node, if possible
    if (result->get_num_children() == 1)
        result = result->get_child(0);

    return result;
}

PT(DNAGroup) load_DNA_file_AI(DNAStorage* store, const Filename& file, CoordinateSystem)
{
    DNALoader loader;
    return loader.load_DNA_file_AI(store, file);
}
