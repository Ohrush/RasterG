//
//  rgfill.cpp
//  RasterG
//
//  Created by bennyguo on 2017/3/16.
//  Copyright © 2017年 bennyguo. All rights reserved.
//

#include "rgfill.h"
#include <vector>


struct RgSeed {
    int x;
    int y;
};


void RgScanLineFill4(Mat &src, Point inside, Vec3b oldColor, Vec3b newColor)
{
    int rows = src.rows, cols = src.cols;
    int x = inside.x, y = inside.y;
    if(src.at<Vec3b>(x, y) != oldColor)
        return;
    int xl, xr;
    bool spanNeedFill;
    Vector<RgSeed> seedStack;
    RgSeed seed;
    seed.x = x, seed.y = y;
    seedStack.push_back(seed);
    while(!seedStack.empty())
    {
        seed = seedStack.back();
        seedStack.pop_back();
        y = seed.y;
        
        x = seed.x;
        while(x < rows && src.at<Vec3b>(x, y) == oldColor)
        {
            src.at<Vec3b>(x, y) = newColor;
            x++;
        }
        xr = x - 1;
        
        x = seed.x - 1;
        while(x >= 0 && src.at<Vec3b>(x, y) == oldColor)
        {
            src.at<Vec3b>(x, y) = newColor;
            x--;
        }
        xl = x + 1;
        
        x = xl, y = y + 1;
        while(x <= xr)
        {
            spanNeedFill = false;
            while(x < rows && src.at<Vec3b>(x, y) == oldColor)
            {
                spanNeedFill = true;
                x++;
            }
            if(spanNeedFill)
            {
                seed.x = x - 1, seed.y = y;
                seedStack.push_back(seed);
                spanNeedFill = false;
            }
            while(x < rows && src.at<Vec3b>(x, y) != oldColor && x <= xr)
                x++;
        }
        
        x = xl, y = y - 2;
        while(x <= xr)
        {
            spanNeedFill = false;
            while(x < rows && src.at<Vec3b>(x, y) == oldColor)
            {
                spanNeedFill = true;
                x++;
            }
            if(spanNeedFill)
            {
                seed.x = x - 1, seed.y = y;
                seedStack.push_back(seed);
                spanNeedFill = false;
            }
            while(x < rows && src.at<Vec3b>(x, y) != oldColor && x <= xr)
                x++;
        }
        
    }
}
