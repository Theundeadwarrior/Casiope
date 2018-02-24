#include "Core/File/ImageUtilities.h"

#include <png.h>

namespace Core
{


	template<typename T>
	void LoadPNGImageFromFile(Image<T>& outputImage, const char* path)
	{
		png_byte color_type;
		png_byte bit_depth;
		FILE* fp;
		errno_t err = fopen_s(&fp, path, "rb");

		png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
		if (!png) abort();

		png_infop info = png_create_info_struct(png);
		if (!info) abort();

		if (setjmp(png_jmpbuf(png))) abort();

		png_init_io(png, fp);

		png_read_info(png, info);

		outputImage.m_Width = png_get_image_width(png, info);
		outputImage.m_Height = png_get_image_height(png, info);
		color_type = png_get_color_type(png, info);
		bit_depth = png_get_bit_depth(png, info);

		// Read any color_type into 8bit depth, RGBA format.
		// See http://www.libpng.org/pub/png/libpng-manual.txt

		if (bit_depth == 16)
			png_set_strip_16(png);

		if (color_type == PNG_COLOR_TYPE_PALETTE)
			png_set_palette_to_rgb(png);

		// PNG_COLOR_TYPE_GRAY_ALPHA is always 8 or 16bit depth.
		if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
			png_set_expand_gray_1_2_4_to_8(png);

		if (png_get_valid(png, info, PNG_INFO_tRNS))
			png_set_tRNS_to_alpha(png);

		// These color_type don't have an alpha channel then fill it with 0xff.
		if (color_type == PNG_COLOR_TYPE_RGB ||
			color_type == PNG_COLOR_TYPE_GRAY ||
			color_type == PNG_COLOR_TYPE_PALETTE)
			png_set_filler(png, 0xFF, PNG_FILLER_AFTER);

		if (color_type == PNG_COLOR_TYPE_GRAY ||
			color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
			png_set_gray_to_rgb(png);

		png_read_update_info(png, info);
		outputImage.m_Spectrum = png_get_channels(png, info);

		outputImage.imageData.reserve(outputImage.m_Height * outputImage.m_Width * outputImage.m_Spectrum);
		unsigned char** dataPtr = static_cast<unsigned char**>(malloc(outputImage.m_Height * sizeof(char*)));

		for(uint32_t i = 0; i < outputImage.m_Height; ++i)
		{
			dataPtr[i] = static_cast<unsigned char*>(outputImage.imageData.data()) + outputImage.m_Width * outputImage.m_Spectrum * (outputImage.m_Height - i - 1);
		}

		// Read the image
		png_read_image(png, dataPtr);
		png_read_end(png, nullptr);

		// Free the data structs
		free(dataPtr);
		png_destroy_read_struct(&png, &info, nullptr);
		png = nullptr;
		info = nullptr;

		fclose(fp);
	}

	template void LoadPNGImageFromFile(Image<unsigned char>& outputImage, const char* path);
}
