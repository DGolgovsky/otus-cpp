#include <iostream>
#include <map>

int main()
{
    std::map<int, int> map;
    int N, M, x;
    int answer = 0;
    
    std::cin >> N;
    for (int i = 0; i != N; ++i) {
        std::cin >> x;
        map[x]++;
    }
    
    std::cin >> M;
    for(int i = 0; i != M; ++i) {
        std::cin >> x;
        if (map[x])
            answer++;
    }
    
    std::cout << answer << std::endl;

    return 0;
}
