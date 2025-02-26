#include <bits/stdc++.h>
#define ll long long
#define el '\n'
using namespace std;
// so serve para prefix sum
struct segTree{
    double *seg;
    int N;
    segTree(int N){
        this->N = N;
        seg = new double[4*N];
    }
    // n = 1 
    // significa [nao utilizado, root, left child, right child];

    void build(const vector<double>& v, int no, int l, int r){
        if(r > this->N - 1) return;
        if(l == r){ seg[no] = v[l]; return; }

        
        int m = (l+r)/2; // meio
        int e = no*2; // esquerda
        int d = no*2 + 1; // direita

        build(v, e, l, m);
        build(v, d, m+1, r);

        seg[no] = seg[e] + seg[d];
    };


    void update(int pos, double val){
        return update_node(1, 1, N-1, pos, val);
    }
    void update_node(int no, int l, int r, int pos, double val){
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

    double query_node(int no, int l, int r, int lq, int rq){
        if(rq < l || r < lq) return 0; // fora do intervalo
        if(lq <= l && r <= rq) return seg[no];
        int m = (l+r)/2; // meio
        int e = no*2; // esquerda
        int d = no*2 + 1; // direita

        return query_node(e, l, m, lq, rq) + query_node(d, m+1, r, lq, rq);
    }

    double query(int lq, int rq){
        return query_node(1,1,N-1, lq,rq);
    }
};
int main(){
    int n; cin >> n;
    segTree seg(n+1);
    vector<double> notas(n+1);

    for(int i = 1; i < n+1; i++){
        double nota; cin >> nota;
        notas[i] = nota;
    }
    seg.build(notas, 1,1, n);
    int q; cin >> q;
    while(q--){
        int t; cin >> t;
        if(t == 1){
            int e; cin >> e;
            double new_nota; cin >> new_nota;
            seg.update(e, new_nota);
        } else {
            int l; cin >> l;
            int r; cin >> r;
            double sum = seg.query(l,r);
            cout << (double) sum / (r - l + 1) << el;
        }
    }

    return 0;
}