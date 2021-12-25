#include "cache.h"
#include <vector>
#include "util.h"
#include <functional>
#include "ooo_cpu.h"

uint32_t CACHE:: lru_victim(uint32_t cpu, uint64_t instr_id, uint32_t set, const BLOCK *current_set, uint64_t ip, uint64_t full_addr, uint32_t type)
{
    return std::distance(current_set, std::max_element(current_set, std::next(current_set, NUM_WAY), lru_comparator<BLOCK, BLOCK>()));
}

void O3_CPU::get_furthest_instruction(__gnu_cxx::__normal_iterator<BLOCK *, vector<BLOCK>> instr){
    // scan through IFETCH_BUFFER to find instructions that hit in the decoded instruction buffer
    auto end = std::min(IFETCH_BUFFER.end(), std::next(IFETCH_BUFFER.begin(), FETCH_WIDTH));
    for (auto it = IFETCH_BUFFER.begin(); it != end; ++it)
        if(instr->ip == it->ip)
            std::cout << "True" ;
}

void CACHE::lru_update(uint32_t set, uint32_t way, uint32_t type, uint8_t hit)
{
    if (hit && type == WRITEBACK)
        return;
    auto begin = std::next(block.begin(), set*NUM_WAY);
    auto end   = std::next(begin, NUM_WAY);
    uint32_t hit_lru = std::next(begin, way)->lru;
    cout << "lru" << " ";
    std::for_each(begin, end, [hit_lru](BLOCK &x){
        if (x.lru <= hit_lru) x.lru++;
        cout << x.lru << " ";
    });
    cout << "instruction-id" << " ";
    std::for_each(begin, end, [hit_lru](BLOCK &x){
        cout << x.instr_id << " ";
    });
    cout<< endl;
    std::next(begin, way)->lru = 0; // promote to the MRU position
}

void CACHE::lru_final_stats()
{
}

