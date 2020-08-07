#include "config_dna.h"

#include "DNASuitPath.h"
#include "DNASuitEdge.h"
#include "DNASuitPoint.h"
#include "DNAAnimBuilding.h"
#include "DNAAnimProp.h"
#include "DNABattleCell.h"
#include "DNACornice.h"
#include "DNAData.h"
#include "DNADoor.h"
#include "DNAFlatBuilding.h"
#include "DNAFlatDoor.h"
#include "DNAGroup.h"
#include "DNAInteractiveProp.h"
#include "DNALandmarkBuilding.h"
#include "DNANode.h"
#include "DNAProp.h"
#include "DNASign.h"
#include "DNASignText.h"
#include "DNASignBaseline.h"
#include "DNASignGraphic.h"
#include "DNAStreet.h"
#include "DNAVisGroup.h"
#include "DNAWall.h"
#include "DNAWindows.h"

#include <pandabase.h>
#include <dconfig.h>

Configure(config_dna);
NotifyCategoryDef(dna, "");

ConfigureFn(config_dna)
{
    init_libpandadna();
}

void init_libpandadna()
{
    static bool initialized = false;
    if (initialized)
        return;

    initialized = true;

    DNASuitPath::init_type();
    DNASuitEdge::init_type();
    DNASuitPoint::init_type();
    DNAAnimBuilding::init_type();
    DNAAnimProp::init_type();
    DNABattleCell::init_type();
    DNACornice::init_type();
    DNAData::init_type();
    DNADoor::init_type();
    DNAFlatBuilding::init_type();
    DNAFlatDoor::init_type();
    DNAGroup::init_type();
    DNAInteractiveProp::init_type();
    DNALandmarkBuilding::init_type();
    DNANode::init_type();
    DNAProp::init_type();
    DNASign::init_type();
    DNASignText::init_type();
    DNASignBaseline::init_type();
    DNASignGraphic::init_type();
    DNAStreet::init_type();
    DNAVisGroup::init_type();
    DNAWall::init_type();
    DNAWindows::init_type();
}
