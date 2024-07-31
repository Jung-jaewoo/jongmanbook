#include <iostream>
#include <algorithm>
#include <cmath>
#define ll long long
#define INF 987654321
#define fastio ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
using namespace std;

string str;
int dp[10000];

int getLevel(int index);
int calculate(int index, int size);

int main()
{
    int C;
    cin >> C;
    while(C--){
        cin >> str;
        fill(dp,dp+10000,INF);
        cout << getLevel(0) << "\n";
    }
	return 0;
}

int getLevel(int index)
{
    int& ret = dp[index];
    if(ret != INF) return dp[index];

    //index가 뒤에서 3,4,5번째
    if(str.size() - index <= 5)
        return ret = min(ret,calculate(index, str.size() - index));
    //index가 뒤에서 6번째
    if(str.size() - index == 6)
        return ret = getLevel(str.size()-3) + calculate(index,3);
    //index가 뒤에서 7번째
    if(str.size() - index == 7)
        return ret = min(getLevel(str.size()-3) + calculate(index,4), getLevel(str.size()-4) + calculate(index,3));
    //index가 뒤에서 8번째 이상
    // if(str.size() - index >= 8){
    int minimum = calculate(index,3) + getLevel(index+3);
    minimum = min(minimum, calculate(index,4)+getLevel(index+4));
    return ret = min(minimum, calculate(index,5)+getLevel(index+5));   
}

int calculate(int index, int size){

    char first = str[index];
    bool flag1, flag2, flag3, flag4;
    flag1 = flag2 = flag3 = flag4 = true;
    int diff = str[index + 1] - first;
    int diff_abs = abs(diff);

    for(int i=index + 1; i<index + size; i++){
        if(str[i] != first)
            flag1 = false;
        if(flag2 && (diff_abs != 1  || str[i] - str[i-1] != diff))
            flag2 = false;
        if(flag3 && i>index+1 && str[i-2] != str[i])
            flag3 = false;
        if(flag4 && str[i] - str[i-1] != diff)
            flag4 = false;
    }

    if(flag1) return 1;
    if(flag2) return 2;
    if(flag3) return 4;
    if(flag4) return 5;
    return 10;
}
