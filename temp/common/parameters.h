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

class Parameters
{
public:
    Parameters() = default;
};


class PathParameters: public Parameters
{
private:
    std::string path;
public:
    PathParameters(const std::string &path):
        path(path)
    {}
    std::string get_path(){ return path;}
};

class brightAndContrastParameters: public Parameters
{
private:
    int nBright;
    int nContrast;
public:
    brightAndContrastParameters(int bright = 0, int contrast = 100):
        nBright(bright), nContrast(contrast)
    {}

    int get_nBright(){return nBright;}
    int get_nContrast(){return nContrast;}
};

class IntParameters :public Parameters 
{
private:
    int value;
public:
    IntParameters(int value):
        value(value)
    {}
    void setvalue(int v) { value = v; }
    int getvalue() { return value; }
};

class MouseMoveParameters: public Parameters 
{
private:
    double x_s;
    double y_s;
    double x_e;
    double y_e;
public:
    MouseMoveParameters():
        x_s(0), y_s(0), x_e(0), y_e(0) 
    {}

    void set_start_pnt(double vx_s, double vy_s) { x_s = vx_s; y_s = vy_s; }
    void set_end_pnt(double vx_e, double vy_e) { x_e = vx_e; y_e = vy_e; }
    double getx_s() { return x_s; }
    double gety_s() { return y_s; }
    double getx_e() { return x_e; }
    double gety_e() { return y_e; }
};


