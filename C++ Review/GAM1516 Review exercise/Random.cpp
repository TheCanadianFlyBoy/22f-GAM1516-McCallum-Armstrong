#include "Random.h"

Random Random::s_Instance = Random::Random();

Random& Random::Instance()
{
	return s_Instance;
}

Random::Random() :
	m_MersenneTwister(std::random_device{}())
{
}

Random::Random(int seed) :
	m_MersenneTwister(seed)
{
}

int Random::RandomInt(int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(m_MersenneTwister);
}

float Random::RandomFloat(float min, float max)
{
	std::uniform_real_distribution<float> distribution(min, max);
	return distribution(m_MersenneTwister);
}
