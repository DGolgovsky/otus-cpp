#include <iostream>
#include <string>

#include "libcracker/cracker.h"

int main()
{
    unsigned int T = 0; // total number of test cases
    unsigned int N = 0; // number of users with passwords

	std::cout << "Enter number of test cases >> ";
    std::cin >> T;
    if (T < 1 || T > 10) {
		std::cout << "Number of test must be between 1 and 10" << std::endl;
		return -1;
	}

    /* Test cases  */
    for (size_t t = 0; t < T; ++t) {
	    std::string passwds;// passwords of each user
	    std::string login_attempts;
 
		std::cout << "TEST CASE [" << t + 1 << "]" << std::endl;
		std::cout << "Enter number of users passwords >> ";
		std::cin >> N;
		std::cin.ignore();
	    if (N < 1 || N > 10) {
			std::cout << "Number of user passwords must be between 1 and 10" << std::endl;
			return -1;
		}

		std::cout << "Enter users passwords >> ";
		getline(std::cin, passwds);

		std::cout << "Enter attempts >> ";
        getline(std::cin, login_attempts);
        
		std::cout << cracker::crack(N, std::move(passwds), std::move(login_attempts)) << std::endl;
    }

    return 0;
}
