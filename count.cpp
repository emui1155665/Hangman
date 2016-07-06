#include "count.hpp"

Count::Count(){
}
Count::~Count(){
}

bool compare (pair<string,float> x, pair<string,float> y){
    return x.second > y.second;
}
int Count::countTotal(const string &in){
    int count = 0;
    int total = 0;
    ifstream input(in);
    if(!input){
        cerr<<"Unable to open file - "<<in<<std::endl;
        return EXIT_FAILURE;
    }
    string word;
    int number;
    while(input.good()){
        input>>word>>number;
        total += number;
        count++;
    }
    totalCount = total;
    totalWord = count;
    return totalCount;
}

//generate the possibilities in an output file. Return 1 for success or EXIT_FAILURE for failure.
int Count::genP(const string &in, const string &out){
    ifstream input(in);
    ofstream output(out);
    if(!input){
        cerr<<"Unable to open file - "<<in<<std::endl;
        return EXIT_FAILURE;
    }
    string word;
    int number;
    while(input.good()){
        input>>word>>number;
        library.push_back(pair<string,float>(word,(float)number/totalCount));
    }
    sort(library.begin(),library.end(),compare);
    for (vector<pair<string,float>>::iterator it = library.begin() ; it != library.end(); ++it){
        output<<it->first<<" "<<it->second<<'\n';
    }
    return 1;
}

void Count::problem1(const string &in, const string &out){
    string line;
    int counter = 0;
    ifstream input(in);
    ofstream output(out);
    if(!input){
        cerr<<"Unable to open file - "<<in<<std::endl;
    }
    if (input.is_open())
    {
        while ( getline (input,line))
        {
            if(counter<15)
                output << "No."<<counter+1<<" most frequent word "<<line << '\n';
            else if(counter>totalWord-16)
                output << "No."<<totalWord-counter<<" least frequent word "<<line << '\n';
            counter++;
        }
        input.close();
    }
}

float calcP(char character, string s, float pos){
    float p2 = 0.0;
    if(s.find(character) != string::npos){
        p2 = 1.0;
    }
    return p2;
}

void Count::calcTotalP(string s, float pos, float currp, string guess){
    float result = 0.0;
    bool flag = 1;
    for(int i = 0; i<26; i++){
        result = calcP(letters.at(i),s,pos);
        for(int l =0; l<correctGuess.length(); l++){
            if(letters[i] == correctGuess[l]){
                result = 0.0;
                flag = 0;
                break;
            }
            else{
                result = calcP(letters.at(i),s,pos);
            }
        }
        if(!flag) {
            letterP[i] += result*pos*currp;
            continue;
        }
        for(int k =0; k<guess.length(); k++){
            if(letters[i] == guess[k]){
                result = 0.0;
                flag = 0;
                break;
            }
            else{
                result = calcP(letters.at(i),s,pos);
            }
        }
        letterP[i] += result*pos*currp;
    }
}

float Count::seeks(string s, string evidence, string guess){
    float result = 1;
    bool flag = 1;
    for(int i = 0; i<5; i++){
        if(evidence.at(i) == '_') {
            for(int k = 0; k<guess.length(); k++){
                if(s[i] == guess[k]){
                    result = 0;
                    flag = 0;
                }
            }
            for(int k = 0; k<correctGuess.length(); k++){
                if(s[i] == correctGuess[k]){
                    result = 0;
                    flag = 0;
                }
            }
            if(!flag){
                break;
            }
        }
        else if(s[i]!=(evidence[i])){
            result = 0;
            break;
        }
        else{
            result = 1;
        }
    }
    return result;
}

//input evidence like: a_b_c. '_'means unknown
void Count::problem2(string evidence, string guess, const string &in, const string &out){
    for(int i = 0; i<26; i++){
        letterP[i] = 0.0;
    }
    for(int k = 0; k<evidence.length(); k++){
        if(evidence[k] != '_'){
            correctGuess+=evidence[k];
        }
    }
    float currp;
    float p;
    string cur;
    float denominator = 0.0;
    ifstream input(in);
    ofstream output(out);
    output<<"evidence is "<<evidence<<" Have guessed "<<guess<<endl;
    if(!input){
        cerr<<"Unable to open file - "<<in<<std::endl;
    }
    while(input.good()){
        input>>cur>>p;
        cerr<<"checking "<<cur<<endl;
        currp = 0.0;
        if(seeks(cur,evidence,guess)){
            denominator += p;
            currp = 1.0;
        }
        calcTotalP(cur,p,currp,guess);
    }
    for(int i = 0; i<26; i++){
        output<<letters[i]<<" "<<letterP[i]/denominator<<endl;
    }
    float max=0.0;
    char ch='A';
    for(int i = 0; i<26; i++){
        if(letterP[i]/denominator>max){
            max = letterP[i]/denominator;
            ch = letters[i];
        }
    }
    output<< ch<<" "<<max<<endl;
}