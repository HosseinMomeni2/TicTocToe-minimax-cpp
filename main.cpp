#include <iostream>
#include <vector>
#include <algorithm>
#include <windows.h>
using namespace std;

const char empty_cell = ' ';
const char x_cell = 'x';
const char o_cell = 'o';


int gameResult(vector<vector<char>> board);
bool isGameOver(vector<vector<char>> board)
{
    if(gameResult(board) == 0) return false;

//    for(int i=0; i<3; i++)
//        for(int j=0; j<3; j++)
//            if(board[i][j] == empty_cell)
//                return false;

    return true;
}

int gameResult(vector<vector<char>> board) /// 0: not over, 1: o, 2: tie, 3: x
{
    for(int i=0; i<3; i++)
    {
        if(board[i][0] == empty_cell) continue;

        if(board[i][0] == board[i][1])
        {
//            cout << 11 << endl; ///debug line
            if(board[i][1] == board[i][2])
            {
                if(board[i][0] == x_cell) return 3;
                else return 1;
            }
        }
    }
    for(int i=0; i<3; i++)
    {
        if(board[0][i] == empty_cell) continue;

        if(board[0][i] == board[1][i])
        {
//            cout << 22 << endl; ///debug line
            if(board[1][i] == board[2][i])
            {
                if(board[0][i] == x_cell) return 3;
                else return 1;
            }
        }
    }
    if(board[0][0]==board[1][1] && board[1][1]==board[2][2])
    {
        if(board[0][0] == x_cell) return 3;
        if(board[0][0] == o_cell) return 1;
    }
    if(board[0][2]==board[1][1] && board[1][1]==board[2][0])
    {
        if(board[0][2] == x_cell) return 3;
        if(board[0][2] == o_cell) return 1;
    }
    ///every possible state of winning is now checked!

    ///is it a tie or is it over at all???
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            if(board[i][j] == empty_cell)
                return 0;
    return 2;
}

/// minimax returns evaluation of a board
/// if x is winning it returns 1
/// if o is winning it returns -1
/// if the game is going to be a dead draw it returns 0
int minimax(vector<vector<char>> board, bool isMaximizing, int depth = 4)
{
    /// is it tie?
    int game_result = gameResult(board);
    if(game_result == 1) return -1;
    if(game_result == 2) return 0;
    if(game_result == 3) return 1;

    /// depth should be more than 0
    if(!depth) return 0;

    if(isMaximizing)
    {
        int valuation = -2;
        for(int i=0; i<3; i++)
        {
            for(int j=0; j<3; j++)
            {
                if(board[i][j] == empty_cell)
                {
                    board[i][j] = x_cell;
//                    if(i==2 && j==2) cout << "this is 2,2 : " << endl; ///debug line
                    int score = minimax(board, false, depth-1);
                    valuation = max(valuation, score);
                    board[i][j] = empty_cell;
//                    if(depth==1) cout << "i,j: " << i << "," << j << " sc: " << score << "\n"; ///debug line
                }
            }
        }
//        cout << "\n"; ///debug line
        return valuation;
    }
    else
    {

        int valuation = 2;
        for(int i=0; i<3; i++)
        {
            for(int j=0; j<3; j++)
            {
                if(board[i][j] == empty_cell)
                {
                    board[i][j] = o_cell;
                    int score = minimax(board, true, depth-1);
                    valuation = min(valuation, score);
                    board[i][j] = empty_cell;
                }
            }
        }

        return valuation;
    }
}

vector<int> AI_choice(vector<vector<char>> board, bool isMaximizing)
{
    vector<int> res(2);
    if(isGameOver(board))
    {
        res[0] = res[1] = -1;
    }
    else
    {
        if(isMaximizing)
        {
            int best_evaluation = -2;
            for(int i=0; i<3; i++)
            {
                for(int j=0; j<3; j++)
                {
                    if(board[i][j] == empty_cell)
                    {
//                        cout << "empty " << i << " " << j << "detected" << endl; /// debug line
                        board[i][j] = x_cell;
                        int current_evaluation = minimax(board, false);
                        cout << current_evaluation << "  "; ///debug line
                        if(current_evaluation > best_evaluation)
                        {
                            best_evaluation = current_evaluation;
                            res[0] = i;
                            res[1] = j;
                        }
                        board[i][j] = empty_cell;
                    }
                    else cout << "f  "; ///debug line
                }
                cout << "\n"; ///debug line
            }
        }
        else
        {
            int best_evaluation = 2;
            for(int i=0; i<3; i++)
            {
                for(int j=0; j<3; j++)
                {
                    if(board[i][j] == empty_cell)
                    {
                        board[i][j] = o_cell;
                        int current_evaluation = minimax(board, true);
                        if(current_evaluation < best_evaluation)
                        {
                            best_evaluation = current_evaluation;
                            res[0] = i;
                            res[1] = j;
                        }
                        board[i][j] = empty_cell;
                    }
                }
            }
        }
    }

    return res;
}

