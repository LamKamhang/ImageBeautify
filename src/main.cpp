#include <iostream>
#include "Image.hpp"

using namespace std;
using namespace cv;

inline void test(const std::string &name, Image &image)
{
	namedWindow(name);
	try
	{
		image.ImgShow(name);
	}
	catch (const ErrorMsg &e)
	{
		std::cerr << e.what() << endl;
	}

}

int main(int argc, char const *argv[])
{
    cout << "Hello, OpenCV!" << endl;

    Image testImg;
	testImg.AttachTo("lena.jpg");
	test("origin", testImg);

	//testImg._blur();
	//test("mean_blur", testImg);
	//
	//testImg._gaussianBlur();
	//test("gaussian_blur", testImg);
 //   
 //   testImg._medianBlur();
 //   test("median_blur", testImg);

    testImg._bilateralFilter();
    test("bilateralFilter", testImg);

	cv::waitKey();

    
    
    return 0;
}