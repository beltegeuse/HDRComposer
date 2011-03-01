#include "StdAfx.h"
#include "Operations/tpImageConvert.hpp"
#include "Operations/tpHDROperations.h"

const double tpImageConvert::eps = 0.008856;
const double tpImageConvert::k = 903.3;

bool tpImageConvert::createColorImage(const tpImage<unsigned char> &I, tpImage<tpRGB> &O)
{
	int w = I.getWidth();
	int h = I.getHeight();

	if(O.getWidth() != w || O.getHeight() != h)
	{
		std::cout << "[INFO] [createColorImage] Resize ... " << w << "x" << h << std::endl;
		O.resize(h,w);
	}

	std::cout << "[INFO] [createColorImage] Parcours ... " << std::endl;

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			O[x][y].r = I[x][y];
			O[x][y].g = I[x][y];
			O[x][y].b = I[x][y];
		}
	}

	return true;
}

void tpImageConvert::ConvertToFloat(const tpImageColorHDR& I, tpImageColorHDRFloat& O)
{
	int w = I.getWidth();
	int h = I.getHeight();

	if(O.getWidth() != w || O.getHeight() != h)
	{
		std::cout << "[INFO] [ConvertToFloat] Resize ... " << w << "x" << h << std::endl;
		O.resize(h,w);
	}

	std::cout << "[INFO] [ConvertToFloat] Parcours ... " << std::endl;

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			O[x][y].r = I[x][y].r;
			O[x][y].g = I[x][y].g;
			O[x][y].b = I[x][y].b;
			O[x][y].a = 1.0;
		}
	}
}

void tpImageConvert::ConvertToFloat(const tpImageLuminanceHDR& I, tpImageLuminanceHDRFloat& O)
{
	int w = I.getWidth();
	int h = I.getHeight();

	if(O.getWidth() != w || O.getHeight() != h)
	{
		std::cout << "[INFO] [ConvertToFloat] Resize ... " << w << "x" << h << std::endl;
		O.resize(h,w);
	}

	std::cout << "[INFO] [ConvertToFloat] Parcours ... " << std::endl;

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			O[x][y] = I[x][y];
		}
	}
}

bool tpImageConvert::createGreyImage(const tpImage<tpRGB> &I, tpImage<unsigned char> &O)
{
	int w = I.getWidth();
	int h = I.getHeight();

	if(O.getWidth() != w || O.getHeight() != h)
	{
		std::cout << "[INFO] [createGreyImage] Resize ... " << std::endl;
		O.resize(h,w);
	}

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			//FIXME Faire le test d'un buffer overflow (Possible ?)
			O[x][y] = 0.299*I[x][y].r + 0.587*I[x][y].g + 0.114*I[x][y].r;
		}
	}

	return true;
}

bool tpImageConvert::createLuminanceImage(const tpImageColorHDR& I, tpImageLuminanceHDR& O, double fR, double fG, double fB)
{
	// FIXME: Faire un test sur les factor (somme == 1)

	int w = I.getWidth();
	int h = I.getHeight();

	if(O.getWidth() != w || O.getHeight() != h)
	{
		std::cout << "[INFO] [createLuminanceImage] Resize ... " << std::endl;
		O.resize(h,w);
	}

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			//FIXME Faire le test d'un buffer overflow (Possible ?)
			O[x][y] = fR*I[x][y].r + fG*I[x][y].g + fB*I[x][y].r;
		}
	}

	return true;
}

bool tpImageConvert::createGrayImageFromLuminance(const tpImageLuminanceHDR &I, tpImageGray& O)
{

	Assert(tpHDROperations::GetMax(I) <= 1 && tpHDROperations::GetMin(I) >= 0);

	int w = I.getWidth();
	int h = I.getHeight();

	if(O.getWidth() != w || O.getHeight() != h)
	{
		std::cout << "[INFO] [createGrayImageFromLuminance] Resize ... " << std::endl;
		O.resize(h,w);
	}

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			O[x][y] = 255*I[x][y];
		}
	}

	return true;
}

bool tpImageConvert::createGrayImageFromFilterResult(const tpFilterResult &I, tpImageGray& O)
{
	int w = I.getWidth();
	int h = I.getHeight();

	float max = tpHDROperations::GetMax(I);

	if(O.getWidth() != w || O.getHeight() != h)
	{
		std::cout << "[INFO] [createGrayImageFromFilterResult] Resize ... " << std::endl;
		O.resize(h,w);
	}

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			O[x][y] = 255*(I[x][y] / max);
		}
	}

	return true;
}

