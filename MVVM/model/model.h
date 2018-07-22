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
#include "logoperation/aux_log_alg.h"


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
    bool sub2tmp();
    bool mix_tmp_main(int alpha);
    
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
    bool histogramEqualization(int *histo);
    bool colorLevel(PColorLevelData clData);
    bool watershed();
    bool isBinaryImage();
    bool isGrayImage();

    // log operation
    bool redo();
    bool undo();
    QString getRedoMsg();
    QString getUndoMsg();
    bool commit(const QString &cmd);
    bool redoEnabled();
    bool undoEnabled();
    bool clear();

    // art effect
    // 浮雕
    void _emboss();
    // 雕刻
    void _sculpture();
    // 虚幻
    void _dilate();
    // 惊悚
    void _erode();
    // 磨砂玻璃
    void _frostGlass();
    // 手稿
    void _sketch();
    // 油画
    void _oilPaint();
    // 木刻
    void _woodCut();
    // 反色
    void _inverted();
    // 回忆
    void _memory();
    // 冰冻
    void _freezing();
    // 熔铸
    void _casting();
    // 黑白漫画
    void _comicStrip();

    //锐化
    void _sharpen();
    //黑白
    void _colortoblack();
    //去雾气
    void _defog();
    //柔和
    void _soft();
    //均衡图
    void _balance();
    //怀旧
    void _nostalgia();
    //连环画
    void _BlackComic();
    //时光隧道
    void _timetuunel();
    //经典lomo
    void _classiclomo();
    // 美白
    void _whiteFace();
    // 美颜
    void _beautifyFace();
    // 粉红佳人
    void _pinkLady();

private:
    QImage originImg;
    QImage mainImg;
    QImage subImg;
    QImage tmpImg;

    Log log;
};
