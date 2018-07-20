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
#include "type.h"
#include <QString>

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
