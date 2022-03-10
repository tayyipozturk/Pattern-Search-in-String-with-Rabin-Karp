#include <sys/types.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <list>
#include <string>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <cmath>

using namespace std;

vector<int> substringMatch(const string&, const vector<string>&);
void buildHash(int, int, int, const vector<string>&, vector<vector<int> >&);
int64_t hashCode(string, int, int, int);
int64_t moduloPower(int, int, int, int, int);
int64_t exponentiation(int32_t, int32_t, int);

vector<int> substringMatch(const string& text, const vector<string>& patterns){

    vector<int> shifts;
    int n = text.length();
    int m = patterns[0].length();
    int mult = 26;
    int prime = 10139;
    vector<vector<int> > hashTable(prime);
    
    buildHash(m, mult, prime, patterns, hashTable);
    
    string target = text.substr(0,m);
    int64_t code = hashCode(target, m, mult, prime);
    int it = 0;
    int size = hashTable[code].size();
    while(it<size){
        string val = patterns[hashTable[code][it]];
        if(!target.compare(val)){
            shifts.push_back(0);
            break;
        }
        ++it;
    }
    for(int i=1; i<=n-m; i++){
        int ll = text[i-1] - 'a' + 1;
        int nn = text[i+m-1] - 'a' + 1;
        code -= moduloPower(ll, m, mult, prime, 0);
        if(code<0){
            code+=prime;
        }
        code *= mult;
        code += nn;
        code = code % prime;
        target = text.substr(i,m);
        size = hashTable[code].size();
        it=0;
        while(it<size){
            string val = patterns[hashTable[code][it]];
            if(!target.compare(val)){
                shifts.push_back(i);
                break;
            }
            ++it;
        }
    }
    return shifts;
}

void buildHash(int m, int mult, int prime, const vector<string>& patterns, vector<vector<int> >& hashTable){
    int p = patterns.size();
    for(int k=0; k<p; k++){
        int64_t code=0;
        for(int i = 0; i<m; i++){
            int ll = patterns[k][i] - 'a' + 1;
            code += moduloPower(ll, m, mult, prime, i);
            code = code % prime;
        }
        hashTable[code].push_back(k);
    }
}

int64_t hashCode(string target, int m, int mult, int prime){
    int64_t code=0;
    for(int i=0; i<m; i++){
        int ll = target[i] - 'a' + 1;
        code += moduloPower(ll, m, mult, prime, i);
        code = code % prime;
    }
    return code;
}

int64_t moduloPower(int number, int m, int mult, int prime, int i){
    int64_t result = number;
    int64_t x = exponentiation(mult, m-i-1, prime);
    result *= x;
    result = result % prime;
    return result;
    
}

int64_t exponentiation(int32_t base,
                        int32_t exp, int prime)
{
    if (exp == 0)
        return 1;
  
    if (exp == 1)
        return base % prime;
  
    int64_t t = exponentiation(base, exp / 2, prime);
    t = (t * t) % prime;
    if (exp % 2 == 0)
        return t;
    else
        return ((base % prime) * t) % prime;
}

int main(){
    string target;
    vector<string> patterns;
    ifstream file("input.txt");
    getline(file, target);
    string temp;
    while(getline(file, temp)){
        patterns.push_back(temp);
    }

    vector<int> v = substringMatch(target, patterns);
    for(vector<int>::iterator i=v.begin();i!=v.end();i++){
        cout<<*i<<" ";
    }

    return 0;
    int64_t x;
    while(1){
        cin>>target;
        x = hashCode(target,target.size(),26,10313);
        cout<<x<<endl;
    }
}
