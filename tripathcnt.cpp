#include <iostream>
#include <algorithm>
#include <cstring>
#define fastio ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define INF 987654321

using namespace std;

int n;
int arr[100][100];
int cache[100][100];
int countCache[100][100];

int path(int x, int y){
    if(x==n-1) return arr[x][y];

    int& ret = cache[x][y];
    if(ret != -1) return cache[x][y];

    return ret = max(path(x+1,y),path(x+1,y+1)) + arr[x][y];
}

int count(int x, int y){
    if(x==n-1) return 1;

    int& ret = countCache[x][y];
    if(ret != -1) return ret;

    ret = 0;
    if(path(x+1,y) >= path(x+1,y+1)) ret += count(x+1,y);
    if(path(x+1,y) <= path(x+1,y+1)) ret += count(x+1,y+1);
    return ret;
}

int main()
{
    fastio;
    int C;
    cin >> C;
    while(C--){
        for(int i=0; i<100; i++){
            memset(&cache[i],-1,sizeof(cache[i]));
            memset(&countCache[i],-1,sizeof(countCache[i]));
        }
        cin >> n;
        for(int i=0; i<n; i++)
            for(int j=0; j<i+1; j++)
                cin >> arr[i][j];
        cout << count(0,0) << "\n";
    }
    return 0;
}