#include "Random.h"
#include <iostream>

void displayVector(const std::vector<int> &_vector)
{
	std::cout << "Array Size: " << _vector.size() << std::endl;
	std::cout << "Array Values:";
	for (int i : _vector)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl << std::endl;
}

// Part 3: count how many times a va;ue appears in a vector
int countValues(const std::vector<int>& _vector, int value) 
{
	//Initialize counter
	int count = 0;

	for (int i : _vector)
	{
		if (i == value) {
			count++;
		}
	}
	return count;
}

int uniqueValue(const std::vector<int>& _vector, int min, int max, Random& random) {
	//Generate value
	int _value = random.RandomInt(min, max);
	bool present = false;
	for (int i : _vector) {
		if (i == _value) {
			_value = uniqueValue(_vector, min, max, random);
		}
	}


	return _value;
}


int main()
{

	//Create the Random number generator object
	Random random;
	int range_min = 1;
	int range_max = 20;

	//Create random ints
	std::vector<int> randomIntegers;
	for (int i = 0; i < 50; i++)
	{
		randomIntegers.push_back(random.RandomInt(range_min, range_max));
	}

	displayVector(randomIntegers);

	//Part 1: remove all multiples of 5 using iterator based loop
	auto it = randomIntegers.begin();
	while (it != randomIntegers.end())
	{
		//Check if multiple of 5
		if (*it % 5 == 0)
		{
			//Delete and replace invalid iterator
			it = randomIntegers.erase(it);
		}
		//Iterate iterator
		else {
			it++;
		}

	}
	//Display results
	displayVector(randomIntegers);
	
	//Part 2: remove multiples of 2 using index based loop
	for (int i = 0; i < randomIntegers.size(); i++) {
		if (randomIntegers.at(i) % 2 == 0)
		{
			randomIntegers.erase(randomIntegers.begin() + i);
			i--;
		}
	}
	displayVector(randomIntegers);

	//Part 3: count values function
	int searchValue = random.RandomInt(range_min, range_max);
	std::cout << "Number of " << searchValue << " iterations: " << countValues(randomIntegers, searchValue) << std::endl << std::endl;

	//Part 4:
	std::vector<int> lotto_ticket;
	std::vector<int> lotto_numbers;

	for (int i = 0; i < 6; i++)
	{
		int _value = uniqueValue(lotto_ticket, 1, 49, random);
		lotto_ticket.push_back(_value);
	}

	displayVector(lotto_ticket);

	return 0;
}
