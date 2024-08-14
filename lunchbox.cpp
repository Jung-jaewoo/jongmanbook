#include <iostream>
#include <algorithm>
#include <cstring>
#define fastio ios_base::sync_with_stdio(false), cin.tie(NULL)

using namespace std;

typedef struct{
    int M;
    int E;
}ME;

ME arr[10000];
int sum[10000];
int n;

bool compare(ME a, ME b){
    return a.E > b.E;
}

int getSol(){
    int sol = 0, restEatTime = 0;
    sort(arr,arr+n,compare);
    sum[0] = arr[0].M;
    for(int i=0; i<n; i++){
        sol+=arr[i].M;
        if(i>0) sum[i] = sum[i-1] + arr[i].M;
    }
    for(int i=0; i<n; i++)
        restEatTime = max(restEatTime, arr[i].E - (sum[n-1] - sum[i]));

    return sol += restEatTime;
}

int getSol2(){
    int ret = 0, beginEat =0 ;
    sort(arr,arr+n,compare);
    for(int i=0; i<n; i++){
        beginEat += arr[i].M;
        ret = max(ret, beginEat + arr[i].E);
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
        for(int i=0; i<n; i++) cin >> arr[i].M;
        for(int i=0; i<n; i++) cin >> arr[i].E;
        cout << getSol() << "\n";
        // cout << getSol2() << "\n";
    }
    return 0;
}