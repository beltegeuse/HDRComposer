#include "StdAfx.h"

#include "tpImageThreshold.hpp"
#include <iostream>

bool tpImageThreshold::threshold(const tpImage<unsigned char> &I,
								unsigned char threshold,
								tpImage<unsigned char> &O)
{
	int w = I.getWidth();
	int h = I.getHeight();

	if(O.getWidth() != w || O.getHeight() != h)
	{
		std::cout << "[INFO] [Threshold] Resize ... " << std::endl;
		O.resize(h,w);
	}

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			//std::cout << x << "x" << y << std::endl;

			if(I[x][y] < threshold)
			{
				O[x][y] = 0;
			}
			else
			{
				O[x][y] = 255;
			}
		}
	}
	return true;
}



