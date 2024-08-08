#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#define fastio ios_base::sync_with_stdio(false), cin.tie(NULL)

using namespace std;

const int MAX_N = 50;
const int EMPTY = -987654321;
int n;
int arr[MAX_N];
int cache[MAX_N][MAX_N];


int play(int left, int right){
    if(left>right) return 0;
    int& ret = cache[left][right];
    if(ret!= EMPTY) return ret;

    ret = max(arr[left]-play(left+1,right), arr[right]-play(left,right-1));
    if(right - left + 1 >= 2){
        ret = max(ret, -play(left+2, right));
        ret = max(ret, -play(left, right-2));
    }
    return ret;
}

int main()
{
    fastio;
    int C;
    cin >> C;
    while(C--){
        cin >> n;
        for(int i=0; i<n; i++) cin >> arr[i];
        fill(cache[0], cache[MAX_N], EMPTY);
        cout << play(0,n-1) << "\n";
    }
    return 0;
}