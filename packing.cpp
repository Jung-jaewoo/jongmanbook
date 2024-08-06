#include <iostream>
#include <algorithm>
#include <string>
#define fastio ios_base::sync_with_stdio(false), cin.tie(NULL)

using namespace std;

int N, W;
int volume[100], need[100];
string name[100];
int cache[1001][100];

int getMaxNeed(int capacity, int item)
{
    if(item == N) return 0;
    int& ret = cache[capacity][item];
    if(ret != -1) return ret;

    ret = getMaxNeed(capacity, item + 1);
    if(capacity>=volume[item])
        ret = max(ret, getMaxNeed(capacity-volume[item],item+1) + need[item]);
    return ret;
}

void reconstruct(int capacity, int item, vector<string>& picked)
{
    if(item == N) return;
    if(getMaxNeed(capacity,item) == getMaxNeed(capacity,item+1))
        reconstruct(capacity,item+1,picked);
    else{
        picked.push_back(name[item]);
        reconstruct(capacity-volume[item],item+1,picked);
    }
}

int main()
{
    fastio;
    int C;
    vector<string> picked;
    cin >> C;
    while(C--){
        picked.clear();
        for(int i=0; i<1001; i++)
            fill(cache[i], cache[i] + 100, -1);
        cin >> N >> W;
        for(int i=0; i<N; i++) cin >> name[i] >> volume[i] >> need[i];
        reconstruct(W,0,picked);
        cout << getMaxNeed(W,0) << " " << picked.size() << "\n";
        for(int i=0; i<picked.size(); i++) cout << picked[i] << "\n";
    }
}