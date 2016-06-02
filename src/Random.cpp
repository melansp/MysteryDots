#include "Random.h"

Random::Random()
	:mt(rd())
{
}

int Random::operator()(int max)
{
	return (*this)(0, max);
}

int Random::operator()(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max-1);
	return dist(mt);
}
float Random::operator()(float max)
{
	return (*this)(0.f, max);
}

float Random::operator()(float min, float max)
{
	std::uniform_real_distribution<float> dist(min, max);
	return dist(mt);
}
