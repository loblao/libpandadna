#pragma once

#include "DNASuitEdge.h"
#include "DNABattleCell.h"
#include "DNAGroup.h"

typedef std::vector<std::string> visibles_vec_t;
typedef std::vector<DNASuitEdge*> suit_edge_vec_t;
typedef std::vector<DNABattleCell*> battle_cell_vec_t;

class EXPCL_DNA DNAVisGroup : public DNAGroup
{
    PUBLISHED:
        DNAVisGroup(const std::string& name);
        ~DNAVisGroup();
        
        void add_visible(const std::string& visible);
        bool remove_visible(const std::string& visible);
        size_t get_num_visibles();
        const std::string& get_visible(size_t index);
        
        void add_suit_edge(DNASuitEdge* edge);
        bool remove_suit_edge(DNASuitEdge* edge);
        size_t get_num_suit_edges();
        DNASuitEdge* get_suit_edge(size_t index);
        
        void add_battle_cell(DNABattleCell* cell);
        bool remove_battle_cell(DNABattleCell* cell);
        size_t get_num_battle_cells();
        DNABattleCell* get_battle_cell(size_t index);

    public:
        virtual void make_from_dgi(DatagramIterator& dgi, DNAStorage* store);
        virtual void traverse(NodePath& np, DNAStorage* store);
        
    protected:
        visibles_vec_t m_visibles;
        suit_edge_vec_t m_suit_edges;
        battle_cell_vec_t m_battle_cells;
     
    TYPE_HANDLE(DNAVisGroup, DNAGroup);
};
