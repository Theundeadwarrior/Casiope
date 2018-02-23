#include "Core/File/ImageUtilities.h"

#include <png.h>

namespace Core
{
	png_byte color_type;
	png_byte bit_depth;
	png_bytep *row_pointers;

	template<typename T>
	void LoadPNGImageFromFile(Image<T>& outputImage, const char* path)
	{
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

		// TEMP TO DELETE!!!
		row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * outputImage.m_Height);
		for (int y = 0; y < outputImage.m_Height; y++) {
			row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png, info));
		}
		png_read_image(png, row_pointers);


		outputImage.imageData.reserve(outputImage.m_Height * outputImage.m_Width * outputImage.m_Spectrum);
		for (int y = outputImage.m_Height - 1; y >= 0; --y)
		{
			for (int x = 0; x < outputImage.m_Width; ++x)
			{
				for (int z = 0; z < outputImage.m_Spectrum; ++z)
				{
					outputImage.imageData.push_back(row_pointers[y][x * outputImage.m_Spectrum + z]);
				}
			}
		}
		// END OF TO DELETE



		png_destroy_read_struct(&png, &info, nullptr);
		png = nullptr;
		info = nullptr;

		fclose(fp);
	}

	template void LoadPNGImageFromFile(Image<unsigned char>& outputImage, const char* path);
}
