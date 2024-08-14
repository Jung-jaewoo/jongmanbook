#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#define fastio ios_base::sync_with_stdio(false), cin.tie(NULL)

using namespace std;

vector<vector<pair<int,int>>> rotations;
int blockSize;
int boardH, boardW;
vector<string> board;
int covered[10][10];
int best;

vector<string> rotate(const vector<string>& arr){
    vector<string> ret(arr[0].size(), string(arr.size(), ' '));
    for(int i=0; i<arr.size(); i++)
        for(int j=0; j<arr[0].size(); j++)
            ret[j][arr.size()-i-1] = arr[i][j];
    return ret;
}

void generateRotations(vector<string> block){
    rotations.clear();
    rotations.resize(4);
    for(int rot = 0; rot < 4; rot++){
        int originY = -1, originX = -1;
        for(int i=0; i<block.size(); i++)
            for(int j=0; j<block[i].size(); j++){
                if(block[i][j] == '#'){
                    if(originY == -1){
                        originY = i;
                        originX = j;
                    }
                    rotations[rot].push_back(make_pair(i-originY, j-originX));
                }
            }
        block = rotate(block);
    }
    sort(rotations.begin(), rotations.end());
    rotations.erase(unique(rotations.begin(), rotations.end()), rotations.end());
    
    blockSize = rotations[0].size();
}

bool set(int y, int x, const vector<pair<int,int>>& block, int delta){
    int delta_set = delta;
    if(delta_set == -1) delta_set = 0;

    if(delta_set == 1){
        for(int i=0; i<block.size(); i++){
            int dy = block[i].first;
            int dx = block[i].second;
            if(y+dy < 0 || y+dy >=boardH || x+dx < 0 || x+dx >= boardW)
                return false;
            if(covered[y+dy][x+dx] == delta_set)
                return false;    
        }
    }

    for(int i=0; i<block.size(); i++){
        int dy = block[i].first;
        int dx = block[i].second;
        covered[y+dy][x+dx] = delta_set;
    }
    return true;
}

bool pruning(int placed){
    int emptys = 0;
    for(int i=0; i<boardH; i++)
        for(int j=0; j< boardW; j++)
            if(covered[i][j] == 0) emptys++;
    return (emptys/blockSize) + placed <= best ? true : false;
}

void search(int placed){
    if(pruning(placed)) return;
    int y = -1, x = -1;
    for(int i=0; i<boardH; i++){
        for(int j=0; j<boardW; j++){
            if(covered[i][j] == 0){
                y = i;
                x = j;
                break;
            }
        }
        if(y != -1) break;
    }
    if(y == -1)   {
        best = max(best,placed);
        return;
    }
    for(int i=0; i<rotations.size(); i++){
        if(set(y,x,rotations[i],1)){
            search(placed+1);
            set(y,x,rotations[i],-1);
        }
    }
    covered[y][x] = 1;
    search(placed);
    covered[y][x] = 0;
}

int solve(){
    best = 0;
    for(int i=0; i<boardH; i++)
        for(int j=0; j<boardW; j++)
            covered[i][j] = (board[i][j] == '#' ? 1 : 0);
    search(0);
    return best;
}

int main()
{
    int T, blockH, blockW;
    vector<string> block;
    cin >> T;
    while(T--){
        cin >> boardH >> boardW >> blockH >> blockW;
        board.resize(boardH);
        block.resize(blockH);
        for(int i=0; i<boardH; i++) cin >> board[i];
        for(int i=0; i<blockH; i++) cin >> block[i];
        generateRotations(block);
        cout << solve() << "\n";
    }
    return 0;
}