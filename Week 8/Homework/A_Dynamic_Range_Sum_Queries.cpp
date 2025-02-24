#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define el '\n'
#define step(begin,end) for(ll i = begin; i < end; i++)
#define vi vector<int>

ll nxt(){
    ll x; cin >> x;
    return x;
}
struct segTree{
    ll *seg;
    int N;
    segTree(int N){
        this->N = N;
        seg = new ll[4*N];
    }
    // n = 1 
    // significa [nao utilizado, root, left child, right child];

    void build(const vector<ll>& v, int no, int l, int r){
        if(r > this->N - 1) return;
        if(l == r){ seg[no] = v[l]; return; }

        
        int m = (l+r)/2; // meio
        int e = no*2; // esquerda
        int d = no*2 + 1; // direita

        build(v, e, l, m);
        build(v, d, m+1, r);

        seg[no] = seg[e] + seg[d];
    };


    void update(int pos, int val){
        return update_node(1, 1, N-1, pos, val);
    }
    void update_node(int no, int l, int r, int pos, int val){
        // estou fora do intervalo
        if((pos < l) || (r < pos)) return;
        if(l == r){ seg[no] = val; // atualizo o valor do nó
        return;}

        int m = (l+r)/2; // meio
        int e = no*2; // esquerda
        int d = no*2 + 1; // direita

        update_node(e,l,m,pos,val); // ir pra esquerda, pega o intervalo [L, (L+R)/2]
        update_node(d, m+1, r, pos, val); // ir pra direita, pega o intervalo [(L+R)/2 + 1, R]

        seg[no] = seg[e] + seg[d]; 
    }

    ll query_node(int no, int l, int r, int lq, int rq){
        if(rq < l || r < lq) return 0; // fora do intervalo
        if(lq <= l && r <= rq) return seg[no];
        int m = (l+r)/2; // meio
        int e = no*2; // esquerda
        int d = no*2 + 1; // direita

        return query_node(e, l, m, lq, rq) + query_node(d, m+1, r, lq, rq);
    }

    ll query(int lq, int rq){
        return query_node(1,1,N-1, lq,rq);
    }
};

int main(){
    
    int n = nxt();
    int q = nxt();

    vector<ll> nums(n+1);
    step(1, n+1){
        nums[i] = nxt();
    }
    
    segTree seg(n+1);
    seg.build(nums, 1, 1, n);

    while(q--){
        int type_query = nxt();
        if(type_query == 1){
            // update
            int pos_update = nxt();
            ll novo_valor = nxt();
            seg.update(pos_update, novo_valor);
        } else{
            // return sum
            int a = nxt();
            int b = nxt();
            cout << seg.query(a,b) << el;
        }
    }
    return 0;
}