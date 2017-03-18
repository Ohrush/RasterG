//
//  rgssaa.cpp
//  RasterG
//
//  Created by bennyguo on 2017/3/17.
//  Copyright © 2017年 bennyguo. All rights reserved.
//

#include "rgssaa.h"


void RgKernelFilter(Mat &src)
{
    Mat copy = src.clone();
//    int c = 3;
//    int filter[9] = {1, 2, 1, 2, 4, 2, 1, 2, 1};
    int c = 7;
    int filter[49] = {1, 2, 3, 4, 3, 2, 1,
        2, 4, 6, 8, 6, 4, 2,
        3, 6, 9, 12, 9, 6, 3,
        4, 8, 12, 16, 12, 8, 4,
        3, 6, 9, 12, 9, 6, 3,
        2, 4, 6, 8, 6, 4, 2,
        1, 2, 3, 4, 3, 2, 1};
    int rows = src.rows, cols = src.cols;
    for(int i = 0; i < rows; i ++)
        for(int j = 0; j < cols; j ++)
        {
            int weight = 0, cnt = 0;
            int sumb = 0, sumg = 0, sumr = 0;
            for(int dr = c / 2, ii = - dr; ii <= dr; ii ++)
                for(int dc = c / 2, jj = - dc; jj <= dc; jj ++)
                {
                    int x = i + ii, y = j + jj;
                    if(x >= 0 && x < rows && y >= 0 && y < cols)
                    {
                        Vec3b oldColor = copy.at<Vec3b>(x, y);
                        sumb += oldColor[0] * filter[cnt];
                        sumg += oldColor[1] * filter[cnt];
                        sumr += oldColor[2] * filter[cnt];
                        weight += filter[cnt];
                    }
                    cnt++;
                }
            Vec3b newColor = Vec3b(sumb / weight, sumg / weight, sumr / weight);
            src.at<Vec3b>(i, j) = newColor;
        }
}


void RgShrink(Mat& lg, Mat& sm)
{
    int c = 3;
    int filter[9] = {1, 2, 1, 2, 4, 2, 1, 2, 1};
//    int c = 7;
//    int filter[49] = {1, 2, 3, 4, 3, 2, 1,
//        2, 4, 6, 8, 6, 4, 2,
//        3, 6, 9, 12, 9, 6, 3,
//        4, 8, 12, 16, 12, 8, 4,
//        3, 6, 9, 12, 9, 6, 3,
//        2, 4, 6, 8, 6, 4, 2,
//        1, 2, 3, 4, 3, 2, 1};
    int rowsl = lg.rows, colsl = lg.cols;
    int rowss = rowsl / c, colss = colsl / c;
    int weight = 0;
    for(int i = 0, len = c * c; i < len; i ++)
        weight += filter[i];
    for(int i = 0; i < rowss; i ++)
        for(int j = 0; j < colss; j ++)
        {
            int sumb = 0, sumg = 0, sumr = 0;
            int cnt = 0;
            for(int is = i * c, ie = is + c; is < ie; is ++)
                for(int js = j * c, je = js + c; js < je; js ++)
                {
                    Vec3b oldColor = lg.at<Vec3b>(is, js);
                    sumb += oldColor[0] * filter[cnt];
                    sumg += oldColor[1] * filter[cnt];
                    sumr += oldColor[2] * filter[cnt];
                    cnt ++;
                }
            Vec3b newColor = Vec3b(sumb / weight, sumg / weight, sumr / weight);
            sm.at<Vec3b>(i, j) = newColor;
        }
}

