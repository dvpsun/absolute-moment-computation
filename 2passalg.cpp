#include <pch.h>;
#include <iostream>;
#include <chrono>;
#include <random>;
#include <array>;
#include <vector>;
#include <fstream>;
#include <cstdio>

float countMoment(int p, std::vector <float> a) {
	float mean = 0;
	for (int i = 0; i < a.size(); i++) {
		mean += a[i];
	}
	mean /= a.size();
	float result = 0;
	for (int j = 0; j < a.size(); j++) {
		result += std::pow(std::abs(a[j] - mean), p);
	}
	return result;
}


int main() {
	int a = 10000;
	float curr;
	FILE *stream;
	std::ofstream myfile;
	myfile.open("results.txt");
	std::vector <float> sample(a);
	srand(time(NULL));
	for (int i = 0; i < a; i++) {
		curr = rand() % 10000;
		curr /= 10000;
		sample[i] = curr;
	}
	for (int j = 0; j < sample.size(); j++) {
		std::vector <float> currSample(sample.begin(), sample.begin() + j);
		std::chrono::high_resolution_clock::time_point t_start = std::chrono::high_resolution_clock::now();
		countMoment(10, currSample);
		std::chrono::high_resolution_clock::time_point t_finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>> (t_finish - t_start);
		myfile << time_span.count() << std::endl;
		std::cout << time_span.count() << std::endl;
	}
	sample.erase(sample.begin(), sample.end());
	return 0;
}
