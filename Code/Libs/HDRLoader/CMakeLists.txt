SET(HDRLoader_SRCS
	tpDisplayManager.cpp
	tpDynamicToneMappingManager.cpp
	tpException.cpp
	tpHDROperations.cpp
	tpHDRToneOperatorAshikhmin.cpp
	tpHDRToneOperatorChiu.cpp
	tpHDRToneOperatorDrago.cpp
	tpHDRToneOperatorDurand.cpp
	tpHDRToneOperatorExp.cpp
	tpHDRToneOperatorFilmic.cpp
	tpHDRToneOperatorFilmicDynamic.cpp
	tpHDRToneOperatorHistogramme.cpp
	tpHDRToneOperatorLinear.cpp
	tpHDRToneOperatorLog.cpp
	tpHDRToneOperatorLumAbstract.cpp
	tpHDRToneOperatorPhotographic.cpp
	tpHDRToneOperatorPhotographicBurn.cpp
	tpHDRToneOperatorPhotographicLocal.cpp
	tpHDRToneOperatorRetinex.cpp
	tpHDRToneOperatorSchlick.cpp
	tpHDRToneOperatorSigmoid.cpp
	tpHDRToneOperatorTumblin.cpp
	tpHDRToneOperatorWard.cpp
	tpImage.cpp
	tpImageConvert.cpp
	tpImageFilter.cpp
	tpImageIO.cpp
	tpImageManager.cpp
	tpImageThreshold.cpp
	tpMath.cpp
	tpOperations.cpp
	tpOperatorCropping.cpp
	tpPerformances.cpp
	tpReadOption.cpp
	tpToneOperatorAbstract.cpp
	tpToneOperatorGroup.cpp
)


INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}
)

ADD_LIBRARY(HDRLoader SHARED ${HDRLoader_SRCS})

target_link_libraries(
  HDRLoader
  ${FREEIMAGE_LIBRARY}
  ws2_32
  wsock32
  gomp
)

install(TARGETS HDRLoader 
  RUNTIME DESTINATION ${PROJECT_BUILD_PATH}
  LIBRARY DESTINATION ${PROJECT_BUILD_PATH}
  ARCHIVE DESTINATION ${PROJECT_BUILD_PATH}
)