#ifndef ___Image___tpImage
#define ___Image___tpImage

/*
 * Classe tpImage "template"
 */
#include <iostream>
#include <stdio.h>
#include <string.h>

#include "tpException.hpp"
#include "tpConfig.h"

struct tpRGB
{
  unsigned char r;
  unsigned char g;
  unsigned char b;

  tpRGB operator -(const tpRGB& v) const;

};

struct tpRGBf
{
	double r;
	double g;
	double b;
};

struct tpRGBAfloat
{
	float r;
	float g;
	float b;
	float a;
};

/*!

  \class tpImage
  \brief Image gestion class.
*/

template < class T > class tpImage
{
        // ============= Attributs =============
    private:
		// Taille
        unsigned int _width;
        unsigned int _height;

        // L'indexation
        T** _row;

    public:
        T* _bitmap;

        // ============= Methodes, operateurs et constructeurs =============
    public:
        // ========= Constructeurs et destructeur =============
    	/*!
		 * Default constructor. Create an empty image.
		 */
        tpImage();
        /*!
		 * Copy constructor.
		 */
        tpImage(const tpImage<T>& image);
        /*!
		 * Constructor.
		 * \param width : image width.
		 * \param height : image height.
		 */
        tpImage(unsigned int width, unsigned int height);
        /*!
		 * Destructor.
		 */
        virtual ~tpImage();

        // ============= Methodes publiques =============
        /*!
		 * Resize the current image. if you really resize the image, the data image will be loss.
		 * \param width : new image width.
		 * \param height : new image height.
		 */
        void resize(unsigned int height, unsigned int width, bool memorySet = false);
        /*!
		 * \return : current width of the image.
		 */
        inline unsigned int getWidth() const;
        /*!
		 * \return : current height of the image.
		 */
        inline unsigned int getHeight() const;
		/*!
		 * Pour pouvoir copier une image
		 */
		void copy(const tpImage<T>& I);

        // ============= Operateurs =============
        inline T* operator[](unsigned int i);
        inline const T* operator[](unsigned int i) const;
		inline T& GetPixel(unsigned int i, unsigned int j);
        void operator=(const tpImage<T> &image);

    private:
        // ============= Methodes privees =============
        void setWidth(unsigned int width);
        void setHeight(unsigned int height);
};

template< class T > tpImage< T >::tpImage() :
        _width(0),
        _height(0),
        _bitmap(NULL),
        _row(NULL)
        {
        }

template< class T > tpImage< T >::tpImage(const tpImage<T>& image) :
        _width(image._width),
        _height(image._height),
		_bitmap(NULL),
        _row(NULL)
        {
            *this = image;
        }

template<class T>
tpImage<T>::tpImage(unsigned int width, unsigned int height) :
        _width(0),
        _height(0),
        _bitmap(NULL),
        _row(NULL)
        {
            resize(height, width);
        }

template<class T>
tpImage<T>::~tpImage()
        {
            if( _bitmap != NULL )
                delete[] _bitmap;

            if( _row != NULL )
                delete[] _row;
        }

template<class T>
unsigned int tpImage<T>::getWidth() const
        {
            return _width;
        }

template<class T>
unsigned int tpImage<T>::getHeight() const
        {
            return _height;
        }

template<class T>
void tpImage<T>::resize(unsigned int height, unsigned int width, bool memorySet)
        {
            if( (height != _height) || (width != _width) )
            {
                if( _bitmap != NULL )
                {
		  //std::cout << "[DEBUG] Delete Bitmap ... " << std::endl;
                    delete[] _bitmap;
                    _bitmap = NULL;
                }
            }

            if( width != _width )
            {
                if( _row != NULL )
                {
		  //std::cout << "[DEBUG] Delete row ... " << std::endl;
                    delete[] _row;
                    _row = NULL;
                }
            }

            setWidth(width);
            setHeight(height);

            if( _bitmap == NULL )
            {
	      //std::cout << "[DEBUG] new Bitmap ... " << std::endl;
                _bitmap = new T[width*height];
				if(memorySet)
				{
					memset(_bitmap,0,width*height*sizeof(T));
				}
            }

            if( _bitmap == NULL )
            {
                throw tpException("Resize(Impossible d'allouer bipmap)");
            }

            if( _row == NULL )
            {
	      //std::cout << "[DEBUG] new Row ... " << std::endl;
            	_row = new T*[height];
            }

            if( _row == NULL )
            {
                throw tpException("Resize(Impossible d'allouer row");
            }

            for(unsigned int i = 0; i < height; i++)
            {
	      //std::cout << "[DEBUG]  * Row :  " << (int)(i*width) << std::endl;
                _row[i] = _bitmap + i*width;
            }
        }

template<class T>
void tpImage<T>::copy(const tpImage<T>& I)
{
	resize(I.getHeight(), I.getWidth());
	memcpy(_bitmap,I._bitmap,I.getHeight()*I.getWidth()*sizeof(T));
}

template<class T>
void tpImage<T>::setWidth(unsigned int width)
        {
            _width = width;
        }

template<class T>
void tpImage<T>::setHeight(unsigned int height)
        {
            _height = height;
        }

template<class T>
T& tpImage<T>::GetPixel(unsigned int i, unsigned int j)
{
	Assert(i >= 0 && i < getHeight());
	Assert(j >= 0 && j < getWidth());
	return this[i][j];
}

template<class T>
T* tpImage<T>::operator[](unsigned int i)
{
	Assert(i >= 0 && i < getHeight());
	return _row[i];
}

template<class T>
const T* tpImage<T>::operator[](unsigned int i) const
{
	Assert(i >= 0 && i < getHeight());
	return _row[i];
}

template<class T>
void tpImage<T>::operator=(const tpImage<T> &image)
        {
            resize(image.getHeight(), image.getWidth());

            memcpy(_bitmap, image._bitmap, image.getHeight()*image.getWidth()*sizeof(T));

            for(unsigned int i = 0; i < _height; i++)
            {
                _row[i] = _bitmap + i*_width;
            }
        }

/*
 * Les typedef
 */

typedef tpImage<unsigned char> tpImageGray;
typedef tpImage<tpRGB> tpImageColor;
typedef tpImage<tpRGBf> tpImageColorHDR;
typedef tpImage<tpRGBAfloat> tpImageColorHDRFloat;
typedef tpImage<double> tpImageLuminanceHDR;
typedef tpImage<float> tpImageLuminanceHDRFloat;
#endif

