#include <iostream>
#include <algorithm>
#include <cstring>
#define fastio ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define INF 987654321

using namespace std;

int arr[100], pSum[100], pSqSum[100];
int N, S;

void precalc(){
    sort(arr, arr+N);
    pSum[0] = arr[0];
    pSqSum[0] = arr[0] * arr[0];
    for(int i=1; i<N; i++){
        pSum[i] = pSum[i-1] + arr[i];
        pSqSum[i] = pSqSum[i-1] + arr[i] * arr[i];
    }
}

int minError(int lo, int hi){
    int sum = pSum[hi] - (lo == 0 ? 0 : pSum[lo-1]);
    int sqSum = pSqSum[hi] - (lo == 0 ? 0 : pSqSum[lo-1]);
    int m = round((double)sum / (hi - lo + 1));

    return (hi - lo + 1) * m * m - 2 * m * sum + sqSum;
}

int cache[100][11];
int quantize(int from, int parts){
    if(from == N) return 0;
    if(parts == 0) return INF;
    int& ret = cache[from][parts];
    if(ret != -1) return ret;
    ret = INF;

    for(int partSize = 1; partSize < N-from + 1; partSize++)
        ret = min(ret, minError(from,from+partSize-1) + quantize(from+partSize,parts-1));
    return ret;
}

int main()
{
    int C;
    cin >> C;
    while(C--){
        cin >> N >> S;
        memset(cache,-1,sizeof(cache));
        memset(arr,0,sizeof(arr));
        for(int i=0; i<N; i++) cin >> arr[i];
        precalc();
        cout << quantize(0, S) << "\n";
    }

    return 0;
}