/*
   "You cannot believe in God until you believe in yourself."
                                          by Swami Vivekananda
*/

#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
const char el = '\n';
const char sp = ' ';
const int mod = 1e9 + 7;
const int inf = INT_MAX;
// const ld ep = 0.0000001;
// const ld pi = acos(-1.0);

#define rep(i, a, b) for (int i = (a); i < (b); ++i)
#define rev(i, a, b) for (int i = (a); i > (b); --i)
#define eif(cds, a, b) ((cds) ? (a) : (b))

#define setpr(x) cout << setprecision(x) << fixed
#define sz size()

using pii = pair<int, int>;
#define ff first
#define ss second
#define mp make_pair

using vb = vector<bool>;
using vi = vector<int>;
#define pb push_back
#define eb emplace_back
#define all(a) a.begin(), a.end()

template <typename T1, typename T2> using P = pair<T1, T2>;
template <typename T> using V = vector<T>;
template <typename T> using pq = priority_queue<T>;
template <typename T> using pqg = priority_queue<T, vector<T>, greater<T>>;
template <typename T1, typename T2> using umap = unordered_map<T1, T2>;
template <typename T> using uset = unordered_set<T>;

const int N = 100000 + 5;
ll fact[N], invfact[N];

long long invM(ll a)
{
   int b = mod - 2;
   long long ans = 1;

   while (b)
   {
      if (b & 1)
         ans = (1ll * ans * a) % mod;
      a = (1ll * a * a) % mod;
      b >>= 1;
   }

   return ans;
}

void factorialcul()
{
   fact[0] = 1;
   for (int i = 1; i < N; i++)
   {
      fact[i] = ((fact[i - 1] % mod) * (i % mod)) % mod;
   }

   invfact[N - 1] = invM(fact[N - 1]);
   for (int i = N - 2; i >= 0; --i)
   {
      invfact[i] = ((invfact[i + 1] % mod) * (i + 1)) % mod;
   }

   return;
}

ll ncr(ll n, ll r)
{
   if (r > n)
      return 0ll;

   ll res = fact[n] % mod;
   res = (res * (invfact[n - r] % mod)) % mod;
   res = (res * (invfact[r] % mod)) % mod;

   return res;
}

int32_t main()
{
   ios_base::sync_with_stdio(0);
   cin.tie(0), cout.tie(0);

   factorialcul();

   int n, m, k;
   cin >> n >> m >> k;

   int ans = 0;

   for (int i = 0, t; i <= n; i++)
   {
      t = ncr(n, i);
      if (t < 0)
         t += mod;

      if (n + k - i * m - 1 < n - 1)
         break;
      t = (t * ncr(n + k - i * m - 1, n - 1)) % mod;

      if (t < 0)
         t += mod;

      if (i & 1)
         ans = (ans - t + mod) % mod;
      else
         ans = (ans + t) % mod;
   }

   cout << ans;

   return 0;
}
