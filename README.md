# Cache-Simulator
Simulate and Analyze cache hit/miss for standard benchmark tests like daxpy

### Compile and Run

- **Use makefile**
  - Compile: `make cache-sim`
  - Run example: `./cache-sim -a mxm_blocked -d 400 -n 16 -f 8`

### Capabilities Implemented

1. Variable total RAM size (Change `RAM_SIZE` constant)
2. Variable total cache size
3. Variable block size
4. Block placement strategy:
   - Direct-mapped cache
   - Fully associative cache
   - n-way associative cache for arbitrary n
5. Block replacement policy:
   - Random
   - Least Recently Used (LRU)
   - First In First Out (FIFO)
6. Write policy: write-through with write allocate
7. Algorithms:
   - Daxpy
   - Matrix-Matrix Multiplication
   - Matrix-Matrix Multiplication with blocking and variable blocking factor
8. CPU instructions for double precision floating point arithmetic:
   - `value3 = addDouble(value1, value2)`
   - `value3 = multDouble(value1, value2)`
   - `value = loadDouble(address)`
   - `storeDouble(address, value)`

### Measuring Events Implemented

- Instruction Count (adds, mults, loads, stores)
- Read Hits
- Read Misses and percentage
- Write Hits
- Write Misses and percentage

### Interface Implemented

- `-c`: The size of the cache in bytes (default: 65536)
- `-b`: The size of a data block in bytes (default: 64)
- `-n`: The n-way associativity of the cache. `-n 1` is a direct-mapped cache. (default: 2)
- `-r`: The replacement policy. Can be random, FIFO, or LRU. (default: LRU)
- `-a`: The algorithm to simulate. Can be daxpy (daxpy product), mxm (matrix-matrix multiplication), mxm_block (mxm with blocking). (default: mxm_block).
- `-d`: The dimension of the algorithmic matrix (or vector) operation. `-d 100` would result in a 100×100 matrix-matrix multiplication. (default: 480)
- `-p`: Enables printing of the resulting “solution” matrix product or daxpy vector after the emulation is complete. Elements should be read in emulation mode (e.g. using your loadDouble method) so as to assess if the emulator actually produced the correct solution.
- `-f`: The blocking factor for use when using the blocked matrix multiplication algorithm. (default: 32)

### 1.2 Correctness

- Daxpy
- Mxm 
- Mxm_blocked with Blocking Factor = 3:

### 1.3 Associativity
| Cache Associativity      | Instructions | Read Hits | Read Misses | Read Miss % | Write Hits | Write Misses | Write Miss % |
| ------------------------ | ------------ | --------- | ----------- | ----------- | ---------- | ------------ | ------------ |
| 1                        | 452736000    | 224640000 | 2615415     | 1.151%      | 3456000    | 0            | 0%           |
| 2                        | 452736000    | 224640000 | 892800      | 0.396%      | 3456000    | 0            | 0%           |
| 4                        | 452736000    | 224640000 | 892800      | 0.396%      | 3456000    | 0            | 0%           |
| 8                        | 452736000    | 224640000 | 892800      | 0.396%      | 3456000    | 0            | 0%           |
| 16                       | 452736000    | 224640000 | 892800      | 0.396%      | 3456000    | 0            | 0%           |
| 1024 (Fully Associative) | 452736000    | 224640000 | 892800      | 0.396%      | 3456000    | 0            | 0%           |


### 1.4 Memory Block Size
| Block Size (bytes) | Instructions | Read Hits | Read Misses | Read Miss % | Write Hits | Write Misses | Write Miss % |
| ------------------ | ------------ | --------- | ----------- | ----------- | ---------- | ------------ | ------------ |
| 8                  | 452736000    | 224640000 | 7142400     | 3.082%      | 3456000    | 0            | 0%           |
| 16                 | 452736000    | 224640000 | 3571200     | 1.565%      | 3456000    | 0            | 0%           |
| 32                 | 452736000    | 224640000 | 1785600     | 0.789%      | 3456000    | 0            | 0%           |
| 64                 | 452736000    | 224640000 | 892800      | 0.396%      | 3456000    | 0            | 0%           |
| 128                | 452736000    | 224640000 | 446400      | 0.198%      | 3456000    | 0            | 0%           |
| 256                | 452736000    | 224640000 | 223200      | 0.099%      | 3456000    | 0            | 0%           |
| 512                | 452736000    | 224640000 | 2245535     | 0.990%      | 3456000    | 0            | 0%           |
| 1024               | 452736000    | 224640000 | 6291644     | 2.724%      | 3456000    | 0            | 0%           |


### 1.5 Total Cache Size
| Cache Size (bytes) | Instructions | Read Hits  | Read Misses | Read Miss % | Write Hits | Write Misses | Write Miss % |
|--------------------|--------------|------------|-------------|-------------|------------|--------------|--------------|
| 4096               | 452736000    | 224640000  | 117961680   | 34.431%     | 3456000    | 0            | 0%           |
| 8192               | 452736000    | 224640000  | 20003422    | 8.177%      | 3456000    | 0            | 0%           |
| 16384              | 452736000    | 224640000  | 1493505     | 0.660%      | 3456000    | 0            | 0%           |
| 32768              | 452736000    | 224640000  | 892800      | 0.396%      | 3456000    | 0            | 0%           |
| 65536              | 452736000    | 224640000  | 892800      | 0.396%      | 3456000    | 0            | 0%           |
| 131072             | 452736000    | 224640000  | 890768      | 0.395%      | 3456000    | 0            | 0%           |
| 262144             | 452736000    | 224640000  | 604792      | 0.269%      | 3456000    | 0            | 0%           |
| 524288             | 452736000    | 224640000  | 512108      | 0.227%      | 3456000    | 0            | 0%           |


### 1.6 Replacement Policy

| Replacement Policy | Instructions | Read Hits | Read Misses | Read Miss % | Write Hits | Write Misses | Write Miss % |
| ------------------ | ------------ | --------- | ----------- | ----------- | ---------- | ------------ | ------------ |
| Random             | 452736000    | 224640000 | 1105703     | 0.490%      | 3456000    | 0            | 0%           |
| FIFO               | 452736000    | 224640000 | 994864      | 0.441%      | 3456000    | 0            | 0%           |
| LRU                | 452736000    | 224640000 | 892800      | 0.396%      | 3456000    | 0            | 0%           |
