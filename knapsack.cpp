#include <bits/stdc++.h>
#define ll long long
#define el '\n'
#define step(begin, end) for(ll i = begin; i < end; i++)
#define stepdown(begin, end) for(ll i = begin; i > end; i--)
using namespace std;

vector<vector<ll>> memo((unsigned ll) 1e5 + 5, vector<ll>(105,-1)); // quantidade de peso (Até 1e5) e qtde de itens (Até 100)

ll knapsack(vector<pair<int,int>>& itens, int W, int i){
    if(W == 0) return 0;
    if (i >= itens.size()) return 0;

    if (memo[W][i] != -1 ) return memo[W][i];

    ll ans = knapsack(itens, W, i+1);
    if(itens[i].first <= W){
        ans = max(ans, itens[i].second + knapsack(itens, W - itens[i].first, i + 1));
    }

    memo[W][i] = ans;
    return ans;
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // cada item tem um valor de V e peso de W
    // preciso saber o quanto a mochila ainda aguenta de forma que não atinja capacidade máxima e segure o maior número possível de itens

    int n; int W;
    cin >> n; cin >> W;
    vector<pair<int,int>> itens; // pares {peso, valor}
    while(n--){
        ll v; int w;
        cin >> w; cin >> v;
        itens.push_back({w,v});
    }

    cout << knapsack(itens, W, 0) << el;
    return 0;
}