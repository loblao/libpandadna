#ifndef _H_DNA_FLATBUILDING_
#define _H_DNA_FLATBUILDING_

#include "DNANode.h"

class EXPCL_DNA DNAFlatBuilding : public DNANode
{
    PUBLISHED:
        DNAFlatBuilding(const std::string& name);
        ~DNAFlatBuilding();
        
        WRITE_PDNA
        {
            DNANode::write_pdna(dg, false);
            
            dg.add_int16(floor(m_width * 10));
            dg.add_bool(m_has_door);
            
            if (recursive)
                pack_children_pdna(dg);
        }
        
        WRITE_DNA
        {
            DNANode::write_dna(out, false, indent);
            indent += 1;
            
            if (m_width)
                INDENTED_OUT << "width [ " << m_width << " ]" << std::endl;
            
            if (recursive)
                pack_children_dna(out, indent - 1);
        }
        
        COMP_CODE(COMPCODE_FLAT_BUILDING);
        COMP_NAME(flat_building);

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
        static int current_wall_height;
    
    protected:
        void setup_flat(NodePath& np, DNAStorage* store, const char chr,
                        const std::string& wall_code);
        void setup_suit_flat_building(NodePath& np, DNAStorage* store);
        void setup_cogdo_flat_building(NodePath& np, DNAStorage* store);
        
    PROPERTY(float, width);
    PROPERTY(bool, has_door);
        
    TYPE_HANDLE(DNAFlatBuilding, DNANode);
};

#endif
