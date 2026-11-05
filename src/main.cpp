#include "Board.h"

int main(int argc, char* argv[]) {
    std::string fen = (argc < 2) ? "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR" : argv[1];
    
    Board board;
    board.parse_fen(fen);
    board.print();
    
    return 0;
}

