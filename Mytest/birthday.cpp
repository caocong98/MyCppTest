#include <iostream>
using namespace std;


// 给出生日，和当前日期计算离下一次生日还有几天
// 先求出下次生日日期， 再求出两个日期时间差(计算两个日期到今年1月1日的时间差再作差)  特判 2月29生日， 四年一次

int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main() {
    cout << "input birthday:";
    int bmonth, bday;
    cin >> bmonth >> bday;
    cout << "input now date:";
    int nyear, nmonth, nday;
    cin >> nyear >> nmonth >> nday;
    int byear = nyear; //下一次生日年份
    if (bmonth < nmonth || (bmonth == nmonth && bday < nday)) {
        //当年生日已过，加一年
        ++byear;
    }
    //2.29生日特判
    if (bmonth == 2 && bday == 29) {
        while (!((byear % 4 == 0 && byear % 100) || byear % 400 == 0)) {
            ++byear;
        }
    }

    int day1 = 0, day2 = 0;
    //计算下次生日与 当前年份1月1日时间差
    if (byear > nyear) {
        day1 += 365;
        if (((nyear % 4 == 0 && nyear % 100) || nyear % 400 == 0)) ++day1;
    }
    for (int i = 1; i < bmonth; ++i) {
        day1 += days[i];
        if (i == 2 && ((byear % 4 == 0 && byear % 100) || byear % 400 == 0)) ++day1;
    }
    day1 += bday;

    //计算当前时间与当前年份1月1日时间差
    for (int i = 1; i < nmonth; ++i) {
        day2 += days[i];
        if (i == 2 && ((nyear % 4 == 0 && nyear % 100) || nyear % 400 == 0)) ++day2;
    }
    day2 += nday;
    cout << "The next birsthday have " << day1 - day2 << " days" << endl;

    //精确到小时分钟 天数-1 ，  时间差为 24:00 与当前时间的时间差  

    return 0;
}