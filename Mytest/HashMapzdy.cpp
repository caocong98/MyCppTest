#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <map>
#include <set>
#include <unordered_set>
#include <sstream>
#include <cmath>
// #include <bits/stdc++.h>
using namespace std;

static int num = 0;

struct pair_hash
{
    template<typename T1, typename T2>
    std::size_t operator() (const std::pair<T1, T2>& p) const {
        return std::hash<T1>{}(p.first) ^ std::hash<T2>{}(p.second);
    }
};

struct pair_equal
{
    template<typename T1, typename T2>
    bool operator() (const std::pair<T1, T2>& a, const std::pair<T1, T2>& b) const {
        return a.first == b.first && a.second == b.second;
    }
};



int main() {

    cout << endl;
    return 0;
}