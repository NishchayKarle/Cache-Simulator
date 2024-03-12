#pragma once

struct DataBlock
{
    static int size;

    double *data = (double *)malloc(size);
    static int length;

    DataBlock()
    {
        for (int i = 0; i < length; i++)
            data[i] = -123456789;
    }

    DataBlock(double const *dataArr)
    {
        for (int i = 0; i < length; i++)
            data[i] = dataArr[i];
    }

    DataBlock(DataBlock const &other)
    {
        for (int i = 0; i < length; i++)
            data[i] = other.data[i];
    }
};