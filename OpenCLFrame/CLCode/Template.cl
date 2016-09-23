#include "contracts\Contracts.h"
 

__kernel void Add(__global int* pA, __global int* pB, __global int* pC)
{
	//get global id (dymension) 
    const int x     = get_global_id(0);
    const int y     = get_global_id(1);
    const int z     = get_global_id(2);

    const int width = get_global_size(0);

    const int id = y * width + x;
	struct ChessBoard bla;
    pC[id] += pA[id] + pB[id];
}

__kernel void Generate(__global struct ChessBoard* board,)
{
 boa
}




