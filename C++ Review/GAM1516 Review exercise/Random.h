#pragma once

#include <random>

class Random
{
public:
	//Returns a static instance of the random number generator 
	//so that you don't have to keep making Random objects
	static Random& Instance();

	//Uses a random seed for the random number generator
	Random();

	//Overloaded constructor to provide a specific seed 
	//for the random number generator
	Random(int seed);

	//Returns an int value between a min value and a max value
	int RandomInt(int min, int max);

	//Returns a float value between a min value and a max value
	float RandomFloat(float min, float max);

private:
	std::mt19937 m_MersenneTwister;
	static Random s_Instance;
};