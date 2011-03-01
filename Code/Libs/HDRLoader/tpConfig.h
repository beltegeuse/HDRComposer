/**************************************************************************** 
 * 
 * $Id$ 
 * 
 * Copyright (C) 1998-2006 Inria. All rights reserved. 
 * 
 * This software was developed at: 
 * IRISA/INRIA Rennes 
 * Projet Lagadic 
 * Campus Universitaire de Beaulieu 
 * 35042 Rennes Cedex 
 * http://www.irisa.fr/lagadic 
 * 
 * Description: 
 * Project configuration. 
 * 
 * Authors: 
 * Fabien Spindler 
 * 
 *****************************************************************************/ 
 
#ifndef tpConfig_h 
#define tpConfig_h 
 
// Under Windows, for shared libraries (DLL) we need to define export on 
// compilation or import on use (like a third party project). 
// We exploit here the fact that cmake auto set xxx_EXPORTS (with S) on  
// compilation. 
#if defined (WIN32) && 0
#  ifdef tp_EXPORTS && 1 
#    define TP_EXPORT __declspec(dllexport) 
#  else   
#    define TP_EXPORT __declspec(dllimport) 
#  endif  
#else 
#  define TP_EXPORT 
#endif 
 
#endif 
