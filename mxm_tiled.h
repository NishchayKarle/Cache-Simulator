#pragma once

#include "Cpu.h"

#define MIN(a, b) ((a < b) ? a : b)

void mxmTiled(Cpu &mycpu, int N, int B)
{
    int sz = 8;

    double register0,
        register1,
        register2,
        register3,
        register4;

    for (int i = 0; i < N * N; i++)
    {
        mycpu.storeDouble(i * sz, 0);
        mycpu.storeDouble(sz * N * N + i * sz, 3);
        mycpu.storeDouble(2 * sz * N * N + i * sz, 6);
    }

    mycpu.resetCache();
    mycpu.logger.startLogging();
    {
        for (int jj = 0; jj < N; jj += B)
        {
            for (int kk = 0; kk < N; kk += B)
            {
                for (int i = 0; i < N; ++i)
                {
                    for (int j = jj; j < MIN(jj + B, N); ++j)
                    {
                        register0 = 0;
                        for (int k = kk; k < MIN(kk + B, N); ++k)
                        {
                            register1 = mycpu.loadDouble(sz * N * N + (i * N + k) * sz);
                            register2 = mycpu.loadDouble(2 * sz * N * N + (k * N + j) * sz);
                            register3 = mycpu.multDouble(register1, register2);
                            register0 = mycpu.addDouble(register0, register3);
                        }
                        register4 = mycpu.loadDouble((i * N + j) * sz);
                        register4 = mycpu.addDouble(register4, register0);
                        mycpu.storeDouble((i * N + j) * sz, register4);
                    }
                }
            }
        }
    }
    mycpu.logger.stopLogging();
}