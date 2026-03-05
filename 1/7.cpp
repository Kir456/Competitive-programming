#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
const ull BASE = 91138233;

struct Hasher {
    vector<ull> h, p;
    Hasher(const string& s) {
        int n = s.size();
        h.resize(n + 1);
        p.resize(n + 1);
        p[0] = 1;
        for (int i = 0; i < n; ++i) {
            h[i + 1] = h[i] * BASE + (s[i] - 'a' + 1);
            p[i + 1] = p[i] * BASE;
        }
    }
    ull get_hash(int l, int r) const {
        return h[r + 1] - h[l] * p[r - l + 1];
    }
};

bool is_less(const string& s, const Hasher& hasher,
             int l1, int r1, int l2, int r2) {
    int len1 = r1 - l1 + 1, len2 = r2 - l2 + 1;
    int lo = 0, hi = min(len1, len2);
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (hasher.get_hash(l1, l1 + mid - 1) == hasher.get_hash(l2, l2 + mid - 1))
            lo = mid;
        else
            hi = mid - 1;
    }
    if (lo == min(len1, len2)) 
        return len1 < len2;
    else  
        return s[l1 + lo] < s[l2 + lo];
}

void solve() {
    int n, k;
    cin >> n >> k;
    vector<string> s(n);
    for (int i = 0; i < n; ++i) cin >> s[i];

    string T;
    vector<int> start(n), len(n);
    for (int i = 0; i < n; ++i) {
        start[i] = T.size();
        T += s[i];
        len[i] = s[i].size();
    }

    vector<int> pref(n + 1, 0);
    for (int i = 0; i < n; ++i) pref[i + 1] = pref[i] + len[i];

    vector<pair<int, int>> candidates; // (L, R) в T
    for (int i = 0; i < n; ++i) {
        int need = pref[i] + k;
        int j = lower_bound(pref.begin(), pref.end(), need) - pref.begin();
        if (j <= n) {
            --j;
            if (j >= i && j < n) {
                int L = start[i];
                int R = start[j] + len[j] - 1;
                candidates.emplace_back(L, R);
            }
        }
    }

    if (candidates.empty()) {
        cout << "NO\n";
        return;
    }

    Hasher hasher(T);
    int best = 0;
    for (size_t i = 1; i < candidates.size(); ++i) {
        if (is_less(T, hasher,
                    candidates[i].first, candidates[i].second,
                    candidates[best].first, candidates[best].second)) {
            best = i;
        }
    }

    int L = candidates[best].first, R = candidates[best].second;
    cout << "YES\n" << T.substr(L, R - L + 1) << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}
