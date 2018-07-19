#include "../model.h"


void Model::reset()// throw(errorType)
{
	if (originImg.empty())
	{
//		throw(EMPTY_IMAGE);
	}
	else 
    {
		originImg.copyTo(showImg);
        Fire_OnPropertyChanged(MAIN_IMAGE);
	}
}
