#include "decimal.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

Decimal::Decimal(std::string str){
    Decimal num = Decimal::StrToDec(str);
    this->mant = num.mant;
    this->ord = num.ord;
    this->sign = num.sign;
}

Decimal:: ~Decimal(){
    this->mant.clear();
    this->ord.clear();
}

Decimal Decimal::StrToDec(const std::string &num) {
    int i = 0;
    int len = num.size();
    Decimal number = Decimal();
    while (num[i] == ' '){
        i++; len--;
    }
    if (num[i] == '-'){
        len--;
        number.sign = 1;
        i++;
    }else{
        number.sign = 0;
    }
    while ((len != 0) and (num[i] != '.') and (num[i] != ' ') and (num[i] != '\n')) {
        number.ord.push_back(num[i] & 0x0F);
        i++;
        len --;
    }
    if (len == 0) {
        return number;
    }
    if((num[i] == ' ') or (num[i] == '\n')){
            return number;
    }
    i++;
    if (num[i] != ' '){
        while ((len > 1) and (num[i] != ' ') and (num[i] != '\n')) {
            number.mant.push_back(num[i] & 0x0F);
            i++;
            len --;
        }
    }
    return number;
}

std::string Decimal::DecToStr(const Decimal &num){
    int len_mant = num.mant.size();
    int len_ord = num.ord.size();
    std::string number;
    for (int i = 0; i < len_ord; i++){
        number.push_back(num.ord[i] + '0');
    }
    if (len_mant > 0){
        number.push_back('.');
        for (int i = 0; i < len_mant; i++){
            number.push_back(num.mant[i] + '0');
        }
    }
    if (num.sign == 1){
        number.insert(number.begin(), '-');
    }
    return number;
}

Decimal& Decimal::operator=(const Decimal &rhs) {
    mant = rhs.mant;
    ord = rhs.ord;
    sign = rhs.sign;
    return *this;
}

Decimal operator+(const Decimal& lhs, const Decimal& rhs){
    Decimal SumDec (lhs);
    SumDec += rhs;
    return SumDec;
} 

Decimal operator-(const Decimal& lhs, const Decimal& rhs){
    Decimal DiffDec = lhs;
    Decimal Num = rhs;
    DiffDec -= Num;
    return DiffDec;
}

Decimal operator*(const Decimal&lhs, const Decimal& rhs){
    Decimal MultDec = lhs;
    MultDec *= rhs;
    return MultDec;
}

Decimal operator/(const Decimal&lhs, const Decimal& rhs){
    Decimal DivDec = lhs;
    DivDec /= rhs;
    return DivDec;
}

Decimal& operator~(Decimal& lhs){
    if(lhs.sign == 0){
        lhs.sign = 1;
    }
    else {
        lhs.sign = 0;
    }
    return lhs;
}

