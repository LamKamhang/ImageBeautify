#include "aux_image_alg.h"
#include <iostream>
#include <math.h>
#include <QPixmap>
#include <queue>
#include <stack>

#define PI 3.1415926

QImage ImageOperations::imageAdd(QImage img1, QImage img2, double param1, double param2){
    int h, w;
    h = img1.height();
    w = img1.width();
    QRgb *line1;
    QRgb *line2;
    QImage newImage(w, h, QImage::Format_ARGB32);
    int red, green, blue;
    for(int i = 0; i < h; i++){
        line1 = (QRgb *)img1.scanLine(i);
        line2 = (QRgb *)img2.scanLine(i);

        for(int j = 0; j < w; j++){
            red = param1 * qRed(line1[j]) + param2 * qRed(line2[j]);
            green = param1 * qGreen(line1[j]) + param2 * qGreen(line2[j]);
            blue = param1 * qBlue(line1[j]) + param2 * qBlue(line2[j]);
            red = red > 0 ? (red > 255 ? 255 : red) : 0;
            green = green > 0? (green > 255 ? 255 : green): 0;
            blue = blue > 0? (blue > 255 ? 255 : blue): 0;
            QRgb pixColor = qRgb(red, green, blue);
            newImage.setPixel(j, i, pixColor);
        }
    }
    return newImage;
}

QImage ImageOperations::imageSubtract(QImage img1, QImage img2, double param1, double param2){
    int h, w;
    h = img1.height();
    w = img1.width();
    QRgb *line1;
    QRgb *line2;
    QImage newImage(w, h, QImage::Format_ARGB32);
    int red, green, blue;
    for(int i = 0; i < h; i++){
        line1 = (QRgb *)img1.scanLine(i);
        line2 = (QRgb *)img2.scanLine(i);

        for(int j = 0; j < w; j++){
            red = param1 * qRed(line1[j]) - param2 * qRed(line2[j]);
            red = red > 0 ? (red > 255 ? 255 : red) : 0;
            green = param1 * qGreen(line1[j]) - param2 * qGreen(line2[j]);
            green = green > 0? (green > 255 ? 255 : green): 0;
            blue = param1 * qBlue(line1[j]) - param2 * qBlue(line2[j]);
            blue = blue > 0? (blue > 255 ? 255 : blue): 0;
            QRgb pixColor = qRgb(red, green, blue);
            newImage.setPixel(j, i, pixColor);
        }
    }
    return newImage;
}

QImage ImageOperations::imageMultiply(QImage img1, QImage img2){
    int h, w;
    h = img1.height();
    w = img1.width();
    QRgb *line1;
    QRgb *line2;
    QImage newImage(w, h, QImage::Format_ARGB32);
    for(int i = 0; i < h; i++){
        line1 = (QRgb *)img1.scanLine(i);
        line2 = (QRgb *)img2.scanLine(i);

        for(int j = 0; j < w; j++){
            QRgb pixColor = qRgb((qRed(line1[j]) * qRed(line2[j])) % 256,
                          (qGreen(line1[j]) * qGreen(line2[j])) % 256,
                          (qBlue(line1[j]) * qBlue(line2[j])) % 256);
            newImage.setPixel(j, i, pixColor);
        }
    }
    return newImage;
}

QImage ImageOperations::getSingleChannel(QImage img, ChannelType channel){
    int h, w;
    h = img.height();
    w = img.width();
    QRgb *line;
    for(int i = 0; i < h; i++){
        line = (QRgb *)img.scanLine(i);

        for(int j = 0; j < w; j++){
            QRgb pixColor = qRgb(channel == RED? qRed(line[j]):0,
                                 channel == GREEN? qGreen(line[j]):0,
                                 channel == BLUE? qBlue(line[j]):0);
            img.setPixel(j, i, pixColor);
        }
    }
    return img;
}

QImage ImageOperations::grayScale(QImage img){
    int h, w;
    h = img.height();
    w = img.width();
    QRgb *line;
    for(int i = 0; i < h; i++){
        line = (QRgb *)img.scanLine(i);

        for(int j = 0; j < w; j++){
            int avg = (qRed(line[j]) + qGreen(line[j]) + qBlue(line[j])) / 3;
            img.setPixel(j, i, qRgb(avg, avg, avg));
        }
    }
    return img;
}

QImage ImageOperations::adjustHue(QImage img, QImage img2, QVector<int> hueValues){
    int hh, w;
    hh = img.height();
    w = img.width();
    QRgb *line1, *line2;
    for(int i = 0; i < hh; i++){
        line1 = (QRgb *)img.scanLine(i);
        line2 = (QRgb *)img2.scanLine(i);

        for(int j = 0; j < w; j++){
            QColor color(line1[j]);
            QColor pixColor(line2[j]);
            int h = color.hslHue();
            double red = pixColor.red();
            double green = pixColor.green();
            double blue = pixColor.blue();
            double colorDegree = atan2((green - blue) * sqrt(3) / 2, red - (green + blue) / 2) *(double)180 / PI;

            h = (h + hueValues[0] + 360) % 360;
            if(colorDegree > -30 && colorDegree <= 30){   //red
                h = (h + hueValues[1] + 360) % 360;
            } else if(colorDegree > 30 && colorDegree <= 90){
                h = (h + hueValues[2] + 360) % 360;
            } else if(colorDegree > 90 && colorDegree <= 150){
                h = (h + hueValues[3] + 360) % 360;
            } else if(colorDegree > 150 || colorDegree <= -150){
                h = (h + hueValues[4] + 360) % 360;
            } else if(colorDegree > -150 && colorDegree <= -90){
                h = (h + hueValues[5] + 360) % 360;
            } else {
                h = (h + hueValues[6] + 360) % 360;
            }
            pixColor.setHsl(h, pixColor.hslSaturation(), pixColor.lightness());
            img.setPixel(j, i, pixColor.rgb());
        }
    }
    return img;
}

QImage ImageOperations::adjustSaturation(QImage img, QImage img2, int saturation){
    int hh, w;
    hh = img.height();
    w = img.width();
    QRgb *line1, *line2;
    for(int i = 0; i < hh; i++){
        line1 = (QRgb *)img.scanLine(i);
        line2 = (QRgb *)img2.scanLine(i);

        for(int j = 0; j < w; j++){
            QColor color(line1[j]);
            QColor pixColor(line2[j]);
            int s = color.hslSaturation();
            s *= 1 + (double)saturation / 100;
            if(s > 255) s = 255;
            pixColor.setHsl(pixColor.hslHue(), s, pixColor.lightness());
            img.setPixel(j, i, pixColor.rgb());
        }
    }
    return img;
}

