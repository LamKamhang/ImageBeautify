#include "maincommandsink.h"
#include "../mainview.h"

MainCommandSink::MainCommandSink(MainView *mainview)
    :mainview(mainview)
{
}

void MainCommandSink::OnCommandComplete(const commandsType cmd, bool OK){
    switch (cmd) {
    case OPEN_FILE:
        if(OK);
        else mainview->HandleOpenFileException();
        break;
    case SAVE_FILE:
        if(OK);
        else mainview->HandleSaveFileException();
        break;
    case OPEN_SUB_FILE:
        if(OK);
        else mainview->HandleOpenSubFileException();
        break;
    case FILTER:
        if(OK);
        else mainview->HandleFilterException();
        break;
    case EDGE_DETECTION:
        if(OK);
        else mainview->HandleEdgeDetectionException();
        break;
    case HOUGH_CIRCLE_DETECTION:
        if(OK);
        else mainview->HandleHoughCircleDetectionException();
        break;
    case CHANNEL:
        if(OK);
        else mainview->HandleChannelException();
        break;
    case RED_CHANNEL:
        if(OK);
        else mainview->HandleChannelException();
        break;
    case GREEN_CHANNEL:
        if(OK);
        else mainview->HandleChannelException();
        break;
    case BLUE_CHANNEL:
        if(OK);
        else mainview->HandleChannelException();
        break;
    case HOUGH_LINE_DETECTION:
        if(OK);
        else mainview->HandleHoughLineDetectionException();
        break;
    case GRAY_SCALE_TRANSFER:
        if(OK);
        else mainview->HandleGrayScaleTransferException();
        break;
    case OTSU:
        if(OK);
        else mainview->HandleOtsuException();
        break;
    case OPEN_SUB_DIALOG:
        if(OK);
        else mainview->HandleOpenSubDialogException();
        break;
    case DUAL_THRESHOLD:
        if(OK);
        else mainview->HandleDualThresholdException();
        break;
    case HUE_SATURA_LIGHT:
        if(OK);
        else mainview->HandleHueSaturaLightException();
        break;
    case CURVE:
        if(OK);
        else mainview->HandleCurveException();
        break;
    case LEVEL:
        if(OK);
        else mainview->HandleLevelException();
        break;
    case CLIP:
        if(OK);
        else mainview->HandleClipException();
        break;
    case SCALE:
        if(OK);
        else mainview->HandleScaleException();
        break;
    case HISTOGRAM:
        if(OK);
        else mainview->HandleHistogramException();
        break;
    case ALGEBRAIC:
        if(OK);
        else mainview->HandleAlgebraicException();
        break;
    case ALGEBRAIC_ADD:
        if(OK);
        else mainview->HandleAlgebraicException();
        break;
    case ALGEBRAIC_SUBTRACT:
        if(OK);
        else mainview->HandleAlgebraicException();
        break;
    case ALGEBRAIC_MULTIPLY:
        if(OK);
        else mainview->HandleAlgebraicException();
        break;
    case BINARY_MORPHOLOGY:
        if(OK);
        else mainview->HandleBinaryMorphologyException();
        break;
    case GRAY_MORPHOLOGY:
        if(OK);
        else mainview->HandleGrayMorphologyException();
        break;
    case ART_EFFECTS:
        if(OK);
        else mainview->HandleArtEffectsException();
        break;
    default:
        break;
    }
}
