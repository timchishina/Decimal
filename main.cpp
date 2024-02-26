#include <iostream>
#include "decimal.h"


int main(){
    Decimal a = Decimal("223.7891");
    Decimal c = Decimal("-2212122.00003");
    Decimal k = a;
    Decimal b = Decimal("919.989");
    Decimal o = Decimal("919.9898");
    Decimal t = Decimal("132662.19089287474");
    Decimal e = Decimal("695.9970");
    Decimal si = Decimal("-22.1");
    Decimal su = Decimal("-22.05");
    Decimal four = Decimal("4.002");
    Decimal two = Decimal ("2");
    std::cout <<"b < o: "<< b<<" "<<"<" <<" "<< o<<" = "<< (b < o)<< '\n';
    std::cout << "t > e: " << t <<" "<< ">" <<" "<< e<<" = "<< (t > e) << '\n';
    std::cout << "a == k: " << a<<" "<< "==" <<" "<< k<<" = "<< (a == k) << '\n';
    std::cout << "a != k: " << a<<" "<< "!=" <<" "<< k<<" = "<< (a != k) << '\n';
    std::cout <<"four + two : "<< four << " + "<< two <<" = "<< (four + two) <<'\n';
    std::cout <<"t - e : "<< t << " - "<< e <<" = "<< (t - e) <<'\n';
    std::cout << (23.4_dc )<< '\n';
    std::cout << " o * b: "<< o << " * "<< b << " = " << (o *= b) << "\n";
    std::cout <<( c/=a)<<" == " << " -9884.851" <<'\n';
    std::cout <<( t/=e)<<" == " << " 190,60"<< '\n';
    return 0;
}