QImage ImageOperations::adjustLightness(QImage img, QImage img2, int lightness){
    int hh, w;
    hh = img.height();
    w = img.width();
    QRgb *line1, *line2;
    for(int i = 0; i < hh; i++){
        line1 = (QRgb *)img.scanLine(i);
        line2 = (QRgb *)img2.scanLine(i);

        for(int j = 0; j < w; j++){
            QColor color(line1[j]);
            QColor pixColor(line2[j]);
            int l = color.lightness();
            l *= 1 + (double)lightness / 100;
            if(l > 255) l = 255;
            pixColor.setHsl(pixColor.hslHue(), pixColor.hslSaturation(), l);
            img.setPixel(j, i, pixColor.rgb());
        }
    }
    return img;
}

QImage ImageOperations::otsu(QImage image){
    int hist[256] = {0};
    int h, w;
    h = image.height();
    w = image.width();
    QRgb *line;
    for(int i = 0; i < h; i++){
        line = (QRgb *)image.scanLine(i);

        for(int j = 0; j < w; j++){
            int avg = (qRed(line[j]) + qGreen(line[j]) + qBlue(line[j])) / 3;
            hist[avg]++;
        }
    }
    int t = threshold(hist);

    for(int i = 0; i < h; i++){
        line = (QRgb *)image.scanLine(i);

        for(int j = 0; j < w; j++){
            int avg = (qRed(line[j]) + qGreen(line[j]) + qBlue(line[j])) / 3;
            int color = avg >= t? 255 : 0;
            image.setPixel(j, i, qRgb(color, color, color));
        }
    }



    return image;
}

int ImageOperations::threshold(int *list){
    int maxT;
    double maxDevi = 0;
    int sum = 0;
    for(int i = 0; i < 256; i++){
        sum += list[i];
    }
    for(int t = 0; t < 255; t++){
        double u0 = 0;
        int count = 0;
        for(int i = 0; i <= t; i++){
            u0 += i * list[i];
            count += list[i];
        }
        u0 /= count;
        double w0 = (double)count / sum;

        double u1 = 0;
        for(int i = t + 1; i < 256; i++){
            u1 += i * list[i];
        }
        u1 /= (sum - count);
        double w1 = 1 - w0;

        double devi = w0 * w1 * (u1 - u0) * (u1 - u0);
        if(devi > maxDevi){
            maxDevi = devi;
            maxT = t;
        }
    }
    return maxT;
}

QImage ImageOperations::dualThreshold(QImage img, int thresh1, int thresh2){
    int h, w;
    h = img.height();
    w = img.width();
    QRgb *line;
    if(thresh1 > thresh2){
        img.fill(QColor(0, 0, 0));
        return img;
    }

    for(int i = 0; i < h; i++){
        line = (QRgb *)img.scanLine(i);

        for(int j = 0; j < w; j++){
            int avg = (qRed(line[j]) + qGreen(line[j]) + qBlue(line[j])) / 3;
            int color = avg >= thresh1? (avg <= thresh2? 255: 0) : 0;
            img.setPixel(j, i, qRgb(color, color, color));
        }
    }
    return img;
}

inline int ImageOperations::round(double value){
    return (value > 0.0)? (value + 0.5):(value - 0.5);
}

QImage ImageOperations::nearnestInterpolation(QImage img, int scale, int rotation){
    int h, w;
    h = img.height();
    w = img.width();
    double scaleFactor = (double)scale / 100;
    double degree = (abs(rotation) > 90)?(double)(abs(rotation) - 90) * PI / 180:(double)abs(rotation) * PI / 180;
    int newH, newW;
    newW = round(w * scaleFactor * cos(degree)
                 + h * scaleFactor * sin(degree));
    newH = round(w * scaleFactor * sin(degree)
                 + h * scaleFactor * cos(degree));
    if(abs(rotation > 90)){
        int temp = newW;
        newW = newH;
        newH = temp;
    }

    QImage newImage(newW, newH, img.format());
    for(int j = 0; j < newH; j++){
        for(int i = 0; i < newW; i++){
            int xx = i, yy = j;
            if(rotation < 0){
                xx = newW - xx;
            }
            if(abs(rotation) > 90){
                int temp = xx;
                xx = yy;
                yy = newW - temp;
            }
            int x = round((double)yy / scaleFactor * sin(degree)
                          + (double)xx / scaleFactor * cos(degree)
                          - (double)h * sin(degree) * cos(degree));
            int y = round((double)yy / scaleFactor * cos(degree)
                          - (double)xx / scaleFactor * sin(degree)
                          + (double)h * sin(degree) * sin(degree));
            if(rotation < 0){
                x = w - x;
            }
            QColor color;
            if(x < 0 || x >= w || y < 0 || y >= h){
                color = QColor(0, 0, 0);
            } else {
                color = img.pixelColor(x, y);
            }
            newImage.setPixelColor(i, j, color);
        }
    }
    return newImage;
}

QImage ImageOperations::BilinearInterpolation(QImage img, int scale, int rotation){
    int h, w;
    h = img.height();
    w = img.width();
    double scaleFactor = (double)scale / 100;
    double degree = (abs(rotation) > 90)?(double)(abs(rotation) - 90) * PI / 180:(double)abs(rotation) * PI / 180;
    int newH, newW;
    newW = round(w * scaleFactor * cos(degree)
                 + h * scaleFactor * sin(degree));
    newH = round(w * scaleFactor * sin(degree)
                 + h * scaleFactor * cos(degree));
    if(abs(rotation > 90)){
        int temp = newW;
        newW = newH;
        newH = temp;
    }

    QImage newImage(newW, newH, img.format());
    for(int j = 0; j < newH; j++){
        for(int i = 0; i < newW; i++){
            int xx = i, yy = j;
            if(rotation < 0){
                xx = newW - xx;
            }
            if(abs(rotation) > 90){
                int temp = xx;
                xx = yy;
                yy = newW - temp;
            }
            double x = (double)yy / scaleFactor * sin(degree)
                          + (double)xx / scaleFactor * cos(degree)
                          - (double)h * sin(degree) * cos(degree);
            double y = (double)yy / scaleFactor * cos(degree)
                          - (double)xx / scaleFactor * sin(degree)
                          + (double)h * sin(degree) * sin(degree);
            if(rotation < 0){
                x = w - x;
            }
            int i1, i2, j1, j2;
            i1 = (int)x;
            j1 = (int)y;
            i2 = i1 + 1;
            j2 = j1 + 1;
            double u = x - i1;
            double v = y - j1;
            double s1 = (1.0 - u) * (1.0 - v);
            double s2 = (1.0 - u) * v;
            double s3 = u * (1.0 - v);
            double s4 = u * v;

            QColor color;
            if(i1 < 0 || i2 >= w || j1 < 0 || j2 >= h){
                color = QColor(0, 0, 0);
            } else {
                QRgb color1 = img.pixel(i1, j1);
                QRgb color2 = img.pixel(i2, j1);
                QRgb color3 = img.pixel(i1, j2);
                QRgb color4 = img.pixel(i2, j2);
                color = QColor(qRed(color1)*s1 + qRed(color2)*s2 + qRed(color3)*s3 + qRed(color4)*s4,
                               qGreen(color1)*s1 + qGreen(color2)*s2 + qGreen(color3)*s3 + qGreen(color4)*s4,
                               qBlue(color1)*s1 + qBlue(color2)*s2 + qBlue(color3)*s3 + qBlue(color4)*s4);
            }
            newImage.setPixelColor(i, j, color);
        }
    }
    return newImage;
}

