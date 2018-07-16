#ifndef LOG_H
#define LOG_H

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

#endif // LOG_H