bool tpImageConvert::createColorImage(const tpImageLuminanceHDR &I, const tpImageColorHDR& Ic, tpImage<tpRGB> &O, double s)
{
	int w = I.getWidth();
	int h = I.getHeight();

	tpImageLuminanceHDR Ll;
	createLuminanceImage(Ic,Ll);

	if(O.getWidth() != w || O.getHeight() != h)
	{
		std::cout << "[INFO] [createColorImage] Resize ... " << w << "x" << h << std::endl;
		O.resize(h,w);
	}

	std::cout << "[INFO] [createColorImage] Parcours ... " << std::endl;
	std::cout << "[Info] [createColorImage] s : " << s << std::endl;

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			O[x][y].r = std::min(255*I[x][y]*pow(Ic[x][y].r / Ll[x][y], s), 255.0);
			O[x][y].g = std::min(255*I[x][y]*pow(Ic[x][y].g / Ll[x][y], s), 255.0);
			O[x][y].b = std::min(255*I[x][y]*pow(Ic[x][y].b / Ll[x][y], s), 255.0);
		}
	}

	return true;
}

bool tpImageConvert::createColorImageHDR(const tpImageLuminanceHDR &I, const tpImageColorHDR& Ic, tpImageColorHDR &O, double s)
{
	int w = I.getWidth();
	int h = I.getHeight();

	tpImageLuminanceHDR Ll;
	createLuminanceImage(Ic,Ll);

	if(O.getWidth() != w || O.getHeight() != h)
	{
		std::cout << "[INFO] [createColorImageHDR] Resize ... " << w << "x" << h << std::endl;
		O.resize(h,w);
	}

	std::cout << "[INFO] [createColorImageHDR] Parcours ... " << std::endl;
	std::cout << "[Info] [createColorImageHDR] s : " << s << std::endl;

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			O[x][y].r = std::min(I[x][y]*pow(Ic[x][y].r / Ll[x][y], s), 1.0);
			O[x][y].g = std::min(I[x][y]*pow(Ic[x][y].g / Ll[x][y], s), 1.0);
			O[x][y].b = std::min(I[x][y]*pow(Ic[x][y].b / Ll[x][y], s), 1.0);
		}
	}

	return true;
}

void tpImageConvert::XYZtoLAB(const tpImageColorHDR& I1, tpImageColorHDR& O)
{
	
	tpImageColorHDR I;
	I.copy(I1);

	//Clamp(I);

	int w = I.getWidth();
	int h = I.getHeight();

	O.resize(I.getHeight(), I.getWidth());

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			// First convert
			/*double r = FLab(I[x][y].r / 0.95047) ;
			double g = FLab(I[x][y].g);
			double b = FLab(I[x][y].b / 1.08883);
			*/

			double r = FLab(I[x][y].r) ;
			double g = FLab(I[x][y].g);
			double b = FLab(I[x][y].b);

			// Second pass
			O[x][y].r = 116*g - 16;
			O[x][y].g = 500*(r - g);
			O[x][y].b = 200*(g - b);
		}
	}
}

double tpImageConvert::FLab(double ratio)
{
	if(ratio > 0.008856)
	{
		return pow(ratio, 1.0/3.0);
	}
	else
	{
		return 7.787*ratio + (16.0 / 116.0);
	}
}

void tpImageConvert::LABtoXYZ(const tpImageColorHDR& I, tpImageColorHDR& O)
{
	int w = I.getWidth();
	int h = I.getHeight();

	O.resize(I.getHeight(), I.getWidth());

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			// First convert
			double fy = (I[x][y].r + 16.0) / 116.0;
			double fz = fy - (I[x][y].b / 200.0);
			double fx = fy + (I[x][y].g / 500.0) ;

			double fz3 = pow(fz, 3);
			double fx3 = pow(fx,3);

			if(fx3 > eps)
			{
				O[x][y].r = fx3;
			}
			else
			{
				O[x][y].r = (116*fx - 16)/k;
			}

			if(I[x][y].r > eps*k)
			{
				O[x][y].g = pow(fy,3);
			}
			else
			{
				O[x][y].g = I[x][y].r / k;
			}

			if(fz3 > eps)
			{
				O[x][y].b = fz3;
			}
			else
			{
				O[x][y].b = (116*fz - 16)/k;
			}

			// White point correction
			//O[x][y].r = O[x][y].r * 0.95047;
			//O[x][y].b = O[x][y].b * 1.08883;
		}
	}
}

