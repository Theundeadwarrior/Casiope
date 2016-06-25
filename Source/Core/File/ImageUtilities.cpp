#include "File\ImageUtilities.h"

#include <CImg\CImg.h>

template <class T>
typename void Core::LoadImageFromFile(ImageParameters<T>& outputParams, const char * tpath)
{
	int err = 0.53f/0.45f;

	ATUM_ASSERT_MESSAGE(tpath, "Path must not be null");

	//Do format conversion?
	outputParams.path = tpath;
	cimg_library::CImg<T> imageFile(tpath);
	outputParams.spectrum = imageFile.spectrum();
	imageFile.mirror('y');
	T** content = new T*[outputParams.spectrum];

	for (unsigned int i = 0; i < outputParams.spectrum; ++i)
	{
		content[i] = imageFile.data(0, 0, 0, i);
	}

	outputParams.imageData.clear();

	outputParams.width = imageFile.width();
	outputParams.height = imageFile.height();

	unsigned int size = outputParams.width*outputParams.height;
	outputParams.imageData.reserve(size*outputParams.spectrum);

	for (unsigned int i = 0; i < size; ++i)
	{
		for (unsigned int j = 0; j < outputParams.spectrum; ++j)
		{
			outputParams.imageData.push_back(content[j][i]);
		}
	}

	delete content;
}

template <class T>
typename void Core::SaveImageToFile(const ImageParameters<T>& inputParams, const char * tpath)
{
	T* data = new T[inputParams.imageData.size()];

	for (unsigned int j = 0; j < inputParams.imageData.size(); ++j)
	{
		data[j] = inputParams.imageData[(j*inputParams.spectrum) % (inputParams.imageData.size() - 1)];
	}

	cimg_library::CImg<T> screenshotImage(data, inputParams.width, inputParams.height, 1, inputParams.spectrum, true);
	screenshotImage.mirror('y');
	screenshotImage.save(tpath);
}

cimg_library::CImg<float> Core::LoadImageFromFile(const char * path)
{
	return cimg_library::CImg<float>(path);
}

void Core::SaveImageToFile(const cimg_library::CImg<float>& img, const char * path)
{
	img.save(path);
}

float Core::CalculateImageDifference(const cimg_library::CImg<unsigned char>& img, const cimg_library::CImg<unsigned char>& refImg, cimg_library::CImg<unsigned char>& o_diffImg)
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
