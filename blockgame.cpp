#include <iostream>
#include <vector>
#include <cstring>
#define fastio ios_base::sync_with_stdio(false), cin.tie(NULL)

using namespace std;

int board;
char cache[1<<25];
vector<int> moves;
inline int cell(int y, int x) {return 1<<(x*5 +y);}

void precalc(){
    for(int x=0; x<4; x++){
        for(int y=0; y<4; y++){
            vector<int> cells;
            for(int dx=0; dx<2; dx++)
                for(int dy=0; dy<2; dy++)
                    cells.push_back(cell(x+dx,y+dy));
            int square = cells[0] + cells[1] + cells[2] + cells[3];
            for(int i=0; i<4; i++)
                moves.push_back(square - cells[i]);
        }
    }

    for(int i=0; i<5; i++){
        for(int j=0; j<4; j++){
            moves.push_back(cell(i,j)+cell(i,j+1));
            moves.push_back(cell(j,i)+cell(j+1,i));
        }
    }
}

char canWin(int board){
    char& ret = cache[board];
    if(ret != -1) return ret;
    ret = 0;

    for(int i=0; i<moves.size(); i++){
        if((moves[i] & board) == 0){
            if(!canWin(board|moves[i])){
                ret = 1;
                break;
            }
        }
    }
    return ret;
}

int main()
{
    fastio;
    int C;  
    cin >> C;
    precalc();
    while(C--){
        char tmp;
        board = 0;
        memset(cache,-1,sizeof(cache));
        for(int i=0; i<5; i++){
            for(int j=0; j<5; j++){
                cin >> tmp;
                if(tmp=='#')   
                    board |= (1<<(i*5+j));
            }
        }
        if(canWin(board)==1)
            cout << "WINNING\n";
        else
            cout << "LOSING\n";
    }
    return 0;
}