Decimal& Decimal::operator+=(const Decimal &rhs){
    int overflow = 0;
    int len_mant_this = this->mant.size();
    int len_ord_this = this->ord.size();
    int len_mant_rhs = rhs.mant.size();
    int len_ord_rhs = rhs.ord.size();
    int len_mant_mn = std::min(len_mant_rhs,len_mant_this);
    int len_ord_mn = std::min(len_ord_this, len_ord_rhs);
    if (((this->sign == 0) and (rhs.sign == 0)) or ((this->sign == 1) and (rhs.sign == 1))){
        if (len_mant_this <= len_mant_rhs){
            for (int i = len_mant_this - 1; i >= 0 ; i--){
                this->mant[i] = this->mant[i] + rhs.mant[i] + overflow;
                overflow = this->mant[i] / 10;
                this->mant[i] = this->mant[i] % 10;
            }
            if (len_mant_rhs > len_mant_this){
                for (int i = len_mant_this; i < len_mant_rhs; i++){
                    this->mant.push_back(rhs.mant[i]);
                }  
            }
        }
        else{
            for (int i = len_mant_rhs - 1; i >= 0; i--){
                this->mant[i] = this->mant[i] + rhs.mant[i] + overflow;
                overflow = this->mant[i] / 10;
                this->mant[i] = this->mant[i] % 10;
            }
        }

        if (len_ord_this <= len_ord_rhs){
            for (int i = 1; i <= len_ord_this; i++){
                this->ord[len_ord_this - i] = this->ord[len_ord_this - i] + rhs.ord[len_ord_rhs - i] + overflow;
                overflow = this->ord[len_ord_this - i] / 10;
                this->ord[len_ord_this - i] = this->ord[len_ord_this - i] % 10;
            }
            if (len_ord_rhs > len_ord_this){
                for (int i = len_ord_this + 1; i <= len_ord_rhs; i++){
                    this->ord.insert(this->ord.begin(), (rhs.ord[len_ord_rhs - i] + overflow)%10);
                    overflow = (rhs.ord[len_ord_rhs - i] + overflow)/10;
                }
            }
            if (overflow > 0){
                this->ord.insert(this->ord.begin(), overflow);
            }
        }
        else{
            for (int i = 1; i <= len_ord_rhs; i++){
                this->ord[len_ord_this - i] = this->ord[len_ord_this - i] + rhs.ord[len_ord_rhs - i] + overflow;
                overflow = this->ord[len_ord_this - i] / 10;
                this->ord[len_ord_this - i] = this->ord[len_ord_this - i] % 10;
            }
            for (int i = len_ord_rhs + 1; i <= len_ord_this; i++){
                this->ord[len_mant_this - i] = (this->ord[len_mant_this - i] + overflow)%10;
                overflow = (this->ord[len_ord_this - i] + overflow)/10;
            }
            if (overflow > 0){
                this->ord.insert(this->ord.begin(), overflow);
            }
        }
        return *this;
    }
    else if ((this->sign == 0) and (rhs.sign == 1)) {
        Decimal two = rhs;
        two.sign = 0;
        return ((*this) -= two);
    }
    else {
        Decimal two = *this;
        Decimal first = rhs;
        two.sign = 0;
        *this = first - two;
        return *this;
    }
}

