#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9 + 10;

struct SegTree {
    int n;
    vector<int> t;
    SegTree(const vector<int>& a) {
        n = a.size();
        t.resize(4 * n);
        build(1, 0, n - 1, a);
    }
    void build(int v, int tl, int tr, const vector<int>& a) {
        if (tl == tr) {
            t[v] = a[tl];
        } else {
            int tm = (tl + tr) / 2;
            build(v * 2, tl, tm, a);
            build(v * 2 + 1, tm + 1, tr, a);
            t[v] = min(t[v * 2], t[v * 2 + 1]);
        }
    }
    void update(int v, int tl, int tr, int pos, int val) {
        if (tl == tr) {
            t[v] = val;
        } else {
            int tm = (tl + tr) / 2;
            if (pos <= tm) update(v * 2, tl, tm, pos, val);
            else update(v * 2 + 1, tm + 1, tr, pos, val);
            t[v] = min(t[v * 2], t[v * 2 + 1]);
        }
    }

    int find_first(int v, int tl, int tr, int l, int r, int x) {
        if (l > r || t[v] >= x) return -1;
        if (tl == tr) return tl;
        int tm = (tl + tr) / 2;
        int res = -1;
        if (l <= tm) res = find_first(v * 2, tl, tm, l, min(r, tm), x);
        if (res != -1) return res;
        if (r > tm) res = find_first(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, x);
        return res;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        map<int, vector<int>> pos;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            pos[a[i]].push_back(i);
        }
        SegTree seg(a);
        vector<int> vals;
        for (auto& p : pos) vals.push_back(p.first);
        sort(vals.begin(), vals.end());
        long long ans = 0;
        for (int val : vals) {
            auto& v = pos[val];
            if (v.size() < 2) continue;
            int L = v.front(), R = v.back();
            int i = seg.find_first(1, 0, n - 1, L, R, val);
            while (i != -1) {
                ++ans;
                seg.update(1, 0, n - 1, i, INF);
                i = seg.find_first(1, 0, n - 1, i + 1, R, val);
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
