#include <bits/stdc++.h>
#define ll long long
using namespace std;
// so serve para prefix sum
struct FenwickTree{
    ll *ft;
    int N;
    FenwickTree(int N){
        this->N = N;
        ft = new ll[N];
    }

    void update(int pos, ll val){
        while(pos < N){
            ft[pos] += val;
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