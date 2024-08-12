#include <iostream>
#include <algorithm>
#define fastio ios_base::sync_with_stdio(false), cin.tie(NULL)

using namespace std;

int kteam[100], rteam[100];
int n;

int getPoint(){
    sort(rteam, rteam+n);
    sort(kteam, kteam+n);

    int i = 0, j = 0, cnt = 0;
    while(i<n&&j<n){
        if(j>=n) break;
        if(rteam[i] <= kteam[j]){
            cnt++;
            i++;
            j++;
            continue;
        }
        j++;
    }
    return cnt;
}

int main()
{
    fastio;
    int C;
    cin >> C;
    while(C--){
        cin >> n;
        for(int i=0; i<n; i++) cin >> rteam[i];
        for(int i=0; i<n; i++) cin >> kteam[i];
        cout << getPoint() << "\n";
    }
    return 0;
}