#include "../model.h"
#include "../filters/art_effect.h"

// 浮雕
void Model::_emboss()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ArtEffect::_emboss(src, dst);
	subImg = Tools::Mat2QImage(dst);
	Fire_OnPropertyChanged(SUB_IMAGE);
}

// 雕刻
void Model::_sculpture()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ArtEffect::_sculpture(src, dst);
	subImg = Tools::Mat2QImage(dst);
	Fire_OnPropertyChanged(SUB_IMAGE);
}

// 虚幻
void Model::_dilate()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ArtEffect::_dilate(src, dst);
	subImg = Tools::Mat2QImage(dst);
	Fire_OnPropertyChanged(SUB_IMAGE);
}

// 惊悚
void Model::_erode()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ArtEffect::_erode(src, dst);
	subImg = Tools::Mat2QImage(dst);
	Fire_OnPropertyChanged(SUB_IMAGE);
}

// 磨砂玻璃
void Model::_frostGlass()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ArtEffect::_frostGlass(src, dst);
	subImg = Tools::Mat2QImage(dst);
	Fire_OnPropertyChanged(SUB_IMAGE);
}

// 手稿
void Model::_sketch()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ArtEffect::_sketch(src, dst);
	subImg = Tools::Mat2QImage(dst);
	Fire_OnPropertyChanged(SUB_IMAGE);
}

// 油画
void Model::_oilPaint()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ArtEffect::_oilPaint(src, dst);
	subImg = Tools::Mat2QImage(dst);
	Fire_OnPropertyChanged(SUB_IMAGE);
}

// 木刻
void Model::_woodCut()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ArtEffect::_woodCut(src, dst);
	subImg = Tools::Mat2QImage(dst);
	Fire_OnPropertyChanged(SUB_IMAGE);
}

// 反色
void Model::_inverted()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ArtEffect::_inverted(src, dst);
	subImg = Tools::Mat2QImage(dst);
	Fire_OnPropertyChanged(SUB_IMAGE);
}

// 回忆
void Model::_memory()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ArtEffect::_memory(src, dst);
	subImg = Tools::Mat2QImage(dst);
	Fire_OnPropertyChanged(SUB_IMAGE);
}

// 冰冻
void Model::_freezing()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ArtEffect::_freezing(src, dst);
	subImg = Tools::Mat2QImage(dst);
	Fire_OnPropertyChanged(SUB_IMAGE);
}

// 熔铸
void Model::_casting()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ArtEffect::_casting(src, dst);
	subImg = Tools::Mat2QImage(dst);
	Fire_OnPropertyChanged(SUB_IMAGE);
}

// 黑白漫画
void Model::_comicStrip()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ArtEffect::_comicStrip(src, dst);
	subImg = Tools::Mat2QImage(dst);
	Fire_OnPropertyChanged(SUB_IMAGE);
}
