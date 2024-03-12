cache-sim: cache-sim.cpp Cache.h Cpu.h DataBlock.h daxpy.h Logger.h mxm_tiled.h mxm.h Ram.h utils.h
	g++ -O3 -o cache-sim cache-sim.cpp -Wall -Werror -pedantic