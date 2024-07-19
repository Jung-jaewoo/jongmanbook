#include <iostream>

using namespace std;

int C, H, W;
char board[20][20];
int dx[4][2] = {{0, 1}, {1, 1}, {1, 1}, {1, 0}};
int dy[4][2] = {{1, 1}, {0, -1}, {0, 1}, {0, 1}};

void input();
bool isValid();
int getSol(int x, int y);
bool isPossible(int x, int y, int idx);
void setBlock(int x, int y, int idx, char type);


void mapOut(){
    cout <<"\n";
    for(int i=0; i<H; i++){
        for(int j=0; j<W; j++){
            cout << board[i][j] << " ";
        }
        cout <<"\n";
    }
}

int main()
{
    cin >> C;
    while(C--){
        input();
        if(!isValid())
            cout << 0 << endl;
        else
            cout << getSol(1, 1) << endl;
    }
}  

void input(){
    cin >> H >> W;
    for(int i=0; i<H; i++)
        for(int j=0; j<W; j++)
            cin >> board[i][j];
}

bool isValid(){
    int blankCnt = 0;
    for(int i=0; i<H; i++)
        for(int j=0; j<W; j++)
            if(board[i][j] == '.')
                blankCnt++;
    if(blankCnt%3!=0)
        return false;
    return true;
}

int getSol(int x, int y){
    int sol = 0, nx, ny;
    
    bool flag = true;
    for(int i=0; i<H; i++){
        for(int j=0; j<W; j++){
            if(board[i][j] == '.'){
            nx = i;
            ny = j;
            flag = false;
            break;
            }    
        }
        if(!flag) break;
    }
    // mapOut();
    if(flag) 
        return 1;

    for(int idx=0; idx<4; idx++){
        // cout << nx << ny << " ";
        if(isPossible(nx, ny, idx)){ 
            setBlock(nx, ny, idx, '#');
            sol += getSol(nx, ny+1);
            setBlock(nx, ny, idx, '.');
        }
    }

    return sol;
}

bool isPossible(int x, int y, int idx){
    for(int i=0; i<2; i++){
        if(x + dx[idx][i] < 0 || H <= x + dx[idx][i])
            return false;
        if(y + dy[idx][i] < 0 || W <= y + dy[idx][i])
            return false;
        if(board[x + dx[idx][i]][y + dy[idx][i]] == '#')
            return false;
    }
    return true;
}

void setBlock(int x, int y, int idx, char type){
    board[x][y] = type;
    for(int i=0; i<2; i++)
        board[x + dx[idx][i]][y + dy[idx][i]] = type;
}