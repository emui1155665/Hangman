//
//  main.cpp
//  HW1
//
//  Created by Emma Li on 7/4/16.
//  Copyright © 2016 Emma Li. All rights reserved.
//

#include <iostream>
#include "main.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
 
    Count count;
    count.countTotal("hw1_word_counts_05.txt");// insert code here...
    //count.genP("word_counts.txt", "out.txt");
    //count.problem1("out.txt","prob1.txt");
    count.problem2("D__I_","A","out.txt","b8.txt");
    cerr<<"hello world\n";
}
