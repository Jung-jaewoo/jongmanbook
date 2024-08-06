#include <iostream>
#include <algorithm>
#include <cstring>
#define fastio ios_base::sync_with_stdio(false), cin.tie(NULL)

using namespace std;

int arr[501], cacheLen[501], cacheCnt[501];
int n, k;

int getlis(int start){
    if(start == n-1) return 1;
    int& ret = cacheLen[start + 1];
    if(ret != -1) return ret;

    ret = 1;
    for(int next=start+1; next < n; next++){
        if(start == -1 || arr[start] < arr[next])
            ret = max(ret, getlis(next) + 1);
    }
    return ret;
}

int count(int start){
    if(getlis(start) == 1) return 1;
    int& ret = cacheCnt[start + 1];
    if(ret != -1) return ret;
    ret = 0;
    for(int next = start +1; next < n; next++){
        if((start==-1 || arr[start] < arr[next]) && getlis(start) == getlis(next) + 1)
            ret = min<long long>(INT32_MAX, (long long)ret + count(next));
    }
    return ret;
}

void reconstruct(int start, int skip, vector<int>& lis){
    if(start!=-1) lis.push_back(arr[start]);
    vector<pair<int,int>> followers;
    for(int next = start+1; next<n; next++)
        if((start == -1 || arr[start]<arr[next]) && getlis(start) == getlis(next) + 1)
            followers.push_back(make_pair(arr[next],next));
    sort(followers.begin(),followers.end());
    for(int i=0; i<followers.size(); i++){
        int idx = followers[i].second;
        int cnt = count(idx);
        if(cnt <= skip) skip -= cnt;
        else{
            reconstruct(idx,skip,lis);
            break;
        }
    }
}   

int main()
{
    vector<int> lis;
    int C;
    cin >> C;
    while(C--){
        lis.clear();
        memset(cacheCnt, -1, sizeof(cacheCnt));
        memset(cacheLen, -1, sizeof(cacheLen));
        cin >> n >> k;
        for(int i=0; i<n; i++) cin >> arr[i];
        cout << getlis(-1) - 1 << "\n";
        reconstruct(-1,k-1,lis);
        for(int i=0; i<lis.size(); i++) cout << lis[i] << " ";
        cout << "\n";
    }
    return 0;
}