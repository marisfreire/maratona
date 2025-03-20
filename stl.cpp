
// LEMBRAR DE QUANDO PASSAR VETORES OU MAPAS COMO PARAMETROS PASSAR POR REFERENCIA (NAO FAZER COPIAS)
/// estrutura.size() retorna o tamanho da estrutura
// estrutura.empty() retorna se a estrutura está vazia ou não

// iteravel.begin() -> ponteiro para o primeiro elemento
// iteravel.end() -> ponteiro para uma posição depois do último elemento
//      !!OBS: Iteráveis são maps, sets, arrays, vectors, strings. Ints, long long, char não são iteráveis.


///////////// VECTOR //////////////////////

// Operações O(1)
// vector<tipo1, tipo2> lista;
// lista.push_back(elemento)  
// lista.pop_back() 

/////////// DEQUE ////////////

// Operações O(1)
// pop_front(), pop_back()
// push_back(elemento), push_front(elemento)

///////////// STACK //////////////////

// Operações O(1)
// pop() 
// push(elemento)

///////// QUEUE ////////////

// Operações O(1)
// push(elemento), pop() remove o elemento da frente
// front() mostra o elemento que tá na frente

/////////// PRIORITY QUEUE ////////

// O(Log N)
// Vai manter a prioridade
// pop() remove a frente
// top() frente


///////////// SET //////////

// O(Log N)
// Conjunto que mantém ordenado
// menor *s.begin()
// maior *s.rbegin()

////////// MAP ///////////

// O(Log N)
// mapa[chave]
// for (auto [chave, valor] : mapa)

///////// PAIR ///////////
// O(1)
// auto [f ,s] = par
// par.first
// par.second
// par<tipo1, tipo2> = {elemento1, elemento2};


/////// sort() //////
// O(N log N)
// sort(begin(vetor), end(vetor))

////// reverse() ////////
// O(N)
// inverte o vetor
// reverse(v.begin(), v.end())

/// PREFIX SUM ///

// O(N) - Build
// Build -> vetor 1 maior que o vetor original

vector<int> buildPrefix(vector<int> lista_original){
    vector<int> lista_ps(lista_original.size() + 1);
    lista_ps[0] = 0;
    for(int i = 0; i < lista_ps.size(); i++){
        lista_ps[i+1] = lista_ps[i] + lista_original[i];
    }
    return lista_ps
}

int sumQuery(vector<int> lista_ps, int esquerda, int direita){
    return lista_ps[direita + 1] - lista_ps[esquerda];
}

///// Subarray de soma K /////////
// Um subarray de soma K obedecerá a seguinte fórmula
// lista_ps[esquerda - 1] == lista_ps[direita] - K
// testa todos os R menores que Q

// Stack Monotônica //

// BACKTRACKING //
// data_structure candidate;
// do_the_thing(){
// incrementar contador se for um problema de contar candidatos validos
// appendar a um vetor se for um problema de enumerar candidatos validos
// habilitar um bool se for um problema de sim ou nao 
// etc }

// backtracking(i) sendo i o numero do passo atual
//      if candidate.is_full_valid_candidate(){
//      do_the_thing()
//      return }

//      for option in curr_options()
//      if is_valid_step(option):
//          candidate.add_step(option)
//          backtracking(i+1)
//          candidate.remove_step(option)

// PRESTA ATENÇÃO PARA BACKTRACKING: QUAIS SÃO OS CANDIDATOS RELEVANTES, QUAL A COMPLEXIDADE E QUAIS AS CONSTRAINTS

// BUSCA BINARIA //

//                         !!!!!!!!PRECISA SER EM UM VETOR ORDENADO

long long buscaBinaria(vector<long long>& lista, long long valor){
    long long esquerda = 0;
    long long direita = lista.size() - 1;
    while(esquerda <= direita){
        long long meio = (esquerda + direita)/2;
        if(lista[meio] == valor){
            // achei
            return meio
        } 
        if(lista[meio] > valor){
            direita = meio - 1;
        } else {
            esquerda = meio + 1;
        }
    }
}

// AMBAS ABAIXO RETORNAM ITERADORES
// O(log N) -> Melhor que map
//  lower_bound(v.begin(), v.end(), target) -> primeiro elemento >= target
// upper_bound(v.begin(), v.end(), target) -> primeiro elemento > target



