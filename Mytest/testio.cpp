#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int main()
{
    vector<string> teststr{"abc", "ccc"};
    ifstream fin;
    fin.open("test.txt");
    // while (fin.peek() != EOF) 
    // {
    //     string line;
    //     getline(fin, line);
    //     cout << line << endl;
    // }
    // fin.close();
    if(getline(fin, teststr[0]))
        cout << 'a';
    
    cout << teststr[0];
    fin.close();
    // vector<ifstream> fins;
    // fins.emplace_back("test.txt");
    // string line;
    // getline(fins[0], line);
    // cout << line << endl;
    // fins[0].close();

    return 0;
}