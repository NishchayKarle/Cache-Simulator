#pragma once

#include "Cpu.h"

void mxm(Cpu &mycpu, int N)
{
    int sz = 8;

    double register0,
        register1,
        register2,
        register3;

    for (int i = 0; i < N * N; i++)
    {
        mycpu.storeDouble(sz * N * N + i * sz, 1);
        mycpu.storeDouble(2 * sz * N * N + i * sz, 1);
    }

    mycpu.resetCache();
    mycpu.startLogging();
    {
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                register0 = 0;
                for (int k = 0; k < N; ++k)
                {
                    register1 = mycpu.loadDouble(sz * N * N + (i * N + k) * sz);
                    register2 = mycpu.loadDouble(2 * sz * N * N + (k * N + j) * sz);
                    register3 = mycpu.multDouble(register1, register2);
                    register0 = mycpu.addDouble(register0, register3);
                }
                mycpu.storeDouble((i * N + j) * sz, register0);
            }
        }
    }
    mycpu.stopLogging();
}