#include <iostream>
#include <string>

int main()
{
    int n = 0;
    int s = 0;
    std::cin >> n;
    std::string *str = new std::string[n];
    for (int i = 0; i < n; ++i)
        std::cin >> str[i];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (str[i] == str[j] && i != j) {
                str[j] = "1";
                s = 1;
            }
        }
        
        if (s == 1 && str[i] != "1")
            std::cout << str[i] << std::endl;
        
        str[i] = "1";
        s = 0;
    }

    return 0;
}

