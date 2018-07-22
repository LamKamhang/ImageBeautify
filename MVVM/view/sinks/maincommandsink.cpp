#include "maincommandsink.h"

MainCommandSink::MainCommandSink(MainView *mainview)
    :mainview(mainview)
{
}

void MainCommandSink::OnCommandComplete(const commandsType cmd, bool OK){
    switch (cmd) {
    case OPEN_FILE:
        if(OK);
        else;
        break;
    case SAVE_FILE:
        if(OK);
        else;
        break;
    case OPEN_SUB_FILE:
        if(OK);
        else;
        break;
    case FILTER:
        if(OK);
        else;
        break;
    case EDGE_DETECTION:
        if(OK);
        else;
        break;
    case HOUGH_CIRCLE_DETECTION:
        if(OK);
        else;
        break;
    case CHANNEL:
        if(OK);
        else;
        break;
    case RED_CHANNEL:
        if(OK);
        else;
        break;
    case GREEN_CHANNEL:
        if(OK);
        else;
        break;
    case BLUE_CHANNEL:
        if(OK);
        else;
        break;
    case HOUGH_LINE_DETECTION:
        if(OK);
        else;
        break;
    case GRAY_SCALE_TRANSFER:
        if(OK);
        else;
        break;
    case OTSU:
        if(OK);
        else;
        break;
    case OPEN_SUB_DIALOG:
        if(OK);
        else;
        break;
    case DUAL_THRESHOLD:
        if(OK);
        else;
        break;
    case HUE_SATURA_LIGHT:
        if(OK);
        else;
        break;
    case CURVE:
        if(OK);
        else;
        break;
    case LEVEL:
        if(OK);
        else;
        break;
    case CLIP:
        if(OK);
        else;
        break;
    case SCALE:
        if(OK);
        else;
        break;
    case HISTOGRAM:
        if(OK);
        else;
        break;
    case ALGEBRAIC:
        if(OK);
        else;
        break;
    case ALGEBRAIC_ADD:
        if(OK);
        else;
        break;
    case ALGEBRAIC_SUBTRACT:
        if(OK);
        else;
        break;
    case ALGEBRAIC_MULTIPLY:
        if(OK);
        else;
        break;
    case BINARY_MORPHOLOGY:
        if(OK);
        else;
        break;
    case GRAY_MORPHOLOGY:
        if(OK);
        else;
        break;
    case ART_EFFECTS:
        if(OK);
        else;
        break;
    default:
        break;
    }
}
