#include "DNABattleCell.h"

TypeHandle DNABattleCell::_type_handle;

DNABattleCell::DNABattleCell(float width, float height,
                             LPoint3f pos): m_width(width),
                             m_height(height), m_pos(pos)
{
}

DNABattleCell::~DNABattleCell()
{
}