// KNAPSACK
// Problemas em que temos uma certa capacidade para preencher com itens que tem pesos diferentes

vector<vector<ll>> memo((unsigned ll) QTDGRANDE, vector<ll>(QTDGRANDE,-1)); // quantidade de peso (Até 1e5) e qtde de itens (Até 100)

ll knapsack(vector<pair<int,int>>& itens, int peso, int item){
    if(peso == 0) return 0;
    if (item >= itens.size()) return 0;

    if (memo[peso][item] != -1 ) return memo[peso][item];

    ll resposta = knapsack(itens, peso, item+1);
    if(itens[item].first <= peso){
        resposta = max(resposta, itens[i].second + knapsack(itens, peso - itens[item].first, item + 1));
    }

    memo[peso][item] = resposta;
    return resposta;
};

// Resposta final
// itens é um vetor de pares {peso do item, valor do item}
knapsack(itens, peso, 0);


/////// LCS - LONGEST COMMON SEQUENCE
// Para problemas em que você quer a maior subsequência em comum entre s e t, pode ser string ou vetor 
// Complexidade O(tamanho de s * tamanho de t)
// usa busca binária

ll LCS(vector<ll>& sequencia1, vector<ll>& sequencia2, ll i, ll j){
    if(i >= sequencia1.size()) return 0
    if(j >= sequencia2.size()) return 0

    ll resposta = max(LCS(sequencia1, sequencia2, i+1, j), LCS(sequencia1, sequencia2, i, j+1));
    if(sequencia1[i] == sequencia2[j]){
        resposta = max(resposta, 1 + LCS(sequencia1, sequencia2, i+1, j+1))
    }
    return resposta
}

//////// LIS - Longest Increasing Subsequence
// Maior subsequência crescente e não necessariamente contígua em uma sequência s
ll LIS(vector<ll>& values){
    vector<ll> aux = {};
    for(unsigned ll i = 0; i < values.size(); i++){
        int pos = buscaBinaria(values[i], aux);
        if (pos == -1 || pos == aux.size()){
            aux.push_back(values[i]);
        } else if (values[i] != aux[pos]){
            aux[pos] = values[i];
        }
    }
    return aux.size();
}


////// CRIVO DE ERASTOTENES ////////
// ENCONTRAR TODOS OS NUMEROS PRIMOS
// Complexidade Temporal : O (N log(log N))
const int LIM = 1e6 + 5; // LIMITE
bool isPrime[LIM];

vector<int> crivo(){
    memset(isPrime, 1, sizeof(isPrime));
    isPrime[0] = isPrime[1] = false;

    vector<int> primes;
    for(int i = 2; i < LIM; i++){
        if(isPrime[i]){
            primes.push_back(i);
            for(int j = i*2; j < LIM; j += i){
                isPrime[j] = false;
            }
        }
    }
    return primes;
}


///      CONTAR A QUANTIDADE DE DIVISORES DE UM NÚMERO N
//      Se temos N = a * b, então a divide N e b divide N;
//      a vai ser <= sqrt(N) ou b vai ser < sqrt(N)
//      Complexidade O(sqrt(N))
int qntDivisores(int n){
    int cnt = 0;
    for(int i = 1; i*i <= n; i++){
        if(n % i == 0){
            cnt++;
            if(i != n/i){
                cnt++;
            }
        }
    }

    return cnt;
}

// DIVISORES PRIMOS
// Como obter o vetor dos números primos
vector<pair<int,int>> get_primes(int n){
    vector<pair<int,int>> primes;
    for(int i = 2; i*i<= n; i++){
        int cnt = 0;
        while(n%i == 0){
            n/=i;
            cnt++;
        }
        if(cnt > 0){
            primes.push_back({i,cnt});
        }
    }
    if(n > 1){
        primes.push_back({n,1});
    }
    return primes;
}

// MDC (GCD) E MMC (LCM)

ll gcd(ll a, ll b){
    if(!b) return a;
    return gcd(b, a % b);
}

ll lcm(ll a, ll b){
    return a/gcd(a,b) * b;
}