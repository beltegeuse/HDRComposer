
#ifndef TPIMAGECONVERT_H_
#define TPIMAGECONVERT_H_

#include "tpConfig.h"
#include "tpImage.hpp"
#include "tpImageFilter.hpp"

/*!
  \file tpImageConvert.hpp
  \brief Image Convert management.
*/

/*!

  \class tpImageConvert
  \brief Image Convert management.
*/
class tpImageConvert {
public:
	/*
	 * Create => Conversion type image
	 */
	static  bool createColorImage(const tpImage<unsigned char> &I, tpImage<tpRGB> &O);
	static  bool createColorImage(const tpImageLuminanceHDR &I, const tpImageColorHDR& Ic, tpImage<tpRGB> &O, double s = 0.65);
	static  void createColorImage(const tpImageColorHDR& I, tpImageColor &O);
	static  void createColorImage(const tpImageGray &R, const tpImageGray &G, const tpImageGray &B, tpImageColor& O);

	static  bool createGreyImage(const tpImage<tpRGB> &I, tpImage<unsigned char> &O);
	static  bool createGrayImageFromLuminance(const tpImageLuminanceHDR &I, tpImageGray& O);
	static  bool createGrayImageFromFilterResult(const tpFilterResult &I, tpImageGray& O);

	static  bool createColorImageHDR(const tpImageLuminanceHDR &I, const tpImageColorHDR& Ic, tpImageColorHDR &O, double s = 0.65);
	static  void createColorImageHDR(const tpImageColor &I, tpImageColorHDR &O);
	
	static  bool createLuminanceImage(const tpImageColorHDR& I, tpImageLuminanceHDR& O, double fR = 0.2126, double fG = 0.7152, double fB = 0.0722);

	/*
	 * Colorimetrie
	 */
	
	static  void RGBtoXYZ(const tpImageColorHDR& I, tpImageColorHDR& O);
	static  void XYZtoRGB(const tpImageColorHDR& I, tpImageColorHDR& O);
	
	static  void sRGBtoXYZ(const tpImageColorHDR& I, tpImageColorHDR& O);
	static  void XYZtosRGB(const tpImageColorHDR& I, tpImageColorHDR& O);

	static  void XYZtoLAB(const tpImageColorHDR& I, tpImageColorHDR& O);
	static  void LABtoXYZ(const tpImageColorHDR& I, tpImageColorHDR& O);

	static  void RGBtoLAB(tpImageColorHDR& I);
	static  void LABtoRGB(tpImageColorHDR& I);
	
	static  void XYZtoYxy(const tpImageColorHDR& I, tpImageColorHDR& O);
	static  void YxytoXYZ(const tpImageColorHDR& I, tpImageColorHDR& O);

	static  void YCbCrtoRGB(const tpImageColorHDR& I, tpImageColorHDR& O);
	static  void RGBtoYCbCr(const tpImageColorHDR& I, tpImageColorHDR& O);


	/*
	 * Other operations
	 */
	enum ChannelType
	{
		R,
		G,
		B
	};

	static  void ParseChannel(const tpImageLuminanceHDR& I, tpImageColorHDR& O, tpImageConvert::ChannelType c);
	static  void ParseChannel(const tpImageGray& I, tpImageColor& O, tpImageConvert::ChannelType c);

	static  void CopyChannel(const tpImageColor& I, tpImageGray& O, tpImageConvert::ChannelType c);
	static  void CopyChannel(const tpImageColorHDR& I, tpImageLuminanceHDR& O, ChannelType c);

	static  void Log2WithNorm(tpImageColorHDR& I);
	static  void Calibration(tpImageLuminanceHDR& I);

	static void Clamp(tpImageColorHDR& I);
	static void ConvertToFloat(const tpImageLuminanceHDR& I, tpImageLuminanceHDRFloat& O);
	static void ConvertToFloat(const tpImageColorHDR& I, tpImageColorHDRFloat& O);
private:
	// For copy channel
	template <typename T, typename TRes>
	static  void CopyChannelTemplate(const T& I, TRes& O, ChannelType c);

	// For parse channel
	template <class T, class TRes>
	static  void ParseChannel(const T& I, TRes& O, tpImageConvert::ChannelType c);

	// For XYZ => LAB
	static  double FLab(double ratio);
	static  const double eps;
	static  const double k;

	// For sRGB <=> XYZ
	inline static  double FsRBG(double value);
	inline static  double FsXYZ(double value);

	// For Log2Norm
	static  inline double Log2Channel(const double value); 
	static  void Norm(tpImageColorHDR& I);
};

#endif /* TPIMAGECONVERT_H_ */
