#include <iostream>
#include "SP.h"
#include <vector>

using namespace std;


int main() {
    cout << "test hunger patter(double lock):" << endl;
    vector<thread> myThread;
    for (int i = 0; i < 5; ++i) {
        myThread.push_back(thread(SinglePa::get_instance));
    }
    for (int i = 0; i < 5; ++i) {
        myThread[i].join();
    }
    SinglePa* p1 = SinglePa::get_instance();
    p1->test();
    SinglePa::destroy();

    cout << "test hunger patter(static local object):" << endl;
    SinglePb* p2 = SinglePb::get_instance();

    cout << "test lazy patter:" << endl;

    SinglePc* p3 = SinglePc::get_instance();
    SinglePc::destroy();

    return 0;
}