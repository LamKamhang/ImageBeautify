/*
 * File: model.h
 * Version: 1.0
 * Author: kk
 * Created Date: Wed Jul 18 19:19:59 DST 2018
 * -------------------------------------------
 * 构建Model类
 */
#pragma once

#include <string>
#include "../common/etlbase.h"
#include "imageoperation/aux_image_alg.h"


class Model
    : public Proxy_PropertyNotification<Model>
{
public:
    Model(){}
    const QImage &getMain();
    const QImage &getSub();

    // basic methods.
    bool open_file(const QString &path);
    bool open_sub_file(const QString &path);
    bool save_file(const QString &path);
    bool sub2main();
    bool origin2main();
    bool main2sub();
    
    // image operation.
    bool imageAdd(double param1, double param2);
    bool imageSubtract(double param1, double param2);
    bool imageMultiply();
    bool getSingleChannel(ChannelType channel);
    bool grayScale();
    bool adjustHue(QVector<int> hueValues);
    bool adjustSaturation(int saturation);
    bool adjustLightness(int lightness);
    bool otsu();
    bool dualThreshold(int thresh1, int thresh2);
    bool nearnestInterpolation(int scale, int rotation);
    bool BilinearInterpolation(int scale, int rotation);
    bool meanFilter(int col, int row, int x, int y);
    bool medianFilter(int col, int row, int x, int y);
    bool gaussianFilter(int col, int row, int x, int y, double sigma);
    bool sobelEdgeDetection(int threshold);
    bool laplacianEdgeDetection(int threshold);
    bool cannyEdgeDetection(int lo, int hi);
    bool houghLineDetect();
    bool houghCircleDetect(int lo, int hi);
    bool clip(int startX, int endX, int startY, int endY);
    bool dilation(int size, int x, int y, int *array);
    bool erosion(int size, int x, int y, int *array);
    bool opening(int size, int x, int y, int *array);
    bool closing(int size, int x, int y, int *array);
    bool thinning();
    bool thicking();
    bool distanceTransform();
    bool skeletonization(int size, int x, int y, int *array);
    bool skeletionReconstruct(int size, int x, int y, int *array);
    bool binaryReconstruction(int size, int x, int y, int *array);
    bool obr(int size, int x, int y, int *array);
    bool cbr(int size, int x, int y, int *array);
    bool linearContrastAdjust(int x1, int y1, int x2, int y2);
    bool pieceLinContrastAdjust(int x1, int y1, int x2, int y2);
    bool logContrastAdjust(double a, double b);
    bool expContrastAdjust(double a, double b);
    bool getHistogram(int *histo);
    bool histogramEqualization(int *histo);
    bool colorLevel(PColorLevelData clData);
    bool watershed();
    bool isBinaryImage();
    bool isGrayImage();

private:
    QImage originImg;
    QImage mainImg;
    QImage subImg;
    QImage tmpImg;
};