void print_board(vector<vector<char>> board)
{
    cout << "\n-------------\n";
    for(int i=0; i<3; i++)
    {
        cout << "| ";
        for(int j=0; j<3; j++)
        {
            cout << board[i][j] << " | ";
        }
        cout << "\n-------------\n";
    }

    cout << flush;
}

void run_as_x()
{
    char e = empty_cell;
    vector<vector<char>> v = {{e, e, e},
                              {e, e, e},
                              {e, e, e}};

//    cout << gameResult(v) << endl; ///debug line
//    cout << isGameOver(v); ///debug line
    while(!isGameOver(v))
    {
        int i, j;
        while(true)
        {
            int choice;
            cout << "enter your choice number :";
            cin >> choice;
            switch (choice) {
                case 1:
                    i = 2;
                    j = 0;
                    break;
                case 2:
                    i = 2;
                    j = 1;
                    break;
                case 3:
                    i = 2;
                    j = 2;
                    break;
                case 4:
                    i = 1;
                    j = 0;
                    break;
                case 5:
                    i = 1;
                    j = 1;
                    break;
                case 6:
                    i = 1;
                    j = 2;
                    break;
                case 7:
                    i = 0;
                    j = 0;
                    break;
                case 8:
                    i = 0;
                    j = 1;
                    break;
                case 9:
                    i = 0;
                    j = 2;
                    break;
            }

            if(v[i][j] == empty_cell) break;
        }

        v[i][j] = x_cell;
        print_board(v);
        cout << "\n\n";

        cout << "computer is thinking...";
        Sleep(2000);


        vector<int> ai = AI_choice(v, false);
        v[ai[0]][ai[1]] = o_cell;
        print_board(v);
        cout << "\n\n";
    }
}

void run_as_o()
{
    char e = empty_cell;
    vector<vector<char>> v = {{e, e, e},
                              {e, e, e},
                              {e, e, e}};
    v[rand()%3][rand()%3] = x_cell;

    while(!isGameOver(v))
    {
        int i, j;
        while(true)
        {
            int choice;
            cout << "enter your choice number :";
            cin >> choice;
            switch (choice) {
                case 1:
                    i = 2;
                    j = 0;
                    break;
                case 2:
                    i = 2;
                    j = 1;
                    break;
                case 3:
                    i = 2;
                    j = 2;
                    break;
                case 4:
                    i = 1;
                    j = 0;
                    break;
                case 5:
                    i = 1;
                    j = 1;
                    break;
                case 6:
                    i = 1;
                    j = 2;
                    break;
                case 7:
                    i = 0;
                    j = 0;
                    break;
                case 8:
                    i = 0;
                    j = 1;
                    break;
                case 9:
                    i = 0;
                    j = 2;
                    break;
            }

            if(v[i][j] == empty_cell) break;
        }

        v[i][j] = o_cell;
        print_board(v);
        cout << "\n\n";

        cout << "computer is thinking...";
        Sleep(2000);

        vector<int> ai = AI_choice(v, true);
        v[ai[0]][ai[1]] = x_cell;
        print_board(v);
        cout << "\n\n";
    }

}

void run()
{
    cout << "which side are you going to play(x / o)?";
    char side; cin >> side;

    if(side == 'x')
    {
        run_as_x();
    }
    else
    {
        run_as_o();
    }
}


int main() {
    char e = empty_cell;
    vector<vector<char>> v = {{' ',' ',' '},
                              {' ',' ',' '},
                              {' ',' ',' '}};


//    cout << gameResult(v);
//    cout << minimax(v, true);
//    vector<int> c = AI_choice(v, true);
//    cout << c[0] << " , " << c[1];

    run();
    
    return 0;
}