void tpImageConvert::RGBtoXYZ(const tpImageColorHDR& I, tpImageColorHDR& O)
{
	int w = I.getWidth();
	int h = I.getHeight();

	O.resize(I.getHeight(), I.getWidth());

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			O[x][y].r = 0.4124*I[x][y].r + 0.3576*I[x][y].g + 0.1805*I[x][y].b;
			O[x][y].g = 0.2126*I[x][y].r + 0.7152*I[x][y].g + 0.0722*I[x][y].b;
			O[x][y].b = 0.0193*I[x][y].r + 0.1192*I[x][y].g + 0.9505*I[x][y].b;
		}
	}
}

void tpImageConvert::sRGBtoXYZ(const tpImageColorHDR& I, tpImageColorHDR& O)
{
	int w = I.getWidth();
	int h = I.getHeight();

	O.resize(I.getHeight(), I.getWidth());

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			double r, g, b;
			/*r = FsRBG(I[x][y].r);
			g = FsRBG(I[x][y].g);
			b = FsRBG(I[x][y].b);*/
			r = I[x][y].r;
			g = I[x][y].g;
			b = I[x][y].b;

			O[x][y].r = 0.412424 *r + 0.357579*g + 0.180464*b;
			O[x][y].g = 0.212656*r + 0.715158*g + 0.0721856*b;
			O[x][y].b = 0.0193324*r + 0.119193*g + 0.950444*b;
		}
	}
}

void tpImageConvert::XYZtosRGB(const tpImageColorHDR& I, tpImageColorHDR& O)
{
	int w = I.getWidth();
	int h = I.getHeight();

	O.resize(I.getHeight(), I.getWidth());

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			double r, g, b;
			r = I[x][y].r;
			g = I[x][y].g;
			b = I[x][y].b;

			O[x][y].r =  3.24070846*r + -1.53725917*g + -0.49857039*b;
			O[x][y].g = -0.96925735*r + 1.87599516*g + 0.04155555*b;
			O[x][y].b = 0.05563507*r + -0.2039958*g + 1.05706957*b;

			//O[x][y].r = FsXYZ(O[x][y].r);
			//O[x][y].g = FsXYZ(O[x][y].g);
			//O[x][y].b = FsXYZ(O[x][y].b);
		}
	}
}

double tpImageConvert::FsXYZ(double value)
{
	if(value > 0.0031308)
	{
		return std::pow(1.055*value, 0.41666666666666669) - 0.055; // 1 / 2.4 => 0.41666666666666669
	}
	else
	{
		return 12.92 * value;
	}
}

double tpImageConvert::FsRBG(double value)
{
	if(value > 0.04045)
	{
		return std::pow((value + 0.055) / 1.055, 2.4);
	}
	else
	{
		return value / 12.92;
	}
}

void tpImageConvert::XYZtoRGB(const tpImageColorHDR& I, tpImageColorHDR& O)
 {
	int w = I.getWidth();
	int h = I.getHeight();

	O.resize(I.getHeight(), I.getWidth());

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			O[x][y].r = 3.2405*I[x][y].r + -1.5371*I[x][y].g + -0.4985*I[x][y].b;
			O[x][y].g = -0.9693*I[x][y].r + 1.8760*I[x][y].g + 0.0416*I[x][y].b;
			O[x][y].b = 0.0556*I[x][y].r + -0.2040*I[x][y].g + 1.0572*I[x][y].b;
		}
	}
 }


void tpImageConvert::CopyChannel(const tpImageColor& I, tpImageGray& O, tpImageConvert::ChannelType c)
{
	CopyChannelTemplate<tpImageColor,tpImageGray>(I,O,c);
}

void tpImageConvert::CopyChannel(const tpImageColorHDR& I, tpImageLuminanceHDR& O, tpImageConvert::ChannelType c)
{
	CopyChannelTemplate<tpImageColorHDR,tpImageLuminanceHDR>(I,O,c);
}


template <typename T, typename TRes>
void tpImageConvert::CopyChannelTemplate(const T& I, TRes& O, tpImageConvert::ChannelType c)
{
	int w = I.getWidth();
	int h = I.getHeight();

	O.resize(I.getHeight(), I.getWidth());

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			if(R == c)
			{
				O[x][y] = I[x][y].r;
			}
			else if(G == c)
			{
				O[x][y] = I[x][y].g;
			}
			else
			{
				O[x][y] = I[x][y].b;
			}
		}
	}
}

