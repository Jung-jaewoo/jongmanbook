#include <iostream>
#define fastio ios_base::sync_with_stdio(false), cin.tie(NULL)

using namespace std;

int candidates[10][46][1024];

int getSize(int mask){
    int size = 0, i=1;
    while(i<=1024){
        if((mask & i) == i) size++;
        i = i<<1;
    }
    return size;
}

int getSum(int mask){
    int sum = 0, i=1, j=1;
    while(i<=1024){
        if((mask & i) == i) sum += j;
        i = i<<1;
        j++;
    }
    return sum;
}

int getCandidates(int len, int sum, int known){
    int allSets = 0;
    for(int set = 0; set < 1024; set += 2)
        if((set & known) == known && getSize(set) == len && getSum(set) == sum)
            allSets |= set;
    return allSets & ~known;
}

void generateCandidates(){
    memset(candidates, 0, sizeof(candidates));
    for(int set =0; set < 1024; set += 2){
        int l = getSize(set), s = getSum(set);
        int subset = set;
        while(true){
            candidates[l][s][subset] |= (set & ~subset);
            if(subset == 0) break;
            subset = (subset - 1) & set;
        }
    }
}
const int MAXN = 20;
int n, color[MAXN][MAXN], value[MAXN][MAXN], hint[MAXN][MAXN][2];
int q, sum[MAXN*MAXN], length[MAXN*MAXN], known[MAXN*MAXN];

void put(int y, int x, int val){
    for(int h = 0; h < 2; h++)
        known[hint[y][x][h]] += (1<<val);
    value[y][x] = val;
}

void remove(int y, int x, int val){
    for(int h = 0; h < 2; h++)
        known[hint[y][x][h]] -= (1<<val);
    value[y][x] = 0;
}

int getCandHint(int hint){
    return candidates[length[hint]][sum[hint]][known[hint]];
}

int getCandCoord(int y, int x){
    return getCandHint(hint[y][x][0]) & getCandHint(hint[y][x][1]);
}

void printSolution(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cout << value[i][j] << " ";
        }
        cout << "\n";
    }
}

bool search(){
    int y = -1, x = -1, minCands = 1023;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(color[i][j] == 1 && value[i][j] == 0){
                int cands = getCandCoord(i, j);
                if(getSize(minCands) > getSize(cands)){
                    minCands = cands;
                    y = i; x = j;
                }
            }
    if(minCands == 0) return false;
    if(y == -1){
        printSolution();
        return true;
    }

    for(int val = 1; val <= 9; val++){
        if(minCands & (1<<val)){
            put(y, x, val);
            if(search()) return true;
            remove(y, x, val);
        }
    }
    return false;
}


int main()
{
    fastio;
    int T;
    cin >> T; 
    while(T--){
        cin >> n; 
        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
                cin >> color[i][j];
        cin >> q;
        int x, y, type;
        for(int i=0; i<q; i++){
            cin >> x >> y >> type;
            cin >> hint[x][y][type];
        }
        generateCandidates();
        search();
    }
    return 0;
}