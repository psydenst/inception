#include <map>
#include <iostream>
#include <map>
#include <limits>
#include <string>
#include <typeinfo>
#include <cmath>

# define RESET			"\e[0m"
# define CYAN			"\e[0;36m"
# define LILAC			"\e[0;38;5;13m"

template<typename K, typename V>
class interval_map
{
	friend void IntervalMapTest();
	V m_valBegin;
	std::map<K,V> m_map;

	public:
	// constructor associates whole range of K with val
	interval_map(V const& val)
	: m_valBegin(val)
	{}

	// Assign value val to interval [keyBegin, keyEnd).
	// Overwrite previous values in this interval.
	// Conforming to the C++ Standard Library conventions, the interval
	// includes keyBegin, but excludes keyEnd.
	// If !( keyBegin < keyEnd ), this designates an empty interval,
	// and assign must do nothing.
	void assign( K const& keyBegin, K const& keyEnd, V const& val)
    {

        // Validate input parameters
        if (!(keyBegin < keyEnd))
        {
          //  std::cerr << LILAC << "Invalid keys" << RESET << std::endl;
            return;
        }

		// Check if the first val == m_valBegin
		if (m_map.empty() && m_valBegin == val)
		{
		//std::cerr << LILAC << "First entry has the same value as m_valBegin" << RESET << std::endl;
			return;
		}

        // Creating some conditions that will guarantee that canonical form is respected. 

		auto it_begin_minus_one = m_map.find(keyBegin);
		if (it_begin_minus_one != m_map.begin())
		{
			it_begin_minus_one--;
			if (it_begin_minus_one->second == val)
			{
				// std::cerr << "Consecutive vals. Disrespects Canonical Form" << std::endl;
				return;
			}
		}

		// Check if (keyEnd + 1) exists in the map and has the same value
		auto it_end_plus_one = m_map.find(keyEnd);
		if (it_end_plus_one != m_map.end())
		{
			it_end_plus_one++;
			if (it_end_plus_one != m_map.end() && it_end_plus_one->second == val)
			{
				// Consecutive vals. Disrespects Canonical Form
				return;
			}
		}

		auto i = keyBegin;
		long double i2 = i;
		while (i < keyEnd)
        {
			if (m_map.find(i) != m_map.end())
				m_map.erase(i);
          	m_map.insert(std::make_pair(i, val));
			i2 = i2 + 1;
			i = i2;
        }
	}

	// look-up of the val associated with key
	V const& operator[]( K const& key ) const {
		auto it=m_map.upper_bound(key);
		if(it==m_map.begin()) {
			return m_valBegin;
		} else {
			return (--it)->second;
		}
	}

	std::map<K, V>getMap()
	{
		return (m_map);
	}

};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of int intervals to char.

// RANDOM GETTERS
#include <cstdlib>
#include <ctime>

int getRandomInt(long int min, long int max)
{
	long long int ret = min + rand() % (max - min + 1);
    return (ret);
}

float getRandomFloat(float min, float max)
{
    return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (max - min);
}

char getRandomChar(char c)
{
    return (c + rand() % 26);
}

char* getRandomStr(int length)
{
    char* str = new char[length + 1];

    for (int i = 0; i < length; ++i) 
    {
        str[i] = getRandomChar('A');
    }

    str[length] = '\0'; // Null-terminate the string

    return str;
}

unsigned int getRandomUInt(unsigned int min, unsigned int max)
{
    return (min + rand() % (max - min + 1));
}

// TESTS FOR MULTIPLE DATA TYPES

void    random_int_char(interval_map<int, char>map_f)
{
    int limit = 5;

    while (limit--)
    {
        int k_b = getRandomInt(INT_MAX - 30, INT_MAX - 20);
        int k_e = getRandomInt(INT_MAX - 19, INT_MAX);
        char v = getRandomChar('A');
        std::cout << CYAN << "Value of k_b: " << k_b << " value of k_e: " << k_e <<" when limits at: " << limit << RESET << std::endl;
        std::cout << CYAN << "Value of v: " << v << " when limits at: " << limit << RESET << std::endl;
        map_f.assign(k_b, k_e, v);
    }

    std::map<int, char>testMap = map_f.getMap();
    for (auto it = testMap.begin(); it != testMap.end(); ++it)
    {
        std::cout << LILAC << it->first << " => " << it->second << RESET << std::endl;
    }
}

