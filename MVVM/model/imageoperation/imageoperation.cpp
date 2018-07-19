#include "aux_image_alg.h"
#include "../model.h"
#include "../../common/util.h"

bool Model::imageAdd(double param1, double param2)
{
    if (mainImg.height != subImg.height || mainImg.width != subImg.width)
    {
        return false;
    }
    else
    {
        QImage src1 = Tools::Mat2QImage(mainImg);
        QImage src2 = Tools::Mat2QImage(subImg);
        QImage dst = ImageOperations::imageAdd(src1, src2, param1, param2);
        mainImg = Tools::QImage2Mat(dst);
        Fire_OnPropertyChanged(MAIN_IMAGE);
        return true;
    }
}

bool Model::imageSubtract(double param1, double param2)
{
    if (mainImg.height != subImg.height || mainImg.width != subImg.width)
    {
        return false;
    }
    else
    {
        QImage src1 = Tools::Mat2QImage(mainImg);
        QImage src2 = Tools::Mat2QImage(subImg);
        QImage dst = ImageOperations::imageSubtract(src1, src2, param1, param2);
        mainImg = Tools::QImage2Mat(dst);
        Fire_OnPropertyChanged(MAIN_IMAGE);
        return true;
    }
}

bool Model::imageMultiply()
{
    if (mainImg.height != subImg.height || mainImg.width != subImg.width)
    {
        return false;
    }
    else
    {
        QImage src1 = Tools::Mat2QImage(mainImg);
        QImage src2 = Tools::Mat2QImage(subImg);
        QImage dst = ImageOperations::imageMultiply(src1, src2);
        mainImg = Tools::QImage2Mat(dst);
        Fire_OnPropertyChanged(MAIN_IMAGE);
        return true;
    }
}