void tpImageConvert::createColorImageHDR(const tpImageColor &I, tpImageColorHDR &O)
{
	int w = I.getWidth();
	int h = I.getHeight();

	if(O.getWidth() != w || O.getHeight() != h)
	{
		std::cout << "[INFO] [createColorImageHDR] Resize ... " << w << "x" << h << std::endl;
		O.resize(h,w);
	}

	std::cout << "[INFO] [createColorImageHDR] Parcours ... " << std::endl;

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			O[x][y].r = I[x][y].r / 255.0;
			O[x][y].g = I[x][y].g / 255.0;
			O[x][y].b = I[x][y].b / 255.0;
		}
	}
}

void tpImageConvert::Log2WithNorm(tpImageColorHDR& I)
{
	int w = I.getWidth();
	int h = I.getHeight();

	tpImageLuminanceHDR cR,cG,cB;

	std::cout << "[Info] [Log2Norm] Recherche min (avoid 0) ... " << std::endl;

	double min = 100000000;
	
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			double minTemp = std::min(std::min(I[x][y].r,I[x][y].g), I[x][y].b);		
			if(min != 0.0)
			{
				min = std::min(minTemp, min);
			}
		}
	}

	std::cout << "[Info] [Log2Norm] Remplacement des 0 ... " << std::endl;

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			if(I[x][y].r == 0.0)
				I[x][y].r = min;

			if(I[x][y].g == 0.0)
				I[x][y].g = min;

			if(I[x][y].b == 0.0)
				I[x][y].b = min;
		}
	}

	std::cout << "[Info] [Log2Norm] Application du log ... " << std::endl;

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			I[x][y].r = Log2Channel(I[x][y].r);
			I[x][y].g = Log2Channel(I[x][y].g);
			I[x][y].b = Log2Channel(I[x][y].b);
		}
	}

	Norm(I);

	CopyChannel(I, cR, R);
	CopyChannel(I, cG, G);
	CopyChannel(I, cB, B);
	
    double	max = std::max(std::max(tpHDROperations::GetMax(cR),tpHDROperations::GetMax(cG)), tpHDROperations::GetMax(cB)); 
	min = std::min(std::min(tpHDROperations::GetMin(cR),tpHDROperations::GetMin(cG)), tpHDROperations::GetMin(cB)); 
	std::cout << "[Info] [Log2Norm] [" << min << "," << max << "]" << std::endl; 
}

void tpImageConvert::Norm(tpImageColorHDR &I)
{
	int w = I.getWidth();
	int h = I.getHeight();

	tpImageLuminanceHDR cR,cG,cB;
	
	std::cout << "[Info] [Norm] Copy all channel ... " << std::endl;
	
	CopyChannel(I, cR, R);
	CopyChannel(I, cG, G);
	CopyChannel(I, cB, B);

	std::cout << "[Info] [Norm] Recherche max & min ... " << std::endl;

	double max = std::max(std::max(tpHDROperations::GetMax(cR),tpHDROperations::GetMax(cG)), tpHDROperations::GetMax(cB)); 
	double min = std::min(std::min(tpHDROperations::GetMin(cR),tpHDROperations::GetMin(cG)), tpHDROperations::GetMin(cB)); 

	std::cout << "[Info] [Norm] max : " << max << std::endl;
	std::cout << "[Info] [Norm] min : " << min << std::endl;

	std::cout << "[Info] [Norm] Normalisation ... " << std::endl;

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			if(min != max)
			{
				I[x][y].r = (I[x][y].r - min) / (max - min);
				I[x][y].g = (I[x][y].g - min) / (max - min);
				I[x][y].b = (I[x][y].b - min) / (max - min);
			}
		}
	}
}

double tpImageConvert::Log2Channel(const double value)
{
	if(value <= 0.0)
	{
		return 0;
	}
	else
	{
		return log(value);
	}
}

void tpImageConvert::RGBtoLAB(tpImageColorHDR& I)
{
	tpImageColorHDR temp;

	Log2WithNorm(I);
	
	RGBtoXYZ(I,temp);
	XYZtoLAB(temp,I);

}

