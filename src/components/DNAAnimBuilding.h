#ifndef _H_DNA_ANIMBUILDING_
#define _H_DNA_ANIMBUILDING_

#include "DNALandmarkBuilding.h"

class EXPCL_DNA DNAAnimBuilding : public DNALandmarkBuilding
{
    PUBLISHED:
        DNAAnimBuilding(const std::string& name);
        ~DNAAnimBuilding();
        
        WRITE_PDNA
        {
            DNALandmarkBuilding::write_pdna(dg, false);

            dg.add_string(m_anim_name);
            
            if (recursive)
                pack_children_pdna(dg);
        }
        
        WRITE_DNA
        {
            DNALandmarkBuilding::write_dna(out, false, indent);
            indent += 1;
                             
            if (m_anim_name.size())
                INDENTED_OUT << "anim [ \"" << m_anim_name << "\" ]" << std::endl;
            
            if (recursive)
                pack_children_dna(out, indent - 1);
        }
        
        COMP_CODE(COMPCODE_ANIM_BUILDING);
        COMP_NAME(anim_building);

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
    PROPERTY_STRING(anim_name);
        
    TYPE_HANDLE(DNAAnimBuilding, DNALandmarkBuilding);
};

#endif
