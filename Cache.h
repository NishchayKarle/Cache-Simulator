#pragma once

#include "DataBlock.h"
#include "Address.h"
#include "utils.h"
#include <string>

#define RANDOM 0
#define FIFO 1
#define LRU 2
#define INT_MAX 2147483647

class Cache
{
private:
    DataBlock **blocks;
    int blockLength = DataBlock::size / 8;

    int **valid,
        **allTags,
        **usageOrder;

    int lastUsed = 0;

    int numOffsetBits,
        numIndexBits;

    int replacementPolicy = LRU; // 0: Random, 1: FIFO, 2: LRU

    void updateUsage(int set, int block, bool newBlockAdded)
    {
        if (replacementPolicy == LRU)
            usageOrder[set][block] = lastUsed++;

        else if (newBlockAdded)
            usageOrder[set][block] = lastUsed++;
    }

    int getReplacementIndex(int set)
    {
        if (replacementPolicy == RANDOM)
            return rand() % numBlocks;

        int minVal = INT_MAX,
            minValIndex = 0;

        for (int i = 0; i < numBlocks; i++)
        {
            if (usageOrder[set][i] < minVal)
            {
                minVal = usageOrder[set][i];
                minValIndex = i;
            }
        }
        return minValIndex;
    }

public:
    static int numSets,
        numBlocks;

    Cache()
    {
        numOffsetBits = calNumBits(blockLength);
        numIndexBits = calNumBits(numSets);

        blocks = new DataBlock *[numSets];
        valid = new int *[numSets];
        allTags = new int *[numSets];
        usageOrder = new int *[numSets];

        for (int i = 0; i < numSets; i++)
        {
            blocks[i] = new DataBlock[numBlocks];
            valid[i] = new int[numBlocks];
            allTags[i] = new int[numBlocks];
            usageOrder[i] = new int[numBlocks];
        }

        for (int i = 0; i < numSets; i++)
            for (int j = 0; j < numBlocks; j++)
                valid[i][j] = 0;
    }

    ~Cache()
    {
        for (int i = 0; i < numSets; i++)
        {
            free(valid[i]);
            free(allTags[i]);
            free(usageOrder[i]);
        }

        free(blocks);
        free(valid);
        free(allTags);
        free(usageOrder);

        blocks = nullptr;
        valid = nullptr;
        allTags = nullptr;
        usageOrder = nullptr;
    }

    void setReplacementPolicy(std::string policy)
    {
        if (policy == "LRU")
            replacementPolicy = LRU;

        else if (policy == "FIFO")
            replacementPolicy = FIFO;

        else
            replacementPolicy = RANDOM;
    }

    double getDouble(Address address)
    {
        int offset = address.getOffset(address.address, numOffsetBits, numIndexBits),
            index = address.getIndex(address.address, numOffsetBits, numIndexBits),
            tag = address.getTag(address.address, numOffsetBits, numIndexBits);

        double value = -123456789;

        for (int i = 0; i < numBlocks; i++)
        {
            if (valid[index][i] == 0)
                continue;

            if (allTags[index][i] == tag)
            {
                value = blocks[index][i].data[offset];
                updateUsage(index, i, false);
            }
        }
        return value;
    }

    bool setDouble(Address address, double value)
    {
        int offset = address.getOffset(address.address, numOffsetBits, numIndexBits),
            index = address.getIndex(address.address, numOffsetBits, numIndexBits),
            tag = address.getTag(address.address, numOffsetBits, numIndexBits);

        for (int i = 0; i < numBlocks; i++)
        {
            if (valid[index][i] == 0)
                continue;

            if (allTags[index][i] == tag)
            {
                blocks[index][i].data[offset] = value;
                updateUsage(index, i, false);
                return true;
            }
        }

        return false;
    }

    DataBlock getBlock(Address address)
    {
        int index = address.getIndex(address.address, numOffsetBits, numIndexBits),
            tag = address.getTag(address.address, numOffsetBits, numIndexBits);

        for (int i = 0; i < numBlocks; i++)
        {
            if (valid[index][i] == 0)
                continue;

            if (allTags[index][i] == tag)
            {
                updateUsage(index, i, false);
                return blocks[index][i];
            }
        }
        return DataBlock(0);
    }

    void setBlock(Address address, DataBlock const block)
    {
        int index = address.getIndex(address.address, numOffsetBits, numIndexBits),
            tag = address.getTag(address.address, numOffsetBits, numIndexBits);

        for (int i = 0; i < numBlocks; i++)
        {
            if (valid[index][i] == 0)
            {
                blocks[index][i] = block;
                allTags[index][i] = tag;
                valid[index][i] = 1;
                updateUsage(index, i, true);
                return;
            }
        }

        int i = getReplacementIndex(index);
        updateUsage(index, i, true);
        blocks[index][i] = block;
        allTags[index][i] = tag;
        valid[index][i] = 1;
    }

    void print()
    {
        for (int i = 0; i < numSets; i++)
        {
            for (int j = 0; j < numBlocks; j++)
            {
                for (int k = 0; k < blockLength; k++)
                    std::cout << blocks[i][j].data[k] << " ";
                std::cout << std::endl;
            }
            std::cout << std::endl;
        }
    }

    void reset()
    {
        for (int i = 0; i < numSets; i++)
        {
            for (int j = 0; j < numBlocks; j++)
            {
                valid[i][j] = 0;
                usageOrder[i][j] = 0;
            }
        }
    }
};