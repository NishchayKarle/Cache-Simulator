#include <iostream>
#include <string.h>
#include "Cpu.h"
#include "mxm.h"
#include "daxpy.h"
#include "mxm_tiled.h"

#define RAM_SIZE 8388608

#define RANDOM 0
#define FIFO 1
#define LRU 2

#define DAXPY 0
#define MXM 1
#define MXM_TILED 2

using namespace std;

int DataBlock::size;
int DataBlock::length;
int Ram::size = RAM_SIZE;
int Cache::numSets;
int Cache::numBlocks;

int main(int argc, char **argv)
{
    int cacheSize = 65536,
        dataBlockSize = 64,
        setAssociativity = 2,
        matrixDimension = 480,
        blockingFactor = 32;

    string replacementPolicy = "LRU",
           algorithm = "BLOCKED MXM";

    bool printResult = false;

    for (int i = 1; i < argc; i++)
    {
        if (strcmp("-c", argv[i]) == 0)
            cacheSize = atoi(argv[++i]);

        else if (strcmp("-b", argv[i]) == 0)
            dataBlockSize = atoi(argv[++i]);

        else if (strcmp("-n", argv[i]) == 0)
            setAssociativity = atoi(argv[++i]);

        else if (strcmp("-r", argv[i]) == 0)
        {
            if (strcmp("FIFO", argv[i + 1]) == 0)
                replacementPolicy = "FIFO";

            else if (strcmp("LRU", argv[i + 1]) == 0)
                replacementPolicy = "LRU";

            else
                replacementPolicy = "RANDOM";

            i++;
        }

        else if (strcmp("-a", argv[i]) == 0)
        {
            if (strcmp("daxpy", argv[i + 1]) == 0)
                algorithm = "DAXPY";

            else if (strcmp("mxm", argv[i + 1]) == 0)
                algorithm = "MXM";
            i++;
        }

        else if (strcmp("-d", argv[i]) == 0)
            matrixDimension = atoi(argv[++i]);

        else if (strcmp("-f", argv[i]) == 0)
            blockingFactor = atoi(argv[++i]);

        else if (strcmp("-p", argv[i]) == 0)
            printResult = true;

        else
        {
            cout << "INVALID ARGUMENTS" << endl;
            return EXIT_FAILURE;
        }
    }

    DataBlock::size = dataBlockSize;
    DataBlock::length = DataBlock::size / 8;
    Cache::numBlocks = setAssociativity;
    Cache::numSets = cacheSize / (DataBlock::size * Cache::numBlocks);

    srand(time(nullptr));
    Cpu cpu;
    cpu.setCacheReplacementPolicy(replacementPolicy);

    if (algorithm == "DAXPY")
        daxpy(cpu, matrixDimension);

    else if (algorithm == "MXM")
        mxm(cpu, matrixDimension);

    else
        mxmTiled(cpu, matrixDimension, blockingFactor);

    if (printResult)
    {
        cout << "INPUTS======================================" << endl;
        cout << "RAM SIZE:                      " << RAM_SIZE << " bytes" << endl;
        cout << "CACHE SIZE:                    " << cacheSize << " bytes" << endl;
        cout << "BLOCK SIZE:                    " << dataBlockSize << " bytes" << endl;
        cout << "TOTAL BLOCKS IN CACHE:         " << Cache::numSets * Cache::numBlocks << endl;
        cout << "ASSOCIATIVITY:                 " << setAssociativity << endl;
        cout << "NUMBER OF SETS:                " << Cache::numSets << endl;
        cout << "REPLACEMENT POLICY:            " << replacementPolicy << endl;
        cout << "ALGORITHM:                     " << algorithm << endl;
        if (algorithm == "BLOCKED MXM")
            cout << "MXM BLOCKING FACTOR:           " << blockingFactor << endl;
        cout << "MATRIX OR VECTOR DIMENSION:    " << matrixDimension << endl;
        cpu.logger.printResults();
    }

    return EXIT_SUCCESS;
}