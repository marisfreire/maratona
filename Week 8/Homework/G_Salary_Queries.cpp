#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define el '\n'
#define step(begin,end) for(ll i = begin; i < end; i++)

template<typename T>
T nxt(){
    T x; cin >> x;
    return x;
}
struct segTree{
    pair<ll,ll> *seg;
    int N;
    segTree(int N){
        this->N = N;
        seg = new pair<ll,ll>[4*N];
    }
    // n = 1 
    // significa [nao utilizado, root, left child, right child];

    void build(const vector<ll>& v, int no, int l, int r){
        if(r > this->N - 1) return;
        if(l == r){ seg[no] = {v[l], v[l]}; return; }

        int m = (l+r)/2; // meio
        int e = no*2; // esquerda
        int d = no*2 + 1; // direita

        build(v, e, l, m);
        build(v, d, m+1, r);

        seg[no] = {min(seg[e].first, seg[d].first), max(seg[e].second, seg[d].second)};
    };


    void update(int pos, int val){
        return update_node(1, 1, N-1, pos, val);
    }
    void update_node(int no, int l, int r, int pos, int val){
        // estou fora do intervalo
        if((pos < l) || (r < pos)) return;
        if(l == r){ seg[no] = {val, val}; // atualizo o valor do nó
        return;}

        int m = (l+r)/2; // meio
        int e = no*2; // esquerda
        int d = no*2 + 1; // direita

        update_node(e,l,m,pos,val); // ir pra esquerda, pega o intervalo [L, (L+R)/2]
        update_node(d, m+1, r, pos, val); // ir pra direita, pega o intervalo [(L+R)/2 + 1, R]

        seg[no] = {min(seg[e].first, seg[d].first), max(seg[e].second, seg[d].second)}; 
    }

    ll query_node(int no, int l, int r, int min, int max){
        if(0 > l || r > N - 1 || no > (4 * N)) return 0; // fora do intervalo
        if(seg[no].first >= min && seg[no].second <= max){
            if(no == 1) return r;
            if(l == r) return 1;
            return (r - l) + 1;
        }
        if(l == r){ return 0 ; }
        int m = (l+r)/2; // meio
        int e = no*2; // esquerda
        int d = no*2 + 1; // direita


        return query_node(e, l, m, min, max) + query_node(d, m+1, r, min, max);
    }

    ll query(int min, int max){
        return query_node(1,1,N-1, min,max);
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n = nxt<int>();
    int q = nxt<int>();
    // Meu update: mudar o salário
    // Meu query: contar o número de pessoas com salário entre [a,b]
    // armazenar [Minimo daquele intervalo, maximo daquele intervalo] no nó
    // nao precisaria nem ordenar por que eu garantiria que todo mundo DAQUELE intervalo é ou maior que o min ou menor que o maximo, então l - r seria a quantidade de elementos que satisfazem aquela condição
    vector<ll> v(n+1);
    segTree seg(n+1);
    step(1, n+1){
        v[i] = nxt<ll>();
    }
    seg.build(v, 1, 1, n);

    while(q--){
        char query = nxt<char>();
        if(query == '?'){
            int min = nxt<int>();
            int max = nxt<int>();
            cout << seg.query(min, max) << el;
        } else {
            int pos = nxt<int>();
            int val = nxt<ll>();
           seg.update(pos, val);
        }
    }
    return 0;
}