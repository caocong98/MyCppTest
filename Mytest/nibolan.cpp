#include <iostream>
#include <string.h>
#include <stack>
#include <unordered_set>
using namespace std;
//字符串表达式计算， 中序转后序(逆波兰表达式) 后运算  

class Solution {
public:
    int solve(string s) {
        // write code here
        stack<char> sign;
        stack<int> num;
        for (int i = 0; i < s.size(); i++) {
            if(s[i] >= '0' && s[i] <= '9'){
                int n = 0;
                while (i < s.size() && s[i] >= '0' && s[i] <= '9') {
                    n = n * 10 + (s[i] - '0');
                    ++i;
                }
                --i;
                num.push(n);
            }
            else if (sign.size() == 0 || s[i] == '*'|| s[i] == '(') { 
                sign.push(s[i]);
            }
            else if (s[i] == '+' || s[i] == '-') {
                while(1){
                    if(sign.size() == 0){
                        break;
                    }
                    if(sign.top() == '*'){
                        sign.pop();
                        int n2 = num.top();
                        num.pop();
                        int n1 = num.top();
                        num.pop();
                        num.push(n1*n2);
                    }
                    else if(sign.top() == '+'){
                        sign.pop();
                        int n2 = num.top();
                        num.pop();
                        int n1 = num.top();
                        num.pop();
                        num.push(n1+n2);
                    }
                    else if(sign.top() == '-'){
                        sign.pop();
                        int n2 = num.top();
                        num.pop();
                        int n1 = num.top();
                        num.pop();
                        num.push(n1-n2);
                    }
                    else{
                        break;
                    }
                }
                sign.push(s[i]);
            }
            else if(s[i] == ')'){
                while(1){
                    if(sign.size() == 0){
                        break;
                    }
                    else if(sign.top() == '('){
                        sign.pop();
                        break;
                    }
                    else if(sign.top() == '+'){
                        sign.pop();
                        int n2 = num.top();
                        num.pop();
                        int n1 = num.top();
                        num.pop();
                        num.push(n1+n2);
                    }
                    else if(sign.top() == '-'){
                        sign.pop();
                        int n2 = num.top();
                        num.pop();
                        int n1 = num.top();
                        num.pop();
                        num.push(n1-n2);
                    }
                    else if(sign.top() == '*'){
                        sign.pop();
                        int n2 = num.top();
                        num.pop();
                        int n1 = num.top();
                        num.pop();
                        num.push(n1*n2);
                    }
                }
            }
        }
        while(sign.size()!=0){
            if(sign.top() == '+'){
                sign.pop();
                int n2 = num.top();
                num.pop();
                int n1 = num.top();
                num.pop();
                num.push(n1+n2);
            }
            else if(sign.top() == '-'){
                sign.pop();
                int n2 = num.top();
                num.pop();
                int n1 = num.top();
                num.pop();
                num.push(n1-n2);
            }
            else if(sign.top() == '*'){
                sign.pop();
                int n2 = num.top();
                num.pop();
                int n1 = num.top();
                num.pop();
                num.push(n1*n2);
            }
        }
        return num.top();
    }
};

int main() {

    return 0;
}