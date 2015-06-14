#ifndef _H_DNA_SUITEDGE_
#define _H_DNA_SUITEDGE_

#include "DNASuitPoint.h"

#include <typedObject.h>

class EXPCL_DNA DNASuitEdge : public TypedObject
{
    PUBLISHED:
        DNASuitEdge(DNASuitPoint* start_point, DNASuitPoint* end_point, zone_id_t zone_id);
        ~DNASuitEdge();
        
    PROPERTY(zone_id_t, zone_id);
    PROPERTY(DNASuitPoint*, start_point);
    PROPERTY(DNASuitPoint*, end_point);
        
    TYPE_HANDLE(DNASuitEdge, TypedObject);
};

#endif
