#include <iostream>
#include <algorithm>
#include <cstring>
#include <bitset>
#define fastio ios_base::sync_with_stdio(false), cin.tie(NULL);
#define INF 987654321
#define MAXN 12
using namespace std;

int N, K, M, L;
int prior_subject[MAXN];
int open_subject[10];
int cache[10][1<<MAXN];

void input();
int sol(int taken, int semester);

int main()
{
    fastio;
    int C;
    cin >> C;
    while(C--){
        memset(prior_subject,0,sizeof(prior_subject));
        memset(open_subject,0,sizeof(open_subject));
        memset(cache,-1,sizeof(cache));
        input();
        int solution = sol(0,0);
        if(solution == INF)
            cout << "IMPOSSIBLE\n";
        else
            cout << solution << "\n";
    }

    return 0;
}

void input(){
    cin >> N >> K >> M >> L;
    //선이수과목
    for(int i=0; i<N; i++){
        int cnt, tmp;
        cin >> cnt;
        for(int j=0; j<cnt; j++){
            cin >> tmp;
            prior_subject[i] |= (1<<tmp);
        }
    }
    //학기당 개설과목
    for(int i=0; i<M; i++){
        int cnt, tmp;
        cin >> cnt;
        for(int j=0; j<cnt; j++){
            cin >> tmp;
            open_subject[i] |= (1<<tmp);
        }
    }
}

int sol(int taken, int semester){
    if(__builtin_popcount(taken) >= K) return 0;
    if(semester == M) return INF;

    int& ret = cache[semester][taken];
    if(ret != -1) return ret;

    ret = INF; 
    int canTake = (open_subject[semester] & ~taken);

    for(int i = 0; i < N; i++){
        //선수과목 조건 못맞추는과목 버리기
        if((canTake & (1 << i)) && (taken &  prior_subject[i]) != prior_subject[i])
            canTake &= ~(1 << i);
    }

    for(int take = canTake; take > 0; take = ((take-1) & canTake)){
        if(__builtin_popcount(take)>L) continue;
        ret = min(ret, sol(taken | take, semester + 1) + 1);
    }
    ret = min(ret, sol(taken, semester+1));

    return ret;
}