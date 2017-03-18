//
//  rgfill.h
//  RasterG
//
//  Created by bennyguo on 2017/3/16.
//  Copyright © 2017年 bennyguo. All rights reserved.
//

#ifndef rgfill_h
#define rgfill_h

#include <opencv2/core/core.hpp>
using namespace cv;

void RgScanLineFill4(Mat &src, Point inside, Vec3b oldColor, Vec3b newColor);

#endif /* rgfill_h */
