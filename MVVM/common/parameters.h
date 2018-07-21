/*
 * File: parameters.h
 * Version: 1.0
 * Author: kk
 * Created Date: Tue Jul 17 21:56:41 DST 2018
 * -------------------------------------------
 * 参数基类与派生类的声明
 *  - 所有参数类都要继承parameters这个工厂类
 */

#pragma once

#include <string>
#include <map>
#include <vector>

#include "type.h"
#include <QString>
#include <QVector>
#include <QPoint>

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


class ParametersBase
{
public:
    ParametersBase() = default;
};

class JsonParameters
    : public ParametersBase
{
public:
    void insert(const std::string &key,std::shared_ptr<ParametersBase>value){
        data.insert(std::make_pair(key,value));
    }

    std::shared_ptr<ParametersBase> operator [](const std::string&key){
        if(data.find(key) != data.end())
            return data[key];
        else return std::make_shared<ParametersBase>();
    }
private:
    std::map<std::string,std::shared_ptr<ParametersBase> > data;
};

class StringParameters
    : public ParametersBase
{
public:
    StringParameters(const std::string& value)
        : value(value)
    {}
    void setvalue(std::string s){value = s;}
    std::string getvalue(){return value;}
private:
    std::string value;
};

class QStringParameters
    : public ParametersBase
{
public:
    QStringParameters(const QString& value)
        : value(value)
    {}
    void setvalue(QString s){value = s;}
    QString getvalue(){return value;}
private:
    QString value;
};

template <class T>
class QVectorParameters
    : public ParametersBase
{
public:
    QVectorParameters(const QVector<T>& value)
        : value(value)
    {}
    void setvalue(QVector<T> v){
        QVector<T> tmp(v);
        value = tmp;
    }
    QVector<T> getvalue(){ return value; }
private:
    QVector<T> value;
};

class QPointParameters
    : public ParametersBase
{
public:
    QPointParameters(const QPoint& value)
        : value(value)
    {}
    void setvalue(QPoint v){
        QPoint tmp(v);
        value = tmp;
    }
    QPoint getvalue(){ return value; }
private:
    QPoint value;
};

//typedef struct
//{
//    int Shadow;
//    float Midtones;
//    int Highlight;
//    int OutShadow;
//    int OutHighlight;
//}ColorLevelItem, *PColorLevelItem;

//typedef struct
//{
//    ColorLevelItem Blue;
//    ColorLevelItem Green;
//    ColorLevelItem Red;
//    ColorLevelItem RGB;
//}ColorLevelData, *PColorLevelData;

class ColorLevelDataParameters
    : public ParametersBase
{
public:
    ColorLevelDataParameters(const ColorLevelData& value)
        : value(value)
    {}
    void setvalue(ColorLevelData v){
        ColorLevelData tmp(v);
        value = tmp;
    }
    ColorLevelData getvalue(){ return value; }
private:
    ColorLevelData value;
};




class BoolParameters
    :public ParametersBase
{
public:
    BoolParameters(bool value)
        :value(value)
    {}
    void setvalue(bool v){value = v;}
    bool getvalue(){return value;}
private:
    bool value;
};

class IntParameters
    : public ParametersBase
{
public:
    IntParameters(int value):
        value(value)
    {}
    void setvalue(int v) { value = v; }
    int getvalue() { return value; }
private:
    int value;
};

class FloatParameters
    : public ParametersBase
{
public:
    FloatParameters(float value):
        value(value)
    {}
    void setvalue(float v) { value = v; }
    float getvalue() { return value; }
private:
    float value;
};

class DoubleParameters
    : public ParametersBase
{
public:
    DoubleParameters(double value):
        value(value)
    {}
    void setvalue(double v){ value = v; }
    double getvalue() { return value; }
private:
    double value;
};

class EnumCommandParameters
    : public ParametersBase
{
public:
    EnumCommandParameters(enum commandsType type):
        value(type)
    {}
    void setvalue(enum commandsType type){ value = type; }
    enum commandsType getvalue() { return value; }
private:
    enum commandsType value;
};

template<typename T>
class VectorParameters
    : public ParametersBase
{
public:
    VectorParameters(const std::vector<T> &value):
        value(value)
    {}
    void setvalue(const std::vector<T> &value){this->value = value; }
    std::vector<T> getvalue() {return value; }
private:
    std::vector<T> value;
};
