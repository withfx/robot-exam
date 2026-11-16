#include <iostream>
#include <algorithm>//sort排序用
#include <functional>//greater用
using namespace std;

int main() {
    int scores[10];//能存10个同学的成绩

    cout << "请输入10名同学的成绩：";
    for (int i = 0; i < 10; i++) {
        cin >> scores[i];
    }

    sort(scores, scores + 10, greater<int>());//从大到小排

    cout << "成绩从高到低排序结果：" << endl;
    for (int i = 0; i < 10; i++) {
        cout << scores[i];
        if (i != 9) {
            cout << " ";//最后一个数后面不加空格
        }
    }
    cout << endl;

    return 0;
}