Decimal& Decimal::operator-=(const Decimal &rhs){
    if ((this->sign == 0) and (rhs.sign == 1)){
        Decimal second = rhs;
        return *this += (~second);
    }
    if ((this->sign == 1) and (rhs.sign == 0)){
        Decimal second = rhs;
        return *this += (~second);
    }
    int overflow = 0;
    int len_mant_this = this->mant.size();
    int len_ord_this = this->ord.size();
    int len_mant_rhs = rhs.mant.size();
    int len_ord_rhs = rhs.ord.size();
    if ((this->sign == 0) and (rhs.sign == 0)){
        if (*this > rhs){
            if (len_mant_this < len_mant_rhs){
                int len = len_mant_rhs - len_mant_this;
                for (int i = 0; i < len; i++){
                    this->mant.push_back(0);
                    len_mant_this++;
                }
            }
            for (int i = len_mant_rhs - 1; i >= 0 ; i--){
                this->mant[i] = this->mant[i] - rhs.mant[i] - overflow;
                if (this->mant[i] < 0){
                    this->mant[i] = 10 + this->mant[i];
                    overflow = 1;
                }
                else{
                    overflow = 0;
                }
            }
            
            for (int i = 1; i <= len_ord_rhs; i++){                    
                this->ord[len_ord_this - i] = this->ord[len_ord_this - i] - rhs.ord[len_ord_rhs - i] - overflow;
                if (this->ord[len_ord_this - i] < 0){
                    this->ord[len_ord_this - i] = 10 + this->ord[len_ord_this - i];
                    overflow = 1;
                }
                else{
                    overflow = 0;
                }
            }
            if (overflow > 0){
                for (int i = len_ord_rhs + 1; i <= len_ord_this; i++){
                    this->ord[len_ord_this - i] = this->ord[len_ord_this - i] - overflow;
                    if (this->ord[len_ord_this - i] < 0){
                        this->ord[len_ord_this - i] = 10 + this->ord[len_ord_this - i];
                        overflow = 1;
                    } else{
                        overflow = 0;
                        break;
                    }
                }
            }
            int len_zero = 0;
            while((len_ord_this > 1) and (this->ord[len_zero] == 0)){
                this->ord.erase(this->ord.begin());
                len_ord_this--;
            }
            return *this;
        }
        else {
            Decimal tmp = *this;
            *this = rhs;
            len_mant_rhs = tmp.mant.size();
            len_mant_this = rhs.mant.size();
            len_ord_rhs = tmp.ord.size();
            len_ord_this = rhs.ord.size();
            if (len_mant_this < len_mant_rhs){
                int len = len_mant_rhs - len_mant_this;
                for (int i = 0; i < len; i++){
                    this->mant.push_back(0);
                    len_mant_this++;
                }
            }
            for (int i = len_mant_rhs - 1; i >= 0 ; i--){
                this->mant[i] = this->mant[i] - tmp.mant[i] - overflow;
                if (this->mant[i] < 0){
                    this->mant[i] = 10 + this->mant[i];
                    overflow = 1;
                }
                else{
                    overflow = 0;
                }
            }
            for (int i = 1; i <= len_ord_rhs; i++){                    
                this->ord[len_ord_this - i] = this->ord[len_ord_this - i] - tmp.ord[len_ord_rhs - i] - overflow;
                if (this->ord[len_ord_this - i] < 0){
                    this->ord[len_ord_this - i] = 10 + this->ord[len_ord_this - i];
                    overflow = 1;
                }
                else{
                    overflow = 0;
                }
            }
            if (overflow > 0){
                for (int i = len_ord_rhs + 1; i <= len_ord_this; i++){
                    this->ord[len_ord_this - i] = this->ord[len_ord_this - i] - overflow;
                    if (this->ord[len_ord_this - i] < 0){
                        this->ord[len_ord_this - i] = 10 + this->ord[len_ord_this - i];
                        overflow = 1;
                    } else{
                        overflow = 0;
                        break;
                    }
                }
            }
            int len_zero = 0;
            while((len_ord_this > 1) and (this->ord[len_zero] == 0)){
                this->ord.erase(this->ord.begin());
                len_ord_this--;
            }
            this->sign = 1;
            return *this;
        }
    }
    else{
        if(*this > rhs){
            Decimal tmp = *this;
            *this = rhs;
            len_mant_rhs = tmp.mant.size();
            len_mant_this = rhs.mant.size();
            len_ord_rhs = tmp.ord.size();
            len_ord_this = rhs.ord.size();
            if (len_mant_this < len_mant_rhs){
                int len = len_mant_rhs - len_mant_this;
                for (int i = 0; i < len; i++){
                    this->mant.push_back(0);
                    len_mant_this++;
                }
            }
            for (int i = len_mant_rhs - 1; i >= 0 ; i--){
                this->mant[i] = this->mant[i] - tmp.mant[i] - overflow;
                if (this->mant[i] < 0){
                    this->mant[i] = 10 + this->mant[i];
                    overflow = 1;
                }
                else{
                    overflow = 0;
                }
            }
            for (int i = 1; i <= len_ord_rhs; i++){                    
                this->ord[len_ord_this - i] = this->ord[len_ord_this - i] - tmp.ord[len_ord_rhs - i] - overflow;
                if (this->ord[len_ord_this - i] < 0){
                    this->ord[len_ord_this - i] = 10 + this->ord[len_ord_this - i];
                    overflow = 1;
                }
                else{
                    overflow = 0;
                }
            }
            if (overflow > 0){
                for (int i = len_ord_rhs + 1; i <= len_ord_this; i++){
                    this->ord[len_ord_this - i] = this->ord[len_ord_this - i] - overflow;
                    if (this->ord[len_ord_this - i] < 0){
                        this->ord[len_ord_this - i] = 10 + this->ord[len_ord_this - i];
                        overflow = 1;
                    } else{
                        overflow = 0;
                        break;
                    }
                }
            }
            int len_zero = 0;
            while((len_ord_this > 1) and (this->ord[len_zero] == 0)){
                this->ord.erase(this->ord.begin());
                len_ord_this--;
            }
            this->sign = 0;
            return *this;
        }
        else{
            if (len_mant_this < len_mant_rhs){
                int len = len_mant_rhs - len_mant_this;
                for (int i = 0; i < len; i++){
                    this->mant.push_back(0);
                    len_mant_this++;
                }
            }
            for (int i = len_mant_rhs - 1; i >= 0 ; i--){
                this->mant[i] = this->mant[i] - rhs.mant[i] - overflow;
                if (this->mant[i] < 0){
                    this->mant[i] = 10 + this->mant[i];
                    overflow = 1;
                }
                else{
                    overflow = 0;
                }
            }
            
            for (int i = 1; i <= len_ord_rhs; i++){                    
                this->ord[len_ord_this - i] = this->ord[len_ord_this - i] - rhs.ord[len_ord_rhs - i] - overflow;
                if (this->ord[len_ord_this - i] < 0){
                    this->ord[len_ord_this - i] = 10 + this->ord[len_ord_this - i];
                    overflow = 1;
                }
                else{
                    overflow = 0;
                }
            }
            if (overflow > 0){
                for (int i = len_ord_rhs + 1; i <= len_ord_this; i++){
                    this->ord[len_ord_this - i] = this->ord[len_ord_this - i] - overflow;
                    if (this->ord[len_ord_this - i] < 0){
                        this->ord[len_ord_this - i] = 10 + this->ord[len_ord_this - i];
                        overflow = 1;
                    } else{
                        overflow = 0;
                        break;
                    }
                }
            }
            int len_zero = 0;
            while((len_ord_this > 1) and (this->ord[len_zero] == 0)){
                this->ord.erase(this->ord.begin());
                len_ord_this--;
            }
            return *this;
        }
    }
    return *this;
}

