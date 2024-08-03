#include <iostream>
#include <algorithm>
#include <cstring>
#define fastio ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define INF 987654321

using namespace std;

int n;
const int MOD = 1000000007;
int cache[101];

int tiling(int width){
    int& ret = cache[width];
    if(ret != -1) return ret;
    if(width <= 1) return 1;
    return ret = (tiling(width-1) + tiling(width-2)) % MOD;
}

int main()
{
    int C;
    cin >> C;
    for(int i=0; i<C; i++){
        fill(cache,cache+sizeof(cache),-1);
        cin >> n;
        cout << tiling(n) << "\n";
    }
    return 0;
}