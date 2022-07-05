#include <iostream>
#include <sstream>
using namespace std;

int main() {
// istringstream 按空格分割字符串

    string test1("aa  bb cc dd   ");
    // istringstream is(test1);
    stringstream is(test1);  // 可输入可输出
    string temp;
    while (is >> temp) {
        cout << temp << ' ';
    }
    cout << "end" << endl;

// getline + sstream 按指定字符分割
// getline原型    istream& getline(istream& is, string& str, char delim)  delim默认为‘\n’因此默认取1行

    // istringstream is2("a/b/c/d///");   // 遇到连续/会输出空串
    // stringstream is2("a/b/c/d///");   // 遇到连续/会输出空串
    stringstream is2;   // 遇到连续/会输出空串
    getline(cin, test1);
    is2 << test1;
    while(getline(is2, temp, '/')) cout << temp;
    cout << "end" << endl;

    // test cin.ignore(), getline 混用
    string tignore("");
    cin >> tignore;
    cin.ignore();  //不加会出现异常情况
    getline(cin, tignore);
    cout << tignore << endl;
    return 0;
}