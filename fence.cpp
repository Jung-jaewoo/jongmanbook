#include <iostream>
#include <vector>
#include <algorithm>
#define ll long long
#define fastio ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);

using namespace std;

vector<int> height;
int N;

int getBig(int start, int end);

int main()
{   
    fastio;

    int C;
    cin >> C;
    while(C--){
        cin >> N;
        height.assign(N,0);
        for(int i=0; i<N; i++)
            cin >> height[i];
        cout << getBig(0,N-1) << "\n";
    }
    
    return 0;
}

int getBig(int start, int end){
    int left=0, right=0, biggest = 0;

    if(start == end){
        return height[start];
    }

    int small = start;
    for(int i = start+1; i<=end; i++)
        if(height[small] > height[i])
            small = i;
            
    if(small != start)
        left = getBig(start,small-1);
    if(small != end)
        right = getBig(small+1,end);
        
    biggest = max(left,right);
    biggest = max(biggest, height[small]*(end - start + 1));

    return biggest;
}