void    random_uint_int(interval_map<unsigned int, int>map_f)
{
    int limit = 5;

    while (limit--)
    {
        unsigned int k_b = getRandomUInt(0, 20);
        unsigned int k_e = getRandomUInt(20, 30);
        int v = getRandomInt(0, 1500);
    	std::cout << "Value of k_b: " << k_b << " value of k_e: " << k_e <<" when limits at: " << limit << std::endl;
    	std::cout << "Value of v: " << v << " when limits at: " << limit << std::endl;
        map_f.assign(k_b, k_e, v);
    }

    std::map<unsigned int, int>testMap = map_f.getMap();
    for (auto it = testMap.begin(); it != testMap.end(); ++it)
    {
        std::cout << LILAC << it->first << " => " << it->second << RESET << std::endl;
    }
}

void    random_char_char(interval_map<char, char>map_f)
{
    int limit = 5;

    while (limit--)
    {
        char k_b = getRandomChar('A');
        char k_e = getRandomChar('a');
        char v = getRandomChar('A');
    	std::cout << "Value of k_b: " << k_b << " value of k_e: " << k_e <<" when limits at: " << limit << std::endl;
    	std::cout << "Value of v: " << v << " when limits at: " << limit << std::endl;
        map_f.assign(k_b, k_e, v);
    }

    std::map<char, char>testMap = map_f.getMap();
    for (auto it = testMap.begin(); it != testMap.end(); ++it)
    {
        std::cout << LILAC << it->first << " => " << it->second << RESET << std::endl;
    }
}

void    random_float_char(interval_map<float, char>map_f)
{
    int limit = 5;

    while (limit--)
    {
        float k_b = (float) getRandomFloat(0, 6.4);
        float k_e = (float) getRandomFloat(8.5, 12.3);
        char v = getRandomChar('A');

		int decimal_places = 2; // Adjust this as needed
        k_b = std::round(k_b * std::pow(10, decimal_places)) / std::pow(10, decimal_places);
        k_e = std::round(k_e * std::pow(10, decimal_places)) / std::pow(10, decimal_places);
      	std::cout << "Value of k_b: " << k_b << " value of k_e: " << k_e <<" when limits at: " << limit << std::endl;
      	std::cout << "Value of v: " << v << " when limits at: " << limit << std::endl;
        map_f.assign(k_b, k_e, v);
    }

    std::map<float, char>testMap = map_f.getMap();
    for (auto it = testMap.begin(); it != testMap.end(); ++it)
    {
        std::cout << LILAC << it->first << " => " << it->second << RESET << std::endl;
    }
}

void IntervalMapTest()
{
	std::cout << CYAN << "----- MAP1 : MANUAL TEST WITH INT AND CHAR -----" << RESET << std::endl;
    interval_map<int, char> map1('A');
    map1.assign(0, 3, 'A');
    map1.assign(3, 8, 'b');
    map1.assign(7, 9, 'c');
    map1.assign(9, 13, 'd');

    // std::map<int, char>testMap = map1.m_map;
    // for (auto it = testMap.begin(); it != testMap.end(); ++it)
    // {
    //     std::cout << LILAC << it->first << " => " << it->second << RESET << std::endl;
    // }

    // std::cout << CYAN << "\n\n----- MAP 2: RANDOM TEST WITH INT AND CHAR -----\n\n" << RESET << std::endl;
    // interval_map<int, char>map2('B');
    // random_int_char(map2);

    // std::cout << CYAN << "\n\n----- MAP 3: RANDOM TEST WITH UNSIGNED INT AND INT -----\n\n" << RESET << std::endl;
    // interval_map<unsigned int, int>map3('C');
    // random_uint_int(map3);

    // std::cout << CYAN << "\n\n----- MAP 4: RANDOM TEST WITH CHAR AND CHAR -----\n\n" << RESET << std::endl;
    //  interval_map<char, char>map4('D');
    // random_char_char(map4);

//     std::cout << CYAN << "\n\n----- MAP 5: RANDOM TEST WITH FLOAT AND CHAR -----\n\n" << RESET << std::endl;
//     interval_map<float, char>map5('E');
//    // random_float_char(map5);
//    	map5.assign(10.3, 10.6, 'A');

    std::map<float, char>testMap = map5.m_map;
	for (auto it = testMap.begin(); it != testMap.end(); ++it)
    {
        std::cout << LILAC << (float)it->first << " => " << it->second << RESET << std::endl;
    }
}

// MAIN

int main() 
{
    srand(static_cast<unsigned int>(time(nullptr)));

	IntervalMapTest();
    return 0;
}