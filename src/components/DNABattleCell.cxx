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

void DNABattleCell::set_width(float width)
{
    m_width = width;
};

float DNABattleCell::get_width()
{
    return m_width;
}

void DNABattleCell::set_height(float height)
{
    m_height = height;
}

float DNABattleCell::get_height()
{
    return m_height;
}

void DNABattleCell::set_width_height(float width, float height)
{
    set_width(width);
    set_height(height);
}

void DNABattleCell::set_pos(LPoint3f const pos)
{
    m_pos = pos;
}

const LPoint3f DNABattleCell::get_pos()
{
    return m_pos;
}
