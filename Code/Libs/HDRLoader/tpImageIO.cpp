#include "StdAfx.h"

#include "tpImageIO.hpp"
#include "tpImageConvert.hpp"

#include <algorithm>
#include <iterator>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>
#include <FreeImage.h>

TP_EXPORT bool tpImageIO::readHDR(tpImageColorHDR& I, const std::string& path)
{
	return readHDR(I,path.c_str());
}

bool tpImageIO::readHDR(tpImageColorHDR& I, const char* path)
{

	FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(path, 0);
	
	if(fifmt == FIF_UNKNOWN)
	{
		std::cerr << "[Error] tpImageIO : Unknow type !" << std::endl; 
		//TODO: Exceptions ?
		return false;
	}
	
	

	FIBITMAP *dib = FreeImage_Load(fifmt, path,0);
    
	if( dib == NULL )
	{
		std::cerr << "[Error] tpImageIO : Impossible d'ouvrir l'image : " << path << std::endl;
		// TODO: Exceptions ?
		return false;
	}

	if(FreeImage_GetImageType(dib)!=FIT_RGBF)
	{
		std::cerr << "[Error] tpImageIO : Unknow type !" << std::endl; 
		//TODO: Exceptions ?
		return false;
	}

	unsigned width = FreeImage_GetWidth(dib);
	unsigned height = FreeImage_GetHeight(dib);
	unsigned pitch = FreeImage_GetPitch(dib);

	I.resize(height,width);

	FREE_IMAGE_TYPE image_type = FreeImage_GetImageType(dib);
	// test pixel access avoiding scanline calculations
	// to speed-up the image processing
	if(image_type == FIT_RGBF) {
		BYTE *bits = (BYTE*)FreeImage_GetBits(dib);
		for(int y = 0; y < height; y++) {
		FIRGBF *pixel = (FIRGBF*)bits;
		for(int x = 0; x < width; x++) {
		I[y][x].r = pixel[x].red;
		I[y][x].g = pixel[x].green;
		I[y][x].b = pixel[x].blue;
		}
		// next line
		bits += pitch;
		}
	}

	FreeImage_Unload(dib);

	return true;
}

bool tpImageIO::write(const tpImageGray& I, const std::string& path)
{
	return write(I, path.c_str());
}

bool tpImageIO::write(const tpImageGray& I, const char* filename)
{
	
	// On essaye de trouver l'extension
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	fif = FreeImage_GetFIFFromFilename(filename);

	if(fif == FIF_UNKNOWN)
	{
		std::cerr << "[Error] [tpImageIO] Write : Unknown file format !" << std::endl;
		return false;
	}

	unsigned width = I.getWidth();
	unsigned height = I.getHeight();

	FIBITMAP *dib = FreeImage_Allocate(width, height, 32);

	unsigned pitch = FreeImage_GetPitch(dib);

	BYTE *bits = (BYTE*)FreeImage_GetBits(dib);
	for(unsigned int y = 0; y < height; y++) {
		BYTE *pixel = (BYTE*)bits;
		for(unsigned int x = 0; x < width; x++) {
			//std::cout << "[DEBUG] (" << y << "," << x << ") " << (int)I[y][x] << std::endl;
			pixel[FI_RGBA_RED] = I[y][x];
			pixel[FI_RGBA_GREEN] = I[y][x];
			pixel[FI_RGBA_BLUE] = I[y][x];
			pixel[FI_RGBA_ALPHA] = 255;
			pixel += 4;
		} // next line
		bits += pitch;
	}

	FreeImage_Save (fif, dib, filename, 0);

	FreeImage_Unload(dib);

	return true;
}


