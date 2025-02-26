#include <bits/stdc++.h>
using namespace std;
struct PrefixSum2D{    // building a 2D prefix sum

    const static int N = 1005;
    const static int M = 1005;
    int ps[N][M];

    // matriz original 0 indexada
    void build(vector<vector<long long>>& val, int n, int m){
        for(int i = 1;i < n+1; i++){
            for(int j = 1; j < m+1; j++){
                ps[i][j] = val[i-1][j-1] + ps[i-1][j] + ps[i][j-1] - ps[i-1][j-1];
            }
        }
    }
    // diminuir os valores antes de enviar caso sejam 1-indexados.
    long long query(int xi, int yi, int xf, int yf){
        return ps[xf][yf]
        - ps[xf][yi-1] - ps[xi-1][yf] + ps[xi-1][yi-1];
    }
};
