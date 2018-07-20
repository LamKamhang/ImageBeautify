
/*
 * File: aux_log_alg.h
 * Version: 1.0
 * Author: kk
 * Created Date: Fri Jul 20 13:23:58 DST 2018
 * -------------------------------------------
 * 日志基本操作辅助类
 */

#pragma once

#include <stdlib.h>
#include <QImage>
#include <vector>

struct Commit {
    QImage before;
    QString info;
    Commit(QImage image, QString str)
        : before(image)
        , info(str){}
};

class Log
{
public:
    Log();
    ~Log();
    QImage redo();
    QImage undo(QImage *curImg);
    QString getRedoMsg();
    QString getUndoMsg();
    void commit(QImage image, QString str);
    bool redoEnabled();
    bool undoEnabled();
    void clear();
private:
    std::vector<Commit *> commits;
    int curPos;  //目前所处的位置
    QImage imgFinalState;
    void freeCommits(int i);
    void addCommit(Commit *commit);
    QImage getImgBeforeOperation();
    QImage getImgAfterOperation();
    QString getLastOperation();
    QString getNextOperation();
};
