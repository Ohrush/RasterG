//
//  rgline.h
//  RasterG
//
//  Created by bennyguo on 2017/3/14.
//  Copyright © 2017年 bennyguo. All rights reserved.
//

#ifndef rgline_h
#define rgline_h

#include <opencv2/core/core.hpp>
using namespace cv;

void RgLineMid(Mat &src, Point_<int> start, Point_<int> end, Vec3b color);

#endif /* rgline_h */
