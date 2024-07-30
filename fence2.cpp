#include <iostream>
#include <vector>
#include <algorithm>
#define fastio ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

using namespace std;

vector<int> h;
int N;

int solve(int left, int right);

int main()
{   
    fastio;

    int C;
    cin >> C;
    while(C--){
        cin >> N;
        h.resize(N);
        for(int i=0; i<N; i++)
            cin >> h[i];
        cout << solve(0,N-1) << "\n";
    }
    
    return 0;
}

int solve(int left, int right){
    if(left == right) return h[left];
    int mid = (left + right) / 2;
    int ret = max(solve(left,mid), solve(mid+1,right));
    int lo = mid, hi = mid + 1;
    int height = min(h[lo],h[hi]);
    ret = max(ret, height * 2);
    while(left < lo || hi < right){
        if(hi < right && (lo == left || h[lo-1] < h[hi+1])){
            ++hi;
            height = min(height, h[hi]);
        }
        else{
            --lo;
            height = min(height, h[lo]);
        }
        ret = max(ret, height * (hi - lo + 1));
    }
    return ret;
}