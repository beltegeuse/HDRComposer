// HDRLoaderTest.cpp : définit le point d'entrée pour l'application console.
//

#include <iostream>

#include <tpMath.h>
#include <Operations/tpImageFilter.hpp>
#include <tpImage.hpp>
#include <tpImageIO.hpp>
#include <Operations/tpImageConvert.hpp>
#include <Operations/tpHDROperations.h>
#include <Operations/tpOperations.h>
#include <Operations/tpOperatorCropping.h>
#include <Tools/tpToneOperatorGroup.h>
#include <Managers/tpDisplayManager.h>

void ToneMappingColorSaturation(const std::string& path, const std::string & nom, bool clamp, double s = 0.65)
{
	std::cout << " *** ToneMappingColorSaturation *** " << std::endl;

	tpImageGray imG;
	tpImageColorHDR im;
	tpImageColorHDR im2;
	tpImageLuminanceHDR imL;

	// On va lire l'image
	// RenoSuburb01_sm.hdr
	// aisle1.hdr
	// office3.hdr
	// buildingInside4.hdr
	tpImageIO::readHDR(im,path);

	// === On la met en forme carre
	//int s = std::min(im2.getHeight(), im2.getWidth());
	//tpOperations::Resize(im2,im,0,0,s,s);

	// On converti en lumineance
	tpImageConvert::createLuminanceImage(im,imL);

	// On regarde quelques valeurs interessantes
	std::cout << "*** Info Luminance ***" << std::endl;
	std::cout << " Min : " << tpHDROperations::GetMin(imL) << std::endl;
	std::cout << " Max : " << tpHDROperations::GetMax(imL) << std::endl;
	std::cout << " Mean : " << tpHDROperations::GetMean(imL) << std::endl;
	
	// On compresse (with group)
	tpToneOperatorGroup tpG;
	tpG.AddAllOperators();

	if(clamp)
	{
		tpOperatorCropping crop(0.07,0.02);
		tpG.ApplyAllSaturation(im,"",nom + "_s.png",&crop,s);
	}
	else
	{
		tpG.ApplyAllSaturation(im,"",nom + "_s.png", 0, s);
	}
}

void ToneMappingTest()
{
	std::cout << "===== ToneMappingTest =======" << std::endl;

	// On va lire l'image
	// RenoSuburb01_sm.hdr
	// aisle1.hdr
	// office3.hdr
	// buildingInside4.hdr
	// memorial.hdr
	// mpi_atrium_1.hdr
	// mpi_office.hdr
	// nancy_church_1.hdr
	// nancy_church_3.hdr
	std::string path = "../Donnees/nancy_church_1.hdr";
	std::string nom = "nancy_church_1";
	bool clamp = false;

	ToneMappingColorSaturation(path, nom, clamp, 0.50);

	std::cout << "=====================================" << std::endl;
}

void GaussianTest()
{

	std::cout << "===== GaussianTest =======" << std::endl;

	tpImageGray imG;
	tpFilterResult r1;
	tpFilterResult r2;

	std::cout << " * Lecture ... " << std::endl;

	tpImageIO::read(imG,"Donnees/gun.png");

	std::cout << " * Creation Noyeaux gaussiens ... " << std::endl;
	
	tpFilter g1 = tpMath::GaussianKernel2D((float)1.0);
	tpFilter g2 = tpMath::GaussianKernel2D((float)2.0);

	std::cout << " * Filtrage ... "  << std::endl;

	tpImageFilter::ApplyFilter(imG,r1,g1);
	tpImageFilter::ApplyFilter(imG,r2,g2);

	std::cout << " * Conversion ... " << std::endl;

	tpImageGray i1,i2;

	tpImageConvert::createGrayImageFromFilterResult(r1,i1);
	tpImageConvert::createGrayImageFromFilterResult(r2,i2);

	std::cout << " * Ecriture ... " << std::endl;

	tpImageIO::write(i1,"resGaussian1.png");
	tpImageIO::write(i2,"resGaussian2.png");

	std::cout << "=====================================" << std::endl;

}

void ColorimetrieChannelTest()
{
	std::cout << " *** ColorimetrieChannelTest *** " << std::endl;

	tpImageColor im;
	tpImageColor im2;
	tpImageColor imD;

	tpImageGray imR, imG, imB;

	tpImageIO::read(im,"Donnees/gun.png");

	tpImageConvert::CopyChannel(im, imR, tpImageConvert::R);
	tpImageConvert::CopyChannel(im, imG, tpImageConvert::G);
	tpImageConvert::CopyChannel(im, imB, tpImageConvert::B);

	tpImageIO::write(imR, "channel_test_gun_R.png");
	tpImageIO::write(imG, "channel_test_gun_G.png");
	tpImageIO::write(imB, "channel_test_gun_B.png");

	tpImageConvert::createColorImage(imR, imG, imB, im2);

	tpImageIO::write(im2, "channel_test_gun_all.png");

	tpOperations::Distance(im, im2, imD);
	
	if(tpOperations::isAllBlack(imD))
	{
		std::cout << " * Pass ! " << std::endl;
	}
	else
	{
		std::cout << " * Error ! " << std::endl;
	}
}

