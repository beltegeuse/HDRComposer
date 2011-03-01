#ifndef __IMAGE__tpImageIO
#define __IMAGE__tpImageIO

#include "tpImage.hpp"
#include "tpConfig.h"

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

/**
 * @class tpImageIO
 * @brief Classe pour faire la lecture de format d'images.
 */
class TP_EXPORT tpImageIO
{
public:
  /**
   * Pour lire du PPM
   * @param I l'image a charger
   * @param filename le path de l'image a lire
   * @return sucess or not
   */
  static  bool readHDR(tpImageColorHDR& I, const char* path);
  static  bool readHDR(tpImageColorHDR& I, const std::string& path);

  static  bool read(tpImageGray& I, const char* path);
  static  bool read(tpImageGray& I, const std::string& path);

  static  bool read(tpImageColor& I, const char* path);
  static  bool read(tpImageColor& I, const std::string& path);

  static  bool write(const tpImageGray& I, const char* filename);
  static  bool write(const tpImageGray& I, const std::string& path);

  static  bool write(const tpImageColor& I, const char* filename);
  static  bool write(const tpImageColor& I, const std::string& path);
};

#endif
