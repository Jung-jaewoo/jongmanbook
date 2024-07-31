#include <iostream>
#include <algorithm>
#define ll long long

using namespace std;

int n; 
int cache[501], S[500];

int lis(int start){
    int& ret = cache[start+1];
    if(ret != -1) return ret;
    ret = 1;
    for(int next = start + 1; next < n; next++)
        if(start == -1 || S[start] < S[next])
            ret = max(ret, lis(next) + 1);
    return ret;
}

int main()
{
    int C;
    cin >> C;
    while(C--){
        cin >> n;
        for(int i=0; i<n; i++)
            cin >> S[i];
        fill(cache, cache + 501, -1);
        cout << lis(-1) - 1 << "\n";
    }
	return 0;
}