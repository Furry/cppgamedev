#include <map>

using namespace std;

class MyClass {
    private:
        map<int, map<int, int>> test;
    public:
        MyClass();
        void run();
};

MyClass::MyClass() {
    test = map<int, map<int, int>>();
}

void MyClass::run() {
    map<int, int> tmp = map<int, int>();
    test.insert_or_assign(0, tmp);
}

int main() {
    MyClass* myClass = new MyClass();
    myClass->run();
    return 0;
}