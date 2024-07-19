#include <iostream>
#include <algorithm>
#include <memory.h>
using namespace std;

int C, n, m, sol;
bool relation[10][10];
bool included[10];

void input();
void getMethodNum();

int main()
{
    cin >> C;
    while(C--){
        input();
        sol = 0;

        getMethodNum();
        cout << sol << "\n";

        fill(included,included+10,false);
        memset(relation, 0, sizeof(relation));
    }
}  

void input(){
    cin >> n >> m;
    int r1, r2;
    for(int i=0; i<m; i++){
        cin >> r1 >> r2;
        relation[r1][r2] = true;
        relation[r2][r1] = true;
    }
}

void getMethodNum(){
    int first_free = -1;
    for(int i=0; i<n; i++){
        if(!included[i]){
            first_free = i;
            break;
        }
    }
    
    if(first_free == -1){
        sol++;
        return;
    }

    for(int i=first_free+1; i<n; i++){
        if(!included[i] && relation[first_free][i]){
            included[first_free] = included[i] = true;
            getMethodNum();
            included[first_free] = included[i] = false;
        }
    }
}