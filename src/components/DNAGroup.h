#ifndef _H_DNA_GROUP_
#define _H_DNA_GROUP_

#include "dnabase.h"

#include "nodePath.h"
#include "typedReferenceCount.h"
#include "datagramIterator.h"

class DNAStorage;

class DNAGroup;
typedef std::vector<PT(DNAGroup)> dna_group_vec_t;

class EXPCL_DNA DNAGroup : public TypedReferenceCount
{
    PUBLISHED:
        DNAGroup(const std::string& name);
        ~DNAGroup();

        void add(PT(DNAGroup) group);
        PT(DNAGroup) at(size_t index);
        size_t get_num_children();

        void clear_parent();

        WRITE_PDNA
        {
            dg.add_uint8(get_comp_code());
            dg.add_string(m_name);

            if (recursive)
                pack_children_pdna(dg);
        }

        WRITE_DNA
        {
            INDENTED_OUT << get_comp_name();

            if (m_name.size())
                out << " \"" << m_name << "\"";

            out << " [" << std::endl;

            if (recursive)
                pack_children_dna(out, indent);
        }

        COMP_CODE(COMPCODE_GROUP);
        COMP_NAME(group);

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);

    protected:
        void raise_code_not_found();
        void raise_code_not_found(const char* code);

        INLINE void traverse_children(NodePath& np, DNAStorage* store)
        {
            for (dna_group_vec_t::iterator it = m_children.begin(); it != m_children.end(); ++it)
                (*it)->traverse(np, store);
        }

        INLINE void pack_children_dna(std::ostream& out, int indent)
        {
            for (dna_group_vec_t::iterator it = m_children.begin(); it != m_children.end(); ++it)
                (*it)->write_dna(out, true, indent + 1);

            INDENTED_OUT << "]" << std::endl;
        }

        INLINE void pack_children_pdna(Datagram& dg)
        {
            for (dna_group_vec_t::iterator it = m_children.begin(); it != m_children.end(); ++it)
                (*it)->write_pdna(dg, true);

            dg.add_uint8(COMPCODE_RETURN);
        }

        dna_group_vec_t m_children;

    PROPERTY_STRING(name);
    PROPERTY(PT(DNAGroup), parent);
    PROPERTY(PT(DNAGroup), vis_group);

    TYPE_HANDLE(DNAGroup, TypedReferenceCount);
};

#endif