void tpImageConvert::LABtoRGB(tpImageColorHDR& I)
{
	tpImageColorHDR temp;

	LABtoXYZ(I, temp);
	XYZtoRGB(temp, I);
}

template <class T, class TRes>
void tpImageConvert::ParseChannel(const T& I, TRes& O, tpImageConvert::ChannelType c)
{
	unsigned int w = O.getWidth();
	unsigned int h = O.getHeight();

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			if(R == c)
			{
				O[x][y].r = I[x][y];
			}
			else if(G == c)
			{
				O[x][y].g = I[x][y];
			}
			else
			{
				O[x][y].b = I[x][y];
			}
		}
	}
}

void tpImageConvert::Clamp(tpImageColorHDR& I)
{
	int w = I.getWidth();
	int h = I.getHeight();

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			I[x][y].r = std::min(std::max(I[x][y].r, 0.0),1.0);
			I[x][y].g = std::min(std::max(I[x][y].g, 0.0),1.0);
			I[x][y].b = std::min(std::max(I[x][y].b, 0.0),1.0);
		}
	}
}

void tpImageConvert::createColorImage(const tpImageColorHDR& I1, tpImageColor &O)
{
	tpImageColorHDR I;
	I.copy(I1);

	if(!(tpHDROperations::GetMinColor(I) >= 0 & tpHDROperations::GetMaxColor(I) <= 1))
	{
		std::cout << "[Warning] Clamping ! " << std::endl;
		Clamp(I);
	}


	int w = I.getWidth();
	int h = I.getHeight();

	O.resize(h,w);

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			//std::cout << I[x][y].r << " " << I[x][y].g << " " << I[x][y].b << std::endl;
			O[x][y].r = 255*I[x][y].r;
			O[x][y].g = 255*I[x][y].g;
			O[x][y].b = 255*I[x][y].b;
		}
	}
}

void tpImageConvert::createColorImage(const tpImageGray &R, const tpImageGray &G, const tpImageGray &B, tpImageColor& O)
{

	int w = R.getWidth();
	int h = R.getHeight();

	O.resize(h,w);

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			//std::cout << I[x][y].r << " " << I[x][y].g << " " << I[x][y].b << std::endl;
			O[x][y].r = R[x][y];
			O[x][y].g = G[x][y];
			O[x][y].b = B[x][y];
		}
	}
}

void tpImageConvert::ParseChannel(const tpImageLuminanceHDR& I, tpImageColorHDR& O, tpImageConvert::ChannelType c)
{
	ParseChannel<tpImageLuminanceHDR, tpImageColorHDR>(I,O,c);
}

void tpImageConvert::ParseChannel(const tpImageGray& I, tpImageColor& O, tpImageConvert::ChannelType c)
{
	ParseChannel<tpImageGray, tpImageColor>(I,O,c);
}

void tpImageConvert::XYZtoYxy(const tpImageColorHDR& I, tpImageColorHDR& O)
{
	int w = I.getWidth();
	int h = I.getHeight();

	O.resize(h,w);

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			double sum = I[x][y].g + I[x][y].r + I[x][y].b;
			
			O[x][y].r = I[x][y].g;
			O[x][y].g = I[x][y].r / sum;
			O[x][y].b = I[x][y].g / sum;
		}
	}
}

void tpImageConvert::YxytoXYZ(const tpImageColorHDR& I, tpImageColorHDR& O)
{
	int w = I.getWidth();
	int h = I.getHeight();

	O.resize(h,w);

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			double factor = I[x][y].r / I[x][y].b;
			
			

			O[x][y].r = I[x][y].g*factor;
			O[x][y].g = I[x][y].r;
			O[x][y].b = (1 - I[x][y].g - I[x][y].b)*factor;
		}
	}
}

void tpImageConvert::Calibration(tpImageLuminanceHDR& I)
{

	double Lav = tpHDROperations::GetMean(I);
	double Lmin = tpHDROperations::GetMin(I);
	double Lmax = tpHDROperations::GetMax(I);

	int w = I.getWidth();
	int h = I.getHeight();

	double f = (2*log(Lav) - log(Lmin) - log(Lmax)) / (log(Lmax) - log(Lmin));
	double alpha = 0.18*pow(4.0,f);

	#pragma omp parallel for
	for(int x = 0; x < h; x++)
	{
		for(int y = 0; y < w; y++)
		{
			I[x][y] = (alpha / Lav)*I[x][y]; 
		}
	}
}


