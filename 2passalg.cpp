#include "pch.h";
#include <iostream>;
#include <chrono>;
#include <random>;
#include <array>;
#include <vector>;
#include <fstream>;
#include <cstdio>

float countMoment(int p, std::vector<float>::const_iterator it1, std::vector<float>::const_iterator it2) {
	float mean = 0;
	int size = 0;
	std::vector<float>::const_iterator it3 = it1;
	for(auto it = it1; it != it2; it++)  {
		mean += *it;
		size += 1;
	}
	mean /= size;
	float result = 0;
	for(auto it_ = it3; it_ != it2; it_++) {
		result += std::pow(std::abs(*it_ - mean), p);
	}
	return result;
}


int main() {
	int a = 10000;
	float curr;
	std::ofstream myfile;
	myfile.open("results.txt");
	std::vector <float> sample(a);
	srand(time(NULL));

	for (int i = 0; i < a; i++) {
		curr = rand() % 100;
		curr /= 100;
		sample[i] = curr;
	}

	for (int j = 0; j < sample.size(); j++) {
		//std::vector <float> currSample(sample.begin(), sample.begin() + j);
		std::chrono::high_resolution_clock::time_point t_start = std::chrono::high_resolution_clock::now();
		countMoment(2, sample.cbegin(), sample.cbegin()+j);
		std::chrono::high_resolution_clock::time_point t_finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>> (t_finish - t_start);
		myfile << time_span.count() << std::endl;
	}

	sample.clear();
	return 0;
}