/*
 * File: type.h
 * Version: 1.0
 * Author: kk
 * Created Date: Wed Jul 18 13:32:01 DST 2018
 * -------------------------------------------
 * 所有的命令/属性都用一个相应的枚举变量区分。
 * 属性也使用枚举变量
 * 每增加一个command, 就在相应的枚举变量后面增加一个值
 */

#pragma once


enum commandsType{
    OPEN_FILE,
    SAVE_FILE,
    FILTER,
    EDGE_DETECTION,
    HOUGH_CIRCLE_DETECTION,
    CHANNEL,
    RED_CHANNEL,
    GREEN_CHANNEL,
    BLUE_CHANNEL,
    HOUGH_LINE_DETECTION,
    GRAY_SCALE_TRANSFER,
    OTSU,
    OPEN_SUB_DIALOG,
    DUAL_THRESHOLD,
    HUE_SATURA_LIGHT,
};

enum propertyType{
    MAIN_IMAGE,
    SUB_IMAGE,
    LOG,
};

enum ChannelType{
    RED,
    GREEN,
    BLUE,
};
