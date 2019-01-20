#ifndef _H_DNA_SUITEDGE_
#define _H_DNA_SUITEDGE_

#include "DNASuitPoint.h"

#include "typedReferenceCount.h"

class EXPCL_DNA DNASuitEdge : public TypedReferenceCount
{
    PUBLISHED:
        DNASuitEdge(PT(DNASuitPoint) start_point, PT(DNASuitPoint) end_point, zone_id_t zone_id);
        ~DNASuitEdge();

    PROPERTY(zone_id_t, zone_id);
    PROPERTY(PT(DNASuitPoint), start_point);
    PROPERTY(PT(DNASuitPoint), end_point);

    TYPE_HANDLE(DNASuitEdge, TypedReferenceCount);
};

#endif
