#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <queue>
#include <set>
 
int main()
{
	const int N = 111;

	std::set<std::string> all;
	std::set<std::string> used;
	std::map<std::string, unsigned int> d;
	std::string s[N][3];
	unsigned int n;

    std::cin >> n;
    std::string enter;
    getline(std::cin, enter);
 
    for (unsigned int i = 0; i < n; ++i) {
        for (unsigned int j = 0; j < 3; ++j) {
            std::cin >> s[i][j];
            all.insert(s[i][j]);
        } 
        getline(std::cin, enter);
    }
 
    d["Isenbaev"] = 0;
    used.insert("Isenbaev");
    std::queue<std::string> q;
    q.push("Isenbaev");
 
    while (!q.empty()) {
        std::string v = q.front();
        q.pop();
        unsigned int dist = d[v];
 
        for (unsigned int i = 0; i < n; ++i) {
            bool find = false;
            for (unsigned int j = 0; j < 3; ++j)
                find |= (s[i][j] == v);
 
            if (find) {
                for (unsigned int j = 0; j < 3; ++j) {
                    std::string to = s[i][j];
                    if (used.find(to) == used.end()) {
                        used.insert(to);
                        q.push(to);
                        d[to] = dist + 1;
                    }
                }
            }
        }
    }
 
    for (auto it : all) {
        std::string name = it;
        std::cout << name << ' ';
        if (used.find(name) == used.end())
            std::cout << "undefined" << std::endl;
        else
            std::cout << d[name] << std::endl;
    }
 
    return 0;
}
