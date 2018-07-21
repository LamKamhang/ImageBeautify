#include "aux_image_alg.h"
#include "../model.h"
#include "../../common/util.h"

bool Model::imageAdd(double param1, double param2)
{
    if (mainImg.height() != subImg.height() || mainImg.width() != subImg.width())
    {
        return false;
    }
    else
    {
        QImage tmp(ImageOperations::imageAdd(mainImg, subImg, param1, param2));
        mainImg = tmp;
        Fire_OnPropertyChanged(MAIN_IMAGE);
        return true;
    }
}

bool Model::imageSubtract(double param1, double param2)
{
    if (mainImg.height() != subImg.height() || mainImg.width() != subImg.width())
    {
        return false;
    }
    else
    {
        QImage tmp(ImageOperations::imageSubtract(mainImg, subImg, param1, param2));
        mainImg = tmp;
        Fire_OnPropertyChanged(MAIN_IMAGE);
        return true;
    }
}

bool Model::imageMultiply()
{
    if (mainImg.height() != subImg.height() || mainImg.width() != subImg.width())
    {
        return false;
    }
    else
    {
        QImage tmp(ImageOperations::imageMultiply(mainImg, subImg));
        mainImg = tmp;
        Fire_OnPropertyChanged(MAIN_IMAGE);
        return true;
    }
}

