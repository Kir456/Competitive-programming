#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int xor_sum = 0;
    int cnt_one = 0;
    bool has_big = false;

    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        int bits = __builtin_popcount(a);
        if (bits > 0) {
            xor_sum ^= bits;
            if (bits == 1)
                ++cnt_one;
            else
                has_big = true;
        }
    }

    if (!has_big) {
        cout << (cnt_one % 2 == 0 ? "A" : "B") << '\n';
    } else {
        cout << (xor_sum != 0 ? "A" : "B") << '\n';
    }

    return 0;
}
