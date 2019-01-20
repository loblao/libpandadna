#ifndef _H_DNA_BATTLECELL_
#define _H_DNA_BATTLECELL_

#include "dnabase.h"

#include "luse.h"
#include "typedReferenceCount.h"
#include "nodePath.h"

class EXPCL_DNA DNABattleCell : public TypedReferenceCount
{
    PUBLISHED:
        DNABattleCell(float width, float height, LPoint3f pos);
        ~DNABattleCell();

        INLINE void set_width_height(float width, float height)
        {
            set_width(width);
            set_height(height);
        }

    PROPERTY(float, width);
    PROPERTY(float, height);
    PROPERTY(LPoint3f, pos);

    TYPE_HANDLE(DNABattleCell, TypedReferenceCount);
};

#endif
