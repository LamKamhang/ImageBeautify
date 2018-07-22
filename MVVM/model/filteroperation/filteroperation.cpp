#include "../model.h"
#include "../filters/art_effect.h"
#include "../filters/classic_effect.h"
#include "../../common/util.h"

// 浮雕
void Model::_emboss()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ArtEffect::_emboss(src, dst);
    subImg = Tools::Mat2QImage(dst);
    tmpImg = subImg.copy();
	Fire_OnPropertyChanged(SUB_IMAGE);
}

// 雕刻
void Model::_sculpture()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ArtEffect::_sculpture(src, dst);
	subImg = Tools::Mat2QImage(dst);
    tmpImg = subImg.copy();
	Fire_OnPropertyChanged(SUB_IMAGE);
}

// 虚幻
void Model::_dilate()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ArtEffect::_dilate(src, dst);
	subImg = Tools::Mat2QImage(dst);
    tmpImg = subImg.copy();
	Fire_OnPropertyChanged(SUB_IMAGE);
}

// 惊悚
void Model::_erode()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ArtEffect::_erode(src, dst);
	subImg = Tools::Mat2QImage(dst);
    tmpImg = subImg.copy();
	Fire_OnPropertyChanged(SUB_IMAGE);
}

// 磨砂玻璃
void Model::_frostGlass()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ArtEffect::_frostGlass(src, dst);
	subImg = Tools::Mat2QImage(dst);
    tmpImg = subImg.copy();
	Fire_OnPropertyChanged(SUB_IMAGE);
}

// 手稿
void Model::_sketch()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ArtEffect::_sketch(src, dst);
	subImg = Tools::Mat2QImage(dst);
    tmpImg = subImg.copy();
	Fire_OnPropertyChanged(SUB_IMAGE);
}

// 油画
void Model::_oilPaint()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ArtEffect::_oilPaint(src, dst);
	subImg = Tools::Mat2QImage(dst);
    tmpImg = subImg.copy();
	Fire_OnPropertyChanged(SUB_IMAGE);
}

// 木刻
void Model::_woodCut()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ArtEffect::_woodCut(src, dst);
	subImg = Tools::Mat2QImage(dst);
    tmpImg = subImg.copy();
	Fire_OnPropertyChanged(SUB_IMAGE);
}

// 反色
void Model::_inverted()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ArtEffect::_inverted(src, dst);
	subImg = Tools::Mat2QImage(dst);
    tmpImg = subImg.copy();
	Fire_OnPropertyChanged(SUB_IMAGE);
}

// 回忆
void Model::_memory()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ArtEffect::_memory(src, dst);
	subImg = Tools::Mat2QImage(dst);
    tmpImg = subImg.copy();
	Fire_OnPropertyChanged(SUB_IMAGE);
}

// 冰冻
void Model::_freezing()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ArtEffect::_freezing(src, dst);
	subImg = Tools::Mat2QImage(dst);
    tmpImg = subImg.copy();
	Fire_OnPropertyChanged(SUB_IMAGE);
}

// 熔铸
void Model::_casting()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ArtEffect::_casting(src, dst);
	subImg = Tools::Mat2QImage(dst);
    tmpImg = subImg.copy();
	Fire_OnPropertyChanged(SUB_IMAGE);
}

// 黑白漫画
void Model::_comicStrip()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ArtEffect::_comicStrip(src, dst);
	subImg = Tools::Mat2QImage(dst);
    tmpImg = subImg.copy();
	Fire_OnPropertyChanged(SUB_IMAGE);
}


//锐化
void Model::_sharpen()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ClassicEffect::_sharpen(src, dst);
    subImg = Tools::Mat2QImage(dst);
    tmpImg = subImg.copy();
    Fire_OnPropertyChanged(SUB_IMAGE);
}

//黑白
void Model::_colortoblack()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ClassicEffect::_colortoblack(src, dst);
    subImg = Tools::Mat2QImage(dst);
    tmpImg = subImg.copy();
    Fire_OnPropertyChanged(SUB_IMAGE);
}

//去雾气
void Model::_defog()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ClassicEffect::_defog(src, dst);
    subImg = Tools::Mat2QImage(dst);
    tmpImg = subImg.copy();
    Fire_OnPropertyChanged(SUB_IMAGE);
}

//柔和
void Model::_soft()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ClassicEffect::_soft(src, dst);
    subImg = Tools::Mat2QImage(dst);
    tmpImg = subImg.copy();
    Fire_OnPropertyChanged(SUB_IMAGE);
}

//均衡图
void Model::_balance()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ClassicEffect::_balance(src, dst);
    subImg = Tools::Mat2QImage(dst);
    tmpImg = subImg.copy();
    Fire_OnPropertyChanged(SUB_IMAGE);
}

//怀旧
void Model::_nostalgia()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ClassicEffect::_nostalgia(src, dst);
    subImg = Tools::Mat2QImage(dst);
    tmpImg = subImg.copy();
    Fire_OnPropertyChanged(SUB_IMAGE);
}

//连环画
void Model::_BlackComic()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ClassicEffect::_BlackComic(src, dst);
    subImg = Tools::Mat2QImage(dst);
    tmpImg = subImg.copy();
    Fire_OnPropertyChanged(SUB_IMAGE);
}

//时光隧道
void Model::_timetuunel()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ClassicEffect::_timetuunel(src, dst);
    subImg = Tools::Mat2QImage(dst);
    tmpImg = subImg.copy();
    Fire_OnPropertyChanged(SUB_IMAGE);
}

//经典lomo
void Model::_classiclomo()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ClassicEffect::_classiclomo(src, dst);
    subImg = Tools::Mat2QImage(dst);
    tmpImg = subImg.copy();
    Fire_OnPropertyChanged(SUB_IMAGE);
}

// 美白
void Model::_whiteFace()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ClassicEffect::_whiteFace(src, dst);
    subImg = Tools::Mat2QImage(dst);
    tmpImg = subImg.copy();
    Fire_OnPropertyChanged(SUB_IMAGE);
}

// 美颜
void Model::_beautifyFace()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ClassicEffect::_beautifyFace(src, dst);
    subImg = Tools::Mat2QImage(dst);
    tmpImg = subImg.copy();
    Fire_OnPropertyChanged(SUB_IMAGE);
}

// 粉红佳人
void Model::_pinkLady()
{
    cv::Mat src = Tools::QImage2Mat(mainImg);
    cv::Mat dst;
    ClassicEffect::_pinkLady(src, dst);
    subImg = Tools::Mat2QImage(dst);
    tmpImg = subImg.copy();
    Fire_OnPropertyChanged(SUB_IMAGE);
}
