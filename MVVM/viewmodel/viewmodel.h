#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QImage>
#include <QString>
#include <memory>
#include "../model/model.h"
#include "../common/etlbase.h"
#include "../common/type.h"
#include "commands/openfilecommand.h"
#include "commands/savefilecommand.h"
#include "commands/opensubdialogcommand.h"
#include "commands/undocommand.h"
#include "commands/redocommand.h"
#include "commands/filtercommand.h"
#include "commands/edgedetectioncommand.h"
#include "commands/houghcircledetectioncommand.h"
#include "commands/channelcommand.h"
#include "commands/grayscaletransfercommand.h"
#include "commands/houghlinedetectioncommand.h"
#include "commands/otsucommand.h"
#include "commands/dualthresholdcommand.h"
#include "commands/huesaturalightcommand.h"

#include "sinks/viewmodelsink.h"
#include <opencv2/opencv.hpp>
using namespace cv;

class OpenFileCommand;
class SaveFileCommand;
class OpenSubDialogCommand;
class UndoCommand;
class RedoCommand;
class FilterCommand;
class EdgeDetectionCommand;
class HoughCircleDetectionCommand;
class ChannelCommand;
class OtsuCommand;
class HoughLineDetectionCommand;
class GrayScaleTransferCommand;
class DualThresholdCommand;
class HueSaturaLightCommand;

class ViewModel
    : public Proxy_PropertyNotification<ViewModel>
    , public Proxy_CommandNotification<ViewModel>
{
public:
    ViewModel();
    ~ViewModel(){}
    void bindModel(std::shared_ptr<Model> model);// binding model
    void execOpenFileCommand(const QString &path);
    void execSaveFileCommand(const QString &path);
    void execOpenSubDialogCommand();
    void execUndoCommand();
    void execRedoCommand();

    void execFilterCommand(std::shared_ptr<JsonParameters> json);
    void execEdgeDetectionCommand(std::shared_ptr<JsonParameters> json);
    void execHoughCircleDetectionCommand(std::shared_ptr<JsonParameters> json);
    void execChannelCommand(std::shared_ptr<EnumCommandParameters> type);
    void execHoughLineDetectionCommand();
    void execGrayScaleTransferCommand();
    void execOtsuCommand();
    void execDualThresholdCommand(std::shared_ptr<JsonParameters> json);
    void execHueSaturaLightCommand(std::shared_ptr<JsonParameters> json);

    std::shared_ptr<ICommandBase> getOpenFileCommand();
    std::shared_ptr<ICommandBase> getSaveFileCommand();
    std::shared_ptr<ICommandBase> getOpenSubDialogCommand();
    std::shared_ptr<ICommandBase> getUndoCommand();
    std::shared_ptr<ICommandBase> getRedoCommand();

    std::shared_ptr<ICommandBase> getFilterCommand();
    std::shared_ptr<ICommandBase> getEdgeDetectionCommand();
    std::shared_ptr<ICommandBase> getHoughCircleDetectionCommand();
    std::shared_ptr<ICommandBase> getChannelCommand();
    std::shared_ptr<ICommandBase> getGrayScaleTransferCommand();
    std::shared_ptr<ICommandBase> getOtsuCommand();
    std::shared_ptr<ICommandBase> getHoughLineDetectionCommand();
    std::shared_ptr<ICommandBase> getDualThresholdCommand();
    std::shared_ptr<ICommandBase> getHueSaturaLightCommand();

    std::shared_ptr<QImage> getImage();
    std::shared_ptr<QImage> getSubImage();
    std::shared_ptr<bool> getUndoEnabled();
    std::shared_ptr<bool> getRedoEnabled();
    std::shared_ptr<QString> getUndoMsg();
    std::shared_ptr<QString> getRedoMsg();

    void setImageFromModel();
    void setSubImageFromModel();
    void updateLogManagerFromModel();

private:
    std::shared_ptr<QImage> image;
    std::shared_ptr<QImage> subimage;
    std::shared_ptr<Model> model;

    std::shared_ptr<bool> undoEnabled;
    std::shared_ptr<bool> redoEnabled;
    std::shared_ptr<QString> undoMsg;
    std::shared_ptr<QString> redoMsg;

    std::shared_ptr<ViewModelSink> viewModelSink;

    std::shared_ptr<OpenFileCommand> openfilecommand;
    std::shared_ptr<SaveFileCommand> savefilecommand;
    std::shared_ptr<OpenSubDialogCommand> opensubdialogcommand;
    std::shared_ptr<UndoCommand> undocommand;
    std::shared_ptr<RedoCommand> redocommand;

    std::shared_ptr<FilterCommand> filtercommand;
    std::shared_ptr<EdgeDetectionCommand> edgedetectioncommand;
    std::shared_ptr<HoughCircleDetectionCommand> houghcircledetectioncommand;
    std::shared_ptr<ChannelCommand> channelcommand;
    std::shared_ptr<GrayScaleTransferCommand> grayscaletransfercommand;
    std::shared_ptr<OtsuCommand> otsucommand;
    std::shared_ptr<HoughLineDetectionCommand> houghlinedetectioncommand;
    std::shared_ptr<DualThresholdCommand> dualthresholdcommand;
    std::shared_ptr<HueSaturaLightCommand> huesaturalightcommand;

};



#endif // VIEWMODEL_H