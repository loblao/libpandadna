#include "DNABattleCell.h"

DNABattleCell::DNABattleCell() {};
DNABattleCell::~DNABattleCell() {};

void DNABattleCell::set_width(unsigned char width)
{
	m_width = width;
};

void DNABattleCell::set_height(unsigned char height)
{
	DNABattleCell::m_height = height;
};

void DNABattleCell::set_width_height(unsigned char width, unsigned char height)
{
	set_width(width);
	set_height(height);
};

void DNABattleCell::set_pos(LVector3f* pos)
{
	m_pos = pos;
};

unsigned char DNABattleCell::get_width()
{
	return m_width;
};

unsigned char DNABattleCell::get_height()
{
	return m_height;
};

LVector3f* DNABattleCell::get_pos()
{
	return m_pos;
};