Decimal& ShiftLeft(Decimal &rhs, int num){
    if (num == 0){
        return rhs;
    }
    int len_mant_rhs = rhs.mant.size();
    int len_ord_rhs = rhs.ord.size();
    if (len_mant_rhs == 0){
        for(int i = 0; i < num; i++){
            rhs.ord.push_back(0);
        }
    }
    else{
        for (int i = 0; i < num; ++i){
            if (rhs.mant.size() == 0){
                rhs.ord.push_back(0);
            } else{
                rhs.ord.push_back(rhs.mant.front());
                rhs.mant.erase(rhs.mant.begin());
            }
        }
    }
    while(rhs.ord.size() > 1 && rhs.ord.front() == 0) {
        rhs.ord.erase(rhs.ord.begin());
    }
    if (rhs.ord.size() == 0){
        rhs.ord.push_back(0);
    }
    return rhs;
}

Decimal& ShiftRight(Decimal &rhs, int num){
    if (num == 0){
        return rhs;
    }
    int len_mant_rhs = rhs.mant.size();
    int len_ord_rhs = rhs.ord.size();
    int len = len_mant_rhs + len_ord_rhs + num;
    for(int i = 0; i < num; i++){
        rhs.mant.push_back(0);
    }
    int len_mant_now = rhs.mant.size();
    for (int i = len; i >= num; i--){
        if (i - num -len_ord_rhs + 1 <= 0){
            if (i >= len_ord_rhs ){
                rhs.mant[i - len_ord_rhs] = rhs.ord[i - num];
            }
            else{
                rhs.ord[i] = rhs.ord[i - num];
            }
        }
        else{
            rhs.mant[i - len_ord_rhs] = rhs.mant[i - num - len_ord_rhs]; 
        }
    }
    for (int i = 0; i < num; i++){
        if (i <= len_ord_rhs - 1){
            rhs.ord.erase(rhs.ord.begin());
            if (i == len_ord_rhs - 1){
                rhs.ord.push_back(0);
            }
        }
        else{
            rhs.mant[i - len_ord_rhs] = 0;
        }
    }
    int len_zero = 0;
    while(rhs.ord.size() > 1 && rhs.ord.front() == 0) {
        rhs.ord.erase(rhs.ord.begin());
    }
    if (rhs.ord.size() == 0){
        rhs.ord.push_back(0);
    }
    return rhs;
}

Decimal& Decimal::operator*=(const Decimal& rhs){
    Decimal sum = Decimal();
    Decimal x = Decimal();
    x.ord = ord;
    if (mant.size() != 0){
        for (auto i : mant){
            x.ord.push_back(i);
        }
    }
    
    Decimal y = Decimal();
    y.ord = rhs.ord;
    if (rhs.mant.size() != 0){
        for (auto i : rhs.mant){
            y.ord.push_back(i);
        }
    }
    std::reverse(x.ord.begin(), x.ord.end());
    std::reverse(y.ord.begin(), y.ord.end());
    int overflow;
    for (int i = 0; i  < x.ord.size(); ++i){
        overflow = 0;
        for (int j = 0; j < y.ord.size() || overflow != 0; ++j){
            if (i + j >= sum.ord.size()) sum.ord.push_back(0);
            int z;
            if (j < y.ord.size()){
             z = sum.ord[i + j] + x.ord[i]*y.ord[j] + overflow;

            } else{
             z = sum.ord[i + j] + overflow;

            }
            sum.ord[i+j] = z % 10;
            overflow =  z /  10;
        }
    }



    std::reverse(sum.ord.begin(), sum.ord.end());
    sum = ShiftRight(sum,mant.size() + rhs.mant.size());
    if (this->sign != rhs.sign){
        sum.sign = 1;
    }
    *this = sum;
    return *this;
}

