//
//  rgarc.cpp
//  RasterG
//
//  Created by bennyguo on 2017/3/14.
//  Copyright © 2017年 bennyguo. All rights reserved.
//

#include "rgarc.h"


void RgSym8Points(Mat &src, Point_<int> ctr, Point_<int> p, Vec3b color)
{
    int cx = ctr.x, cy = ctr.y;
    int dx = p.x - ctr.x, dy = p.y - ctr.y;
    src.at<Vec3b>(cx + dx, cy + dy) = color;
    src.at<Vec3b>(cx + dy, cy + dx) = color;
    src.at<Vec3b>(cx - dx, cy + dy) = color;
    src.at<Vec3b>(cx + dy, cy - dx) = color;
    src.at<Vec3b>(cx + dx, cy - dy) = color;
    src.at<Vec3b>(cx - dy, cy + dx) = color;
    src.at<Vec3b>(cx - dx, cy - dy) = color;
    src.at<Vec3b>(cx - dy, cy - dx) = color;
}
void RgCircleMid(Mat &src, Point_<int> ctr, int r, Vec3b color)
{
    int cx = ctr.x, cy = ctr.y, dx = 0, dy = r;
    int d = 6 - (r<<2);
    RgSym8Points(src, ctr, Point(cx + dx, cy + dy), color);
    while(dx <= dy)
    {
        if(d < 0)
            d += (dx<<3) + 12, dx++;
        else

            d += ((dx - dy)<<3) + 20, dx++, dy--;
        RgSym8Points(src, ctr, Point(cx + dx, cy + dy), color);
    }
}
