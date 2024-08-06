#include <iostream>
#include <algorithm>
#include <cstring>
#define fastio ios_base::sync_with_stdio(false), cin.tie(NULL)

using namespace std;

const int M = 1000000000+100;
int bino[201][201];
int n, m, k;

void calcBino(){
    memset(bino, 0, sizeof(bino));
    for(int i=0; i<=200; i++){
        bino[i][0] = bino[i][i] = 1;
        for(int j=1; j<i; j++)
            bino[i][j] = min(M, bino[i-1][j-1] + bino[i-1][j]);
    }
}

string kth(int n, int m, int skip){
    if(n == 0)  return string(m,'o');
    if(skip < bino[n+m-1][n-1])
        return "-" + kth(n-1,m,skip);
    return "o" + kth(n, m-1, skip - bino[n+m-1][n-1]);
}

int main()
{
    fastio;
    calcBino();

    int C;
    cin >> C;
    while(C--){
        cin >> n >> m >> k;
        cout << kth(n,m,k-1) << "\n";
    }
    return 0;
}