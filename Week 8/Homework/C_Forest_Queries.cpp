#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define el '\n'

template<typename T>
T nxt(){
    T x; cin >> x;
    return x;
}

struct PrefixSum2D{    // building a 2D prefix sum

    const static int N = 1005;
    const static int M = 1005;
    int ps[N][M];

    void build(vector<vector<long long>>& val, int n, int m){
        for(int i = 1;i < n; i++){
            for(int j = 1; j < m; j++){
                ps[i][j] = val[i][j] + ps[i-1][j] + ps[i][j-1] - ps[i-1][j-1];
            }
        }
    }

    long long query(int xi, int yi, int xf, int yf){
        return ps[xf][yf]
        - ps[xf][yi-1] - ps[xi-1][yf] + ps[xi-1][yi-1];
    }
};

int main (){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n = nxt<int>();
    vector<vector <long long>> grid(n,vector<long long>(n));
    PrefixSum2D ps;

    int q = nxt<int>();

    for(int i= 0; i < n; i++){
        for(int j = 0; j < n; j++){
            grid[i][j] = (nxt<char>() == '*') ? 1 : 0;
        }
    }
    ps.build(grid, n, n);

    while(q--){
        int y1 = nxt<int>();
        int x1 = nxt<int>();
        int y2 = nxt<int>();
        int x2 = nxt<int>();
        cout << ps.query(x1-1,y1-1,x2-1,y2-1) << el;
    }
    return 0;
}