#pragma GCC optimize("O3")
#pragma GCC target("sse4")

#include <iostream>
#include <algorithm>
#include <vector>

class insane
{
private:
    std::vector<short> number;
public:
    insane() = default;

    insane(const char* num)
    {
        for(int i = 0; num[i] != '\0'; i++)
            number.emplace_back(static_cast<short>(num[i] - 48));
        reverse();
    }

    insane(int num)
    {
        if(num > 9)
        {
            number.clear();
            while (num > 0)
            {
                number.emplace_back(static_cast<short>(num % 10));
                num /= 10;
            }
        }
        else
        {
            number.clear();
            number.emplace_back(static_cast<short>(num));
        }
    }
    void reverse() noexcept { std::reverse(number.begin(), number.end()); }

    const size_t GetCount() const noexcept { return number.size(); }

    friend insane operator+ (const insane& number1, const insane& number2)
    {
        insane out;
        int size = 0, a = 0, carry = 0;

        if(number1.number.size() > number2.number.size())
            size = number1.number.size();
        else
            size = number2.number.size();

        for(int i = 0; i < size; i++)
        {
            if(number1.number.size() <= i)
            {
                if(number2.number[i] + carry > 9)
                {
                    a = (number2.number[i] + carry) % 10;
                    carry = (number2.number[i] + carry) / 10;
                }
                else
                {
                    a = number2.number[i] + carry;
                    carry = 0;
                }
            }
            else if(number2.number.size() <= i)
            {
                if(number1.number[i] + carry > 9)
                {
                    a = (number1.number[i] + carry) % 10;
                    carry = (number1.number[i] + carry) / 10;
                }
                else
                {
                    a = number1.number[i] + carry;
                    carry = 0;
                }
            }
            else
            {
                if(number1.number[i] + number2.number[i] > 9)
                {
                    a = (number1.number[i] + number2.number[i]) % 10;
                    carry = (number1.number[i] + number2.number[i]) / 10;
                }
                else
                {
                    a = number1.number[i] + number2.number[i] + carry;
                    carry = 0;
                }
            }
            out.number.emplace_back(static_cast<short>(a));
        }
        if(carry != 0)
            out.number.emplace_back(static_cast<short>(carry));
        return out;
    }

    friend insane operator- (const insane& left, const insane& right)
    {
        unsigned short borrow = 0, a = 0;
        insane out, number1 = left, number2 = right;
        size_t size = number1.number.size();
        bool negative = false;
        if(number1.number.size() < number2.number.size())
        {
            number1 = right;
            number2 = left;
            negative = true;
        }
        else if(number1.number.size() == number2.number.size())
            for(int i = 0; i < number1.number.size(); i++)
                if(number1.number[i] < number2.number[i])
                {
                    number1 = right;
                    number2 = left;
                    negative = true;
                }
        for(int i = 0; i < size; i++ )
        {
            size = number1.number.size();
            if(number1.number.size() <= i)
                a = number2.number[i];
            else if(number2.number.size() <= i)
                a = number1.number[i];
            else
            {
                if(number1.number[i] >= number2.number[i])
                    a = number1.number[i] - number2.number[i];
                else
                {
                    for(int j = i + 1; j < size; j++)
                    {
                        if(number1.number[j] >= 1)
                        {
                            for(int k = j; k > 0; k--)
                            {
                                if(number1.number[size -1] - 1 == 0 && k + 1 == size)
                                    number1.number.erase(number1.number.end() - 1);
                                else
                                    number1.number[k] = static_cast<short>(number1.number[k] + 9);
                            }
                            borrow = 10;
                            break;
                        }
                    }
                    a = number1.number[i] + borrow - number2.number[i];
                    borrow = 0;
                }
            }
                out.number.emplace_back(a);
        }
        if(negative)
            out.number[size - 1] = -out.number[size - 1];
        return out;
    }

    friend bool operator== (const insane& left, const insane& right)
    {
        size_t size = left.number.size();
        if(left.number.size() > right.number.size() || left.number.size() < right.number.size())
            return false;
        else
            for(size_t i = 0; i < size; i++)
                if(left.number[i] != right.number[i])
                    return false;
        return true;
    }

    friend bool operator!= (const insane& left, const insane& right)
    {
        size_t size = left.number.size();
        if(left.number.size() > right.number.size() || left.number.size() < right.number.size())
            return true;
        else
            for(size_t i = 0; i < size; i++)
                if(left.number[i] != right.number[i])
                    return true;
        return false;
    }

    friend bool operator< (const insane& left, const insane& right)
    {
        size_t size = left.number.size();
        if(left == right)
            return false;
        else if(left.number.size() > right.number.size())
            return false;
        else if(left.number.size() == right.number.size())
            for(size_t i = size; i > 0; i--)
                if(left.number[i - 1] > right.number[i - 1])
                    return false;
        return true;
    }

    friend bool operator> (const insane& left, const insane& right)
    {
        size_t size = left.number.size();
        if(left == right)
            return false;
        else if(left.number.size() < right.number.size())
            return false;
        else if(left.number.size() == right.number.size())
            for(size_t i = size; i > 0; i--)
                if(left.number[i - 1] < right.number[i - 1])
                    return false;
        return true;
    }

    friend bool operator<= (const insane& left, const insane& right)
    {
        size_t size = left.number.size();
        if(left.number.size() > right.number.size())
            return false;
        else if(left.number.size() == right.number.size())
            for(size_t i = size; i > 0; i--)
                if(left.number[i - 1] > right.number[i - 1])
                    return false;
        return true;
    }

    friend bool operator>= (const insane& left, const insane& right)
    {
        size_t size = left.number.size();
        if(left.number.size() < right.number.size())
            return false;
        else if(left.number.size() == right.number.size())
            for(size_t i = size; i > 0; i--)
                if(left.number[i - 1] < right.number[i - 1])
                    return false;
        return true;
    }

    friend std::ostream& operator<< (std::ostream& os, insane data)
    {
        data.reverse();
        if(data.number.size() == 0)
        {
            os << 0;
            return os;
        }
        for(int i = 0; i < data.number.size(); i++)
        if(data.number[i] != -1)
            os << data.number[i];
        else
            os << -data.number[++i];
        return os;
    }

    friend std::istream& operator>> (std::istream& is, insane& number)
    {
        std::string num;
        is >> num;
        for(char c : num)
            number.number.emplace_back(static_cast<short>(c - 48));
        number.reverse();
        return is;
    }

    insane& operator= (const char* number)
    {
        for(int i = 0; number[i] != '\0'; i++)
        {
            this->number.emplace_back(static_cast<short>(number[i] - 48));
        }
        this->reverse();
        return *this;
    }

    insane& operator++()
    {
        *this = *this + 1;
        return *this;
    }

    insane& operator++(int)
    {
        *this = *this + 1;
        return *this;
    }

    insane& operator+ (int number)
    {
        insane a = number;
        *this = *this + a;
        return *this;
    }
};

int main()
{
    insane a, b, c;
    std::cin >> a >> b;
    c = a + b;
    system("cls");
    std::cout << c << std::endl;
    std::cout << "Number of digits:\nInput 1: " << a.GetCount() << "\nInput 2: " << b.GetCount() << "\nResult:  " << c.GetCount() << std::endl;
    return 0;
}