#include <iostream>
#include <map>
#include <cctype>
#include <cmath>
using namespace std;

struct Quadruple
{
    string op;
    string arg1;
    string arg2;
    string result;
};

int constantFolding(int value1, char op, int value2)
{
    switch (op)
    {
    case '+':
        return value1 + value2;
    case '-':
        return value1 - value2;
    case '*':
        return value1 * value2;
    case '/':
        return value1 / value2;
    default:
        return 0;
    }
}

int isPowTwo(int n)
{
    if (n <= 0)
    {
        return -1;
    }
    else if ((n & (n - 1)) == 0)
    {
        return log2(n);
    }
    else
    {
        return -1;
    }
}

int main()
{
    map<char, int> values;

    Quadruple quadruples[] = {
        {"*", "10", "2", "t1"},
        {"+", "a", "b", "t1"},
        {"*", "t1", "2", "t2"},
        {"*", "t1", "8", "t3"},
        {"/", "t3", "2", "z"}};
    cout << "Initial three add. code" << endl;
    for (int i = 0; i < 5; ++i)
    {
        Quadruple &quad = quadruples[i];
        cout << i << "\t" << quad.op << "\t" << quad.arg1 << "\t" << quad.arg2 << "\t" << quad.result << endl;
    }
    cout << endl;

    // Perform Strength Reduction optimization
    for (int i = 0; i < 5; ++i)
    {
        Quadruple &quad = quadruples[i];
        string arg1 = quad.arg1;
        string arg2 = quad.arg2;
        bool digit_str1 = true;
        bool digit_str2 = true;
        for (auto i : arg1)
        {
            if (!isdigit(i))
            {
                digit_str1 = false;
                break;
            }
        }
        for (auto i : arg2)
        {
            if (!isdigit(i))
            {
                digit_str2 = false;
                break;
            }
        }
        if (digit_str1 && !digit_str2)
        {
            if (quad.op[0] == '*')
            {
                if (isPowTwo(stoi(arg1)) != -1)
                {
                    int power = isPowTwo(stoi(arg1));
                    quad.op = "<<";
                    quad.arg1 = to_string(power);
                }
            }
            if (quad.op[0] == '/')
            {
                if (isPowTwo(stoi(arg1)) != -1)
                {
                    int power = isPowTwo(stoi(arg1));
                    quad.op = ">>";
                    quad.arg1 = to_string(power);
                }
            }
        }
        if (!digit_str1 && digit_str2)
        {
            if (quad.op[0] == '*')
            {
                if (isPowTwo(stoi(arg2)) != -1)
                {
                    int power = isPowTwo(stoi(arg2));
                    quad.op = "<<";
                    quad.arg2 = to_string(power);
                }
            }
            if (quad.op[0] == '/')
            {
                if (isPowTwo(stoi(arg2)) != -1)
                {
                    int power = isPowTwo(stoi(arg2));
                    quad.op = ">>";
                    quad.arg2 = to_string(power);
                }
            }
        }
    }
    cout << "After strength reduction" << endl;
    for (int i = 0; i < 5; ++i)
    {
        Quadruple &quad = quadruples[i];
        cout << i << "\t" << quad.op << "\t" << quad.arg1 << "\t" << quad.arg2 << "\t" << quad.result << endl;
    }
    cout << endl;

    // Perform constant folding optimization
    for (int i = 0; i < 5; ++i)
    {
        Quadruple &quad = quadruples[i];
        string arg1 = quad.arg1;
        string arg2 = quad.arg2;
        bool digit_str1 = true;
        bool digit_str2 = true;
        for (auto i : arg1)
        {
            if (!isdigit(i))
            {
                digit_str1 = false;
                break;
            }
        }
        for (auto i : arg2)
        {
            if (!isdigit(i))
            {
                digit_str2 = false;
                break;
            }
        }
        if (digit_str1 && digit_str2)
        {
            int result = constantFolding(stoi(arg1), quad.op[0], stoi(arg2));
            quad.op = "=";
            quad.arg1 = to_string(result);
            quad.arg2 = "❌";
        }
    }
    cout << "After constant folding" << endl;
    for (int i = 0; i < 5; ++i)
    {
        Quadruple &quad = quadruples[i];
        cout << i << "\t" << quad.op << "\t" << quad.arg1 << "\t" << quad.arg2 << "\t" << quad.result << endl;
    }
    cout << endl;

    return 0;
}
