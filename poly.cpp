#include <iostream>
#include <algorithm>
#define fastio ios_base::sync_with_stdio(false), cin.tie(NULL)
using namespace std;

int n;
int cache[101][101];
const int MOD = 10000000;

int getCount(int total, int first){
    if(first == total) return 1;
    
    int& ret = cache[total][first];
    if(ret != -1) return ret;

    ret = 0;
    for(int second=1; second<= total - first; second++){
        int add = first + second - 1;
        add *= getCount(total-first, second);
        add %= MOD;
        ret = (ret + add) % MOD;
    }
    return ret;
}

int main()
{
    fastio;
    int C;
    cin >> C;
    for(int i=0; i<101; i++)
        fill(cache[i],cache[i]+sizeof(cache[i]),-1);
    while(C--){
        cin >> n;
        int sol = 0;
        for(int i=1; i<=n; i++) sol=(sol + getCount(n,i)) % MOD;
        cout << sol << "\n";
    }

    return 0;
}