#include <iostream>
#include <map>
#include <limits>
#include <string>

# define RESET			"\e[0m"
# define CYAN			"\e[0;36m"
# define LILAC			"\e[0;38;5;13m"

template <typename K, typename V>
class interval_map 
{

private:
	friend void IntervalMapTest();
	V m_valBegin;
	std::map<K,V> m_map;
public:
    V m_valBegin;
    // Constructor to initialize the initial value
    interval_map(const V& initialValue) : m_valBegin(initialValue) 
    {
        return ;
    }

    // Member function to assign values to the specified interval [k_begin, k_end)
    void assign(const K& k_begin, const K& k_end, const V& value) 
    {
        // Validate input parameters
        if (!(k_begin < k_end))
        {
            std::cerr << LILAC << "Invalid keys" << RESET << std::endl;
            return;
        }
        if (k_end > std::numeric_limits<K>::max() || k_begin < std::numeric_limits<K>::lowest())
        {
            std::cerr << LILAC << "Keys are outside numeric_limits" << RESET << std::endl;
            return ;
        }

        // Here, I need to create some conditions that will guarantee that canonical form is respected here. 

        // Check if (k_begin - 1) exists in the map and has the same value
        auto it_begin_minus_one = m_map.find(k_begin - 1);
        if (it_begin_minus_one != m_map.end() && it_begin_minus_one->second == value) {
            std::cerr << LILAC << "Consecutive values. Disrespects Canonical Form" << RESET << std::endl;
            return;
        }

        // Check if (k_end + 1) exists in the map and has the same value
        auto it_end_plus_one = m_map.find(k_end + 1);
        if (it_end_plus_one != m_map.end() && it_end_plus_one->second == value) {
            std::cerr << LILAC << "Consecutive values. Disrespects Canonical Form" << RESET << std::endl;
            return;
        }
        // Populate the map positions with value
        for (auto i = k_begin; i < k_end; ++i) 
        {
            m_map[i] = value;
        }
    }

    std::map<K, V>& getMap() 
    {
        return m_map;
    }


};


// RANDOM GETTERS
#include <cstdlib>
#include <ctime>

int getRandomInt(int min, int max)
{
    return (min + rand() % (max - min + 1));
}

float getRandomFloat(float min, float max)
{
    return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (max - min));
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
        int k_b = getRandomInt(0, 7);
        int k_e = getRandomInt(7, 14);
        char v = getRandomChar('A');
        // std::cout << "Value of k_b: " << k_b << " value of k_e: " << k_e <<" when limits at: " << limit << std::endl;
        // std::cout << "Value of v: " << v << " when limits at: " << limit << std::endl;
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
        unsigned int k_b = getRandomUInt(0, 5);
        unsigned int k_e = getRandomUInt(5, 14);
        int v = getRandomInt(300, 350);
       // std::cout << "Value of k_b: " << k_b << " value of k_e: " << k_e <<" when limits at: " << limit << std::endl;
       // std::cout << "Value of v: " << v << " when limits at: " << limit << std::endl;
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
      //  std::cout << "Value of k_b: " << k_b << " value of k_e: " << k_e <<" when limits at: " << limit << std::endl;
      //  std::cout << "Value of v: " << v << " when limits at: " << limit << std::endl;
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
      //  std::cout << "Value of k_b: " << k_b << " value of k_e: " << k_e <<" when limits at: " << limit << std::endl;
      //  std::cout << "Value of v: " << v << " when limits at: " << limit << std::endl;
        map_f.assign(k_b, k_e, v);
    }

    std::map<float, char>testMap = map_f.getMap();
    for (auto it = testMap.begin(); it != testMap.end(); ++it)
    {
        std::cout << LILAC << it->first << " => " << it->second << RESET << std::endl;
    }
}

// MAIN

int main() 
{
    srand(static_cast<unsigned int>(time(nullptr)));

    std::cout << CYAN << "----- MAP1 : MANUAL TEST WITH INT AND CHAR -----" << RESET << std::endl;
    interval_map<int, char> map1('A');
    map1.assign(0, 3, 'B');
    map1.assign(3, 8, 'b');
    map1.assign(7, 9, 'c');
    map1.assign(9, 13, 'd');

    std::map<int, char>testMap = map1.getMap();
    for (auto it = testMap.begin(); it != testMap.end(); ++it)
    {
        std::cout << LILAC << it->first << " => " << it->second << RESET << std::endl;
    }

    std::cout << CYAN << "\n\n----- MAP 2: RANDOM TEST WITH INT AND CHAR -----\n\n" << RESET << std::endl;
    interval_map<int, char>map2('B');
    random_int_char(map2);

    std::cout << CYAN << "\n\n----- MAP 3: RANDOM TEST WITH UNSIGNED INT AND INT -----\n\n" << RESET << std::endl;
    interval_map<unsigned int, int>map3('C');
    random_uint_int(map3);

    std::cout << CYAN << "\n\n----- MAP 4: RANDOM TEST WITH CHAR AND CHAR -----\n\n" << RESET << std::endl;
     interval_map<char, char>map4('D');
    random_char_char(map4);

    std::cout << CYAN << "\n\n----- MAP 5: RANDOM TEST WITH FLOAT AND CHAR -----\n\n" << RESET << std::endl;
    interval_map<float, char>map5('E');
    random_float_char(map5);

    return 0;
}