#ifndef _H_DNA_LOADER_
#define _H_DNA_LOADER_

#include "dnabase.h"
#include "DNAGroup.h"
#include "DNAData.h"
#include "DNAStorage.h"

#include "nodePath.h"

class EXPCL_DNA DNALoader
{
    PUBLISHED:
        DNALoader();
        ~DNALoader();

        NodePath load_DNA_file(DNAStorage* store, const Filename& file);
        PT(DNAGroup) load_DNA_file_AI(DNAStorage* store, const Filename& file);

    private:
       void handle_storage_data(DatagramIterator& dgi);
       void handle_comp_data(DatagramIterator& dgi);
       void load_DNA_file_base(DNAStorage* store, const Filename& file);

       DNAStorage* m_cur_store;
       PT(DNAGroup) m_cur_comp;
};

BEGIN_PUBLISH
// Toontown-specific specialized loaders
EXPCL_DNA PT(PandaNode) load_DNA_file(DNAStorage* store, const Filename& file,
                                      CoordinateSystem cs = CS_default, int ignored = 0);
EXPCL_DNA PT(DNAGroup) load_DNA_file_AI(DNAStorage* store, const Filename& file,
                                        CoordinateSystem cs = CS_default);
END_PUBLISH

#endif
