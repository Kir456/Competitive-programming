#include <iostream>
#include <vector>
#include <algorithm>
 
using namespace std;
 
int main() {
    int t;
    cin >> t;
    vector<int> res;
 
    for (int i = 0; i < t; i++) {
        int n, s;
        cin >> n >> s;
        vector<int> x(n);
        for (int j = 0; j < n; j++) {
            cin >> x[j];
        }
 
        auto max_el = max_element(x.begin(), x.end());
        auto min_el = min_element(x.begin(), x.end());
        if (s >= *max_el) {
            res.push_back(s-*min_el);
        }
        else if (s <= *min_el) {
            res.push_back(*max_el-s);
        }
        else {
            if (min(*max_el-s, s-*min_el) == *max_el-s) {
                res.push_back(*max_el-s+*max_el-*min_el);
            }
            else {
                res.push_back(s-*min_el+*max_el-*min_el);
            }
        }
    }
 
    for (int i = 0; i < t; i++) {
        cout << res[i] << endl;
    }
}