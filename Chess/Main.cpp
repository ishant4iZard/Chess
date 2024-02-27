//#include <iostream>

//peiece Images src:-https://github.com/ImKadaga/chess-pieces?tab=readme-ov-file

#include "SFML/Graphics.hpp"
#include "ChessWindow.h"

const char* defaultimg[12] = {  "./Assets/Pieces/Def/wp.png",
                                "./Assets/Pieces/Def/wr.png",
                                "./Assets/Pieces/Def/wn.png",
                                "./Assets/Pieces/Def/wb.png",
                                "./Assets/Pieces/Def/wk.png",
                                "./Assets/Pieces/Def/wq.png",
                                "./Assets/Pieces/Def/bp.png",
                                "./Assets/Pieces/Def/br.png",
                                "./Assets/Pieces/Def/bn.png",
                                "./Assets/Pieces/Def/bb.png",
                                "./Assets/Pieces/Def/bk.png",
                                "./Assets/Pieces/Def/bq.png" };

int main() {
	ChessWindow window(800, 800, "chess", defaultimg);

	while (window.Update()) {
        //refine moves, checks and other loops
	}
	return 0;
}