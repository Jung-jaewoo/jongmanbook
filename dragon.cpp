#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#define fastio ios_base::sync_with_stdio(false), cin.tie(NULL)

using namespace std;

const int MAX = 1000000000+1;
int n, p, l;
int cacheLen[51];

int countLen(int idx){ // idx = n
    if(idx == 0) return 1;

    int& ret = cacheLen[idx];
    if(ret != 0) return ret;
    
    return cacheLen[idx] = min(MAX, countLen(idx-1)*2 + 2);
}

void getChar(const string& seed, int generations, int& skip)
{
    if(skip<0) return;
    if(generations == 0){
        cout << seed[skip];
        skip = -1;
        return;
    }
    
    for(int i=0; i<seed.size(); i++){
        if(seed[i] == 'X'){
            if(skip >= countLen(generations))
                skip -= countLen(generations);
            else
                getChar("X+YF", generations - 1, skip);
        }
        else if(seed[i] == 'Y'){
            if(skip >= countLen(generations))
                skip -= countLen(generations);
            else
                getChar("FX-Y", generations - 1, skip);
        }
        else
            if(skip-- == 0) cout << seed[i];
    }
}

int main()
{
    fastio;
    int c;
    cin >> c;
    while(c--){
        cin >> n >> p >> l;
        int skip;
        for(int i=p-1; i< p + l - 1; i++){
            skip = i;
            getChar("FX", n, skip);
        }
        cout << "\n";
    }
    return 0;
}