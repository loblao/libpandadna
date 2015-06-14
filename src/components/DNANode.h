#ifndef _H_DNA_NODE_
#define _H_DNA_NODE_

#include "DNAGroup.h"
#include "DNAStorage.h"

#include <math.h>

class EXPCL_DNA DNANode : public DNAGroup
{
    PUBLISHED:
        DNANode(const std::string& name);
        ~DNANode();
        
        WRITE_PDNA
        {
            DNAGroup::write_pdna(dg, false);
            
            dg.add_int32(floor(m_pos.get_x() * 100));
            dg.add_int32(floor(m_pos.get_y() * 100));
            dg.add_int32(floor(m_pos.get_z() * 100));
            
            dg.add_int32(floor(m_hpr.get_x() * 100));
            dg.add_int32(floor(m_hpr.get_y() * 100));
            dg.add_int32(floor(m_hpr.get_z() * 100));
            
            dg.add_uint16(floor(m_scale.get_x() * 100));
            dg.add_uint16(floor(m_scale.get_y() * 100));
            dg.add_uint16(floor(m_scale.get_z() * 100));
            
            if (recursive)
                pack_children_pdna(dg);
        }
        
        WRITE_DNA
        {
            DNAGroup::write_dna(out, false, indent);
            indent += 1;
            
            if (m_pos != LVecBase3f(0, 0, 0))
                INDENTED_OUT << "pos [ " << m_pos.get_x() << " "
                             << m_pos.get_y() << " " << m_pos.get_z()
                             << " ]" << std::endl;
                             
            if (m_hpr != LVecBase3f(0, 0, 0))
                INDENTED_OUT << "nhpr [ " << m_hpr.get_x() << " "
                             << m_hpr.get_y() << " " << m_hpr.get_z()
                             << " ]" << std::endl;
                             
            if (m_scale != LVecBase3f(1, 1, 1))
                INDENTED_OUT << "scale [ " << m_scale.get_x() << " "
                             << m_scale.get_y() << " " << m_scale.get_z()
                             << " ]" << std::endl;
            
            if (recursive)
                pack_children_dna(out, indent - 1);
        }
        
        COMP_CODE(COMPCODE_NODE);
        COMP_NAME(node);
        
    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
    PROPERTY(LVecBase3f, pos);
    PROPERTY(LVecBase3f, hpr);
    PROPERTY(LVecBase3f, scale);
    
    TYPE_HANDLE(DNANode, DNAGroup);
};

#endif
