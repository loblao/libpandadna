#pragma once
#include "DNAGroup.h"

class EXPCL_DNA DNAWindows : public DNAGroup
{
    PUBLISHED:
        DNAWindows(const std::string& name);
        ~DNAWindows();
        
        void make_windows(float x, float y, NodePath& parent_node,
                          const std::string& code, float scale,
                          LVecBase4f& color, DNAStorage* store,
                          bool flip=false);

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
    protected:
        std::string m_code;
        LVecBase4f m_color;
        unsigned char m_window_count;
        
    // Type handle
    public:
        static TypeHandle get_class_type()
        {
            return _type_handle;
        }
        
        static void init_type()
        {
            DNAGroup::init_type();
            register_type(_type_handle, "DNAWindows", DNAGroup::get_class_type());
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
