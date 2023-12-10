#include <iostream>
#include <vector>

using namespace std;

enum Options {
    O,
    X,
    SPACE
};

class Player {
    private:
        string username;
        Options symbol;
    public:
        Player(string username, Options symbol){
            this->username = username;
            this->symbol = symbol;
        }
        string getUsername(){
            return username;
        }
        Options getSymbol(){
            return symbol;
        }
};

class Game{
    private:
        vector<vector<Options>> board;
        Player *player1, *player2, *currentPlayer;
    public:
        Game(Player* player1, Player* player2){
            this->player1 = player1;
            this->player2 = player2;
            board.resize(3, vector<Options>(3, SPACE));
            currentPlayer = player1;
        }
        bool makeMove(int r, int c){
            if(r<0 || r>2 || c<0 || c>2 || board[r][c]!=SPACE){
                return false;
            }
            board[r][c] = currentPlayer->getSymbol();
            currentPlayer = currentPlayer==player1 ? player2 : player1;
            return true;
        }
        bool isWinner(){
            Options symbol = (currentPlayer==player1 ? player2 : player1)->getSymbol();
            for (int i = 0; i < 3; ++i) {
                if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) {
                    return true;
                }
                if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) {
                    return true;
                }
            }
            if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) {
                return true;
            }
            if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) {
                return true;
            }
            return false;
        }
        Player* getWinner(){
            return currentPlayer==player1 ? player2 : player1;
        }
        void displayBoard(){
            cout << "-------------" << endl;
            for (const auto &row : board) {
                cout << "| ";
                for (const auto &cell : row) {
                    cell==SPACE ? cout<<' ' : cout<<cell;
                    cout<<" | ";
                }
                cout << endl << "-------------" << endl;
            }
        }
};

int main() {
    Player* player1 = new Player("Akshay", O);
    Player* player2 = new Player("Shruti", X);
    Game* game = new Game(player1, player2);
    int row, col;
    bool isWinner;
    while(true){
        game->displayBoard();
        cin>>row>>col;
        game->makeMove(row, col);
        if(game->isWinner()) break;
    }
    cout<<"Winner is-"<<game->getWinner()->getUsername();
    return 0;
}
