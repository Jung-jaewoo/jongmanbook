#include <iostream>
#include <algorithm>
#define fastio ios_base::sync_with_stdio(false), cin.tie(NULL)
using namespace std;

int n, d, p, t;
double cache[50][101];
int arr[50][50];
int prob[50];
int q_list[50];

double getProb(int here, int days){
    if(days == 0) return (here==p) ? 1 : 0;
    
    double& ret = cache[here][days];
    if(ret != -1) return ret;

    ret = 0;
    for(int i=0; i<n; i++)
        if(arr[here][i]==1) ret += getProb(i,days-1) / prob[i];

    return ret;
}

int main()
{
    fastio;
    int C;
    cin >> C;
    cout << fixed;
    cout.precision(8);
    while(C--){
        for(int i=0; i<50; i++)
            fill(cache[i],cache[i]+100,-1);
        fill(prob,prob+50,0);

        cin >> n >> d >> p;
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                cin >> arr[i][j];
                if(arr[i][j]==1) prob[i]++;
            }
        }
        cin >> t;
        for(int i=0; i<t; i++) cin >> q_list[i];
        for(int i=0; i<t; i++) cout << getProb(q_list[i],d) << " ";
        cout << "\n";
    }

    return 0;
}