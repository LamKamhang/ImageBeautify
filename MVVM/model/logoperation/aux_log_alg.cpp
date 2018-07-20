#include "aux_log_alg.h"

Log::Log(){
    curPos = -1;
    commits.clear();
}

Log::~Log(){
    auto size = commits.size();
    for(size_t i = 0; i < size; i++){
        delete commits[i];
    }
    commits.clear();
}

void Log::commit(QImage image, QString str){
    if(redoEnabled()) {
        freeCommits(curPos + 1);
    }
    Commit *newCommit = new Commit(image, str);
    addCommit(newCommit);
}

QImage Log::undo(QImage *curImg){
    if(!undoEnabled()){ //不能撤销
        return QImage();
    }
    if(!redoEnabled()){  //记录最后一次操作后的图像
        imgFinalState = *curImg;
    }
    QImage res = getImgBeforeOperation();
    curPos--;
    return res;
}

QImage Log::redo(){
    if(!redoEnabled()){
        return QImage();
    }
    curPos++;
    return getImgAfterOperation();
}

QString Log::getUndoMsg(){
    if(!undoEnabled()){
        return NULL;
    }
    return getLastOperation();
}

QString Log::getRedoMsg(){
    if(!redoEnabled()){
        return NULL;
    }
    return getNextOperation();
}

bool Log::undoEnabled(){
    return curPos >= 0;
}

bool Log::redoEnabled(){
    return commits.size() > (unsigned)curPos + 1;
}

void Log::freeCommits(int i){
    auto size = commits.size();
    for(size_t j = i; j < size; j++){
        delete commits[j];
    }
    commits.erase(commits.begin() + i, commits.end());
}

void Log::addCommit(Commit *commit){
    commits.push_back(commit);
    curPos++;
}

QImage Log::getImgBeforeOperation(){
    Commit *commit = commits[curPos];
    return commit->before;
}

QImage Log::getImgAfterOperation(){
    if((unsigned)curPos + 1 < commits.size()){
        Commit *commit = commits[curPos + 1];
        return commit->before;
    }
    return imgFinalState;
}

QString Log::getLastOperation(){
    Commit *commit = commits[curPos];
    return commit->info;
}

QString Log::getNextOperation(){
    if((unsigned)curPos + 1 < commits.size()){
        Commit *commit = commits[curPos + 1];
        return commit->info;
    }
    return NULL;
}

void Log::clear(){
    curPos = -1;
    commits.clear();
}
