#include "calculator.h"

calculator::calculator() : m_add(0)
{
}

int calculator::plus (int r, int l)
{
    return r+l;
}

int calculator::minus(int r, int l)
{
    return r-l;
}

int calculator::add() 
{
    return m_add++;
}
