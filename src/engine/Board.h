#pragma once
#include "Types.h"
#include <string>

class Board {
private:
    // 2 colors x 6 piece types = 12 bitboards
    uint64_t pieces[2][6] = {{0}};
    
    // Occupancy bitboards to quickly query occupied squares
    uint64_t occupancies[3] = {0}; 

    void update_occupancies();

public:
    Board();
    void parse_fen(const std::string& fen);
    void print() const;
};
