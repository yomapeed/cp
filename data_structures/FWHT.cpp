#include <bits/stdc++.h>
#include <x86intrin.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define END "\n"
#define rall(v) (v).rbegin(), (v).rend()
#define all(v) (v).begin(), (v).end()
#define fastio                                                                 \
    ios_base::sync_with_stdio(false);                                          \
    cin.tie(NULL);                                                             \
    cout.tie(NULL);
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

typedef unsigned long long ull;

namespace fwht {
template <typename T> void hadamard(vector<T> &a) {
    int n = a.size();
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += 2 * k) {
            for (int j = 0; j < k; j++) {
                T x = a[i + j];
                T y = a[i + j + k];
                a[i + j] = x + y;
                a[i + j + k] = x;
            }
        }
    }
}
template <typename T> vector<T> multiply(vector<T> a, vector<T> b) {
    int eq = (a == b);
    int n = 1;
    while (n < (int)max(a.size(), b.size())) {
        n <<= 1;
    }
    a.resize(n);
    b.resize(n);
    hadamard(a);
    if (eq)
        b = a;
    else
        hadamard(b);
    for (int i = 0; i < n; i++) {
        a[i] *= b[i];
    }
    hadamard(a);
    // cout << "WTF: " << endl;
    // for (int i = 0; i < n; ++i) {
    //     cout << a[i] << " ";
    // }
    // cout << END;
    // T q = 1 / static_cast<T>(n);
    // std::cout << q << " " << n << std::endl;
    for (int i = 0; i < n; i++) {
        a[i] /= n;
    }
    return a;
}
} // namespace fwht
// 00000
// 00001
// 00010
// 00011
// 00100
// 00110
// 01000
// 10000
// 11000

template <typename T>
T inverse(T a, T m) {
  T u = 0, v = 1;
  while (a != 0) {
    T t = m / a;
    m -= t * a; swap(a, m);
    u -= t * v; swap(u, v);
  }
  assert(m == 1);
  return u;
}
template <typename T>
class Modular {
 public:
  using Type = typename decay<decltype(T::value)>::type;
  constexpr Modular() : value() {}
  template <typename U>
  Modular(const U& x) {
    value = normalize(x);
  }
  template <typename U>
  static Type normalize(const U& x) {
    Type v;
    if (-mod() <= x && x < mod()) v = static_cast<Type>(x);
    else v = static_cast<Type>(x % mod());
    if (v < 0) v += mod();
    return v;
  }
  const Type& operator()() const { return value; }
  template <typename U>
  explicit operator U() const { return static_cast<U>(value); }
  constexpr static Type mod() { return T::value; }
  Modular& operator+=(const Modular& other) { if ((value += other.value) >= mod()) value -= mod(); return *this; }
  Modular& operator-=(const Modular& other) { if ((value -= other.value) < 0) value += mod(); return *this; }
  template <typename U> Modular& operator+=(const U& other) { return *this += Modular(other); }
  template <typename U> Modular& operator-=(const U& other) { return *this -= Modular(other); }
  Modular& operator++() { return *this += 1; }
  Modular& operator--() { return *this -= 1; }
  Modular operator++(int) { Modular result(*this); *this += 1; return result; }
  Modular operator--(int) { Modular result(*this); *this -= 1; return result; }
  Modular operator-() const { return Modular(-value); }
  template <typename U = T>
  typename enable_if<is_same<typename Modular<U>::Type, int>::value, Modular>::type& operator*=(const Modular& rhs) {
#ifdef _WIN32
    uint64_t x = static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value);
    uint32_t xh = static_cast<uint32_t>(x >> 32), xl = static_cast<uint32_t>(x), d, m;
    asm(
      "divl %4; \n\t"
      : "=a" (d), "=d" (m)
      : "d" (xh), "a" (xl), "r" (mod())
    );
    value = m;
#else
    value = normalize(static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value));
