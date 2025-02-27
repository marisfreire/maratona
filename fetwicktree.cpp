#include <bits/stdc++.h>
#define ll long long
using namespace std;
// so serve para prefix sum
struct FenwickTree{
    ll *ft;
    int N;
    FenwickTree(int N){
        this->N = N+1;
        ft = new ll[N+1];
    }

    void build(vector<ll>& v, int n){
        for(int i = 1; i < n; i++){
            int pos = i;
            while((pos) <= n){
                ft[pos] += v[i];
                pos += (pos&(-pos));
        }    
        }
    }

    void update(int pos, ll val){
        ll diff = val - ft[pos];
        ft[pos] = val;
        while(pos <= N){
            ft[pos] += diff;
            pos += (pos&(-pos));
        }
    }

    ll query(int pos){
        ll sum = 0;
        while(pos > 0){
            sum += ft[pos];
            pos -= (pos&(-pos));
        }
        return sum;
    }
};