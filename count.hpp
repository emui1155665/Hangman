#ifndef COUNT_HPP
#define COUNT_HPP

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>    // std::sort

using namespace std;

class Count{
public:
    Count();
    ~Count();
    int totalCount;
    int totalWord;
    string correctGuess = "";
    string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    vector <pair<string,float>> library;
    float letterP [26] = {};
    int countTotal(const string &in);
    int genP(const string &in, const string &out); //generate possibility
    void problem1(const string &in, const string &out);
    void problem2(string evidence, string guess, const string &in, const string &out);
    void calcTotalP(string s, float pos,float currp, string guess);
    float seeks(string s, string evidence, string guess);
    float maxi();
};

#endif