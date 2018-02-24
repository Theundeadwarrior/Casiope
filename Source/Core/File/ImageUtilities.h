#pragma once

#include <vector>
#include <string>

#include <CImg/CImg.h>


#define cimg_use_png

namespace cimg_library
{
	template<class T>
	struct CImg;
}

namespace Core
{
	template <class T>
	class Image
	{
	public:
		Image<T>()
			: m_Width(0)
			, m_Height(0)
			, m_Spectrum(0)
		{
			imageData.clear();
		}
		std::string path;
		std::vector<T> imageData;
		unsigned int m_Width;
		unsigned int m_Height;
		unsigned int m_Spectrum;
	};

	template <class T>
	void LoadPNGImageFromFile(Image<T>& outputImage, const char* path);

	template <class T>
	inline void LoadImageFromFile(Image<T>& outputImage, const char* path)
	{
		//Do format conversion?
		outputImage.path = path;
		cimg_library::CImg<T> imageFile(path);
		outputImage.m_Spectrum = imageFile.spectrum();
		imageFile.mirror('y');
		T** content = new T*[outputImage.m_Spectrum];

		for (unsigned int i = 0; i < outputImage.m_Spectrum; ++i)
		{
			content[i] = imageFile.data(0, 0, 0, i);
		}

		outputImage.imageData.clear();

		outputImage.m_Width = imageFile.width();
		outputImage.m_Height = imageFile.height();

		unsigned int size = outputImage.m_Width * outputImage.m_Height;
		outputImage.imageData.reserve(size * outputImage.m_Spectrum);

		for (unsigned int i = 0; i < size; ++i)
		{
			for (unsigned int j = 0; j < outputImage.m_Spectrum; ++j)
			{
				outputImage.imageData.push_back(content[j][i]);
			}
		}

		delete[] content;
	}
	template <class T>
	inline void SaveImageToFile(const Image<T>& inputParams, const char* tpath)
	{
		T* data = new T[inputParams.imageData.size()];

		for (unsigned int j = 0; j < inputParams.imageData.size(); ++j)
		{
			data[j] = inputParams.imageData[(j*inputParams.m_Spectrum) % (inputParams.imageData.size() - 1)];
		}

		cimg_library::CImg<T> screenshotImage(data, inputParams.m_Width, inputParams.m_Height, 1, inputParams.m_Spectrum, true);
		screenshotImage.mirror('y');
		screenshotImage.save(tpath);
	}

	inline void SaveImageToFile(const cimg_library::CImg<float>& img, const char* path)
	{
		img.save(path);
	}
}