Decimal& Decimal::operator/=(const Decimal& rhs){
    Decimal second = rhs;
    int f = 0;
    int shift_second = 0;
    int shift_this = 0;
    int size_ord = this->ord.size() - rhs.ord.size();
    if (this->sign != rhs.sign){
        f = 1;
        if (rhs.sign == 1){
            second.sign = 0;
        }
        else{
            this->sign = 0;
        }
    }
    if (this->sign == 1){
        this->sign = 0;
        if (rhs.sign == 1){
            second.sign = 0;
        }
    }
    if (second.ord.size() == 1){
        if (second.ord[0] == 0){
            int q = 0;
            while((second.ord[0] == 0)and (q <= 1000 )){
                ShiftLeft(second, 1);
                shift_second ++;
                q++;
            }
        }
    }
    else{
        ShiftRight(second, second.ord.size() - 1);
        shift_second += second.ord.size() - 1;
    }
    
    if (this->ord.size() == 1){
        if (this->ord[0] == 0){
            int q = 0;
            while((this->ord[0] == 0) and (q <= 1000 )){
                ShiftLeft(*this, 1);
                shift_this ++;
                q++;
            }
        }
    }
    else{
        ShiftRight(*this, this->ord.size() - 1);
        shift_this += this->ord.size() - 1;
    }

    Decimal div = Decimal();
    if (second.ord[0] > ord[0]){
        div.ord.push_back(0);
        *this  = ShiftLeft(*this, 1);
        shift_this++;

    }
    int len = 0;
    Decimal digit = Decimal("0");
    Decimal zero = Decimal("0");
    while(len <= 20 && *this != zero){
        for (int i = 9; i >= 0; i--){
            digit.ord[0] = i;
            if ((second * digit) <= *this){
                break;
            }
        }
        div.ord.push_back(digit.ord[0]);
        *this -= (second * digit);
        ShiftLeft(*this, 1);

        len++;
    }
    
    if (f == 1){
        div.sign = 1;
    }
    ShiftRight(div, shift_this - shift_second - 1 + len - size_ord);
    
    *this = div;
    return *this;

}

bool operator==(const Decimal& lhs, const Decimal& rhs){
    if ((lhs.ord.size() != rhs.ord.size()) or (lhs.sign != rhs.sign)){
        return false;
    }
    else {
        int len_mant = lhs.mant.size();
        int len_mant_rhs = rhs.mant.size();
        int len_ord = lhs.ord.size();
        int f = 0;
        while (len_mant > 0 && lhs.mant[len_mant - 1] == 0){
            len_mant--;
        }
        while (len_mant_rhs > 0 && rhs.mant[len_mant_rhs - 1] == 0){
            len_mant_rhs--;
        }
        if (len_mant != len_mant_rhs){
            return false;
        }
        for (int i = 0; i < len_mant; i++){
            if (lhs.mant[i] != rhs.mant[i]){
                f = 1;
                break;
            }
        }
        if (f == 1) {
            return false;
        }
        else{
            for (int i = 0; i < len_ord; i++){
                if (lhs.ord[i] != rhs.ord[i]){
                    f = 1;
                    break;
                }
            }
            if (f == 1){
                return false;
            }
            else {
                return true;
            }
        }
    }
}

bool operator!=(const Decimal& lhs, const Decimal& rhs){
    return (!(lhs == rhs));
}

