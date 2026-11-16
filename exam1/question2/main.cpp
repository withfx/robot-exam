#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string title;//书名
    float price;//价格
    int stock;//库存

public:
    Book() {//构造函数：对象一创建就会执行
        title = "";
        price = 0.0f;
        stock = 0;
    }

    ~Book() {//析构函数：对象被销毁时会执行
        cout << "Book 对象已销毁" << endl;
    }

    void input() {
        cout << "请输入书名：";
        getline(cin, title);//用getline才能把带空格的书名整行读进来

        cout << "请输入价格：";
        cin >> price;

        cout << "请输入库存：";
        cin >> stock;
    }

    void display() {
        cout << "书名：" << title << endl;
        cout << "价格：" << price << endl;
        cout << "库存：" << stock << endl;
    }
};

int main() {
    Book* p = new Book();//用new在堆上创建一个Book对象
    p->input();//通过指针调用input
    p->display();//通过指针调用display
    delete p;//用完记得释放，不然会内存泄漏

    return 0;
}
