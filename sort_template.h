#ifndef SORT_TEMPLATE_H
#define SORT_TEMPLATE_H
#include <map>
#include <vector>
#include <iostream>
#include "person.h"
#include "course.h"

typedef std::pair<int,int> pair;
typedef std::vector<pair> pair_vec;

template<class T>
struct sort_first : std::binary_function<T, T, bool>
{
    inline bool operator()( const T& l, const T& r )const
    {
          return l.first < r.first;
    }
};
template<class T>
struct sort_second : std::binary_function<T, T, bool>
{
    inline bool operator()( const T& l, const T& r )const
    {
          return l.second > r.second;
    }
};
//map排序
template<class T>
bool First_Cmp_Up(T &l, T &r)
{
    return l.first > r.first;
}

template<class T>
bool Second_Cmp_down(T &l, T &r)
{
    return l.second < r.second;
}
//vector排序
template<class T>
bool Id_Cmp_Up(T &l, T &r)
{
     return l -> get_id() > r -> get_id();
}

template<class T>
bool Id_Cmp_Down(T &l, T &r)
{
    return l -> get_id() < r -> get_id();
}

template<class T>
bool Score_Cmp_Up(T &l, T &r)
{
    return l -> get_credit() < r -> get_credit();
}

template<class T>
bool Score_Cmp_Down(T &l, T &r)
{
     return l -> get_credit() > r -> get_credit();
}

std::vector<pair> FirstUp(std::map<int,int>);
std::vector<pair> FirstDown(std::map<int,int>);
std::vector<pair> SecondUp(std::map<int,int>);
std::vector<pair> SecondDown(std::map<int,int>);
#endif // SORT_TEMPLATE_H
