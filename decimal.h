#ifndef DECIMAL_H
#define DECIMAL_H
#include <vector>
#include <string>

class Decimal {
    public:
        Decimal StrToDec(const std::string&);
        std::string DecToStr(const Decimal&);
        std::vector<int> mant;
        std::vector<int> ord;
        int sign;
        Decimal() = default;
        Decimal(std::string);
        Decimal& operator+=(const Decimal& rhs);
        Decimal& operator-=(const Decimal& rhs);
        Decimal& operator*=(const Decimal& rhs);
        Decimal& operator/=(const Decimal& rhs);
        Decimal& operator=(const Decimal& rhs);
        ~Decimal();
        
        
};
Decimal& ShiftLeft(Decimal &rhs, int num);
Decimal& ShiftRight(Decimal &rhs, int num);
Decimal& operator~(Decimal& lhs);
Decimal operator+ (const Decimal& lhs, const Decimal& rhs);
Decimal operator- (const Decimal& lhs, const Decimal& rhs);
Decimal operator* (const Decimal& lhs, const Decimal& rhs);
// Decimal operator/ (const Decimal lhs, const Decimal& rhs);

bool operator==(const Decimal& lhs, const Decimal& rhs);
bool operator!=(const Decimal& lhs, const Decimal& rhs);
bool operator>(const Decimal& lhs, const Decimal& rhs);
bool operator<(const Decimal& lhs, const Decimal& rhs);
bool operator<=(const Decimal& lhs, const Decimal& rhs);
bool operator>=(const Decimal& lhs, const Decimal& rhs);

Decimal FunctionPi(int precision);

std::ostream& operator<<(std::ostream& os, const Decimal& obj);
std::istream& operator>>(std::istream& is, std::string obj);
#endif 