SET(HDRLoader_SRCS
	tpException.cpp
	tpImage.cpp
	tpImageIO.cpp
	tpMath.cpp
	
	Tools/tpPerformances.cpp
	Tools/tpReadOption.cpp
	Tools/tpToneOperatorGroup.cpp
	
	Operations/tpOperations.cpp
	Operations/tpOperatorCropping.cpp
	Operations/tpHDROperations.cpp
	Operations/tpImageConvert.cpp
	Operations/tpImageFilter.cpp
	Operations/tpImageThreshold.cpp
	
	Managers/tpDisplayManager.cpp
	Managers/tpDynamicToneMappingManager.cpp
	
	ToneOperators/tpHDRToneOperatorAshikhmin.cpp
	ToneOperators/tpHDRToneOperatorChiu.cpp
	ToneOperators/tpHDRToneOperatorDrago.cpp
	ToneOperators/tpHDRToneOperatorDurandSlow.cpp
	ToneOperators/tpHDRToneOperatorDurandFast.cpp
	ToneOperators/tpHDRToneOperatorExp.cpp
	ToneOperators/tpHDRToneOperatorFilmic.cpp
	ToneOperators/tpHDRToneOperatorFilmicDynamic.cpp
	ToneOperators/tpHDRToneOperatorHistogramme.cpp
	ToneOperators/tpHDRToneOperatorLinear.cpp
	ToneOperators/tpHDRToneOperatorLog.cpp
	ToneOperators/tpHDRToneOperatorLumAbstract.cpp
	ToneOperators/tpHDRToneOperatorPhotographic.cpp
	ToneOperators/tpHDRToneOperatorPhotographicBurn.cpp
	ToneOperators/tpHDRToneOperatorPhotographicLocal.cpp
	ToneOperators/tpHDRToneOperatorRetinex.cpp
	ToneOperators/tpHDRToneOperatorSchlick.cpp
	ToneOperators/tpHDRToneOperatorSigmoid.cpp
	ToneOperators/tpHDRToneOperatorTumblin.cpp
	ToneOperators/tpHDRToneOperatorWard.cpp
	ToneOperators/tpToneOperatorAbstract.cpp
)


INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}
)

ADD_LIBRARY(HDRLoader STATIC ${HDRLoader_SRCS})

IF(WIN32)
target_link_libraries(
  HDRLoader
  ${FREEIMAGE_LIBRARY}
  ${FFTW3_LIBRARY}
  ws2_32
  wsock32
  #gomp
)
ELSE()
target_link_libraries(
  HDRLoader
  ${FREEIMAGE_LIBRARY}
  ${FFTW3_LIBRARY}
  gomp
)
ENDIF()

install(TARGETS HDRLoader 
  RUNTIME DESTINATION ${PROJECT_BUILD_PATH}
  LIBRARY DESTINATION ${PROJECT_BUILD_PATH}
  ARCHIVE DESTINATION ${PROJECT_BUILD_PATH}
)