#include <iostream>
#include <algorithm>
#define ll long long

using namespace std;

const ll NEGINF = numeric_limits<ll>::min();
int n, m; 
int cache[101][101];
ll A[100], B[100];

int jlis(int indexA, int indexB){
    
    int& ret = cache[indexA + 1][indexB + 1];
    if(ret != -1) return ret;
    ret = 0;

    ll a = (indexA == -1) ? NEGINF : A[indexA];
    ll b = (indexB == -1) ? NEGINF : B[indexB];
    ll max_element = max(a,b);

    for(int nextA = indexA + 1; nextA < n; nextA++)
        if(max_element < A[nextA])
            ret = max(ret, jlis(nextA, indexB) + 1);
    for(int nextB = indexB + 1; nextB < m; nextB++)
        if(max_element < B[nextB])
            ret = max(ret, jlis(indexA, nextB) + 1);

    return ret;
}

int main()
{
    int C;
    cin >> C;
    while(C--){
        cin >> n >> m;
        for(int i=0; i<n; i++) cin >> A[i];
        for(int i=0; i<m; i++) cin >> B[i];
        for(int i=0; i<101; i++)
            fill(cache[i], cache[i] + 101, -1);
        cout << jlis(-1,-1) << "\n";
    }
	return 0;
}