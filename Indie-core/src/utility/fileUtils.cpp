#include "fileUtils.h"
#include "log.h"

namespace indie
{
	namespace utils
	{
		//c style
		std::string readFile(const std::string& fileName)
		{
			FILE* file;
			file = fopen(fileName.c_str(), "rb");

			INDIE_ASSERT(file, "Could not open the file!");

			fseek(file, 0, SEEK_END);
			unsigned long length = ftell(file);
			char* data = new char[length + 1];
			memset(data, 0, length + 1);
			fseek(file, 0, SEEK_SET);

			fread(data, 1, length, file);
			fclose(file);

			std::string result(data);
			delete[] data;

			return result;
		}

		BYTE* loadTexture(const char* fileName, int* width, int* height, unsigned int* bitsPerPixel)
		{
			//image format
			FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
			//pointer to the image, once loaded
			FIBITMAP* dib = nullptr;

			//check the file signature and deduce its format
			fif = FreeImage_GetFileType(fileName, 0);
			//if still unknown, try to guess the file format from the file extension
			if (fif == FIF_UNKNOWN)
				fif = FreeImage_GetFIFFromFilename(fileName);
			//if still unkown, return failure
			if (fif == FIF_UNKNOWN)
				return nullptr;

			//check that the plugin has reading capabilities and load the file
			if (FreeImage_FIFSupportsReading(fif))
				dib = FreeImage_Load(fif, fileName);
			//if the image failed to load, return failure
			/*if (!dib)
				return nullptr;*/

			INDIE_ASSERT(dib, "Faild to load image(texture)!");

			BYTE* bits = nullptr;
			//retrieve the image data
			bits = FreeImage_GetBits(dib);
			//get the image width and height
			*width = FreeImage_GetWidth(dib);
			*height = FreeImage_GetHeight(dib);

			*bitsPerPixel = FreeImage_GetBPP(dib);

#ifdef INDIE_EMSCRIPTEN
			SwapRedBlue32(dib);
#endif
			int size = *width * *height * (*bitsPerPixel / 8);
			BYTE* result = new BYTE[size];
			memcpy(result, bits, size);

			FreeImage_Unload(dib);

			return result;
		}
	}
}