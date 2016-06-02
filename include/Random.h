#ifndef	_RANDOM_H_
#define _RANDOM_H_
#include <random>


class Random
{
public:
	Random();
	int operator()(int max);
	int operator()(int min, int max);
	float operator()(float max);
	float operator()(float min, float max);
private:
	std::random_device rd;
	std::mt19937 mt;
};


#endif