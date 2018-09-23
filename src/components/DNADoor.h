#ifndef _H_DNA_DOOR_
#define _H_DNA_DOOR_

#include "DNAGroup.h"

class EXPCL_DNA DNADoor : public DNAGroup
{
    PUBLISHED:
        DNADoor(const std::string& name);
        ~DNADoor();

        static void setup_door(NodePath door_np, NodePath parent_np, NodePath door_origin, DNAStorage* store, const std::string& block, LVecBase4f& color);
        static void setup_door(NodePath door_np, NodePath parent_np, NodePath door_origin, DNAStorage* store, block_number_t block, LVecBase4f& color);

        WRITE_PDNA
        {
            DNAGroup::write_pdna(dg, false);

            dg.add_string(m_code);
            PACK_COLOR;
        }

        WRITE_DNA
        {
            DNAGroup::write_dna(out, false, indent);
            indent += 1;

            if (m_color != LVecBase4f(1, 1, 1, 1))
                INDENTED_OUT << "color [ " << m_color.get_x() << " "
                             << m_color.get_y() << " " << m_color.get_z()
                             << " " << m_color.get_w() << " ]" << std::endl;

            if (m_code.size())
                INDENTED_OUT << "code [ \"" << m_code << "\" ]" << std::endl;

            indent -= 1;
            INDENTED_OUT << "]" << std::endl;
        }

        COMP_CODE(COMPCODE_DOOR);
        COMP_NAME(door);

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);

    PROPERTY(LVecBase4f, color);
    PROPERTY_STRING(code);

    TYPE_HANDLE(DNADoor, DNAGroup);
};

#endif
