#include <iostream>
#include "floatadd class.hpp"
using namespace std;

int main()
{   
    int const N=160;
    string num1,num2;
    cin >> num1;
    cin >> num2;
    BigDecimal a(num1);
    BigDecimal b(num2);
    BigDecimal c=a+b;
    cout<<c.toString()<<endl;
    

    
    return 0;
}