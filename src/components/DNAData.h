#ifndef _H_DNA_DATA_
#define _H_DNA_DATA_

#include "DNAGroup.h"
#include "DNAStorage.h"

class EXPCL_DNA DNAData : public DNAGroup
{
    PUBLISHED:
        DNAData(const std::string& name);
        ~DNAData();

        WRITE_PDNA
        {
            if (recursive)
                pack_children_pdna(dg);
        }

        WRITE_DNA
        {
            if (recursive)
                pack_children_dna(out, indent);
        }

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);

    TYPE_HANDLE(DNAData, DNAGroup);
};

#endif
