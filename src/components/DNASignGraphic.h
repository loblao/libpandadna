#ifndef _H_DNA_SIGNGRAPHIC_
#define _H_DNA_SIGNGRAPHIC_

#include "DNAProp.h"

class EXPCL_DNA DNASignGraphic : public DNAProp
{
    PUBLISHED:
        DNASignGraphic(const std::string& name);
        ~DNASignGraphic();
        
        WRITE_PDNA
        {
            DNAProp::write_pdna(dg, false);

            dg.add_int16(floor(m_width * 100));
            dg.add_int16(floor(m_height * 100));
            dg.add_bool(false);
            
            if (recursive)
                pack_children_pdna(dg);
        }
                
        COMP_CODE(COMPCODE_SIGN_GRAPHIC);
        COMP_NAME(graphic);

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
    PROPERTY(float, width);
    PROPERTY(float, height);
    
    TYPE_HANDLE(DNASignGraphic, DNAProp);
};

#endif
