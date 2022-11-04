#include <iostream>
#include <thread>
#include <shared_mutex>
#include <vector>
#include <windows.h>
using namespace std;

shared_mutex smtx;

vector<int> Books;

void read(int reader) {
    shared_lock<shared_mutex> lc(smtx);
    cout << "Reader " << reader << " begin read." << endl;
    for (auto book : Books) {
        cout << "read " << book << endl;
    }
    Sleep(2000);
    cout << "Reader " << reader << " end read." << endl;
    cout << endl;
}

void write(int writer) {
    unique_lock<shared_mutex> lc(smtx);
    cout << "Writer " << writer << " begin write." << endl;
    for (int i = 0; i < 3; ++i) {
        int book = rand();
        Books.push_back(book);
        cout << "write " << book << endl;
    } 
    Sleep(2000);
    cout << "Writer " << writer << " end write." << endl;
    cout << endl;
}

int main() {
    thread w1(write, 1);
    thread w2(write, 2);
    thread r1(read, 1);
    thread r2(read, 2);
    thread w3(write, 3);
    w1.join();
    w2.join();
    r1.join();
    r2.join();
    w3.join();
    system("pause");
    return 0;
}