#include <iostream>
#include <string>
#include <cctype>//isalpha、isdigit要包含这个头文件
using namespace std;

int main() {
    string s;
    cout << "请输入一个字符串：";
    getline(cin, s);//用getline，空格也能读进来

    int letters = 0;//英文字母
    int digits = 0;//数字
    int others = 0;//其他字符

    for (int i = 0; i < (int)s.size(); i++) {
        char c = s[i];//把每个字符单独拿出来判断
        if (isalpha(c)) {
            letters++;
        } else if (isdigit(c)) {
            digits++;
        } else {
            others++;
        }
    }

    cout << "英文字母个数：" << letters << endl;
    cout << "数字个数：" << digits << endl;
    cout << "其他字符个数：" << others << endl;

    return 0;
}
