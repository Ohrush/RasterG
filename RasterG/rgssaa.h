//
//  rgssaa.h
//  RasterG
//
//  Created by bennyguo on 2017/3/17.
//  Copyright © 2017年 bennyguo. All rights reserved.
//

#ifndef rgssaa_h
#define rgssaa_h

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;

void RgBlur(Mat &src);
void RgShrink(Mat& lg, Mat& sm);
void RgKernelPoint(Mat& src, int i, int j, Vec3b color);

#endif /* rgssaa_h */
