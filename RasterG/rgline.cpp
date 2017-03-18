//
//  rgline.cpp
//  RasterG
//
//  Created by bennyguo on 2017/3/14.
//  Copyright © 2017年 bennyguo. All rights reserved.
//


#include "rgline.h"


void RgLineMid(Mat &src, Point_<int> p1, Point_<int> p2, Vec3b color)
{
    int x0, x1, y0, y1;
    if(p1.x < p2.x)
        x0 = p1.x, y0 = p1.y, x1 = p2.x, y1 = p2.y;
    else
        x0 = p2.x, y0 = p2.y, x1 = p1.x, y1 = p1.y;
    int a = y0 - y1, b = x1 - x0;
    int x = x0, y = y0;
    if(b == 0)
    {
        for(int yb = min(y0, y1), ye = max(y0, y1); yb <= ye; yb++)
        {
            src.at<Vec3b>(x, yb) = color;
        }
        return;
    }
    double k = - a / (double)b;
    if(k == 0)
    {
        for(; x <= x1; x++)
            src.at<Vec3b>(x, y) = color;
    }
    else if(k > 0)
    {
        if(k <= 1)
        {
            int d = 2 * a + b;
            int d1 = 2 * a, d2 = 2 * (a + b);
            src.at<Vec3b>(x, y) = color;
            while(x < x1)
            {
                if(d < 0)
                    x++, y++, d += d2;
                else
                    x++, d += d1;
                src.at<Vec3b>(x, y) = color;
            }
        }
        else
        {
            int d = a + 2 * b;
            int d1 = 2 * b, d2 = 2 * (a + b);
            src.at<Vec3b>(x, y) = color;
            while(x < x1)
            {
                if(d < 0)
                    y++, d += d1;
                else
                    x++, y++, d += d2;
                src.at<Vec3b>(x, y) = color;
            }
        }
    }
    else
    {
        if(k >= -1)
        {
            int d = 2 * a - b;
            int d1 = 2 * a, d2 = 2 * (a - b);
            src.at<Vec3b>(x, y) = color;
            while(x < x1)
            {
                if(d < 0)
                    x++, d += d1;
                else
                    x++, y--, d += d2;
                src.at<Vec3b>(x, y) = color;
            }
        }
        else
        {
            int d = a - 2 * b;
            int d1 = - 2 * b, d2 = 2 * (a - b);
            src.at<Vec3b>(x, y) = color;
            while(x < x1)
            {
                if(d < 0)
                    x++, y--, d += d2;
                else
                    y--, d += d1;
                src.at<Vec3b>(x, y) = color;
            }
        }
    }
}


