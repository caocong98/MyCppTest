#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
public:
    int numUniqueEmails(vector<string> &emails) {
        unordered_set<string> emailSet;
        for (auto &email: emails) {
            string local;
            for (char c: email) {
                if (c == '+' || c == '@') {
                    break;
                }
                if (c != '.') {
                    local += c;
                }
            }
            cout << local + email.substr(email.find('@')) << endl; 
            emailSet.emplace(local + email.substr(email.find('@')));
        }
        return emailSet.size();
    }
};

int main() {
    vector<int> test{1, 2, 3};
    for (auto& num : test) num = 2;
    for (auto& num : test) cout << num << endl;
    vector<string> emails{"test.email+alex@leetcode.com", "test.email@leetcode.com"};
    cout << Solution().numUniqueEmails(emails) << endl;
    return 0;
}