#ifndef UTILITIES_IMAGE_H
#define UTILITIES_IMAGE_H


#include <vector>
#include <string>

#include <CImg\CImg.h>


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
			, m_Spectrum(0)
		{
			imageData.clear();
		}
		std::string path;
		std::vector<T> imageData;
		unsigned int width;
		unsigned int height;
		unsigned int m_Spectrum;
	};

	template <class T>
	inline typename void LoadImageFromFile(ImageParameters<T>& outputParams, const char* tpath)
	{
		//Do format conversion?
		outputParams.path = tpath;
		cimg_library::CImg<T> imageFile(tpath);
		outputParams.m_Spectrum = imageFile.spectrum();
		imageFile.mirror('y');
		T** content = new T*[outputParams.m_Spectrum];

		for (unsigned int i = 0; i < outputParams.m_Spectrum; ++i)
		{
			content[i] = imageFile.data(0, 0, 0, i);
		}

		outputParams.imageData.clear();

		outputParams.width = imageFile.width();
		outputParams.height = imageFile.height();

		unsigned int size = outputParams.width*outputParams.height;
		outputParams.imageData.reserve(size*outputParams.m_Spectrum);

		for (unsigned int i = 0; i < size; ++i)
		{
			for (unsigned int j = 0; j < outputParams.m_Spectrum; ++j)
			{
				outputParams.imageData.push_back(content[j][i]);
			}
		}

		delete content;
	}
	template <class T>
	inline typename void SaveImageToFile(const ImageParameters<T>& inputParams, const char* tpath)
	{
		T* data = new T[inputParams.imageData.size()];

		for (unsigned int j = 0; j < inputParams.imageData.size(); ++j)
		{
			data[j] = inputParams.imageData[(j*inputParams.m_Spectrum) % (inputParams.imageData.size() - 1)];
		}

		cimg_library::CImg<T> screenshotImage(data, inputParams.width, inputParams.height, 1, inputParams.m_Spectrum, true);
		screenshotImage.mirror('y');
		screenshotImage.save(tpath);
	}

	inline cimg_library::CImg<float> LoadImageFromFile(const char* path)
	{
		return cimg_library::CImg<float>(path);
	}

	inline void SaveImageToFile(const cimg_library::CImg<float>& img, const char* path)
	{
		img.save(path);
	}

	inline float CalculateImageDifference(const cimg_library::CImg<unsigned char>& img, const cimg_library::CImg<unsigned char>& refImg, cimg_library::CImg<unsigned char>& o_diffImg)
	{
		o_diffImg = (refImg - img).abs();
		// percentage diff = abs(ref - actual) / actual * 100
		float sumOfDifference = 0;
		for (int i = 0; i < img.width(); i++)
		{
			for (int j = 0; j < img.height(); j++)
			{
				if (refImg(i, j) > 0.01)
					sumOfDifference += o_diffImg(i, j) / refImg(i, j);
			}
		}

		return sumOfDifference * 100.0f;
	}
}

#endif
