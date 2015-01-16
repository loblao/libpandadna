#pragma once
#include "DNALandmarkBuilding.h"

class EXPCL_DNA DNAAnimBuilding : public DNALandmarkBuilding
{
    PUBLISHED:
        DNAAnimBuilding(const std::string& name);
        ~DNAAnimBuilding();

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
    protected:
        std::string m_anim_name;
        
    // Type handle
    public:
        static TypeHandle get_class_type()
        {
            return _type_handle;
        }
        
        static void init_type()
        {
            DNALandmarkBuilding::init_type();
            register_type(_type_handle, "DNAAnimBuilding", DNALandmarkBuilding::get_class_type());
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
