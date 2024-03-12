#pragma once

#include "Ram.h"
#include "Cache.h"
#include "Logger.h"
#include <string>

#define NOT_FOUND -123456789

class Cpu
{
private:
    Cache cache;
    Ram ram;

public:
    Logger logger;

    double loadDouble(Address address)
    {
        double value = cache.getDouble(address);
        logger.logCacheReadAccess();

        if (value == NOT_FOUND)
        {
            cache.setBlock(address, ram.getBlock(address));
            value = cache.getDouble(address);
            logger.logCacheReadAccess();
        }

        logger.logCacheReadHits();
        logger.logInstructions();

        return value;
    }

    void storeDouble(Address address, double value)
    {
        bool success = cache.setDouble(address, value);
        logger.logCacheWriteAccess();

        if (!success)
        {
            cache.setBlock(address, ram.getBlock(address));
            cache.setDouble(address, value);
            logger.logCacheWriteAccess();
        }

        logger.logCacheWriteHits();
        logger.logInstructions();

        ram.setBlock(address, cache.getBlock(address));
    }

    double addDouble(double value1, double value2)
    {
        logger.logInstructions();
        return value1 + value2;
    }

    double multDouble(double value1, double value2)
    {
        logger.logInstructions();
        return value1 * value2;
    }

    void setCacheReplacementPolicy(std::string policy)
    {
        cache.setReplacementPolicy(policy);
    }

    void startLogging()
    {
        logger.startLogging();
    }

    void stopLogging()
    {
        logger.stopLogging();
    }

    void resetCache()
    {
        cache.reset();
    }

    void printRam()
    {
        ram.print();
    }

    void printCache()
    {
        cache.print();
    }
};