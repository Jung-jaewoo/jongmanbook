#include <iostream>
#include <string>
#include <map>
#include <cstring>
#include <algorithm>
#include <vector>
#define fastio ios_base::sync_with_stdio(false), cin.tie(NULL)
#define INF 987654321

using namespace std;

int n, m;
map<string,int> friends;
vector<vector<int>> person_eat;
int food[50][50];
int sol;
int canEat[50];

bool check(){
    for(int i=0; i<n; i++)
        if(!canEat[i]) return false;
    return true;
}

void setCanEat(int food_idx, int delta){
    int i = 0;
    while(food[food_idx][i]!=-1){
        canEat[food[food_idx][i]] += delta;
        i++;
    }
}

bool isNeeded(int food_idx){
    int i = 0;
    while(food[food_idx][i]!=-1){
        if(!canEat[food[food_idx][i]]) return true;
        i++;
    }
    return false;
}

// 음식중심으로 탐색 -> 시간초과
void getMinFoodNum(int num, long long& food_list){
    //간단한 가지치기
    if(num>=sol) return;

    for(int i=0; i<m; i++){
        if(((food_list & (1<<i)) == 0) && isNeeded(i)){
            food_list |= (1<<i);
            setCanEat(i, 1);
            if(check()) {
                sol = min(sol, num + 1);
                food_list -= (1<<i);
                setCanEat(i, -1);
                break;
            }
            getMinFoodNum(num+1, food_list);
            food_list -= (1<<i);
            setCanEat(i, -1);
        }
    }
}

// 사람중심으로 탐색 
void getMinFoodNum2(int num){
    if(num>=sol) return;

    int p_idx;
    for(p_idx=0; p_idx<n; p_idx++){
        if(canEat[p_idx] == 0) break;
    }
    if(p_idx == n){
        sol = num;
        return;
    }
    for(int i=0; i<person_eat[p_idx].size(); i++){
        int food = person_eat[p_idx][i];
        setCanEat(food, 1);
        getMinFoodNum2(num+1);
        setCanEat(food, -1);
    }  
}

int main()
{
    fastio;
    int T, eat_n;
    string tmp;
    cin >> T;
    while(T--){
        memset(food, -1, sizeof(food));
        memset(canEat, 0, sizeof(canEat));
        person_eat.clear();
        friends.clear();
        sol = INF;

        cin >> n >> m;
        
        for(int i=0; i<n; i++){
            cin >> tmp;
            friends.insert(make_pair(tmp,i));
        } 
        person_eat.resize(n);
        for(int i=0; i<m; i++){
            cin >> eat_n;
            for(int j=0; j<eat_n; j++){
                cin >> tmp;
                food[i][j] = friends[tmp];
                person_eat[friends[tmp]].push_back(i);
            } 
        }
        long long food_list;
        // getMinFoodNum(0, food_list);
        getMinFoodNum2(0);
        cout << sol << "\n";
    }
    return 0;
}