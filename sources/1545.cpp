#include <iostream>
#include <map>
using namespace std;

int main() {
    map<char, string> m;

    int n; cin >> n;
    while (n--) {
        char c1, c2; cin >> c1 >> c2;
        m[c1].push_back(c2);
    }
    char c; cin >> c;
    for (int i = 0; i < m[c].size(); ++i)
        cout << c << m[c][i] << endl;

    return 0;
}
