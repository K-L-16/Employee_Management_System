#pragma once
#include<cstdint>
#include<random>
class RandomGenerator
{
public:
	RandomGenerator(uint32_t seedValue = 1);

	int bounded(int highest);					
	int bounded(int lowest, int highest);
	static RandomGenerator* global();
private:
	std::default_random_engine * m_engine;
};