void ColorimetrieConvertSimpleTest()
{
	std::cout << " *** ColorimetrieConvertSimpleTest *** " << std::endl;
	
	tpImageColor im;
	tpImageColor im2;
	tpImageColor imD;

	tpImageColorHDR imHDR;

	tpImageIO::read(im,"Donnees/gun.png");
	
	tpImageConvert::createColorImageHDR(im, imHDR);
	
	tpImageConvert::createColorImage(imHDR, im2);

	tpImageIO::write(im2, "col_test_gun.png");

	tpOperations::Distance(im, im2, imD);
	if(tpOperations::isAllBlack(imD))
	{
		std::cout << " * Pass ! " << std::endl;
	}
	else
	{
		std::cout << " * Error ! " << std::endl;
	}
	
}

void ColorimetrieRGBtoXYZTest()
{
	std::cout << " *** ColorimetrieRGBtoXYZTest *** " << std::endl;

	tpImageColor im;
	tpImageIO::read(im,"Donnees/gun.png");

	tpImageColorHDR imHDR;
	tpImageConvert::createColorImageHDR(im, imHDR);

	tpHDROperations::PrintInformation(imHDR, "Original (RGB)");

	tpImageColorHDR imTempHDR;
	tpImageConvert::sRGBtoXYZ(imHDR, imTempHDR);
	tpImageConvert::XYZtosRGB(imTempHDR, imHDR);

	tpHDROperations::PrintInformation(imTempHDR, "XYZ");
	tpHDROperations::PrintInformation(imHDR, "Return (RGB)");

	tpImageLuminanceHDR L;
	tpImageConvert::CopyChannel(imTempHDR, L, tpImageConvert::R);
	tpHDROperations::PrintInformation(L, "L");

	tpImageLuminanceHDR a;
	tpImageConvert::CopyChannel(imTempHDR, a, tpImageConvert::G);
	tpHDROperations::PrintInformation(a, "a");

	tpImageLuminanceHDR b;
	tpImageConvert::CopyChannel(imTempHDR, b, tpImageConvert::B);
	tpHDROperations::PrintInformation(b, "b");

	tpImageColor im2;
	tpImageConvert::createColorImage(imHDR,im2);

	tpImageColor imD;
	tpOperations::Distance(im, im2, imD);
	if(tpOperations::isAllBlack(imD))
	{
		std::cout << " * Pass ! " << std::endl;
	}
	else
	{
		std::cout << " * Error ! " << std::endl;
	}

	tpImageIO::write(im2, "col_test_xyz_gun.png");
	tpImageIO::write(imD, "col_test_xyz_diff_gun.png");
}

void ColorimetrieRGBtoLAB()
{
	std::cout << " *** ColorimetrieRGBtoLAB *** " << std::endl;

	tpImageColor im;
	tpImageIO::read(im,"Donnees/gun.png");

	tpImageColorHDR imHDR;
	tpImageConvert::createColorImageHDR(im, imHDR);

	tpHDROperations::PrintInformation(imHDR, "Original (RGB)");

	tpImageColorHDR imTempHDRXYZ;
	tpImageColorHDR imTempHDRXYZr;
	tpImageColorHDR imTempHDRLAB;
	tpImageColorHDR imTempHDRRGBr;

	tpImageConvert::sRGBtoXYZ(imHDR, imTempHDRXYZ);
	tpImageConvert::XYZtoLAB(imTempHDRXYZ, imTempHDRLAB);

	tpImageLuminanceHDR Y;
	tpImageConvert::CopyChannel(imTempHDRXYZ, Y, tpImageConvert::G);
	tpHDROperations::PrintInformation(Y, "Y");

	tpImageLuminanceHDR L;
	tpImageConvert::CopyChannel(imTempHDRLAB, L, tpImageConvert::R);
	tpHDROperations::PrintInformation(L, "L");

	tpHDROperations::PrintInformation(imTempHDRLAB, "L*a*b*");

	tpImageConvert::LABtoXYZ(imTempHDRLAB, imTempHDRXYZr);
	tpImageConvert::XYZtosRGB(imTempHDRXYZr, imTempHDRRGBr);

	tpImageColor im2;
	tpImageConvert::createColorImage(imTempHDRRGBr,im2);

	tpImageColor imD;
	tpOperations::Distance(im, im2, imD);
	if(tpOperations::isAllBlack(imD))
	{
		std::cout << " * Pass ! " << std::endl;
	}
	else
	{
		std::cout << " * Error ! " << std::endl;
	}

	tpImageIO::write(im2, "col_test_lab_gun.png");
	tpImageIO::write(imD, "col_test_lab_diff_gun.png");
	
}

void ColorimetrieTest()
{
	std::cout << "======== ColorimetrieTest ===========" << std::endl;

	ColorimetrieChannelTest();
	ColorimetrieConvertSimpleTest();
	ColorimetrieRGBtoXYZTest();
	ColorimetrieRGBtoLAB();

	std::cout << "=====================================" << std::endl;
}

int main(int argc, char* argv[])
{
	std::cout << "===== Lancement HDRLoaderTest =======" << std::endl;

	tpDisplayManager::Instance()->Initialise(200,0.5,300);

	ToneMappingTest();
	//GaussianTest();
	//ColorimetrieTest();

	std::cout << "=====================================" << std::endl;

	// Attente pour quitter
	char c;
	std::cout << "Une touche pour quitter" << std::endl;
	std::cin >> c;

	return 0;
}

