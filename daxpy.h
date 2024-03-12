#pragma once

#include "Cpu.h"

void daxpy(Cpu &mycpu, int N)
{
    int sz = 8;

    // int *a = new int[n],
    //     *b = new int[n],
    //     *c = new int[n];

    // for (int i = 0; i < n; i++)
    // {
    //     a[i] = i * sz;
    //     b[i] = sz * n + i * sz;
    //     c[i] = 2 * sz * n + i * sz;
    // }

    for (int i = 0; i < N; i++)
    {
        mycpu.storeDouble(i * sz, i);
        mycpu.storeDouble(sz * N + i * sz, 2 * i);
        mycpu.storeDouble(2 * sz * N + i * sz, 0);
    }

    double register0 = 3,
           register1,
           register2,
           register3,
           register4;

    mycpu.resetCache();
    mycpu.startLogging();
    {
        for (int i = 0; i < N; i++)
        {
            register1 = mycpu.loadDouble(i * sz); // register1 = mycpu.loadDouble(a[i]);
            register2 = mycpu.multDouble(register0, register1);
            register3 = mycpu.loadDouble(sz * N + i * sz); // register3 = mycpu.loadDouble(b[i]);
            register4 = mycpu.addDouble(register2, register3);
            mycpu.storeDouble(2 * sz * N + i * sz, register4); // mycpu.storeDouble(c[i], register4);
        }
    }
    mycpu.stopLogging();
}
