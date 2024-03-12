#pragma once

#include "DataBlock.h"
#include "Address.h"
#include <assert.h>

class Ram
{
private:
    int numBlocks = size / DataBlock::size;
    int blockLength = DataBlock::size / 8;
    DataBlock *data = (DataBlock *)malloc(size);

    int getRamOffset(Address address)
    {
        return address.address / blockLength;
    }

public:
    static int size;

    Ram()
    {
        for (int i = 0; i < numBlocks; i++)
        {
            DataBlock block;
            data[i] = block;
        }
    };

    Ram(double const *dataArr, int length)
    {
        for (int i = 0; i < numBlocks; i++)
        {
            DataBlock block = dataArr + i * blockLength;
            data[i] = block;
        }
    }

    ~Ram()
    {
        free(data);
    }

    DataBlock getBlock(Address address)
    {
        assert(getRamOffset(address) < numBlocks);
        return data[getRamOffset(address)];
    }

    void setBlock(Address address, DataBlock block)
    {
        assert(getRamOffset(address) < numBlocks);
        data[getRamOffset(address)] = block;
    }

    void print()
    {
        for (int i = 0; i < numBlocks; i++)
        {
            for (int j = 0; j < blockLength; j++)
                std::cout << data[i].data[j] << " ";
            std::cout << std::endl;
        }
    }
};