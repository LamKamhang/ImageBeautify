#ifndef IMAGEOPERATIONS_H
#define IMAGEOPERATIONS_H

#include <QImage>
#include <QVector>
#include <vector>
#include <queue>

typedef struct
{
    int Shadow;
    float Midtones;
    int Highlight;
    int OutShadow;
    int OutHighlight;
}ColorLevelItem, *PColorLevelItem;

typedef struct
{
    ColorLevelItem Blue;
    ColorLevelItem Green;
    ColorLevelItem Red;
    ColorLevelItem RGB;
}ColorLevelData, *PColorLevelData;

class ImageOperations
{
public:
    enum ChannelType{RED = 0, GREEN, BLUE};

    ImageOperations();
    QImage imageAdd(QImage img1, QImage img2, double param1, double param2);
    QImage imageSubtract(QImage img1, QImage img2, double param1, double param2);
    QImage imageMultiply(QImage img1, QImage img2);
    QImage getSingleChannel(QImage, ChannelType);
    QImage grayScale(QImage);
    QImage adjustHue(QImage, QImage, QVector<int> hueValues);
    QImage adjustSaturation(QImage, QImage, int saturation);
    QImage adjustLightness(QImage, QImage, int lightness);
    QImage otsu(QImage);
    QImage dualThreshold(QImage img, int thresh1, int thresh2);
    QImage nearnestInterpolation(QImage img, int scale, int rotation);
    QImage BilinearInterpolation(QImage img, int scale, int rotation);
    QImage meanFilter(QImage img, int col, int row, int x, int y);
    QImage medianFilter(QImage image, int col, int row, int x, int y);
    QImage gaussianFilter(QImage image, int col, int row, int x, int y, double sigma);
    QImage sobelEdgeDetection(QImage img, int threshold);
    QImage laplacianEdgeDetection(QImage img, int threshold);
    QImage cannyEdgeDetection(QImage img, int lo, int hi);
    QImage houghLineDetect(QImage img);
    QImage houghCircleDetect(QImage img, int lo, int hi);
    QImage clip(QImage img, int startX, int endX, int startY, int endY);
    QImage dilation(QImage img, int size, int x, int y, int *array);
    QImage erosion(QImage img, int size, int x, int y, int *array);
    QImage opening(QImage img, int size, int x, int y, int *array);
    QImage closing(QImage img, int size, int x, int y, int *array);
    QImage thinning(QImage img);
    QImage thicking(QImage img);
    QImage distanceTransform(QImage img);
    QImage skeletonization(QImage img, int size, int x, int y, int *array);
    QImage skeletionReconstruct(QImage img, int size, int x, int y, int *array);
    QImage binaryReconstruction(QImage img, int size, int x, int y, int *array);
    QImage obr(QImage img, int size, int x, int y, int *array);
    QImage cbr(QImage img, int size, int x, int y, int *array);
    QImage linearContrastAdjust(QImage img, int x1, int y1, int x2, int y2);
    QImage pieceLinContrastAdjust(QImage img, int x1, int y1, int x2, int y2);
    QImage logContrastAdjust(QImage img, double a, double b);
    QImage expContrastAdjust(QImage img, double a, double b);
    void getHistogram(QImage img, int *histo);
    QImage histogramEqualization(QImage img, int *histo);
    QImage colorLevel(QImage img, PColorLevelData clData);
    QImage watershed(QImage img);
    QImage Or(QImage &img1, QImage &img2);
    QImage And(QImage &img1, QImage &img2);
    bool isBinaryImage(QImage &);
    bool isGrayImage(QImage &);

private:
    int threshold(int *list);
    inline int round(double);
    unsigned int median(unsigned int *, int, int);
    bool isBlackImage(QImage &img);
    bool isWhiteImage(QImage &img);
    void binaryReverse(QImage &img);
    bool isSame(QImage &img1, QImage &img2);
    QImage grayscaleReconstruct(QImage img, QImage marker, int size, int x, int y, int *array);
    void grayValueTransfer(QImage &img, int *corres);
    bool getColorLevelTable(PColorLevelItem item, unsigned char *clTable);
    bool checkColorLevelData(PColorLevelData clData, unsigned char clTables[][256]);
};

