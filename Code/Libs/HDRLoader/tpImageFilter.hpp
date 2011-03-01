#ifndef TPIMAGEFILTER_H_
#define TPIMAGEFILTER_H_

#include "tpImage.hpp"
#include "tpConfig.h"

typedef tpImage<float> tpFilter;
typedef tpImage<float> tpFilterResult;
typedef tpImage<double> tpFilterResultDouble;

// ============= Operateurs =============
std::ostream& operator<<(std::ostream& out, const tpFilter v);

/**
 * @class tpImageFilter
 * @brief Classe pour appliquer des filtres.
 */
class tpImageFilter {
public:
	// ============= Methodes publiques =============
	/**
	 * Create a filter.
	 * @brief Some Example :
	 * float fV1[] = {-1, 0 ,1};
	 * tpFilter f1 = tpImageFilter::CreateFilter(3,1,fV1,1.0/3.0);
	 * @param h : Height of the filter.
	 * @param w : Width of the filter.
	 * @param values : A float array to normalize.
	 * @param factNorm : Factor to normalize values.
	 * @return the filter created.
	 */
	static  tpFilter CreateFilter(unsigned int h, unsigned int w, float* values, double factNorm);

	/**
	 * Apply a filter to an image.
	 * @param I : The input image.
	 * @param O : The result image.
	 * @param F : The filter.
	 */
	static  bool ApplyFilter(const tpImageGray& I, tpFilterResult& O, const tpFilter& F);
	static  bool ApplyFilter(const tpImageLuminanceHDR& I, tpFilterResultDouble& O, const tpFilter& F);

private:

	template < typename T, typename TRes >
	static  inline void ApplyFilterPixel(const T& I,
									TRes& O,
									const tpFilter& F,
									const int h, const int w,
									const int h2,const int w2);

	template < typename T, typename TRes >
	static  bool ApplyFilter(const T& I, TRes& O, const tpFilter& F);

	static  inline void ComputeRightCoord(int& x, int& y, const int h, const int w);

};

#endif /* TPIMAGEFILTER_H_ */
