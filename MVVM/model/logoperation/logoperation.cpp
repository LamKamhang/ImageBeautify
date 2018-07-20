#include "../model.h"
#include "aux_log_alg.h"
#include <QDebug>
bool Model::redo()
{
    if (log.redoEnabled())
    {
        QImage tmp = log.redo();
        mainImg = tmp;
        Fire_OnPropertyChanged(MAIN_IMAGE);
        Fire_OnPropertyChanged(LOG);
        return true;
    }
    else
    {
        return false;
    }
}

bool Model::undo()
{
    if (log.undoEnabled())
    {
        QImage tmp = log.undo(&mainImg);
        qDebug()<<"tmp.save()  "
               <<tmp.save(QString("/Users/huangwencan/gui/tmp.png"));
        mainImg = tmp;
        Fire_OnPropertyChanged(MAIN_IMAGE);
        Fire_OnPropertyChanged(LOG);
        return true;
    }
    else
    {
        return false;
    }
}

QString Model::getRedoMsg()
{
    return log.getRedoMsg();
}

QString Model::getUndoMsg()
{
    return log.getUndoMsg();
}

bool Model::commit(const QString &cmd)
{
    log.commit(mainImg, cmd);
    Fire_OnPropertyChanged(LOG);
    return true;
}

bool Model::redoEnabled()
{
    return log.redoEnabled();
}

bool Model::undoEnabled()
{
    return log.undoEnabled();
}

bool Model::clear()
{
    log.clear();
    return true;
}
