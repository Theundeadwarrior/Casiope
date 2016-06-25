#ifndef UTILITIES_IMAGE_H
#define UTILITIES_IMAGE_H


#include <vector>
#include <string>

#define cimg_use_png

namespace cimg_library
{
	template<class T>
	struct CImg;
}

namespace Core
{
	template <class T>
	struct ImageParameters
	{
		ImageParameters<T>()
			: width(0)
			, height(0)
			, spectrum(0)
		{
			imageData.clear();
		}
		std::string path;
		std::vector<T> imageData;
		unsigned int width;
		unsigned int height;
		unsigned int spectrum;
	};

	template <class T>
	inline typename void LoadImageFromFile(ImageParameters<T>& outputParams, const char* tpath);
	template <class T>
	inline typename void SaveImageToFile(const ImageParameters<T>& inputParams, const char* tpath);

	inline cimg_library::CImg<float> LoadImageFromFile(const char* path);

	inline void SaveImageToFile(const cimg_library::CImg<float>& img, const char* path);

	inline float CalculateImageDifference(const cimg_library::CImg<unsigned char>& img, const cimg_library::CImg<unsigned char>& refImg, cimg_library::CImg<unsigned char>& o_diffImg);
}

#endif

