#pragma once

struct Address
{
    int address;

    Address(int _address) : address(_address / 8){};

    Address(Address const &other)
    {
        address = other.address;
    }

    int getTag(int address, int numOffsetBits, int numIndexBits)
    {
        return (address >> (numOffsetBits + numIndexBits));
    }

    int getIndex(int address, int numOffsetBits, int numIndexBits)
    {
        return (address >> numOffsetBits) & ((1 << (numIndexBits)) - 1);
    }

    int getOffset(int address, int numOffsetBits, int numIndexBits)
    {
        return address & ((1 << (numOffsetBits)) - 1);
    }
};
