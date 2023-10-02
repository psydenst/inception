#include <iostream>
#include <map>
#include <limits>

# define RESET			"\e[0m"
# define CYAN			"\e[0;36m"

template <typename K, typename V>
class interval_map 
{

public:
    std::map<K, V> m_map;
    V m_valBegin;

// public:
    // Constructor to initialize the initial value
    interval_map(const V& initialValue) : m_valBegin(initialValue) 
    {
        return ;
    }

    // Member function to assign values to the specified interval [k_begin, k_end)
    void assign(const K& k_begin, const K& k_end, const V& value) 
    {
        // Validate input parameters
        if (k_begin >= k_end)
        {
            std::cerr << CYAN << "Invalid keys" << RESET << std::endl;
            return;
        }
        if (k_end > std::numeric_limits<K>::max() || k_begin < std::numeric_limits<K>::lowest())
        {
            std::cerr << CYAN << "Keys are outside numeric_limist" << RESET << std::endl;
            return ;
        }

        // Here, I need to create some conditions that will guarantee that canonical form is respected here. 

        // Check if (k_begin - 1) exists in the map and has the same value
        auto it_begin_minus_one = m_map.find(k_begin - 1);
        if (it_begin_minus_one != m_map.end() && it_begin_minus_one->second == value) {
            std::cerr << CYAN << "Consecutive values. Disrespects Canonical Form" << RESET << std::endl;
            return;
        }

        // Check if (k_end + 1) exists in the map and has the same value
        auto it_end_plus_one = m_map.find(k_end + 1);
        if (it_end_plus_one != m_map.end() && it_end_plus_one->second == value) {
            std::cerr << CYAN << "Consecutive values. Disrespects Canonical Form" << RESET << std::endl;
            return;
        }
        for (auto i = k_begin; i < k_end; ++i) 
        {
            m_map[i] = value;
        }
    }
};

int main() 
{
    interval_map<int, char> map('A');
    map.assign(0, 3, 'B');
    map.assign(3, 8, 'b');
    map.assign(7, 9, 'c');
    map.assign(9, 13, 'c');

    for (auto it = map.m_map.begin(); it != map.m_map.end(); ++it)
    {
        std::cout << it->first << it->second << std::endl;
    }

    return 0;
}