QImage ImageOperations::meanFilter(QImage img, int col, int row, int x, int y){
    int h, w;
    h = img.height();
    w = img.width();
    int size = row * col;
    int totalR, totalG, totalB;
    QImage newImage(w, h, img.format());
    QRgb color;
    if(x == -1){
        x = col/2;
    }
    if(y == -1){
        y = row/2;
    }
    for(int j = 0; j < h; j++){
        for(int i = 0; i < w; i++){
            if(i < x || i + col > w + x
                    || j < y || j + row > h + y){
                newImage.setPixel(i, j, img.pixel(i, j));
            } else{
                totalR = 0;
                totalG = 0;
                totalB = 0;
                for(int c = i - x; c < i -x + col; c++){
                    for(int r = j - y; r < j - y + row; r++){
                        color = img.pixel(c, r);
                        totalR += qRed(color);
                        totalG += qGreen(color);
                        totalB += qBlue(color);
                    }
                }
                totalR /= size;
                totalG /= size;
                totalB /= size;
                newImage.setPixel(i, j, qRgb(totalR, totalG, totalB));
            }
        }
    }
    return newImage;
}

QImage ImageOperations::medianFilter(QImage img, int col, int row, int x, int y){
    int h, w;
    h = img.height();
    w = img.width();
    int size = row * col;
    QImage newImage(w, h, img.format());
    unsigned int *values = new unsigned int[size];
    if(x == -1){
        x = col/2;
    }
    if(y == -1){
        y = row/2;
    }
    for(int j = 0; j < h; j++){
        for(int i = 0; i < w; i++){
            if(i < x || i + col > w + x
                    || j < y || j + row > h + y){
                newImage.setPixel(i, j, img.pixel(i, j));
            } else{
                for(int c = i - x; c < i -x + col; c++){
                    for(int r = j - y; r < j - y + row; r++){
                        values[(c + x - i) * col + r + y - j] = (unsigned int)img.pixel(c, r);
                    }
                }
                newImage.setPixel(i, j, (QRgb)median(values, 0, size - 1));
            }
        }
    }
    delete []values;
    return newImage;
}

QImage ImageOperations::gaussianFilter(QImage img, int col, int row, int x, int y, double sigma){
    int h, w;
    h = img.height();
    w = img.width();
    QImage newImage(w, h, img.format());
    int size = row * col;
    double *gaussian = new double[size];
    double sum;
    int mx = col/2, my = col/2;
    for(int i = 0; i < col; i++){
        for(int j = 0; j < row; j++){
            double val = 0.5 / (PI * sigma * sigma) * exp(-0.5*(double)((i-mx)*(i-mx) + (j-my)*(j-my))/(sigma * sigma));
            gaussian[i * col + j] = val;
            sum += val;
        }
    }
    double totalR, totalG, totalB;
    QRgb color;
    if(x == -1){
        x = col/2;
    }
    if(y == -1){
        y = row/2;
    }
    double p;
    for(int j = 0; j < h; j++){
        for(int i = 0; i < w; i++){
            if(i < x || i + col > w + x
                    || j < y || j + row > h + y){
                newImage.setPixel(i, j, img.pixel(i, j));
            } else{
                totalR = 0;
                totalG = 0;
                totalB = 0;
                for(int c = i - x; c < i -x + col; c++){
                    for(int r = j - y; r < j - y + row; r++){
                        color = img.pixel(c, r);
                        p = gaussian[(c + x - i) * col + r + y - j];
                        totalR += qRed(color) * p;
                        totalG += qGreen(color) * p;
                        totalB += qBlue(color) * p;
                    }
                }
                totalR /= sum;
                totalG /= sum;
                totalB /= sum;
                newImage.setPixel(i, j, qRgb(totalR, totalG, totalB));
            }
        }
    }
    delete []gaussian;
    return newImage;
}

