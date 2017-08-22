#include "AI.h"

using namespace std;


int main(int argc, char **argv)
{
	std::cout << "Hello, World !\n" << endl;
	//Initialiser le board ici
    Player p1, p2;
    p2.setPlayer(false);
    int row;
    Box source[6][7];
    Board playboard(source, 6, 7);
    do {
        for (int i=5;i>=0;i--) {
            for (int j=0;j<7;j++) {
                if (playboard.getBox(i, j).isEmpty() == true) {
                    std::cout << "0 ";
                } else {
                    if (playboard.getBox(i, j).whichColor() == true) {
                        std::cout << "1 ";
                    } else {
                        std::cout << "2 ";
                    }
                }
            }
        std::cout << endl;
        }
        std::cout << "Your turn now ! Give the row where you want to play (between 0 and 6)" << endl;
        cin >> row;
        playboard.setToken(row, p2);        
        std::cout << "Fine, my turn now !" << endl;
        std::pair<int, int> play = BestPlay(p1, playboard, 8);
        
        playboard.setToken(play.second, p1);
        /*if (play.first >= 2) {
            std::cout << "I won !" << endl;
            break;
        } else if (play.first <= 0) {
            std::cout << "You won !" << endl;
            break;
        } else { */
        BoardToFile(playboard, "playboard.txt");

    
        //}
    } while (1);
    
    return 0;
}


/*std::pair<int, int> Recursive(int depth, Player P, Board board, int row) {
    if (depth == 1) { //Conditions d'arrêt du calcul : on ne peut plus jouer ou l'un des joueurs a gagné
        //int res[2] ;
        int res = board.getScoreWinLose(row);
        return std::make_pair(res, row);
    } else {
        return BestPlay(P, board, depth);

    }
}*/

std::pair<int, int> BestPlay(Player P, Board board, int depth) {
    int bestScore = -1;
    int row = -1;
    int score = -1;
    //int res[2] = {bestScore, row};
    for (int i=0;i<=6;i++) {
        //Vérifier que la colonne n'est pas pleine
        if (board.getBox(5,i).isEmpty()==true) {        
            board.setToken(i, P); //On joue dans la colonne non vide
            if (board.getScoreWinLose(P) == 2) { //Si on a gagné on renvoie la colonne où on doit jouer et le score pour win
                    score = 2;
                board.cancelPlay(i);
                if (P.getPlayer() == true) {
                    return std::make_pair(score, i);
                } else {
                    return std::make_pair(2-score,i);
                }
            } else { //Sinon on continue de parcourir l'arbre en cherchant le meilleur score
                
                if (depth == 1) {
                    score = board.getScoreWinLose(P);
                    //cout << "score : " << score << endl;
                } else {
                    P.setPlayer(!P.getPlayer());
                    std::pair<int, int> res = BestPlay(P, board, depth-1);
                        score = res.first;
                    P.setPlayer(!P.getPlayer());
                }
                board.cancelPlay(i);
                if (score > bestScore) {
                    bestScore = score;
                    row = i;
                }
            }
        }
    }
    //si le board est plein -> match nul
    if (row ==-1) {
        bestScore = 1;
    }
    if (P.getPlayer() == true) {
        //std::cout << "return : " << bestScore << row << endl;
        return std::make_pair(bestScore, row);
    } else {
        //std::cout << "return : " << 2-bestScore << row << endl;
        return std::make_pair(2-bestScore, row);
    }
}

void BoardToFile(Board board, char const *filename) {
    ofstream boardFile(filename, ios::out | ios::trunc);
    if (boardFile) {
        for (int i=5;i>=0;i--) {
            for (int j=0;j<7;j++) {
                if (board.getBox(i, j).isEmpty() == true) {
                    boardFile << "0 ";
                } else {
                    if (board.getBox(i, j).whichColor() == true) {
                        boardFile << "1 ";
                    } else {
                        boardFile << "2 ";
                    }
                }
            }
            boardFile << endl;
        }
        boardFile.close();
    } else {
        cerr << "Error while opening boardFile (BoardToFile)" <<endl;
    }
}

Board FileToBoard(char const *filename) {
    Box source[6][7];
    int stock;
    bool test = true;
    std::cout << test <<endl;
    Player p1,p2;
    p2.setPlayer(false);
    Board board(source, 6, 7);
    ifstream boardFile(filename, ios::in);
    if (boardFile) {
        for (int i=5;i>=0;i--) {
            for (int j =0;j<7;j++) {
                boardFile >> stock;
                std::cout << stock;
                switch (stock) {
                    case 0:
                        board.setBox(i,j,p1,false);
                        
                    break;
                    case 1:
                        board.setBox(i,j,p1,true);
                        
                    break;
                    case 2:
                        board.setBox(i,j,p2,true);
                    break;
                }
            }
        }
        boardFile.close();
    } else {
        cerr << "Error while opening boardFile (FileToBoard)" << endl;
    }
    return board;
}

