#pragma once

#include "dnabase.h"

#include <luse.h>
#include <typedObject.h>
#include <nodePath.h>

class EXPCL_DNA DNABattleCell : public TypedObject
{
    PUBLISHED:
        DNABattleCell(float width, float height, LPoint3f pos);
        ~DNABattleCell();

        void set_width(float width);
        float get_width();

        void set_height(float height);
        float get_height();

        void set_width_height(float width, float height);
        
        void set_pos(LPoint3f const pos);
        const LPoint3f get_pos();

    protected:
        float m_width;
        float m_height;
        LPoint3f m_pos;
        
    // Type handle
    public:
        static TypeHandle get_class_type()
        {
            return _type_handle;
        }
        
        static void init_type()
        {
            TypedObject::init_type();
            register_type(_type_handle, "DNABattleCell", TypedObject::get_class_type());
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
