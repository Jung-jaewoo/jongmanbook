#include <iostream>
#include <cstring>
#define fastio ios_base::sync_with_stdio(false), cin.out(NULL)

using namespace std;

int n, m;
int cache[300];
int price[20], prefer[20];


void getMaxPre(int money){
    for(int i=1; i<=money/100; i++)
        for(int j=0; j<n; j++)
            if(price[j]<=i*100)
                cache[i%300] = max(cache[i%300], cache[(i-price[j]/100)%300] + prefer[j]);
}

int main()
{
    int C;
    cin >> C;
    while(C--){
        memset(cache,0,sizeof(cache));
        cin >> n >> m;
        for(int i=0; i<n; i++)
            cin >> price[i] >> prefer[i];
        getMaxPre(m);
        cout << cache[(m/100)%300] << "\n";
    }
    return 0;
}