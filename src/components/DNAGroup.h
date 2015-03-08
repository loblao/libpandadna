#pragma once

#include "dnabase.h"

#include <nodePath.h>
#include <typedObject.h>
#include <datagramIterator.h>

class DNAStorage;

class DNAGroup;
typedef std::vector<DNAGroup*> dna_group_vec_t;

class EXPCL_DNA DNAGroup : public TypedObject
{
    PUBLISHED:
        DNAGroup(const std::string& name);
        ~DNAGroup();
        
        void add(DNAGroup* group);
        DNAGroup* at(size_t index);
        size_t get_num_children();

        void clear_parent();

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
    protected:
        void raise_code_not_found();
        void raise_code_not_found(const char* code);
        void traverse_children(NodePath& np, DNAStorage* store);

        dna_group_vec_t m_children;
        
    PROPERTY_STRING(name);
    PROPERTY(DNAGroup*, parent);
    PROPERTY(DNAGroup*, vis_group);
        
    TYPE_HANDLE(DNAGroup, TypedObject);
};
