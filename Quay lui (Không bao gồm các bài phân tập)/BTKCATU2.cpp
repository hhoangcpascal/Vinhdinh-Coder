#pragma GCC optimize("O2")
#include <iostream>
#include <algorithm>
#define fname "BTKCATU2"
#define llong long long
#define FOR(i, a, b) for(__typeof(a) i = a; i <= b; ++i)

using namespace std;

struct Data {
    llong val;
    llong weight;
    int p[26];

    bool operator < (const Data &other) const {
        return weight < other.weight;
    }
} P[16006], P2[16006], val_max[16006];

int w[26], v[26], x[26];
int n, n1, m1 = 0, m2 = 0;
llong W, w2[16006];

void enter() {
    scanf("%d%I64d", &n, &W); n1 = (n >> 1);
    for(int i=1; i<=n; ++i) scanf("%d%d", &w[i], &v[i]);
}

void perfect1() {
    llong sum_val = 0, sum_weight = 0; ++m1;
    FOR(i, 1, n1) sum_weight += x[i]*w[i], sum_val += v[i]*x[i], P[m1].p[i] = x[i];
    P[m1].val = sum_val;
    P[m1].weight = sum_weight;
}

void perfect2() {
    llong sum_val = 0, sum_weight = 0; ++m2;
    FOR(i, n1+1, n) sum_weight += x[i]*w[i], sum_val += v[i]*x[i], P2[m2].p[i] = x[i];
    P2[m2].val = sum_val;
    P2[m2].weight = sum_weight;
}

void try1(int cnt) {
    if (cnt == n1 + 1) {
        perfect1();
        return;
    }
    FOR(i, 0, 1) x[cnt] = i, try1(cnt+1);
}

void try2(int cnt) {
    if (cnt == n + 1) {
        perfect2();
        return;
    }
    FOR(i, 0, 1) x[cnt] = i, try2(cnt+1);
}

void init() {
    for(int i=1; i<=m2; ++i) {
        w2[i] = P2[i].weight;
        val_max[i] = val_max[i-1];
        if (P2[i].val > val_max[i].val) val_max[i] = P2[i];
    }
}

void find_max() {
    llong res = 0;
    static int trace[26], cnt;
    FOR(i, 1, n) trace[i] = 0;
    FOR(i, 1, m1) {
        if (P[i].weight > W) continue;
        int j = upper_bound(w2+1, w2+m2+1, W - P[i].weight) - w2;
        if (res < P[i].val + val_max[j-1].val) {
            res = P[i].val + val_max[j-1].val;
            cnt = 0;
            FOR(k, 1, n1)
                if (P[i].p[k] == 1) trace[++cnt] = k;
            FOR(k, n1+1, n)
                if (val_max[j-1].p[k] == 1) trace[++cnt] = k;
        }
     }
    cout << cnt << "\n";
    FOR(i, 1, cnt) cout << trace[i] << " ";
}

int main() {

    enter();
    try1(1);
    try2(n1+1);

    sort(P2+1, P2+m2+1);
    init();
    find_max();

    return 0;
}
    
