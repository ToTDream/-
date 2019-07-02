#include <map>
#include <vector>
#include <algorithm>
#include "sort_template.h"

std::vector<pair> FirstUp(std::map<int,int> _map)
{
    std::vector<pair> vec(_map.begin(), _map.end());
    std::sort(vec.begin(), vec.end(), sort_first<pair>());
    return vec;
}
std::vector<pair> SecondUp(std::map<int,int> _map)
{
    std::vector<pair> vec(_map.begin(), _map.end());
    std::sort(vec.begin(), vec.end(), sort_second<pair>());
    return vec;
}
std::vector<pair> FirstDown(std::map<int,int> _map)
{
    std::vector<pair> vec(_map.begin(), _map.end());
    std::sort(vec.begin(), vec.end(), First_Cmp_Up<pair>);
    return vec;
}
std::vector<pair> SecondDown(std::map<int,int> _map)
{
    std::vector<pair> vec(_map.begin(), _map.end());
    std::sort(vec.begin(), vec.end(), Second_Cmp_down<pair>);
    return vec;
}
