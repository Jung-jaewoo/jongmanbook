#include <iostream>
#define fastio ios_base::sync_with_stdio(false), cin.tie(NULL)
#define MAX_N 100

using namespace std;

const int MOD = 1000000007;
int n;
int cache[MAX_N];

int tiling(int start){
    if(start == n) return 1;
    if(start > n) return 0;

    int& ret = cache[start];
    if(ret != -1) return ret;

    return ret = (tiling(start+1) + tiling(start+2)) % MOD;
}

int main()
{
    int C;
    cin >> C;
    while(C--){
        fill(cache,cache+MAX_N,-1);
        cin >> n;
        int total = tiling(0);
        if(n%2==0){
            total = (MOD + total - tiling(n/2+1)) % MOD; 
            total = (MOD + total - tiling(n/2)) % MOD;
        }
        else
            total = (MOD + total - tiling(n/2+1)) % MOD;
        cout << total << "\n";
    }
    return 0;
}