bool operator<(const Decimal& lhs, const Decimal& rhs){
    if (lhs == rhs){
        return false;
    }
    else{
        if (lhs.sign < rhs.sign){
            return false;
        }
        else if (lhs.sign > rhs.sign){
            return true;
        }
        if (lhs.sign == 0){
            if (lhs.ord.size() < rhs.ord.size()){
                return true;
            }
            else if (lhs.ord.size() > rhs.ord.size()){
                return false;
            }
            else{
                int len_ord = lhs.ord.size();
                int f = 0;
                for (int i = 0; i < len_ord; i++){
                    if (lhs.ord[i] < rhs.ord[i]){
                       return true;
                    }
                    else if (lhs.ord[i] > rhs.ord[i]){
                        return false;
                    }
                }
                int len_mant = std::min(lhs.mant.size(), rhs.mant.size());
                for (int i = 0; i < len_mant; i++){
                    if (lhs.mant[i] < rhs.mant[i]){
                       return true;
                    }
                    else if (lhs.mant[i] > rhs.mant[i]){
                        return false;
                    }
                }
                if (lhs.mant.size() < rhs.mant.size()){
                    return true;
                }
                else {
                    return false;
                }
            }
                
        }
        else{
            if (lhs.ord.size() < rhs.ord.size()){
                return false;
            }
            else{
                int len_ord = lhs.ord.size();
                int f = 0;
                if (lhs.ord.size() > rhs.ord.size()){
                    return true;
                }
                for (int i = 0; i < len_ord; i++){
                    if (lhs.ord[i] < rhs.ord[i]){
                       return false;
                    }
                    else if (lhs.ord[i] > rhs.ord[i]){
                        return true;
                    }
                }
                int len_mant = std::min(lhs.mant.size(), rhs.mant.size());
                for (int i = 0; i < len_mant; i++){
                    if (lhs.mant[i] > rhs.mant[i]){
                       return true;
                    }
                    else if (lhs.mant[i] < rhs.mant[i]){
                        return false;
                    }
                }
                if (lhs.mant.size() > rhs.mant.size()){
                    return true;
                }
                else {
                    return false;
                }
                
            }
        }
    }
}

bool operator<=(const Decimal& lhs, const Decimal& rhs){
    return ((lhs == rhs) or (lhs < rhs));
}

bool operator>(const Decimal& lhs, const Decimal& rhs){
    return (!(lhs <= rhs));
}

bool operator>=(const Decimal& lhs, const Decimal& rhs){
    return (!(lhs < rhs));
}

std::ostream& operator<<(std::ostream& os, const Decimal& obj) {
    int len_ord = obj.ord.size();
    int len_mant = obj.mant.size();
    if(obj.sign == 1){
        std::cout << '-';
    }
    for (int i = 0; i < len_ord; i++) {
        std::cout << obj.ord[i];
    }
    if (len_mant == 0){
        return os;
    }
    std::cout << '.';
    for (int j = 0; j < len_mant; j++){
        std::cout << obj.mant[j];
    }
    return os;
}
 
std::istream& operator>>(std::istream& is, std::string obj) {
    int i = 0;
    int len = obj.size();
    Decimal number = Decimal();
    while (obj[i] == ' '){
        i++; len--;
    }
    if (obj[i] == '-'){
        len--;
        number.sign = 1;
        i++;
    }else{
        number.sign = 0;
    }
    while ((len != 0) and (obj[i] != '.') and (obj[i] != ' ') and (obj[i] != '\n')) {
        number.ord.push_back(obj[i] & 0x0F);
        i++;
        len --;
    }
    if (len == 0) {
        return is;
    }
    if((obj[i] == ' ') or (obj[i] == '\n')){
            return is;
    }
    i++;
    if (obj[i] != ' '){
        while ((len > 1) and (obj[i] != ' ') and (obj[i] != '\n')) {
            number.mant.push_back(obj[i] & 0x0F);
            i++;
            len --;
        }
    }
    return is;
}

Decimal operator""_dc(const char *s){
    return Decimal(s);
}


Decimal FunctionPi(int precision){
    Decimal pi = Decimal();
    Decimal term = Decimal();
    Decimal first = Decimal("1");
    Decimal second = Decimal("2");
    Decimal four = Decimal("4");
    Decimal five = Decimal("5");
    Decimal six = Decimal("6");
    Decimal divider = Decimal("8");
    Decimal dividerx = Decimal("1");
    Decimal sixteen = Decimal ("16");
    for (int i = 1; i <= precision; i++){
        std::string k = std::to_string(i);
        std::cout<< "this";
        Decimal idiv = Decimal(k);
        idiv *= divider;
        dividerx *= sixteen;
        std::cout << pi;
        pi += (((four / (idiv + first)) - (second / (idiv + four)) - (first / (idiv + five)) - (first / idiv + six))/ dividerx);
        
    }
    return pi;
}








