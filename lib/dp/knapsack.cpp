#include <bits/stdc++.h>
using namespace std;
#define MAX (long long) 1e4
#define MAX_CAP (long long) 1e4
#define INF INT_MAX

int v[MAX], w[MAX]; 
int dp[2][MAX_CAP];

void get_dp(int x, int l, int r, int cap) {
	memset(dp[x], 0, (cap+1)*sizeof(dp[x][0]));
	for (int i = l; i <= r; i++) for (int j = cap; j >= 0; j--)
		if (j - w[i] >= 0) dp[x][j] = max(dp[x][j], v[i] + dp[x][j - w[i]]);
}

void solve(vector<int>& ans, int l, int r, int cap) {
	if (l == r) {
		if (w[l] <= cap) ans.push_back(l);
		return;
	}
	int m = (l+r)/2;
	get_dp(0, l, m, cap), get_dp(1, m+1, r, cap);
	int left_cap = -1, opt = -INF;
	for (int j = 0; j <= cap; j++)
		if (int at = dp[0][j] + dp[1][cap - j]; at > opt)
			opt = at, left_cap = j;
	solve(ans, l, m, left_cap), solve(ans, m+1, r, cap - left_cap);
}

vector<int> knapsack(int n, int cap) {
	vector<int> ans;
	solve(ans, 0, n-1, cap);
	return ans;
}


/*LATEX_DESC_BEGIN***************************

Resolve mochila, recuperando a resposta
DP usando os itens [l, r], com capacidade = cap
v[max] e w[MAX] valor e peso


    Complexidade:
    -> O(n * cap), O(n + cap)
*****************************LATEX_DESC_END*/