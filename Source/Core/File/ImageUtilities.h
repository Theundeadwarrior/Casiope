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
			m_ImageData.clear();
		}

		Image<T>(uint32_t width, uint32_t height, uint32_t spectrum, bool initData = false)
			: m_Width(width)
			, m_Height(height)
			, m_Spectrum(spectrum)
		{
			if (initData)
			{
				m_ImageData.resize(width * height * spectrum);
			}
		}

		void SetPixelValue(T value, uint32_t x, uint32_t y, uint32_t z)
		{
			m_ImageData[x * m_Spectrum + y * m_Width * m_Spectrum + z] = value;
		}

		std::string path;
		std::vector<T> m_ImageData;
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

		outputImage.m_ImageData.clear();

		outputImage.m_Width = imageFile.width();
		outputImage.m_Height = imageFile.height();

		unsigned int size = outputImage.m_Width * outputImage.m_Height;
		outputImage.m_ImageData.reserve(size * outputImage.m_Spectrum);

		for (unsigned int i = 0; i < size; ++i)
		{
			for (unsigned int j = 0; j < outputImage.m_Spectrum; ++j)
			{
				outputImage.m_ImageData.push_back(content[j][i]);
			}
		}

		delete[] content;
	}
	template <class T>
	inline void SaveImageToFile(const Image<T>& inputParams, const char* tpath)
	{
		T* data = new T[inputParams.m_ImageData.size()];

		for (unsigned int j = 0; j < inputParams.m_ImageData.size(); ++j)
		{
			data[j] = inputParams.m_ImageData[(j*inputParams.m_Spectrum) % (inputParams.m_ImageData.size() - 1)];
		}

		cimg_library::CImg<T> screenshotImage(data, inputParams.m_Width, inputParams.m_Height, 1, inputParams.m_Spectrum, true);
		screenshotImage.mirror('y');
		screenshotImage.save(tpath);

		delete[] data;
	}

	inline void SaveImageToFile(const cimg_library::CImg<float>& img, const char* path)
	{
		img.save(path);
	}
}


