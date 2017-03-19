//
//  main.cpp
//  RasterG
//
//  Created by bennyguo on 2017/3/14.
//  Copyright © 2017年 bennyguo. All rights reserved.
//

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "rgline.h"
#include "rgarc.h"
#include "rgfill.h"
#include "rgssaa.h"
#include <iostream>
#include <fstream>
using namespace cv;
using namespace std;

struct MyLine
{
    Vec3b color;
    Point start;
    Point end;
};

struct MyCircle
{
    Vec3b color;
    Point center;
    int r;
};

struct MyArea
{
    Point inside;
    Vec3b color;
};

void readConfig(const char *file, int &width, int &height, Vec3b& bg)
{
    fstream fs;
    fs.open(file);
    int b, g, r;
    fs >> width >> height
    >> b >> g >> r;
    bg = Vec3b(b, g, r);
    fs.close();
}

void readLines(const char *file, vector<MyLine> &lines)
{
    fstream fs;
    fs.open(file);
    int cnt;
    fs >> cnt;
    for(int i = 0; i < cnt; i ++)
    {
        MyLine line;
        int b, g, r;
        fs >> line.start.x >> line.start.y
        >> line.end.x >> line.end.y
        >> b >> g >> r;
        line.color = Vec3b(b, g, r);
        lines.push_back(line);
    }
    fs.close();
}

void readCircles(const char *file, vector<MyCircle> &circles)
{
    fstream fs;
    fs.open(file);
    int cnt;
    fs >> cnt;
    for(int i = 0; i < cnt; i ++)
    {
        MyCircle circle;
        int b, g, r;
        fs >> circle.center.x >> circle.center.y >> circle.r
        >> b >> g >> r;
        circle.color = Vec3b(b, g, r);
        circles.push_back(circle);
    }
    fs.close();
}

void readAreas(const char *file, vector<MyArea> &areas)
{
    fstream fs;
    fs.open(file);
    int cnt;
    fs >> cnt;
    for(int i = 0; i < cnt; i ++)
    {
        MyArea area;
        int b, g, r;
        fs >> area.inside.x >> area.inside.y
        >> b >> g >> r;
        area.color = Vec3b(b, g, r);
        areas.push_back(area);
    }
    fs.close();
}

void drawLines(Mat &src, vector<MyLine> &lines, int c = 1, bool RG_AA = false)
{
    for(int i = 0, len = lines.size(); i < len; i ++)
    {
        MyLine line = lines[i];
        RgLineMid(src, line.start * c, line.end * c, line.color, RG_AA);
    }
}

void drawCircles(Mat &src, vector<MyCircle> &circles, int c = 1, bool RG_AA = false)
{
    for(int i = 0, len = circles.size(); i < len; i ++)
    {
        MyCircle circle = circles[i];
        RgCircleMid(src, circle.center * c, circle.r * c, circle.color, RG_AA);
    }
}

void drawAreas(Mat &src, Vec3b bg, vector<MyArea> &areas, int c = 1)
{
    for(int i = 0, len = areas.size(); i < len; i ++)
    {
        MyArea area = areas[i];
        RgScanLineFill4(src, area.inside * c, bg, area.color);
    }
}

int main(int argc, const char * argv[]) {
    
    
    
    int width, height, c = 3;
    Vec3b bgColor;
    vector<MyLine> lines;
    vector<MyCircle> circles;
    vector<MyArea> areas;
    readConfig("./config", width, height, bgColor);
    int width_lg = width * c, height_lg = height * c;
    readLines("./lines", lines);
    readCircles("./circles", circles);
    readAreas("./areas", areas);
    Mat lg(width_lg, height_lg, CV_8UC3, Scalar(bgColor[0], bgColor[1], bgColor[2]));
    Mat output(width, height, CV_8UC3, Scalar(bgColor[0], bgColor[1], bgColor[2]));
    Mat aaoutput(width, height, CV_8UC3, Scalar(bgColor[0], bgColor[1], bgColor[2]));
    
    drawLines(output, lines, 1, false);
    drawCircles(output, circles, 1, false);
    drawAreas(output, bgColor, areas, 1);
    imwrite("./output_original.png", output);
    
    
    double t=(double)cvGetTickCount();
    drawLines(lg, lines, c, true);
    t=((double)cvGetTickCount() - t) / (cvGetTickFrequency() * 1000);
    cout << "Draw lines: " << t << " ms" << endl;
    
    t = (double)cvGetTickCount();
    drawCircles(lg, circles, c, true);
    t=((double)cvGetTickCount() - t) / (cvGetTickFrequency() * 1000);
    cout << "Draw circles: " << t << " ms" << endl;
    
    t = (double)cvGetTickCount();
    drawAreas(lg, bgColor, areas, c);
    t=((double)cvGetTickCount() - t) / (cvGetTickFrequency() * 1000);
    cout << "Fill areas: " << t << " ms" << endl;
    
    t = (double)cvGetTickCount();
    RgBlur(lg);
    t=((double)cvGetTickCount() - t) / (cvGetTickFrequency() * 1000);
    cout << "Blur " << t << " ms" << endl;

    t = (double)cvGetTickCount();
    RgShrink(lg, aaoutput);
    t=((double)cvGetTickCount() - t) / (cvGetTickFrequency() * 1000);
    cout << "Shrink: " << t << " ms" << endl;
    
    imwrite("./output_aa.png", aaoutput);
    
    
    return 0;
}
