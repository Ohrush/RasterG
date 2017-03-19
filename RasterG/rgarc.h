//
//  rgarc.h
//  RasterG
//
//  Created by bennyguo on 2017/3/14.
//  Copyright © 2017年 bennyguo. All rights reserved.
//

#ifndef rgarc_h
#define rgarc_h

#include <opencv2/core/core.hpp>
using namespace cv;

void RgCircleMid(Mat &src, Point_<int> ctr, int r, Vec3b color, bool RG_AA = false);

#endif /* rgarc_h */