QImage ImageOperations::sobelEdgeDetection(QImage img, int threshold){
    img = grayScale(img);
    int w, h;
    w = img.width();
    h = img.height();
    QImage newImage = QImage(w, h, img.format());
    QColor color;
    int dx[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int dy[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
    int gx, gy, g, grayscale;

    for(int j = 0; j < h; j++){
        for(int i = 0; i < w; i++){
            if(i < 1 || i >= w - 1 || j < 1 || j>= h - 1){
                newImage.setPixelColor(i, j, img.pixelColor(i, j));
            } else {
                gx = 0;
                gy = 0;
                for(int r = j - 1; r < j + 2; r++){
                    for(int c = i - 1; c < i + 2; c++){
                        grayscale = qRed(img.pixel(c, r));
                        gx += dx[3 * (r - j + 1) + c - i + 1] * grayscale;
                        gy += dy[3 * (r - j + 1) + c - i + 1] * grayscale;
                    }
                }
                g = abs(gx) + abs(gy);
                if(g > threshold){
                    color = QColor(255, 255, 255);
                } else {
                    color = QColor(0, 0, 0);
                }
                newImage.setPixelColor(i, j, color);
            }
        }
    }
    return newImage;
}

QImage ImageOperations::laplacianEdgeDetection(QImage img, int threshold){
    img = grayScale(img);
    int w, h;
    w = img.width();
    h = img.height();
    QImage newImage = QImage(w, h, img.format());
    QColor color;
    int laplacian[9] = {0, -1, 0, -1, 4, -1, 0, -1, 0};
    int num, grayscale;

    for(int j = 0; j < h; j++){
        for(int i = 0; i < w; i++){
            if(i < 1 || i >= w - 1 || j < 1 || j>= h - 1){
                newImage.setPixelColor(i, j, img.pixelColor(i, j));
            } else {
                num = 0;
                for(int r = j - 1; r < j + 2; r++){
                    for(int c = i - 1; c < i + 2; c++){
                        grayscale = qRed(img.pixel(c, r));
                        num += laplacian[3 * (r - j + 1) + c - i + 1] * grayscale;
                    }
                }
                num = abs(num);
                if(num > threshold){
                    color = QColor(255, 255, 255);
                } else {
                    color = QColor(0, 0, 0);
                }
                newImage.setPixelColor(i, j, color);
            }
        }
    }
    return newImage;
}

QImage ImageOperations::cannyEdgeDetection(QImage img, int lo, int hi){
    img = grayScale(img);
    img = gaussianFilter(img, 3, 3, -1, -1, 0.8);
    int w, h;
    w = img.width();
    h = img.height();
    QImage amplitudeImage = QImage(w, h, img.format());
    QImage thetaImage = QImage(w, h, img.format());
    QImage nmsImage = QImage(w, h, img.format());
    int dx[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int dy[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
    int gx, gy, g, grayscale;
    double theta;

    for(int j = 1; j < h - 1; j++){
        for(int i = 1; i < w - 1; i++){
            gx = 0;
            gy = 0;
            for(int r = j - 1; r < j + 2; r++){
                for(int c = i - 1; c < i + 2; c++){
                    grayscale = qRed(img.pixel(c, r));
                    gx += dx[3 * (r - j + 1) + c - i + 1] * grayscale;
                    gy += dy[3 * (r - j + 1) + c - i + 1] * grayscale;
                }
            }
            g = abs(gx) + abs(gy);
            amplitudeImage.setPixel(i, j, qRgb(0, 0, g));
            theta = atan2((double)gy, (double)gx);
            if((theta >= 22.5 && theta < 67.5) || (theta <= -112.5 && theta > -157.5)){
                theta = -45;
            } else if((theta >= 67.5 && theta < 112.5) || (theta <= -67.5 && theta > -112.5)){
                theta = 90;
            } else if((theta >= 112.5 && theta < 157.5) || (theta <= -22.5 && theta > -67.5)){
                theta = 45;
            } else {
                theta = 0;
            }
            thetaImage.setPixel(i, j, qRgb(0, 0, (int)theta));
        }
    }

    unsigned int v, tt;
    for(int j = 0; j < h; j++){
        for(int i = 0; i < w; i++){
            if(i < 2 || i >= w - 2 || j < 2 || j >= h - 2){
                nmsImage.setPixel(i, j, qRgb(0, 0, 0));
            } else{
                tt = qBlue(thetaImage.pixel(i, j));
                v = amplitudeImage.pixel(i, j);
                if(tt == 0 && v >= amplitudeImage.pixel(i, j-1) && v >= amplitudeImage.pixel(i, j+1)){
                    nmsImage.setPixel(i, j, qRgb(0, 0, v));
                } else if(tt == -45 && v >= amplitudeImage.pixel(i+1, j-1) && v >= amplitudeImage.pixel(i-1, j+1)){
                    nmsImage.setPixel(i, j, qRgb(0, 0, v));
                } else if(tt == 90 && v >= amplitudeImage.pixel(i+1, j) && v >= amplitudeImage.pixel(i-1, j)){
                    nmsImage.setPixel(i, j, qRgb(0, 0, v));
                } else if(tt == 45 && v >= amplitudeImage.pixel(i+1, j+1) && v >= amplitudeImage.pixel(i-1, j-1)){
                    nmsImage.setPixel(i, j, qRgb(0, 0, v));
                } else {
                    nmsImage.setPixel(i, j, qRgb(0, 0, 0));
                }
            }

        }
    }


    int color;
    for(int j = 0; j < h; j++){
        for(int i = 0; i < w; i++){
            if(i < 1 || i >= w - 1 || j < 1 || j >= h - 1){
                color = 0;
            } else{
                v = qBlue(nmsImage.pixel(i, j));
                if(v <= lo){
                    color = 0;
                } else if( v > hi){
                    color = 255;
                } else if(qBlue(nmsImage.pixel(i-1, j-1)) <= hi
                          || qBlue(nmsImage.pixel(i, j-1)) <= hi
                          || qBlue(nmsImage.pixel(i+1, j-1)) <= hi
                          || qBlue(nmsImage.pixel(i-1, j)) <= hi
                          || qBlue(nmsImage.pixel(i+1, j)) <= hi
                          || qBlue(nmsImage.pixel(i-1, j+1)) <= hi
                          || qBlue(nmsImage.pixel(i, j+1)) <= hi
                          || qBlue(nmsImage.pixel(i+1, j+1)) <= hi){
                    color = 255;
                } else {
                    color = 0;
                }
            }
            img.setPixel(i, j, qRgb(color, color, color));
        }
    }
    return img;
}

QImage ImageOperations::houghLineDetect(QImage img){
    int w, h;
    w = img.width();
    h = img.height();
    int centerX = w/2, centerY = h/2;
    QImage newImage = cannyEdgeDetection(img, 50, 100);
    double houghSpace = 180;
    double interval = PI/(double)houghSpace;
    int col, row;
    col = houghSpace;
    row = 2 * (int)sqrt(2.0)*(w > h?w:h);
    int **houghMat = new int *[col];
    for(int i = 0; i < col; i++){
        houghMat[i] = new int[row];
        for(int j = 0; j < row; j++){
            houghMat[i][j] = 0;
        }
    }

    QRgb *line;
    int v, r;
    for(int j = 0; j < h; j++){
        line = (QRgb *)newImage.scanLine(j);
        for(int i = 0; i < w; i++){
            v = qBlue(line[i]);
            if(v == 0) continue;

            for(int cell = 0; cell < col; cell++){
                r = (int)((i - centerX) * cos(cell * interval) + (j - centerY) * sin(cell * interval));
                r += row/2;
                if(r >= 0 && r < row){
                    houghMat[cell][r] += 1;
                }
            }
        }
    }

    int maxHough = 0;
    for(int i = 0; i < col; i++){
        for(int j = 0; j < row; j++){
            if(houghMat[i][j] > maxHough){
                maxHough = houghMat[i][j];
            }
        }
    }

    int threshold = (int)(maxHough * 0.6);

    for(int i = 0; i < col; i++){
        for(int j = 0; j < row; j++){
            int count = houghMat[i][j];
            if(count <= threshold) continue;
            bool isLine = true;
            for(int c = i - 1; c < i + 2; c++){
                for(int r = j - 1; r < j + 2; r++){
                    if(r >= 0 && r < row){
                        c = (c + col) % col;
                        if(houghMat[c][r] > count){
                            isLine = false;
                            break;
                        }
                    }
                }
                if(!isLine)break;
            }
            if(isLine){
               double dy = sin(i * interval);
               double dx = cos(i * interval);
               if(i <= houghSpace / 4 || i >= 3 * houghSpace / 4){
                   for(int subrow = 0; subrow < h; subrow++){
                       int subcol = (int)(j - row/2 - (subrow - centerY) * dy) / dx + centerX;
                       if(subcol >= 0 && subcol < w){
                           img.setPixel(subcol, subrow, qRgb(255,0,0));
                       }
                   }
               } else {
                   for(int subcol = 0; subcol < w; subcol++){
                       int subrow = (int)(j - row/2 - (subcol - centerX) * dx) / dy + centerY;
                       if(subrow >= 0 && subrow < h){
                           img.setPixel(subcol, subrow, qRgb(255,0,0));
                       }
                   }
               }
            }
        }
    }

    for(int i = 0; i < col; i++){
        delete houghMat[i];
    }
    delete houghMat;

    return img;
}

QImage ImageOperations::houghCircleDetect(QImage img, int lo, int hi){
    int w, h;
    w = img.width();
    h = img.height();
    QImage newImage = cannyEdgeDetection(img, 50, 100);
    double houghSpace = 180;
    double interval = PI/(double)houghSpace;
    int radiusRange = hi - lo + 1;
    int ***houghMat = new int **[radiusRange];
    for(int i = 0; i < radiusRange; i++){
        houghMat[i] = new int *[w];
        for(int j = 0; j < w; j++){
            houghMat[i][j] = new int [h];
            for(int k = 0; k < h; k++){
                houghMat[i][j][k] = 0;
            }
        }
    }

    int x0, y0, v;
    double t;
    QRgb *line;
    for(int r = lo; r <= hi; r++){
        for(int j = 0; j < h; j++){
            line = (QRgb *)newImage.scanLine(j);
            for(int i = 0; i < w; i++){
                v = qBlue(line[i]);
                if(v == 0) continue;

                for(int theta = 0; theta < 360; theta++){
                    t = (double)theta * interval;
                    x0 = round(i - r * cos(t));
                    y0 = round(j - r * sin(t));
                    if(x0 >= 0 && x0 < w && y0 >= 0 && y0 < h){
                        houghMat[r-lo][x0][y0] += 1;
                    }
                }
            }
        }
    }

    int max = 0;
    for(int r = lo; r <= hi; r++){
        for(int i = 0; i < w; i++){
            for(int j = 0; j < h; j++){
                if(houghMat[r-lo][i][j] > max){
                    max = houghMat[r-lo][i][j];
                }
            }
        }
    }

    int threshold = (int)(max * 0.8);

    for(int r = lo; r <= hi; r++){
        for(int i = 0; i < w; i++){
            for(int j = 0; j < h; j++){
                int count = houghMat[r-lo][i][j];
                if(count <= threshold) continue;

                bool isCircle = true;
                for(int x = i - 1; x < i + 2; x++){
                    for(int y = j - 1; y < j + 2; y++){
                        for(int z = r - 1; z < r + 2; z++){
                            if(x >= 0 && x < w && y>= 0 && y < h && z >= lo && z <= hi){
                                if(houghMat[z-lo][x][y] > count){
                                    isCircle = false;
                                    break;
                                }
                            }
                        }
                        if(!isCircle)break;
                    }
                    if(!isCircle)break;
                }
                if(!isCircle)continue;

                QRgb red = qRgb(255,0,0);
                img.setPixel(i, j + r, red);
                img.setPixel(i, j - r, red);
                img.setPixel(i + r, j, red);
                img.setPixel(i - r, j, red);

                int r2 = r*r;
                int x = 1, y = (int)(sqrt(r2-1)+0.5);
                while(x<y){
                    img.setPixel(i + x, j + y, red);
                    img.setPixel(i + x, j - y, red);
                    img.setPixel(i - x, j + y, red);
                    img.setPixel(i - x, j - y, red);
                    img.setPixel(i + y, j + x, red);
                    img.setPixel(i + y, j - x, red);
                    img.setPixel(i - y, j + x, red);
                    img.setPixel(i - y, j - x, red);
                    x += 1;
                    y = (int)(sqrt(r2 - x*x)+0.5);
                }
                if(x==y){
                    img.setPixel(i + x, j + y, red);
                    img.setPixel(i + x, j - y, red);
                    img.setPixel(i - x, j + y, red);
                    img.setPixel(i - x, j - y, red);
                }
            }
        }
    }

    for(int i = 0; i < radiusRange; i++){
        for(int j = 0; j < w; j++){
            delete houghMat[i][j];
        }
        delete houghMat[i];
    }
    delete houghMat;

    return img;
}

QImage ImageOperations::clip(QImage img, int startX, int endX, int startY, int endY){
    int w = endX - startX + 1;
    int h = endY - startY + 1;
    QImage newImage = QImage(w, h, img.format());

    QRgb *line;
    for(int j = 0; j < h; j++){
        line = (QRgb *)img.scanLine(startY + j);
        for(int i = 0; i < w; i++){
            newImage.setPixel(i, j, line[startX + i]);
        }
    }
    return newImage;

}

QImage ImageOperations::dilation(QImage img, int size, int x, int y, int *array){
    int w = img.width();
    int h = img.height();
    QImage newImage = img.copy();
    int max, v;
    for(int j = y; j <= h - size + y; j++){
        for(int i = x; i <= w - size + x; i++){
            max = 0;
            for(int r = j - y; r < j - y + size; r++){
                for(int c = i - x; c < i - x + size; c++){
                    if(array[(r - j + y) * size + c - i + x] > 0){
                        v = qBlue(img.pixel(c, r));
                        if(v > max){
                            max = v;
                        }
                    }
                }
            }
            newImage.setPixel(i, j, qRgb(max, max, max));
        }
    }

    return newImage;
}

QImage ImageOperations::erosion(QImage img, int size, int x, int y, int *array){
    int w = img.width();
    int h = img.height();
    QImage newImage = img.copy();
    int min, v;
    for(int j = y; j <= h - size + y; j++){
        for(int i = x; i <= w - size + x; i++){
            min = 255;
            for(int r = j - y; r < j - y + size; r++){
                for(int c = i - x; c < i - x + size; c++){
                    if(array[(r - j + y) * size + c - i + x] > 0){
                        v = qBlue(img.pixel(c, r));
                        if(v < min){
                            min = v;
                        }
                    }
                }
            }
            newImage.setPixel(i, j, qRgb(min, min, min));
        }
    }

    return newImage;
}

QImage ImageOperations::opening(QImage img, int size, int x, int y, int *array){
    img = erosion(img, size, x, y, array);
    img = dilation(img, size, x, y, array);
    return img;
}

QImage ImageOperations::closing(QImage img, int size, int x, int y, int *array){
    img = dilation(img, size, x, y, array);
    img = erosion(img, size, x, y, array);
    return img;
}

QImage ImageOperations::thinning(QImage img){
    int w = img.width();
    int h = img.height();
    QImage newImage = QImage(w, h, img.format());

    int p1, p2, p3, p4, p5, p6, p7, p8, p9;
    int sum;
    bool isEnd;
    for(int n = 0; n < 5; n++){
        isEnd = true;
        newImage.fill(Qt::black);
        for(int i = 1; i < w - 1; i++){
            for(int j = 1; j < h - 1; j ++){
                p1 = qBlue(img.pixel(i, j));
                if(p1 == 0) continue;
                bool reserve = false;
                p2 = qBlue(img.pixel(i, j - 1))>0?1:0;
                p3 = qBlue(img.pixel(i + 1, j - 1))>0?1:0;
                p4 = qBlue(img.pixel(i + 1, j))>0?1:0;
                p5 = qBlue(img.pixel(i + 1, j + 1))>0?1:0;
                p6 = qBlue(img.pixel(i, j + 1))>0?1:0;
                p7 = qBlue(img.pixel(i - 1, j + 1))>0?1:0;
                p8 = qBlue(img.pixel(i - 1, j))>0?1:0;
                p9 = qBlue(img.pixel(i - 1, j - 1))>0?1:0;
                if(p2*p4*p6 != 0 || p4*p6*p8 != 0){
                    reserve = true;
                } else {
                    sum = p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9;
                    if(sum < 2 || sum > 6){
                        reserve = true;
                    } else {
                        sum = 0;
                        if(p9 == 0 && p2 == 1)sum++;
                        if(p2 == 0 && p3 == 1)sum++;
                        if(p3 == 0 && p4 == 1)sum++;
                        if(p4 == 0 && p5 == 1)sum++;
                        if(p5 == 0 && p6 == 1)sum++;
                        if(p6 == 0 && p7 == 1)sum++;
                        if(p7 == 0 && p8 == 1)sum++;
                        if(p8 == 0 && p9 == 1)sum++;
                        if(sum != 1) reserve = true;
                    }
                }
                if(reserve){
                    newImage.setPixel(i, j, qRgb(255,255,255));
                } else {
                    isEnd = false;
                    newImage.setPixel(i, j, qRgb(0, 0, 0));
                }
            }
        }
        img.fill(Qt::black);
        for(int i = 1; i < w - 1; i++){
            for(int j = 1; j < h - 1; j ++){
                p1 = qBlue(newImage.pixel(i, j));
                if(p1 == 0) continue;
                bool reserve = false;
                p2 = qBlue(newImage.pixel(i, j - 1))>0?1:0;
                p3 = qBlue(newImage.pixel(i + 1, j - 1))>0?1:0;
                p4 = qBlue(newImage.pixel(i + 1, j))>0?1:0;
                p5 = qBlue(newImage.pixel(i + 1, j + 1))>0?1:0;
                p6 = qBlue(newImage.pixel(i, j + 1))>0?1:0;
                p7 = qBlue(newImage.pixel(i - 1, j + 1))>0?1:0;
                p8 = qBlue(newImage.pixel(i - 1, j))>0?1:0;
                p9 = qBlue(newImage.pixel(i - 1, j - 1))>0?1:0;
                if(p2*p4*p8 != 0 || p2*p6*p8 != 0){
                    reserve = true;
                } else {
                    sum = p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9;
                    if(sum < 2 || sum > 6){
                        reserve = true;
                    } else {
                        sum = 0;
                        if(p9 == 0 && p2 == 1)sum++;
                        if(p2 == 0 && p3 == 1)sum++;
                        if(p3 == 0 && p4 == 1)sum++;
                        if(p4 == 0 && p5 == 1)sum++;
                        if(p5 == 0 && p6 == 1)sum++;
                        if(p6 == 0 && p7 == 1)sum++;
                        if(p7 == 0 && p8 == 1)sum++;
                        if(p8 == 0 && p9 == 1)sum++;
                        if(sum != 1) reserve = true;
                    }
                }
                if(reserve){
                    img.setPixel(i, j, qRgb(255,255,255));
                } else {
                    isEnd = false;
                    img.setPixel(i, j, qRgb(0, 0, 0));
                }
            }
        }
        if(isEnd)break;
    }
    return img;
}

QImage ImageOperations::thicking(QImage img){
    binaryReverse(img);
    img = thinning(img);
    binaryReverse(img);
    return img;
}

QImage ImageOperations::distanceTransform(QImage img){
    int w = img.width();
    int h = img.height();
    double **temp = new double *[w];
    for(int i = 0; i < w; i++){
        temp[i] = new double[h];
    }

    double min, max = 0;
    double v;
    for(int j = 0; j < h; j++){
        for(int i = 0; i < w; i++){
            if(i > 0 && i < w - 1 && j > 0 && j < h - 1){
                v = qBlue(img.pixel(i,j));
                if(v > 0){
                    min = 255;
                    if(v < min)min = v;
                    v = qBlue(temp[i-1][j]) + 1;
                    if(v < min)min = v;
                    v = qBlue(temp[i-1][j-1]) + sqrt(2);
                    if(v < min)min = v;
                    v = qBlue(temp[i][j-1]) + 1;
                    if(v < min)min = v;
                    v = qBlue(temp[i+1][j-1]) + sqrt(2);
                    if(v < min)min = v;
                    temp[i][j] = min;
                }
            } else {
                temp[i][j] = 0;
            }
        }
    }

    for(int j = h - 2; j > 0; j--){
        for(int i = w - 2; i > 0; i--){
            v = qBlue(temp[i][j]);
            if(v > 0){
                min = 255;
                if(v < min)min = v;
                v = qBlue(temp[i+1][j]) + 1;
                if(v < min)min = v;
                v = qBlue(temp[i+1][j+1]) + sqrt(2);
                if(v < min)min = v;
                v = qBlue(temp[i][j+1]) + 1;
                if(v < min)min = v;
                v = qBlue(temp[i-1][j+1]) + sqrt(2);
                if(v < min)min = v;
                temp[i][j] = min;
                if(min > max)max = min;
            }
        }
    }

    int value;
    for(int i = 0; i < w; i++){
        for(int j = 0; j < h; j++){
            value = (int)(temp[i][j] * 255 / max);
            img.setPixel(i, j, qRgb(value, value, value));
        }
    }

    for(int i = 0; i < w; i++){
        delete temp[i];
    }
    delete temp;

    return img;
}

QImage ImageOperations::skeletonization(QImage img, int size, int x, int y, int *array){
    QImage newImage;
    QImage res = QImage(img.width(), img.height(), img.format());
    res.fill(Qt::black);
    while(!isBlackImage(img)){
        img = erosion(img, size, x, y, array);
        newImage = img.copy();
        newImage = opening(newImage, size, x, y, array);
        newImage = imageSubtract(img, newImage, 1, 1);
        res = Or(newImage, res);
    }
    return res;
}

QImage ImageOperations::skeletionReconstruct(QImage img, int size, int x, int y, int *array){
    QImage newImage;
    QImage res = QImage(img.width(), img.height(), img.format());
    res.fill(Qt::black);
    int count = 0;
    std::vector<QImage>sk;
    while(!isBlackImage(img)){
        count++;
        img = erosion(img, size, x, y, array);
        newImage = img.copy();
        newImage = opening(newImage, size, x, y, array);
        newImage = imageSubtract(img, newImage, 1, 1);
        sk.push_back(newImage);
        res = Or(newImage, res);
    }
    res.fill(Qt::black);
    for(int i = 0; i < count; i++){
        img = sk[i];
        for(int j = 0; j <= i; j++){
            img = dilation(img, size, x, y, array);
        }
        res = Or(img, res);
    }
    return res;
}

QImage ImageOperations::binaryReconstruction(QImage img, int size, int x, int y, int *array){
    QImage newImage = opening(img, size, x, y, array);
    QImage res;
    while(!isSame(res, newImage)){
        res = newImage.copy();
        for(int i = 0; i < 4; i++){
            newImage = dilation(newImage, size, x, y, array);
        }
        newImage = And(newImage, img);
    }
    return res;
}

QImage ImageOperations::obr(QImage img, int size, int x, int y, int *array){
    QImage newImage = opening(img, size, x, y, array);
    newImage = grayscaleReconstruct(img, newImage, size, x, y, array);
    return newImage;
}

QImage ImageOperations::cbr(QImage img, int size, int x, int y, int *array){
    QImage newImage = closing(img, size, x, y, array);
    newImage = grayscaleReconstruct(img, newImage, size, x, y, array);
    return newImage;
}

QImage ImageOperations::watershed(QImage img){
    WatershedStructure  watershedStructure(img);

    std::queue<WatershedPixel *> pque;
    int curlab = 0;
    int heightIndex1 = 0;
    int heightIndex2 = 0;

    for (int h = 0; h < 256; ++h) {

        for (int pixelIndex = heightIndex1 ; pixelIndex < watershedStructure.size() ; ++pixelIndex) {
            WatershedPixel *p = watershedStructure.at(pixelIndex);

            if (p->getIntHeight() != h) { heightIndex1 = pixelIndex; break; }

            p->setLabelToMASK();

            std::vector<WatershedPixel *> neighbours = p->getNeighbours();
            for (unsigned i = 0 ; i < neighbours.size() ; ++i) {
                WatershedPixel *q =  neighbours.at(i);

                if (q->getLabel() >= 0) { p->setDistance(1); pque.push(p); break; }
            }
        }

        int curdist = 1;
        pque.push(new WatershedPixel());

        while (true) {
            WatershedPixel *p = pque.front(); pque.pop();

            if (p->isFICTITIOUS())
                if (pque.empty()) { delete p; p = NULL; break; }
                else {
                    pque.push(new WatershedPixel());
                    curdist++;
                    delete p; p = pque.front(); pque.pop();
                }

            std::vector<WatershedPixel *> neighbours = p->getNeighbours();
            for (unsigned i = 0 ; i < neighbours.size() ; ++i) {
                WatershedPixel *q =  neighbours.at(i);

                if ( (q->getDistance() <= curdist) &&  (q->getLabel() >= 0) ) {

                    if (q->getLabel() > 0) {
                        if ( p->isLabelMASK() )
                            p->setLabel(q->getLabel());
                        else if (p->getLabel() != q->getLabel())
                            p->setLabelToWSHED();
                    } else if (p->isLabelMASK())
                        p->setLabelToWSHED();
                } else if ( q->isLabelMASK() && (q->getDistance() == 0) ) {
                    q->setDistance( curdist + 1 );
                    pque.push(q);
                }
            }
        }

        for (int pixelIndex = heightIndex2 ; pixelIndex < watershedStructure.size() ; pixelIndex++) {
            WatershedPixel *p = watershedStructure.at(pixelIndex);
            if (p->getIntHeight() != h) { heightIndex2 = pixelIndex; break; }

            p->setDistance(0);

            if (p->isLabelMASK()) {
                curlab++;
                p->setLabel(curlab);
                pque.push(p);

                while (!pque.empty()) {
                    WatershedPixel *q = pque.front();
                    pque.pop();

                    std::vector<WatershedPixel *> neighbours = q->getNeighbours();

                    for (unsigned i = 0 ; i < neighbours.size() ; i++) {
                        WatershedPixel *r =  neighbours.at(i);

                        if ( r->isLabelMASK() ) { r->setLabel(curlab); pque.push(r); }
                    }
                }
            }
        }
    }
    for (int pixelIndex = 0 ; pixelIndex < watershedStructure.size() ; pixelIndex++) {
        WatershedPixel *p = watershedStructure.at(pixelIndex);

        if (p->isLabelWSHED() && !p->allNeighboursAreWSHED()) {
            img.setPixelColor(p->getX(), p->getY(), Qt::red);
        }
    }

    return img;
}

QImage ImageOperations::linearContrastAdjust(QImage img, int x1, int y1, int x2, int y2){
    int *corres = new int[256];
    for(int i = 0; i < 256; i++){
        if(i <= x1){
            corres[i] = y1;
        } else if(i > x2){
            corres[i] = y2;
        } else {
            corres[i] = (y2 - y1) * (i - x1) / (x2 - x1) + y1;
        }
    }
    grayValueTransfer(img, corres);
    delete corres;
    return img;
}

QImage ImageOperations::pieceLinContrastAdjust(QImage img, int x1, int y1, int x2, int y2){
    int *corres = new int[256];
    corres[0] = 0;
    corres[255] = 255;
    for(int i = 1; i < 255; i++){
        if(i <= x1){
            corres[i] = y1 * i / x1;
        } else if(i > x2){
            corres[i] = (255 - y2) * (i - x2) / (255 - x2) + y2;
        } else {
            corres[i] = (y2 - y1) * (i - x1) / (x2 - x1) + y1;
        }
    }
    grayValueTransfer(img, corres);
    delete corres;
    return img;
}

QImage ImageOperations::logContrastAdjust(QImage img, double a, double b){
    int *corres = new int[256];
    for(int i = 0; i < 256; i++){
        int j = a + log(i + 1) / b;
        if(j < 0) corres[i] = 0;
        else if(j >= 255) corres[i] = 255;
        else corres[i] = j;
    }
    grayValueTransfer(img, corres);
    delete corres;
    return img;
}

QImage ImageOperations::expContrastAdjust(QImage img, double a, double b){
    int *corres = new int[256];
    for(int i = 0; i < 256; i++){
        int j = exp(b * (i - a)) - 1;
        if(j < 0) corres[i] = 0;
        else if(j >= 255) corres[i] = 255;
        else corres[i] = j;
    }
    grayValueTransfer(img, corres);
    delete corres;
    return img;
}

QImage ImageOperations::histogramEqualization(QImage img, int *histo){
    int w = img.width();
    int h = img.height();
    int size = w * h;
    int *corres = new int[256];
    double cur = 0;
    for(int i = 0; i < 256; i++){
        cur += (double)histo[i] / size;
        corres[i] = cur * 255;
    }
    grayValueTransfer(img, corres);
    delete corres;
    return img;
}

QImage ImageOperations::colorLevel(QImage img, PColorLevelData clData){
    int w = img.width();
    int h = img.height();
    unsigned char clTables[3][256];
    if(checkColorLevelData(clData, clTables)){
        QRgb *line;
        int red, green, blue;
        QRgb color;
        for(int j = 0; j < h; j++){
            line = (QRgb *)img.scanLine(j);
            for(int i = 0; i < w; i++){
                color = line[i];
                blue = clTables[0][qBlue(color)];
                green = clTables[1][qGreen(color)];
                red = clTables[2][qRed(color)];
                img.setPixel(i, j, qRgb(red, green, blue));
            }
        }
    }
    return img;
}

bool ImageOperations::getColorLevelTable(PColorLevelItem item, unsigned char *clTable){
    int diff = (int)(item->Highlight - item->Shadow);
        int outDiff = (int)(item->OutHighlight - item->OutShadow);

        if (!((item->Highlight <= 255 && diff < 255 && diff >= 2) ||
            (item->OutShadow <= 255 && item->OutHighlight <= 255 && outDiff < 255) ||
            (!(item->Midtones > 9.99 && item->Midtones > 0.1) && item->Midtones != 1.0)))
            return false;

        double coef = 255.0 / diff;
        double outCoef = outDiff / 255.0;
        double exponent = 1.0 / item->Midtones;

        for (int i = 0; i < 256; i++){
            int v;
            if (clTable[i] <= (unsigned char)item->Shadow)
                v = 0;
            else{
                v = (int)((clTable[i] - item->Shadow) * coef + 0.5);
                if (v > 255)
                    v = 255;
            }
            v = (int)(pow(v / 255.0, exponent) * 255.0 + 0.5);
            clTable[i] = (unsigned char)(v * outCoef + item->OutShadow + 0.5);
        }

        return true;
}

bool ImageOperations::checkColorLevelData(PColorLevelData clData, unsigned char clTables[][256]){
    bool result = false;
        int i, j;
        for (i = 0; i < 3; i++){
            for (j = 0; j < 256; j++)
                clTables[i][j] = (unsigned char)j;
        }

        PColorLevelItem item = &clData->Blue;
        for (i = 0; i < 3; i++, item++){
            if (getColorLevelTable(item, clTables[i]))
                result = true;
        }
        for (i = 0; i < 3; i++){
            if (!getColorLevelTable(item, clTables[i]))
                break;
            result = true;
        }

        return result;
}

void ImageOperations::grayValueTransfer(QImage &img, int *corres){
    int w = img.width();
    int h = img.height();
    int v;
    QRgb *line;
    QColor color;
    for(int j = 0; j < h; j++){
        line = (QRgb *)img.scanLine(j);
        for(int i = 0; i < w; i++){
            color = QColor(line[i]);
            v = color.lightness();
            color.setHsl(color.hslHue(), color.hslSaturation(), corres[v]);
            img.setPixelColor(i ,j ,color);
        }
    }
}

QImage ImageOperations::grayscaleReconstruct(QImage img, QImage marker, int size, int x, int y, int *array){
    QImage res;
    while(!isSame(res, marker)){
        res = marker.copy();
        marker = dilation(marker, size, x, y, array);
        marker = And(marker, img);
    }
    return res;
}

QImage ImageOperations::Or(QImage &img1, QImage &img2){
    int w = img1.width();
    int h = img1.height();
    QImage newImage = QImage(w, h, img1.format());

    int max;
    QRgb *line1, *line2;
    for(int j = 0; j < h; j++){
        line1 = (QRgb *)img1.scanLine(j);
        line2 = (QRgb *)img2.scanLine(j);
        for(int i = 0; i < w; i++){
            if(qBlue(line1[i]) >= qBlue(line2[i])){
                max = qBlue(line1[i]);
            } else {
                max = qBlue(line2[i]);
            }
            newImage.setPixel(i, j, qRgb(max, max, max));
        }
    }
    return newImage;
}

QImage ImageOperations::And(QImage &img1, QImage &img2){
    int w = img1.width();
    int h = img1.height();
    QImage newImage = QImage(w, h, img1.format());

    int min;
    QRgb *line1, *line2;
    for(int j = 0; j < h; j++){
        line1 = (QRgb *)img1.scanLine(j);
        line2 = (QRgb *)img2.scanLine(j);
        for(int i = 0; i < w; i++){
            if(qBlue(line1[i]) <= qBlue(line2[i])){
                min = qBlue(line1[i]);
            } else {
                min = qBlue(line2[i]);
            }
            newImage.setPixel(i, j, qRgb(min, min, min));
        }
    }
    return newImage;
}

bool ImageOperations::isSame(QImage &img1, QImage &img2){
    if(img1.isNull() && !img2.isNull()
            || !img1.isNull() && img2.isNull()){
        return false;
    }
    int w1 = img1.width();
    int h1 = img1.height();
    int w2 = img2.width();
    int h2 = img2.height();
    if(w1 != w2 || h1 != h2){
        return false;
    }

    QRgb *line1, *line2;
    for(int j = 0; j < h1; j++){
        line1 = (QRgb *)img1.scanLine(j);
        line2 = (QRgb *)img2.scanLine(j);
        for(int i = 0; i < w1; i++){
            if(line1[i]!=line2[i])return false;
        }
    }
    return true;
}

void ImageOperations::binaryReverse(QImage &img){
    int w = img.width();
    int h = img.height();

    QRgb *line;
    QRgb pix;
    for(int j = 0; j < h; j++){
        line = (QRgb *)img.scanLine(j);
        for(int i = 0; i < w; i++){
            pix = line[i];
            if(pix == qRgb(0,0,0)){
                img.setPixel(i, j, qRgb(255,255,255));
            } else {
                img.setPixel(i,j,qRgb(0,0,0));
            }
        }
    }
}

bool ImageOperations::isBinaryImage(QImage &img){
    int w = img.width();
    int h = img.height();

    QRgb *line;
    QRgb pix;
    for(int j = 0; j < h; j++){
        line = (QRgb *)img.scanLine(j);
        for(int i = 0; i < w; i++){
            pix = line[i];
            if(pix!=qRgb(0, 0, 0) && pix!=qRgb(255,255,255)){
                return false;
            }
        }
    }
    return true;
}

bool ImageOperations::isGrayImage(QImage &img){
    int w = img.width();
    int h = img.height();

    QRgb *line;
    QRgb pix;
    for(int j = 0; j < h; j++){
        line = (QRgb *)img.scanLine(j);
        for(int i = 0; i < w; i++){
            pix = line[i];
            if(qRed(pix)!=qGreen(pix) || qRed(pix)!=qBlue(pix)){
                return false;
            }
        }
    }
    return true;
}

bool ImageOperations::isBlackImage(QImage &img){
    int w = img.width();
    int h = img.height();

    QRgb *line;
    QRgb pix;
    for(int j = 0; j < h; j++){
        line = (QRgb *)img.scanLine(j);
        for(int i = 0; i < w; i++){
            pix = line[i];
            if(pix != qRgb(0, 0, 0)){
                return false;
            }
        }
    }
    return true;
}

bool ImageOperations::isWhiteImage(QImage &img){
    int w = img.width();
    int h = img.height();

    QRgb *line;
    QRgb pix;
    for(int j = 0; j < h; j++){
        line = (QRgb *)img.scanLine(j);
        for(int i = 0; i < w; i++){
            pix = line[i];
            if(pix != qRgb(255, 255, 255)){
                return false;
            }
        }
    }
    return true;
}

static void swap(unsigned int *array, int left, int right){
    unsigned int temp = array[left];
    array[left] = array[right];
    array[right] = temp;
}

static unsigned int partition(unsigned int *array, int left, int right){
    if(left > right) return -1;
    int pos = right;
    right--;
    while(left <= right){
        while(left<pos && array[left]<=array[pos]) left++;
        while(right>left && array[right]>array[pos]) right--;
        if(left >= right) break;
        swap(array, left, right);
    }

    swap(array, left, pos);
    return left;
}

unsigned int ImageOperations::median(unsigned int *array,int left, int right){
    if(array== NULL) return 0;
    int midIndex = right >> 1;
    int index = -1;
    while(index != midIndex){
        index = partition(array, left, right);
        if(index < midIndex) left = index + 1;
        else if (index > midIndex) right = index - 1;
        else break;
    }
    return array[index];
}