bool tpImageIO::write(const tpImageColor& I, const char* filename)
{
	// On essaye de trouver l'extension
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	fif = FreeImage_GetFIFFromFilename(filename);

	if(fif == FIF_UNKNOWN)
	{
		std::cerr << "[Error] [tpImageIO] Write : Unknown file format !" << std::endl;
		return false;
	}

	unsigned width = I.getWidth();
	unsigned height = I.getHeight();

	FIBITMAP *dib = FreeImage_Allocate(width, height, 32);

	unsigned pitch = FreeImage_GetPitch(dib);

	BYTE *bits = (BYTE*)FreeImage_GetBits(dib);
	for(unsigned int y = 0; y < height; y++) {
		BYTE *pixel = (BYTE*)bits;
		for(unsigned int x = 0; x < width; x++) {
			//std::cout << "[DEBUG] (" << y << "," << x << ") " << (int)I[y][x] << std::endl;
			pixel[FI_RGBA_RED] = I[y][x].r;
			pixel[FI_RGBA_GREEN] = I[y][x].g;
			pixel[FI_RGBA_BLUE] = I[y][x].b;
			pixel[FI_RGBA_ALPHA] = 255;
			pixel += 4;
		} // next line
		bits += pitch;
	}

	FreeImage_Save (fif, dib, filename, 0);

	FreeImage_Unload(dib);

	return true;
}

bool tpImageIO::write(const tpImageColor& I, const std::string& path)
{
	return write(I,path.c_str());
}

bool tpImageIO::read(tpImageGray& I, const char* path)
{
	tpImageColor imC;
	
	if(!read(imC, path))
		return false;

	tpImageConvert::createGreyImage(imC,I);
	
	return true;
}

bool tpImageIO::read(tpImageGray& I, const std::string& path)
{
	return read(I, path.c_str());
}

bool tpImageIO::read(tpImageColor& I, const char* path)
{
	FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(path, 0);
	
	if(fifmt == FIF_UNKNOWN)
	{
		std::cerr << "[Error] tpImageIO : Unknow type !" << std::endl; 
		//TODO: Exceptions ?
		return false;
	}
	
	FIBITMAP *dib = FreeImage_Load(fifmt, path,0);
    
	if( dib == NULL )
	{
		std::cerr << "[Error] tpImageIO : Impossible d'ouvrir l'image : " << path << std::endl;
		// TODO: Exceptions ?
		return false;
	}

	FREE_IMAGE_TYPE image_type = FreeImage_GetImageType(dib);

	int nbBits = (int)FreeImage_GetBPP(dib);

	std::cout << "[Info] [read color] Image BPP : " <<  nbBits << std::endl;

	if((image_type != FIT_BITMAP) || (FreeImage_GetBPP(dib) != 24))
	{
		std::cerr << "[Error] tpImageIO (read Color): Unknow type !" << std::endl; 
		//TODO: Exceptions ?
		return false;
	}

	unsigned width = FreeImage_GetWidth(dib);
	unsigned height = FreeImage_GetHeight(dib);
	unsigned pitch = FreeImage_GetPitch(dib);

	I.resize(height,width);

	BYTE *bits = (BYTE*)FreeImage_GetBits(dib);
	if((image_type == FIT_BITMAP) && (FreeImage_GetBPP(dib) == 24))
	{
		for(unsigned int y = 0; y < height; y++) {
			BYTE *pixel = (BYTE*)bits;
			for(unsigned int x = 0; x < width; x++) {
				I[y][x].r = pixel[FI_RGBA_RED];
				I[y][x].g = pixel[FI_RGBA_GREEN];
				I[y][x].b = pixel[FI_RGBA_BLUE];
				pixel += (nbBits / 8);
			} // next line
			bits += pitch;
		}
	}
	else if(FreeImage_GetBPP(dib) == 8)
	{
		std::cout << "[Warning] Read => Force grayscale image ! " << std::endl;

		for(unsigned int y = 0; y < height; y++) {
			BYTE *pixel = (BYTE*)bits;
			for(unsigned int x = 0; x < width; x++) {
				I[y][x].r = pixel[0];
				I[y][x].g = pixel[0];
				I[y][x].b = pixel[0];
				pixel += 1;
			} // next line
			bits += pitch;
		}
	}

	FreeImage_Unload(dib);

	return true;

}
bool tpImageIO::read(tpImageColor& I, const std::string& path)
{
	return read(I, path.c_str());
}


