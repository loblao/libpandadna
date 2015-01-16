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
        
        void set_name(const std::string& name);
        const std::string& get_name();
        
        void add(DNAGroup* group);
        DNAGroup* at(size_t index);
        size_t get_num_children();
        
        void set_vis_group(DNAGroup* group);
        DNAGroup* get_vis_group();
        
        void set_parent(DNAGroup* group);
        DNAGroup* get_parent();
        void clear_parent();

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
    protected:
        void raise_code_not_found();
        void raise_code_not_found(const char* code);
        void traverse_children(NodePath& np, DNAStorage* store);

        std::string m_name;
        dna_group_vec_t m_children;
        DNAGroup* m_parent;
        DNAGroup* m_vis_group;
        
    // Type handle
    public:
        static TypeHandle get_class_type()
        {
            return _type_handle;
        }
        
        static void init_type()
        {
            TypedObject::init_type();
            register_type(_type_handle, "DNAGroup", TypedObject::get_class_type());
        }
        
        virtual TypeHandle get_type() const
        {
            return get_class_type();
        }
        
        virtual TypeHandle force_init_type()
        {
            init_type();
            return get_class_type();
        }

    private:
        static TypeHandle _type_handle;
};
