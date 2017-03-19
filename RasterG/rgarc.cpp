//
//  rgarc.cpp
//  RasterG
//
//  Created by bennyguo on 2017/3/14.
//  Copyright © 2017年 bennyguo. All rights reserved.
//

#include "rgarc.h"
#include "rgssaa.h"

void RgSym8Points(Mat &src, Point_<int> ctr, Point_<int> p, Vec3b color, bool RG_AA)
{
    int cx = ctr.x, cy = ctr.y;
    int dx = p.x - ctr.x, dy = p.y - ctr.y;
    if(RG_AA)
    {
        RgKernelPoint(src, cx + dx, cy + dy, color);
        RgKernelPoint(src, cx + dy, cy + dx, color);
        RgKernelPoint(src, cx - dx, cy + dy, color);
        RgKernelPoint(src, cx + dy, cy - dx, color);
        RgKernelPoint(src, cx + dx, cy - dy, color);
        RgKernelPoint(src, cx - dy, cy + dx, color);
        RgKernelPoint(src, cx - dx, cy - dy, color);
        RgKernelPoint(src, cx - dy, cy - dx, color);
    }
    else
    {
        src.at<Vec3b>(cx + dx, cy + dy) = color;
        src.at<Vec3b>(cx + dy, cy + dx) = color;
        src.at<Vec3b>(cx - dx, cy + dy) = color;
        src.at<Vec3b>(cx + dy, cy - dx) = color;
        src.at<Vec3b>(cx + dx, cy - dy) = color;
        src.at<Vec3b>(cx - dy, cy + dx) = color;
        src.at<Vec3b>(cx - dx, cy - dy) = color;
        src.at<Vec3b>(cx - dy, cy - dx) = color;
    }
}
void RgCircleMid(Mat &src, Point_<int> ctr, int r, Vec3b color, bool RG_AA)
{
    int cx = ctr.x, cy = ctr.y, dx = 0, dy = r;
    int d = 6 - (r<<2);
    RgSym8Points(src, ctr, Point(cx + dx, cy + dy), color, RG_AA);
    while(dx <= dy)
    {
        if(d < 0)
            d += (dx<<3) + 12, dx++;
        else

            d += ((dx - dy)<<3) + 20, dx++, dy--;
        RgSym8Points(src, ctr, Point(cx + dx, cy + dy), color, RG_AA);
    }
}
