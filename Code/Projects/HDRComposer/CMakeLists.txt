SET(HDRComposer_SRCS
	QChooseOperator.cpp
	QControlPanel.cpp
	QDisplayConfig.cpp
	QDynamicConfig.cpp
	QFenetrePrincipale.cpp
	QImageLabel.cpp
	QToneOperator.cpp
	QToneOperatorAbstract.cpp
	QToneOperatorAshikm.cpp
	QToneOperatorChui.cpp
	QToneOperatorDrago.cpp
	QToneOperatorExp.cpp
	QToneOperatorFormAbstract.cpp
	QToneOperatorLog.cpp
	QToneOperatorPhotographic.cpp
	QToneOperatorPhotographicBurn.cpp
	QToneOperatorPhotographicLocal.cpp
	QToneOperatorRetinex.cpp
	QToneOperatorSchilck.cpp
	QToneOperatorTumblin.cpp
	QWidgetCentral.cpp
	ToneOperatorFactory.cpp
	hdrcomposer.cpp
	main.cpp
)

QT4_WRAP_UI(HDRComposer_SRCS 
	QDisplayConfig.ui
	QDynamicConfig.ui
	hdrcomposer.ui
)

QT4_WRAP_CPP(HDRComposer_SRCS
	QChooseOperator.h
	QControlPanel.h
	QDisplayConfig.h
	QDynamicConfig.h
	QFenetrePrincipale.h
	QImageLabel.h
	QToneOperator.h
	QToneOperatorAbstract.h
	QToneOperatorAshikm.h
	QToneOperatorChui.h
	QToneOperatorDrago.h
	QToneOperatorExp.h
	QToneOperatorFormAbstract.h
	QToneOperatorLog.h
	QToneOperatorPhotographic.h
	QToneOperatorPhotographicBurn.h
	QToneOperatorPhotographicLocal.h
	QToneOperatorRetinex.h
	QToneOperatorSchilck.h
	QToneOperatorTumblin.h
	QWidgetCentral.h
	ToneOperatorFactory.h
	hdrcomposer.h
)

include(${QT_USE_FILE})

INCLUDE_DIRECTORIES(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
	../../Libs/HDRLoader
)

ADD_EXECUTABLE(HDRComposer WIN32 ${HDRComposer_SRCS})

target_link_libraries(
  HDRComposer
  HDRLoader
  ${QT_LIBRARIES}
)

SET_TARGET_PROPERTIES(HDRComposer PROPERTIES
  INSTALL_RPATH ${PROJECT_BUILD_PATH}
  INSTALL_RPATH_USE_LINK_PATH true
)

install(TARGETS HDRComposer RUNTIME DESTINATION ${PROJECT_BUILD_PATH})

