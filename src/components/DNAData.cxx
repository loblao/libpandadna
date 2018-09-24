#include "DNAData.h"

TypeHandle DNAData::_type_handle;

DNAData::DNAData(const std::string& name): DNAGroup(name)
{
}

DNAData::~DNAData()
{
}

void DNAData::make_from_dgi(DatagramIterator& dgi, DNAStorage* store)
{
    // This will never be called
    dna_cat.error() << "called DNAData::make_from_dgi, ignoring..." << std::endl;
}

void DNAData::traverse(NodePath& np, DNAStorage* store)
{
    traverse_children(np, store);
}
