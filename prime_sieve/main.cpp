#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <set>

// error codes
constexpr unsigned long long _NO_ERROR{ 0 };
constexpr unsigned long long _SIEVE_NO_NUMBER{ 10 };

// function definitions
std::set<unsigned long long> sieve_primes(const unsigned long long limit);
std::set<unsigned long long> sieve_primes_verbose(const unsigned long long limit);

int main() {
	unsigned long long last_error{};
	std::set<unsigned long long> primes{};
	std::chrono::duration<double> elapsed_secounds{};

	while (true) {
		// get input
		std::string input{};
		std::printf("Input: ");
		std::getline(std::cin, input);

		// verbose info
		bool verbose{ false };
		if (input.find("-v") != std::string::npos) verbose = true;

		// get number from input
		unsigned long long limit{};
		if (input.find("-s") != std::string::npos) {
			size_t off{ input.find("-s") }, end{};
			end = input.find_first_of("-", off + 1);

			if (end != std::string::npos) end -= 1;
			else end = input.length();

			std::string temp{ input.substr(off + 2, end - off - 1) };

			if (temp.empty())last_error = _SIEVE_NO_NUMBER;
			else {
				limit = std::stoull(temp);

				// Track to time taken to seive the primes
				std::chrono::high_resolution_clock::time_point start{};
				std::chrono::high_resolution_clock::time_point end{};

				if (verbose) {
					start = std::chrono::high_resolution_clock::now();

					primes = sieve_primes_verbose(limit);

					end = std::chrono::high_resolution_clock::now();
				}
				else {
					start = std::chrono::high_resolution_clock::now();

					primes = sieve_primes(limit);

					end = std::chrono::high_resolution_clock::now();
				}

				elapsed_secounds = end - start ;
			}
		}

		// display primes
		if (input.find("-d") != std::string::npos) {
			if (last_error != _SIEVE_NO_NUMBER); {
				std::printf("%llu primes found.\n", primes.size());
				for (std::set<unsigned long long>::iterator it{ primes.begin() }; it != primes.end(); it++) {
					std::printf("%llu\n", *it);
				}
			}
		}

		std::cout << "Time taken: " << elapsed_secounds << "\n";

		// log primes to file
		if (input.find("-l") != std::string::npos) {
			size_t off{ input.find("-l") }, end{};
			end = input.find_first_of("-", off + 1);

			if (end != std::string::npos) end -= 1;
			else end = input.length();

			std::string temp{ input.substr(off + 2, end - off - 1) };

			std::fstream log(temp.append(".csv"), std::ios_base::out);

			std::set<unsigned long long>::iterator it{ primes.begin() };
			log << *it;

			it++;

			for (; it != primes.end(); it++) {
				log << ',' << *it;
			}
		}

		std::printf("\n");
	}

	return last_error;
}

std::set<unsigned long long> sieve_primes(const unsigned long long limit) {
	/*
	std::set<unsigned long long> non_primes{};

	unsigned long long num{ 2 }, mul{ 2 };

	// sieve primes
	while (num <= limit) {
		if (num * mul > limit) {
			num++;
			mul = num;
			if (num * mul > limit) {
				break;
			}
		}
		else {
			non_primes.insert(num * mul);
			mul++;
		}
	}

	// set num equal 2
	num = 2;

	std::set<unsigned long long> primes{};

	// remove non primes
	for (std::set<unsigned long long>::iterator it{ non_primes.begin() }; it != non_primes.end();) {
		if (num != *it) primes.insert(num);
		else it++;
		num++;
	}

	return primes;
	*/

	std::set<unsigned long long> primes{};

	// create number list
	for (int num{ 2 }; num <= limit; num++) {
		primes.insert(num);
	}

	std::set<unsigned long long>::iterator num{ primes.begin() }, pow{ primes.begin() };
	std::set<unsigned long long> non_primes{};

	// sieve primes
	while (num != primes.end()) {
		if (*num * *pow > limit) {
			num++;
			pow = num;
		}
		else {
			non_primes.insert(*num * *pow);
			pow++;
		}
	}

	// remove non primes
	for (std::set<unsigned long long>::iterator it{ non_primes.begin() }; it != non_primes.end(); it++) {
		primes.erase(*it);
	}

	return primes;
}

std::set<unsigned long long> sieve_primes_verbose(const unsigned long long limit) {
	std::set<unsigned long long> non_primes{};

	unsigned long long num{ 2 }, mul{ 2 };
	double upper_limit{};

	// the upper limit is the first number times itself that exceeds the limit
	for (unsigned long long n{ 2 }; n <= limit; n++) {
		if (n * n > limit) {
			upper_limit = static_cast<double>(n);
			break;
		}
	}

	// sieve primes
	std::printf("Sieving primes...\n");
	while (num <= limit) {
		if (num * mul > limit) {
			std::printf("%f%%...\n", (num / upper_limit) * 100);
			num++;
			mul = num;
			if (num * mul > limit) {
				std::printf("%f%%... done.\n", (num / upper_limit) * 100);
				break;
			}
		}
		else {
			non_primes.insert(num * mul);
			mul++;
		}
	}

	// set num equal 2
	num = 2;

	// remove non primes
	std::set<unsigned long long> primes{};

	std::printf("Removing non primes... ");
	for (std::set<unsigned long long>::iterator it{ non_primes.begin() }; it != non_primes.end();) {
		if (num != *it) primes.insert(num);
		else it++;
		num++;
	}
	std::printf("done.\n\n");

	return primes;
}