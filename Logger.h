#pragma once

class Logger
{
private:
    int numCacheReadAccess = 0,
        numCacheReadHits = 0,
        numCacheWriteAccess = 0,
        numCacheWriteHits = 0,
        numInstructionCount = 0;

    bool log = false;

public:
    void startLogging()
    {
        log = true;
    }

    void stopLogging()
    {
        log = false;
    }

    void logCacheReadAccess()
    {
        if (log)
            numCacheReadAccess++;
    }

    void logCacheReadHits()
    {
        if (log)
            numCacheReadHits++;
    }

    void logCacheWriteAccess()
    {
        if (log)
            numCacheWriteAccess++;
    }

    void logCacheWriteHits()
    {
        if (log)
            numCacheWriteHits++;
    }

    void logInstructions()
    {
        if (log)
            numInstructionCount++;
    }

    int getReadAccessCount()
    {
        return numCacheReadAccess;
    }

    int getReadHitsCount()
    {
        return numCacheReadHits;
    }

    int getWriteAccessCount()
    {
        return numCacheWriteAccess;
    }

    int getWriteHitsCount()
    {
        return numCacheWriteHits;
    }

    int getInstructionsCount()
    {
        return numInstructionCount;
    }

    void reset()
    {
        numCacheReadAccess = 0;
        numCacheReadHits = 0;
        numCacheWriteAccess = 0;
        numCacheWriteHits = 0;
        numInstructionCount = 0;
    }

    void printResults()
    {
        int ra = getReadAccessCount(),
            rh = getReadHitsCount(),
            rm = ra - rh,
            wa = getWriteAccessCount(),
            wh = getWriteHitsCount(),
            wm = wa - wh,
            ic = getInstructionsCount();

        printf("RESULTS=====================================\n");
        printf("INSTRUCTION COUNT:             %d\n", ic);
        printf("READ ACCESS:                   %d\n", ra);
        printf("READ HITS:                     %d\n", rh);
        printf("READ MISSES:                   %d\n", rm);
        printf("READ MISS RATE:                %.3f%%\n", ((double)rm / (double)ra) * 100);
        printf("WRITE ACCESS:                  %d\n", wa);
        printf("WRITE HITS:                    %d\n", wh);
        printf("WRITE MISSES:                  %d\n", wm);
        printf("WRITE MISS RATE:               %.3f%%\n", ((double)wm / (double)wa) * 100);
    }
};