bool Model::getSingleChannel(ChannelType channel)
{
    QImage src = Tools::Mat2QImage(mainImg);
    QImage dst = ImageOperations::getSingleChannel(src, channel);
    mainImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::grayScale()
{
    QImage src = Tools::Mat2QImage(mainImg);
    QImage dst = ImageOperations::grayScale(src);
    mainImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::adjustHue(QVector<int> hueValues)
{
    QImage src = Tools::Mat2QImage(subImg);
    QImage dst = ImageOperations::adjustHue(src, src, hueValues);
    subImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(SUB_IMAGE);
    return true;
}

bool Model::adjustSaturation(int saturation)
{
    QImage src = Tools::Mat2QImage(subImg);
    QImage dst = ImageOperations::adjustSaturation(src, src, saturation);
    subImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(SUB_IMAGE);
    return true;
}

bool Model::adjustLightness(int lightness)
{
    QImage src = Tools::Mat2QImage(subImg);
    QImage dst = ImageOperations::adjustLightness(src, src, lightness);
    subImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(SUB_IMAGE);
    return true;
}

bool Model::otsu()
{
    QImage src = Tools::Mat2QImage(mainImg);
    QImage dst = ImageOperations::otsu(src);
    mainImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::dualThreshold(int thresh1, int thresh2)
{
    QImage src = Tools::Mat2QImage(subImg);
    QImage dst = ImageOperations::dualThreshold(src, thresh1, thresh2);
    subImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(SUB_IMAGE);
    return true;
}

bool Model::nearnestInterpolation(int scale, int rotation)
{
    QImage src = Tools::Mat2QImage(mainImg);
    QImage dst = ImageOperations::nearnestInterpolation(src, scale, rotation);
    mainImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::BilinearInterpolation(int scale, int rotation)
{
    QImage src = Tools::Mat2QImage(mainImg);
    QImage dst = ImageOperations::BilinearInterpolation(src, scale, rotation);
    mainImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::meanFilter(int col, int row, int x, int y)
{
    QImage src = Tools::Mat2QImage(mainImg);
    QImage dst = ImageOperations::meanFilter(src, col, row, x, y);
    mainImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::medianFilter(int col, int row, int x, int y)
{
    QImage src = Tools::Mat2QImage(mainImg);
    QImage dst = ImageOperations::medianFilter(src, col, row, x, y);
    mainImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::gaussianFilter(int col, int row, int x, int y, double sigma)
{
    QImage src = Tools::Mat2QImage(mainImg);
    QImage dst = ImageOperations::gaussianFilter(src, col, row, x, y, sigma);
    mainImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::sobelEdgeDetection(int threshold)
{
    QImage src = Tools::Mat2QImage(mainImg);
    QImage dst = ImageOperations::sobelEdgeDetection(src, threshold);
    mainImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::laplacianEdgeDetection(int threshold)
{
    QImage src = Tools::Mat2QImage(mainImg);
    QImage dst = ImageOperations::laplacianEdgeDetection(src, threshold);
    mainImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::cannyEdgeDetection(int lo, int hi)
{
    QImage src = Tools::Mat2QImage(mainImg);
    QImage dst = ImageOperations::cannyEdgeDetection(src, lo, hi);
    mainImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::houghLineDetect()
{
    QImage src = Tools::Mat2QImage(mainImg);
    QImage dst = ImageOperations::houghLineDetect(src);
    mainImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::houghCircleDetect(int lo, int hi)
{
    QImage src = Tools::Mat2QImage(mainImg);
    QImage dst = ImageOperations::houghCircleDetect(src, lo, hi);
    mainImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::clip(, int startX, int endX, int startY, int endY)
{
    QImage src = Tools::Mat2QImage(mainImg);
    QImage dst = ImageOperations::clip(src, startX, endX, startY, endY);
    mainImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::dilation(int size, int x, int y, int *array)
{
    QImage src = Tools::Mat2QImage(mainImg);
    if (!isBinaryImage(src))
    {
        return false;
    }
    QImage dst = ImageOperations::dilation(src, size, x, y, array);
    mainImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::erosion(int size, int x, int y, int *array)
{
    QImage src = Tools::Mat2QImage(mainImg);
    if (!isBinaryImage(src))
    {
        return false;
    }
    QImage dst = ImageOperations::erosion(src, size, x, y, array);
    mainImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::opening(int size, int x, int y, int *array)
{
    QImage src = Tools::Mat2QImage(mainImg);
    if (!isBinaryImage(src))
    {
        return false;
    }
    QImage dst = ImageOperations::opening(src, size, x, y, array);
    mainImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::closing(int size, int x, int y, int *array)
{
    QImage src = Tools::Mat2QImage(mainImg);
    if (!isBinaryImage(src))
    {
        return false;
    }
    QImage dst = ImageOperations::closing(src, size, x, y, array);
    mainImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::thinning()
{
    QImage src = Tools::Mat2QImage(mainImg);
    if (!isBinaryImage(src))
    {
        return false;
    }
    QImage dst = ImageOperations::thinning(src);
    mainImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::thicking()
{
    QImage src = Tools::Mat2QImage(mainImg);
    if (!isBinaryImage(src))
    {
        return false;
    }
    QImage dst = ImageOperations::thicking(src);
    mainImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::distanceTransform()
{
    QImage src = Tools::Mat2QImage(mainImg);
    if (!isBinaryImage(src))
    {
        return false;
    }
    QImage dst = ImageOperations::distanceTransform(src);
    mainImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::skeletonization(, int size, int x, int y, int *array)
{
    QImage src = Tools::Mat2QImage(mainImg);
    if (!isBinaryImage(src))
    {
        return false;
    }
    QImage dst = ImageOperations::skeletonization(src, size, x, y, array);
    mainImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::skeletionReconstruct(int size, int x, int y, int *array)
{
    QImage src = Tools::Mat2QImage(mainImg);
    if (!isBinaryImage(src))
    {
        return false;
    }
    QImage dst = ImageOperations::skeletionReconstruct(src, size, x, y, array);
    mainImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::binaryReconstruction(int size, int x, int y, int *array)
{
    QImage src = Tools::Mat2QImage(mainImg);
    if (!isBinaryImage(src))
    {
        return false;
    }
    QImage dst = ImageOperations::binaryReconstruction(src, size, x, y, array);
    mainImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::obr(int size, int x, int y, int *array)
{
    QImage src = Tools::Mat2QImage(mainImg);
    if (!isBinaryImage(src))
    {
        return false;
    }
    QImage dst = ImageOperations::obr(src, size, x, y, array);
    mainImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::cbr(int size, int x, int y, int *array)
{
    QImage src = Tools::Mat2QImage(mainImg);
    if (!isBinaryImage(src))
    {
        return false;
    }
    QImage dst = ImageOperations::cbr(src, size, x, y, array);
    mainImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::linearContrastAdjust(int x1, int y1, int x2, int y2)
{
    QImage src = Tools::Mat2QImage(mainImg);
    QImage dst = ImageOperations::linearContrastAdjust(src, x1, y1, x2, y2);
    subImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(SUB_IMAGE);
    return true;
}

bool Model::pieceLinContrastAdjust(int x1, int y1, int x2, int y2)
{
    QImage src = Tools::Mat2QImage(mainImg);
    QImage dst = ImageOperations::pieceLinContrastAdjust(src, x1, y1, x2, y2);
    subImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(SUB_IMAGE);
    return true;
}

bool Model::logContrastAdjust(double a, double b)
{
    QImage src = Tools::Mat2QImage(mainImg);
    QImage dst = ImageOperations::logContrastAdjust(src, a, b);
    subImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(SUB_IMAGE);
    return true;
}

bool Model::expContrastAdjust(double a, double b)
{
    QImage src = Tools::Mat2QImage(mainImg);
    QImage dst = ImageOperations::expContrastAdjust(src, a, b);
    subImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(SUB_IMAGE);
    return true;
}

bool Model::getHistogram(int *histo)
{
    QImage src = Tools::Mat2QImage(mainImg);
    ImageOperations::getHistogram(src, histo);
    return true;
}

bool Model::histogramEqualization(int *histo)
{
    QImage src = Tools::Mat2QImage(mainImg);
    QImage dst = ImageOperations::histogramEqualization(src, histo);
    mainImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::colorLevel(PColorLevelData clData)
{
    QImage src = Tools::Mat2QImage(subImg);
    QImage dst = ImageOperations::colorLevel(src, clData);
    subImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(SUB_IMAGE);
    return true;
}

bool Model::watershed()
{
    QImage src = Tools::Mat2QImage(mainImg);
    QImage dst = ImageOperations::watershed(src);
    mainImg = Tools::QImage2Mat(dst);
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::isBinaryImage()
{
    QImage src = Tools::Mat2QImage(mainImg);
    return ImageOperations::isBinaryImage(src);
}

bool Model::isGrayImage()
{
    QImage src = Tools::Mat2QImage(mainImg);
    return ImageOperations::isGrayImage(src);
}

