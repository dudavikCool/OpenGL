#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;
#include "gl++/geometry.hpp"


int main() {
    vector<int> vec1{1, 2, 3, 4};
    vector<int> vec2{5, 6, 7};
    vec1.insert(vec1.end(), vec2.begin(), vec2.end());
    char array[10] = "abcdefghi";
    for(auto i: array) {
        cout << i;
    }
}