#include <iostream>
#include <vector>
#include <algorithm>
#define INF 987654321

using namespace std;

int getMinPut(vector<int>& clock, vector<vector<int>>& switches, int idx);
void setClock(vector<int>& clock, vector<vector<int>>& switches, int idx, int set);
bool checkFinish(vector<int>& clock);

void print(vector<int>& clock){
    for(int i=0; i<16; i++)
        cout << clock[i] <<" ";
    cout << "\n";
}

int main()
{
    int C;
    vector<vector<int>> switches = {{0,1,2},{3,7,9,11},{4,10,14,15},{0,4,5,6,7},{6,7,8,10,12},
                                    {0,2,14,15},{3,14,15},{4,5,7,14,15},{1,2,3,4,5},{3,4,5,9,13}};
    vector<int> clock;
    vector<int> swithches_cnt;
    clock.resize(16);
    swithches_cnt.resize(16);

    cin >> C;

    while(C--){
        for(int i=0; i<16; i++)
            cin >> clock[i];

        if(checkFinish(clock)){
            cout << 0 << "\n";
            continue;
        }
        cout << getMinPut(clock, switches, 0) << "\n";
    }

    return 0;
}

int getMinPut(vector<int>& clock, vector<vector<int>>& switches, int idx){
    // print(clock);
    int sol = INF, push = 0, tmp;
    
    if(idx == 9){
        if(checkFinish(clock))
            return 0;

        for(int i=0; i<3; i++){
            push++;
            setClock(clock,switches,idx,3);
            if(checkFinish(clock)){
                for(int j=0; j<push; j++)
                    setClock(clock,switches,idx,-3);
                return push;
            }
        }
        for(int i=0; i<3; i++)
            setClock(clock,switches,idx,-3);
        return -1;
    }

    tmp = getMinPut(clock,switches, idx + 1);
    if(tmp != -1)
        sol = tmp;
    for(int i=0; i<3; i++){
        push++;
        setClock(clock,switches,idx,3);
        tmp = getMinPut(clock,switches, idx + 1);

        if(tmp == -1)
            continue;
        else 
            sol = min(sol,push + tmp);
    }
    for(int i=0; i<3; i++)
        setClock(clock,switches,idx,-3);
    if(sol == INF)
        return -1;
    return sol;
}

void setClock(vector<int>& clock, vector<vector<int>>& switches, int idx, int set){
    if(set == 3)
        for(int i=0; i<switches[idx].size(); i++)
            clock[switches[idx][i]] = (clock[switches[idx][i]] % 12) + set;
    if(set == -3)
        for(int i=0; i<switches[idx].size(); i++){
            clock[switches[idx][i]] = clock[switches[idx][i]] + set;
            if(clock[switches[idx][i]]==0) clock[switches[idx][i]]+=12;
        }
}

bool checkFinish(vector<int>& clock){
    for(int i=0; i<16; i++)
        if(clock[i]!=12)
            return false;
    return true;
}
