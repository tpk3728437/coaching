#ifndef CALCULATOR_H
#define CALCULATOR_H

class calculator
{
public:
    calculator();

    static int plus (int r, int l);
    static int minus(int r, int l);
    int add();

private:
    int m_add;
};

#endif // CALCULATOR_H
