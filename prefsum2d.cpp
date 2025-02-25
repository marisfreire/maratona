#include <bits/stdc++.h>
using namespace std;
struct PrefixSum2D{    // building a 2D prefix sum
    const static int N = (int)1e6 + 2;
    const static int M = (int) 1e6 + 2;
    int ps[N][M];

    void build(vector<vector<long long>>& val){
        for(int i = 1;i < N; i++){
            for(int j = 1; j < M; j++){
                ps[i][j] = val[i][j] + ps[i-1][j] + ps[i][j-1] - ps[i-1][j-1];

            }
        }
    }

    long long query(int xi, int yi, int xf, int yf){
        return ps[xf][yf]
        - ps[xf][yi-1] - ps[xi-1][yf] + ps[xi-1][yi-1];
    }
};