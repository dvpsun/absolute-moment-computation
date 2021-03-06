#include "pch.h";
#include <iostream>
#include <chrono>
#include <random>
#include <iterator>
#include <vector>
#include <fstream>

double countMoment(const int p, std::vector<double>::const_iterator it_beg, std::vector<double>::const_iterator it_end, const int repeate = 1000) {
	double result = 0.0;
	double mean = 0.0;
	int size = it_end - it_beg;
	for (int i_repeate = 0; i_repeate < repeate; i_repeate += 1) {
		result = 0.0;
		mean = 0.0;
		for (auto it = it_beg; it != it_end; it += 1) {
			mean += *it;
		}
		mean /= size;
		for (auto it = it_beg; it != it_end; it += 1) {
			result += std::pow(std::abs(*it - mean), p);
		}
	}
	return result;
}


int main() {
	const int repeat_count = 500;
	int a = 1000;
	double curr = 0.0;
	std::ofstream myfile;

	myfile.open("results.txt");
	std::vector <double> sample(a);
	for (int i = 0; i < a; i++) {
		curr = rand() % 100;
		curr /= 100.0;
		sample[i] = curr;
	}
	std::cout << countMoment(10, sample.cbegin(), sample.cend()) / (sample.cend() - sample.cbegin()) << std::endl;
	std::cout << sample.size();
	for (int j = 2; j < int(sample.size()); j++) {
		std::chrono::high_resolution_clock::time_point t_start = std::chrono::high_resolution_clock::now();
		curr = countMoment(10, sample.cbegin(), sample.cbegin() + j, repeat_count);
		std::chrono::high_resolution_clock::time_point t_finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double, std::nano>> (t_finish - t_start);
		myfile << (time_span.count() / repeat_count) << '\t' << (curr / j) << std::endl;
	}
	return 0;
}
