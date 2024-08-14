#include <iostream>
#include <queue>
#define fastio ios_base::sync_with_stdio(false), cin.tie(NULL)

using namespace std;

int n;
priority_queue<int> arr;

int getSol(){
    int a, b, sol = 0;

    while(arr.size()!=1){
        a = -arr.top();
        arr.pop();
        b = -arr.top();
        arr.pop();

        sol += a + b;
        arr.push(-(a+b));
    }
    return sol;
}

int main()
{
    int C;
    cin >> C;
    while(C--){
        cin >> n;
        int tmp;
        for(int i=0; i<n; i++) {
            cin >> tmp;
            arr.push(-tmp);
        }
        cout << getSol() << "\n";
        while(arr.size()!=0) arr.pop();
    }
    return 0;
}