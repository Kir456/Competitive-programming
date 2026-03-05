#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<string> strings(n);
    for (int i = 0; i < n; i++) {
        cin >> strings[i];
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strings[i] + strings[j] != strings[j] + strings[i]) {
                cout << "YES" << endl;
                return 0;
            }
        }
    }
    
    cout << "NO" << endl;
    return 0;
}
