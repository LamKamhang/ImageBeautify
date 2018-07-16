#pragma once
#include <iostream>
#include <string>

class ErrorMsg
{
public:
    ErrorMsg():
        msg("ERROR::Unkonwn RunTime Error!")
    {
    }

    ErrorMsg(const std::string &msg):
        msg("ERROR::" + msg)
    {
    }

    const std::string& what() const
    {
		return msg;
    }
private:
    std::string msg;
};
