#include <iostream>
#include <numeric>
#include <fstream>
#include <string>
#include <vector>

std::vector<unsigned int> sieve_primes(unsigned int range);
void print_primes(std::vector<unsigned int> primes);

int main() {
	std::vector<unsigned int> primes{};

	while (true) {
		std::cout << "This program finds every prime number from 2 through n were n is any whole number.\n"
			<< "sieve [range] | Finds primes up to range.\n"
			<< "output (filename) | Outputs primes to a file or the console.\n"
			<< "exit | Terminates the program.\n"
			<< "input: ";

		std::string input{}, cmd{}, arg{};
		std::getline(std::cin, input);

		cmd = input.substr(0, input.find_first_of(' '));
		if (input.find_first_of(' ') == std::string::npos) arg = "";
		else arg = input.substr(input.find_first_of(' ') + 1, input.length() - input.find_first_of(' '));

		if (cmd == "sieve") {
			bool valid = true;

			for (size_t t{}; t < arg.length(); t++) if (!std::isdigit(arg[t])) valid = false;

			if (valid) {
				primes = sieve_primes(std::stoul(arg));
				std::cout << std::endl;
			}
			else std::cout << "[!] Range is not a whole number.\n" << std::endl;
		}
		else if (cmd == "output") {
			if (!primes.empty()) {
				if (arg.empty()) print_primes(primes);
				else {
					std::fstream file(arg, std::ios_base::out);
					if (file.is_open()) for (std::vector<unsigned int>::iterator it{ primes.begin() }; it != primes.end(); it++) file << *it << "\n";
					else std::cout << "[!] File " << arg << " dose not exist.\n" << std::endl;
					file.close();
				}
				std::cout << std::endl;
			}
			else std::cout << "[!] No primes have been found, try \"sieve 100\".\n" << std::endl;
		}
		else if (cmd == "exit") {
			std::cout << "Goodbye!";
			return 0;
		}
		else std::cout << "[!] Unknow command " << cmd << ".\n" << std::endl;
	}

	return 1;
}

std::vector<unsigned int> sieve_primes(unsigned int range) {
	std::vector<unsigned int> primes{};
	primes.resize(range);
	
	std::iota(primes.begin(), primes.end(), 0);
	primes[1] = 0;

	for (std::vector<unsigned int>::iterator it{ primes.begin() }; it != primes.end(); it++) {
		if (*it != 0) {
			for (unsigned int p{ 2 }; p < range; p++) {
				if ((*it) * p >= range) break;
				else primes[(*it) * p] = 0;
			}
		}
	}

	for (std::vector<unsigned int>::iterator it{ primes.begin() }; it != primes.end();) {
		if (*it == 0) it = primes.erase(it);
		else it++;
	}

	return primes;
}

void print_primes(std::vector<unsigned int> primes) {
	for (std::vector<unsigned int>::iterator it{ primes.begin() }; it != primes.end(); it++) std::cout << *it << "\n";
}