#include "pch.h";
#include <iostream>;
#include <chrono>;
#include <random>;
#include <iterator>
#include <array>;
#include <vector>;
#include <fstream>;
#include <cstdio>;
#include <string>;
#include <sstream>;

double countMoment(int p, std::vector<double>::const_iterator it1, std::vector<double>::const_iterator it2) {
		double result = 0.0;
		double mean = 0.0;
		int size = 0;
		std::vector<double>::const_iterator it3 = it1;
		for (auto it = it1; it != it2; it++) {
			mean += *it;
			size += 1;
		}

		mean /= size;

		for (auto it_ = it3; it_ != it2; it_++) {
			result += std::pow(std::abs(*it_ - mean), p);
		}
	return result;
}


int main() {
	int a = 10000;	
	double curr;
	//std::string currPush;
	//std::vector <double> newsample(a);
	std::ofstream myfile;
	//std::ifstream in("newsample.txt");
	//newsample.clear();
	//while (std::getline(in, currPush)) {
	//	std::istringstream os(currPush);
	//	double d;
	//	os >> d;
	//	newsample.push_back(d);
	//}

	//std::cout << countMoment(10, newsample.cbegin(), newsample.cbegin()+ a ) << "is answer" << std::endl;
	//std::cin >> curr;

	myfile.open("results.txt");
	std::vector <double> sample(a);


	for (int i = 0; i < a; i++) {
		curr = rand() % 100;
		curr /= 100;
		sample[i] = curr;
		//std::cout << sample[i] << std::endl;
	}
	std::cout << countMoment(10, sample.cbegin(), sample.cend()) << std::endl;
	std::cout << sample.size();
	std::cin >> curr;

	for (int j = 0; j < sample.size(); j++) {
		std::chrono::high_resolution_clock::time_point t_start = std::chrono::high_resolution_clock::now();
		//for (int l = 0; l < 10000; l++) {
		countMoment(10, sample.cbegin(), sample.cbegin() + j);
		//}
		std::chrono::high_resolution_clock::time_point t_finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>> (t_finish - t_start);
		myfile << time_span.count() << std::endl;
		//std::cout << time_span.count() << std::endl;
	}
	sample.clear();
	return 0;
}