bool Model::getSingleChannel(ChannelType channel)
{
    QImage tmp(ImageOperations::getSingleChannel(mainImg, channel));
	mainImg = tmp;
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::grayScale()
{
    QImage tmp(ImageOperations::grayScale(mainImg));
	mainImg = tmp;
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::adjustHue(QVector<int> hueValues)
{
    QImage tmp(ImageOperations::adjustHue(mainImg, subImg, hueValues));
	subImg = tmp;
    Fire_OnPropertyChanged(SUB_IMAGE);
    return true;
}

bool Model::adjustSaturation(int saturation)
{
    QImage tmp(ImageOperations::adjustSaturation(mainImg, subImg, saturation));
	subImg = tmp;
    Fire_OnPropertyChanged(SUB_IMAGE);
    return true;
}

bool Model::adjustLightness(int lightness)
{
    QImage tmp(ImageOperations::adjustLightness(mainImg, subImg, lightness));
	subImg = tmp;
    Fire_OnPropertyChanged(SUB_IMAGE);
    return true;
}

bool Model::otsu()
{
    QImage tmp(ImageOperations::otsu(mainImg));
	mainImg = tmp;
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::dualThreshold(int thresh1, int thresh2)
{
    QImage tmp(ImageOperations::dualThreshold(mainImg, thresh1, thresh2));
	subImg = tmp;
    Fire_OnPropertyChanged(SUB_IMAGE);
    return true;
}

bool Model::nearnestInterpolation(int scale, int rotation)
{
    QImage tmp(ImageOperations::nearnestInterpolation(mainImg, scale, rotation));
	mainImg = tmp;
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::BilinearInterpolation(int scale, int rotation)
{
    QImage tmp(ImageOperations::BilinearInterpolation(mainImg, scale, rotation));
	mainImg = tmp;
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::meanFilter(int col, int row, int x, int y)
{
    QImage tmp(ImageOperations::meanFilter(mainImg, col, row, x, y));
	mainImg = tmp;
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::medianFilter(int col, int row, int x, int y)
{
    QImage tmp(ImageOperations::medianFilter(mainImg, col, row, x, y));
	mainImg = tmp;
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::gaussianFilter(int col, int row, int x, int y, double sigma)
{
    QImage tmp(ImageOperations::gaussianFilter(mainImg, col, row, x, y, sigma));
	mainImg = tmp;
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::sobelEdgeDetection(int threshold)
{
    QImage tmp(ImageOperations::sobelEdgeDetection(mainImg, threshold));
	mainImg = tmp;
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::laplacianEdgeDetection(int threshold)
{
    QImage tmp(ImageOperations::laplacianEdgeDetection(mainImg, threshold));
	mainImg = tmp;
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::cannyEdgeDetection(int lo, int hi)
{
    QImage tmp(ImageOperations::cannyEdgeDetection(mainImg, lo, hi));
	mainImg = tmp;
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::houghLineDetect()
{
    QImage tmp(ImageOperations::houghLineDetect(mainImg));
	mainImg = tmp;
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::houghCircleDetect(int lo, int hi)
{
    QImage tmp(ImageOperations::houghCircleDetect(mainImg, lo, hi));
	mainImg = tmp;
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::clip(int startX, int endX, int startY, int endY)
{
    QImage tmp(ImageOperations::clip(mainImg, startX, endX, startY, endY));
	mainImg = tmp;
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::dilation(int size, int x, int y, int *array)
{
    if (!isBinaryImage())
    {
        return false;
    }
    QImage tmp(ImageOperations::dilation(mainImg, size, x, y, array));
	mainImg = tmp;
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::erosion(int size, int x, int y, int *array)
{
    if (!isBinaryImage())
    {
        return false;
    }
    QImage tmp(ImageOperations::erosion(mainImg, size, x, y, array));
	mainImg = tmp;
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::opening(int size, int x, int y, int *array)
{
    if (!isBinaryImage())
    {
        return false;
    }
    QImage tmp(ImageOperations::opening(mainImg, size, x, y, array));
	mainImg = tmp;
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::closing(int size, int x, int y, int *array)
{
    if (!isBinaryImage())
    {
        return false;
    }
    QImage tmp(ImageOperations::closing(mainImg, size, x, y, array));
	mainImg = tmp;
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::thinning()
{
    if (!isBinaryImage())
    {
        return false;
    }
    QImage tmp(ImageOperations::thinning(mainImg));
	mainImg = tmp;
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::thicking()
{
    if (!isBinaryImage())
    {
        return false;
    }
    QImage tmp(ImageOperations::thicking(mainImg));
	mainImg = tmp;
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::distanceTransform()
{
    if (!isBinaryImage())
    {
        return false;
    }
    QImage tmp(ImageOperations::distanceTransform(mainImg));
	mainImg = tmp;
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::skeletonization(int size, int x, int y, int *array)
{
    if (!isBinaryImage())
    {
        return false;
    }
    QImage tmp(ImageOperations::skeletonization(mainImg, size, x, y, array));
	mainImg = tmp;
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::skeletionReconstruct(int size, int x, int y, int *array)
{
    if (!isBinaryImage())
    {
        return false;
    }
    QImage tmp(ImageOperations::skeletionReconstruct(mainImg, size, x, y, array));
	mainImg = tmp;
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::binaryReconstruction(int size, int x, int y, int *array)
{
    if (!isBinaryImage())
    {
        return false;
    }
    QImage tmp(ImageOperations::binaryReconstruction(mainImg, size, x, y, array));
	mainImg = tmp;
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::obr(int size, int x, int y, int *array)
{
    if (!isBinaryImage())
    {
        return false;
    }
    QImage tmp(ImageOperations::obr(mainImg, size, x, y, array));
	mainImg = tmp;
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::cbr(int size, int x, int y, int *array)
{
    if (!isBinaryImage())
    {
        return false;
    }
    QImage tmp(ImageOperations::cbr(mainImg, size, x, y, array));
	mainImg = tmp;
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::linearContrastAdjust(int x1, int y1, int x2, int y2)
{
    QImage tmp(ImageOperations::linearContrastAdjust(mainImg, x1, y1, x2, y2));
	subImg = tmp;
    Fire_OnPropertyChanged(SUB_IMAGE);
    return true;
}

bool Model::pieceLinContrastAdjust(int x1, int y1, int x2, int y2)
{
    QImage tmp(ImageOperations::pieceLinContrastAdjust(mainImg, x1, y1, x2, y2));
	subImg = tmp;
    Fire_OnPropertyChanged(SUB_IMAGE);
    return true;
}

bool Model::logContrastAdjust(double a, double b)
{
    QImage tmp(ImageOperations::logContrastAdjust(mainImg, a, b));
	subImg = tmp;
    Fire_OnPropertyChanged(SUB_IMAGE);
    return true;
}

bool Model::expContrastAdjust(double a, double b)
{
    QImage tmp(ImageOperations::expContrastAdjust(mainImg, a, b));
	subImg = tmp;
    Fire_OnPropertyChanged(SUB_IMAGE);
    return true;
}

bool Model::histogramEqualization(int *histo)
{
    QImage tmp(ImageOperations::histogramEqualization(mainImg, histo));
	mainImg = tmp;
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::colorLevel(PColorLevelData clData)
{
    QImage tmp(ImageOperations::colorLevel(mainImg, clData));
	subImg = tmp;
    Fire_OnPropertyChanged(SUB_IMAGE);
    return true;
}

bool Model::watershed()
{
    QImage tmp(ImageOperations::watershed(mainImg));
	mainImg = tmp;
    Fire_OnPropertyChanged(MAIN_IMAGE);
    return true;
}

bool Model::isBinaryImage()
{
    return ImageOperations::isBinaryImage(mainImg);
}

bool Model::isGrayImage()
{
    return ImageOperations::isGrayImage(mainImg);
}

