#include "Board.h"
#include "Bitboard.h"
#include <iostream>
#include <cctype>

Board::Board() {
    // Clear out everything on initialization
    for (int c = 0; c < 2; ++c) {
        for (int p = 0; p < 6; ++p) pieces[c][p] = 0ULL;
    }
    occupancies[WHITE] = occupancies[BLACK] = occupancies[BOTH] = 0ULL;
}

void Board::update_occupancies() {
    occupancies[WHITE] = 0;
    occupancies[BLACK] = 0;
    for (int p = PAWN; p <= KING; ++p) {
        occupancies[WHITE] |= pieces[WHITE][p];
        occupancies[BLACK] |= pieces[BLACK][p];
    }
    occupancies[BOTH] = occupancies[WHITE] | occupancies[BLACK];
}

void Board::parse_fen(const std::string& fen) {
    // Reset state before loading a new FEN
    *this = Board();
    
    int rank = 7; // Start at rank 8 (index 7)
    int file = 0; // Start at file A (index 0)

    for (char c : fen) {
        if (c == ' ') break; // Ignore active color/castling details for now
        
        if (c == '/') {
            rank--;
            file = 0;
        } else if (std::isdigit(c)) {
            file += (c - '0');
        } else {
            Color color = std::isupper(c) ? WHITE : BLACK;
            PieceType type;
            
            switch (std::tolower(c)) {
                case 'p': type = PAWN; break;
                case 'n': type = KNIGHT; break;
                case 'b': type = BISHOP; break;
                case 'r': type = ROOK; break;
                case 'q': type = QUEEN; break;
                case 'k': type = KING; break;
                default: continue;
            }
            
            // Map file and rank cleanly back into your 0-63 square layout
            int square = rank * 8 + file;
            set_bit(pieces[color][type], square);
            file++;
        }
    }
    update_occupancies();
}

void Board::print() const {
    std::cout << "\n";
    // Loop backwards from Rank 8 down to Rank 1
    for (int rank = 7; rank >= 0; --rank) {
        std::cout << (rank + 1) << " ";
        for (int file = 0; file < 8; ++file) {
            int square = rank * 8 + file;
            char piece_char = '.';

            // Look through bitboards to see what is on this square
            for (int c = WHITE; c <= BLACK; ++c) {
                for (int p = PAWN; p <= KING; ++p) {
                    if (get_bit(pieces[c][p], square)) {
                        const char chars[] = {'P', 'N', 'B', 'R', 'Q', 'K'};
                        piece_char = (c == WHITE) ? chars[p] : std::tolower(chars[p]);
                    }
                }
            }
            std::cout << " " << piece_char;
        }
        std::cout << "\n";
    }
    std::cout << "\n   A B C D E F G H\n" << std::endl;
}