class WatershedPixel {
    static const int INIT = -1;
    static const int MASK = -2;
    static const int WSHED = 0;
    static const int FICTITIOUS = -3;

    int x;
    int y;
    char height;
    int label;
    int dist;

    std::vector<WatershedPixel*> neighbours;

public:
    WatershedPixel(int x, int y, char height) {
        this->x = x;
        this->y = y;
        this->height = height;
        label = INIT;
        dist = 0;
        neighbours.reserve(8);
    }
    WatershedPixel() { label = FICTITIOUS; }

    void addNeighbour(WatershedPixel* neighbour) {
        neighbours.push_back(neighbour);
    }
    std::vector<WatershedPixel*>& getNeighbours() {
        return neighbours;
    }

    char getHeight() const { return height; }
    int getIntHeight() const { return (int) height&0xff; }
    int getX() const {	return x; }
    int getY() const {	return y; }

    void setLabel(int label) { this->label = label; }
    void setLabelToINIT() { label = INIT; }
    void setLabelToMASK() { label = MASK; }
    void setLabelToWSHED() { label = WSHED; }
    int getLabel() {   return label; }

    bool isLabelINIT() { return label == INIT; }
    bool isLabelMASK() { return label == MASK; }
    bool isLabelWSHED() { return label == WSHED; }

    void setDistance(int distance) { dist = distance; }
    int getDistance() { return dist; }

    bool isFICTITIOUS() { return label == FICTITIOUS; }

    bool allNeighboursAreWSHED() {
        for (unsigned i = 0 ; i < neighbours.size() ; i++) {
            WatershedPixel* r =  neighbours.at(i);
            if ( !r->isLabelWSHED() ) return false;
        }
        return true;
    }
};

class WatershedStructure {
    std::vector<WatershedPixel*> watershedStructure;

public:
    WatershedStructure(QImage img) {

        int width = img.width();
        int height = img.height();
        watershedStructure.reserve(width * height);
        for (int y = 0; y < height; ++y)
            for (int x = 0; x < width; ++x)
                watershedStructure.push_back(new WatershedPixel(x, y, qRed(img.pixel(x, y))));

        for (int y = 0; y < height; ++y) {
            int offset = y * width;
            int topOffset = offset + width;
            int bottomOffset = offset - width;

            for (int x = 0; x < width; ++x) {
                int currentindex = x + y*width;
                WatershedPixel* currentPixel = watershedStructure.at(currentindex);

                if (x - 1 >= 0) {
                    currentPixel->addNeighbour(watershedStructure.at(currentindex-1));
                    if (y - 1 >= 0)
                        currentPixel->addNeighbour(watershedStructure.at(currentindex-1 - width));
                    if (y + 1 < height)
                        currentPixel->addNeighbour(watershedStructure.at(currentindex-1 + width));
                }

                if (x + 1 < width) {
                    currentPixel->addNeighbour(watershedStructure.at(currentindex+1));
                    if (y - 1 >= 0)
                        currentPixel->addNeighbour(watershedStructure.at(currentindex+1 - width));
                    if (y + 1 < height)
                        currentPixel->addNeighbour(watershedStructure.at(currentindex+1 + width));
                }

                if (y - 1 >= 0)
                    currentPixel->addNeighbour(watershedStructure.at(currentindex-width));

                if (y + 1 < height)
                    currentPixel->addNeighbour(watershedStructure.at(currentindex+width));
            }
        }

        std::sort(watershedStructure.begin(), watershedStructure.end(),
            [](WatershedPixel * pl, WatershedPixel * pr) { return pl->getIntHeight() < pr->getIntHeight(); });
    }

    ~WatershedStructure() {
        while (!watershedStructure.empty()) {
            WatershedPixel* p = watershedStructure.back();
            delete p; p = NULL;
            watershedStructure.pop_back();
        }
    }

    int size() { return watershedStructure.size(); }

    WatershedPixel* at(int i) { return watershedStructure.at(i); }
};


#endif // IMAGEOPERATIONS_H