#endif
    return *this;
  }
  template <typename U = T>
  typename enable_if<is_same<typename Modular<U>::Type, int64_t>::value, Modular>::type& operator*=(const Modular& rhs) {
    int64_t q = static_cast<int64_t>(static_cast<long double>(value) * rhs.value / mod());
    value = normalize(value * rhs.value - q * mod());
    return *this;
  }
  template <typename U = T>
  typename enable_if<!is_integral<typename Modular<U>::Type>::value, Modular>::type& operator*=(const Modular& rhs) {
    value = normalize(value * rhs.value);
    return *this;
  }
  Modular& operator/=(const Modular& other) { return *this *= Modular(inverse(other.value, mod())); }
  template <typename U>
  friend bool operator==(const Modular<U>& lhs, const Modular<U>& rhs);
  template <typename U>
  friend bool operator<(const Modular<U>& lhs, const Modular<U>& rhs);
  template <typename U>
  friend std::istream& operator>>(std::istream& stream, Modular<U>& number);
 private:
  Type value;
};
template <typename T> bool operator==(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value == rhs.value; }
template <typename T, typename U> bool operator==(const Modular<T>& lhs, U rhs) { return lhs == Modular<T>(rhs); }
template <typename T, typename U> bool operator==(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) == rhs; }
template <typename T> bool operator!=(const Modular<T>& lhs, const Modular<T>& rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(const Modular<T>& lhs, U rhs) { return !(lhs == rhs); }
template <typename T, typename U> bool operator!=(U lhs, const Modular<T>& rhs) { return !(lhs == rhs); }
template <typename T> bool operator<(const Modular<T>& lhs, const Modular<T>& rhs) { return lhs.value < rhs.value; }
template <typename T> Modular<T> operator+(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U> Modular<T> operator+(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) += rhs; }
template <typename T, typename U> Modular<T> operator+(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) += rhs; }
template <typename T> Modular<T> operator-(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U> Modular<T> operator-(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T, typename U> Modular<T> operator-(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) -= rhs; }
template <typename T> Modular<T> operator*(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U> Modular<T> operator*(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T, typename U> Modular<T> operator*(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) *= rhs; }
template <typename T> Modular<T> operator/(const Modular<T>& lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> operator/(const Modular<T>& lhs, U rhs) { return Modular<T>(lhs) /= rhs; }
template <typename T, typename U> Modular<T> operator/(U lhs, const Modular<T>& rhs) { return Modular<T>(lhs) /= rhs; }
template<typename T, typename U>
Modular<T> power(const Modular<T>& a, const U& b) {
  assert(b >= 0);
  Modular<T> x = a, res = 1;
  U p = b;
  while (p > 0) {
    if (p & 1) res *= x;
    x *= x;
    p >>= 1;
  }
  return res;
}
template <typename T>
string to_string(const Modular<T>& number) {
  return to_string(number());
}
template <typename T>
std::ostream& operator<<(std::ostream& stream, const Modular<T>& number) {
  return stream << number();
}
template <typename T>
std::istream& operator>>(std::istream& stream, Modular<T>& number) {
  typename common_type<typename Modular<T>::Type, int64_t>::type x;
  stream >> x;
  number.value = Modular<T>::normalize(x);
  return stream;
}
/*
using ModType = int;
struct VarMod { static ModType value; };
ModType VarMod::value;
ModType& md = VarMod::value;
using Mint = Modular<VarMod>;
*/
constexpr int md = 1e9 + 7;
using Mint = Modular<std::integral_constant<decay<decltype(md)>::type, md>>;
template< typename T >
void fast_walsh_hadamard_transform(vector< T > &f, bool inv = false) {
  const int n = (int) f.size();
  assert((n & (n - 1)) == 0);
  for(int i = 1; i < n; i <<= 1) {
    for(int j = 0; j < n; j += i << 1) {
      for(int k = 0; k < i; k++) {
        T s = f[j + k], t = f[j + k + i];
        f[j + k] = s | t;
        f[j + k + i] = s - t;
      }
    }
  }
//   if(inv) {
//     // T inv_n = T(1) / n;
//     for(auto &x : f) x /= n;
//   }
}

/**
 * @brief Bitwise Xor Convolution (Bitwise-XOR畳み込み)
 */
template< typename T >
vector< T > bitwise_xor_convolution(vector< T > f, vector< T > g) {
  const int n = (int) f.size();
  assert(f.size() == g.size());
  assert((n & (n - 1)) == 0);
  fast_walsh_hadamard_transform(f, false);
  fast_walsh_hadamard_transform(g, false);
  for(int i = 0; i < n; i++) f[i] = f[i] | g[i];
  fast_walsh_hadamard_transform(f, true);
  return f;
}

vector<int> transform(vector<int> P, bool inverse) {
    for (int len = 1; 2 * len <= P.size(); len <<= 1) {
        for (int i = 0; i < P.size(); i += 2 * len) {
            for (int j = 0; j < len; j++) {
                int u = P[i + j];
                int v = P[i + len + j];
                // P[i + j] = u + v;
                // P[i + j + len] = u - v;
                if (!inverse) {
                    P[i + j] = u + v;
                    P[i + len + j] = u;
                } else {
                    P[i + j] = v;
                    P[i + len + j] = u - v;
                }
            }
        }
    }
    // if (inverse) {
    //     for (int i = 0; i < P.size(); i++)
    //         P[i] = P[i] / P.size();
    // }
    return P;
}

long long binpow(long long a, long long b) {
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}

template <class ForwardIterator>
void transform(ForwardIterator first, ForwardIterator last) {
  int n = std::distance(first, last);
  assert(n and (n & (n - 1)) == 0);
  for (int step = 1; step < n; step *= 2)
    for (auto i = first; i != last;) {
      auto j = std::next(i, step);
      for (auto end = j; i != end; ++i, ++j) *j += *i;
      i = j;
    }
}
template <class ForwardIterator>
void inverse_transform(ForwardIterator first, ForwardIterator last) {
  int n = std::distance(first, last);
  assert(n and (n & (n - 1)) == 0);
  for (int step = 1; step < n; step *= 2)
    for (auto i = first; i != last;) {
      auto j = std::next(i, step);
      for (auto end = j; i != end; ++i, ++j) *j -= *i;
      i = j;
    }
}

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<bool>> A(n, vector<bool>(n, 0));
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        A[a][b] = A[b][a] = 1;
    }
    int mmask = (1 << n);
    vector<int> poly(mmask);
    vector<int> pow2(25);
    for (int i = 0; i < 25; ++i) pow2[i] = (1 << i);
    poly[0] = 1;
    for (int i = 0; i < mmask; ++i) {
        if (!poly[i])
            continue;
        // vector<int> cur;
        int cnt = 0;
        for (int j = 0; j < n; ++j) {
            if (i & pow2[j]){
                    ++cnt;
                    // cur.push_back(j);
                }
        }
        if (cnt == k)
            continue;
        for (int j = 0; j < n; ++j) {
            if (i & pow2[j] || (poly[i | pow2[j]]))
                continue;
            bool ok = true;
            // for (auto u : cur) {
            //     if (!A[u][j]) {
            //         ok = false;
            //         break;
            //     }
            // }
            for (int l = 0; l < n; ++l) {
                if ((i & pow2[l]) && (!A[l][j])) {
                    ok = false;
                    break;
                }
            }
            if (ok)
                poly[i | pow2[j]] = 1;
        }
    }
    // for (int i = 0; i < mmask; ++i) {
    //     cout << poly[i] << " ";
    // }
    // cout << endl;
    vector<int> res = poly;
    int count = 1;

    // while (!res.back()) {
    //     ++count;
    //     // assert(count <= n + 5);
    //     for (int i = 0; i < mmask; ++i) {
    //         res[i] = res[i] != 0;
    //     }
    //     // res = fwht::multiply(res, poly);
    //     // res = subset_convolution(res, poly);
    //     res = bitwise_xor_convolution(res, poly);

    //     // cout << "After " << count - 1 << END;
    //     // for (int i = 0; i < mmask; ++i) {
    //     //     cout << res[i] << " ";
    //     // }
    //     // cout << endl;
    //     // if (count > 1) break;
    // }
    int lo = 1, hi = n, ans = -1;
    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        // auto v = t.pow(M, poly, mid, OR);
        // auto now = transform(poly, false);
        vector<int> now = poly;
        transform(now.begin(), now.end());
        for (int i = 0; i < mmask; ++i) {
            now[i] = binpow(now[i], mid);
        }
        inverse_transform(now.begin(), now.end());
        // now = transform(now, true);
        
        // cout << mid << endl;
        // for (int i = 0; i < mmask; ++i) cout << v[i] << " ";
        // cout << endl;
        if (now[mmask - 1]) ans = mid, hi = mid - 1;
        else lo = mid + 1;
    }
    cout << ans << END;
    // cout << count << END;
}
int main() {
    fastio int t = 1;
    cin >> t;
    while (t--)
        solve();
    return 0;
}