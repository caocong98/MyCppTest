#include <iostream>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <windows.h>
#include <assert.h>
#include <queue>
using namespace std;

// 赛车比赛， 1、5辆比一次，比完有垃圾残留。 2、垃圾残留达到20需要打扫，打扫至0
// 3、赛场上赛车和清扫车不能同时存在。  4、赛车按顺序循环重复比赛
// 线程安全 模拟   注意最后一场比赛结束，垃圾没到阈值也要清理

class Match {
public:
    Match(int n, int r, int t) : PlayGround(5) {
        assert(n >= 5); //至少5辆赛车
        for (int i = 1; i <= n; ++i) {
            q.push(i); //赛车入队
        } 
        Rabbish = r;
        NowRabbish = 0;
        state = 0;
        Times = t;
    }
    void begin() {
        STOP = false;
        thread a(Match::CarEnter, this);
        thread b(Match::MatchBegin, this);
        thread c(Match::CarLeave, this);
        thread d(Match::Clearn, this);
        a.join();
        b.join();
        c.join();
        d.join();
        cout << "All matches end." << endl;;
    }
    void CarEnter() {
        unique_lock<mutex> lc(mtx);
        for (int i = 1; i <= Times; ++i) {
            while (state != 0) mcon.wait(lc);
            cout << "Car begin Enter." << endl;;
            for (int t = 0; t < 5; ++t) {
                int now = q.front();
                q.pop();
                PlayGround[t] = now;
                cout << "Car " << now << " enter." << endl;
            }
            state = 1; //比赛开始
            mcon.notify_all();
        }
        // Sleep(5000);
        // cout << "Function CarEnter() quit.\n";
    }
    void MatchBegin() {
        unique_lock<mutex> lc(mtx);
        for (int i = 1; i <= Times; ++i) {
            while (state != 1) mcon.wait(lc);
            cout << "Match " << i << " begin" << endl;
            Sleep(2000); //模拟比赛
            NowRabbish += 5; //产生垃圾
            state = 2; //赛车离场
            cout << "Match " << i << " end" << endl;
            mcon.notify_all();
        }
        // Sleep(5000);
        // cout << "Function MatchBegin() quit.\n";
    }
    void CarLeave() {
        unique_lock<mutex> lc(mtx);
        for (int i = 1; i <= Times; ++i) {
            while (state != 2) mcon.wait(lc);
            cout << "Cars begin leave." << endl;
            for (int t = 0; t < 5; ++t) {
                q.push(PlayGround[t]);
                cout << "Car " << PlayGround[t] << " leave" << endl; 
            }
            cout << "All cars have leaving" << endl;
            cout << endl;
            if (NowRabbish >= Rabbish || i == Times) state = 3; //清扫
            else state = 0;  //否则接着入场比赛
            if (i == Times) STOP = true;
            mcon.notify_all();
        }
        // Sleep(5000);
        // cout << "Function CarLeave() quit.\n";
    }
    void Clearn() {
        unique_lock<mutex> lc(mtx);
        while (STOP == false) {
            while (state != 3) mcon.wait(lc);
            cout << "Begin clearn." << endl;
            Sleep(2000);
            cout << "Clearn over." << endl;
            NowRabbish = 0;
            state = 0;
            mcon.notify_all();
            // if (STOP == false) mcon.notify_all();
        }
        // cout << "Function Clearn() quit.\n";
    }
private:
    mutex mtx;
    condition_variable mcon;
    queue<int> q; //参赛赛车
    vector<int> PlayGround; //存放赛场中的赛场
    int Rabbish; // 20为打扫阈值
    int NowRabbish;
    int state; // 0:赛车入场   1:进行比赛   2：赛车离场  3： 打扫赛场
    int Times; //比赛总次数 
    bool STOP; //所有比赛是否结束   用于清扫程序退出
};


int main() {
    Match match1(10, 20, 4);
    match1.begin();
    system("pause");
    return 0;
}