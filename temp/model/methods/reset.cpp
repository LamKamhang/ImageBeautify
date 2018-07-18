#include "../model.h"


void Model::reset()
{
	if (originImg.empty())
	{
		throw(EMPTY_IMAGE)
	}
	else 
    {
		originImg.copyTo(newImg);
        Fire_OnPropertyChanged(MAIN_IMAGE);
	}
}