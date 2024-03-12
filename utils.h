#pragma once

int calNumBits(int n)
{
    int bits = 0;
    n--;
    while (n && ++bits)
        n /= 2;

    return bits;
}