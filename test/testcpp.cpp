
class testcpp
{
private:

public:
    int data;
virtual void test1(); /*抽象函数必须实现，非抽象函数可以不用实现*/
void test2();
    testcpp(int data);
    ~testcpp();
    bool operator< (testcpp &tag) {
        return data < tag.data;
    }
    testcpp & operator = (const testcpp& tag) {
        data = 51;
        return *this;
    }
};

testcpp::testcpp(int d){ data = d;}
testcpp::~testcpp(){}

#include<iostream>
#include<algorithm>
void testcpp::test1() {std::cout <<"test1"<<std::endl;}

int main() {
    testcpp t[5] = {testcpp(21),testcpp(13),testcpp(31),testcpp(16),testcpp(11)};
    std::sort(&t[0],&t[5]);
    for(int i = 0; i< 5;i++) std::cout << t[i].data << std::endl;
    return 0;
}