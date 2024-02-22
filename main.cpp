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
    Decimal si = Decimal("23.1999");
    Decimal su = Decimal("3269");
    Decimal four = Decimal("4");
    Decimal two = Decimal ("2");
    std::cout <<"b < o: "<< b<<" "<<"<" <<" "<< o<<" = "<< (b < o)<< '\n';
    std::cout << "t > e: " << t <<" "<< ">" <<" "<< e<<" = "<< (t > e) << '\n';
    std::cout << "a == k: " << a<<" "<< "==" <<" "<< k<<" = "<< (a == k) << '\n';
    std::cout << "a != k: " << a<<" "<< "!=" <<" "<< k<<" = "<< (a != k) << '\n';
    std::cout <<"t + e : "<< t << " + "<< e <<" = "<< (t + e) <<'\n';
    std::cout <<"t - e : "<< t << " - "<< e <<" = "<< (t - e) <<'\n';
    std::cout << "si * su: " << si<< " * " << su << " = "<< si*su<< "\n";
    std::cout << "\n"<<"Введите число знаков после запятой числа Пи: ";
    int n = 0;
    std::cin >> n ;
    Decimal g = Decimal();
    g = FunctionPi(n);
    std::cout << g;
    return 0;
}