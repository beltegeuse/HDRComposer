SET(HDRComposer_SRCS
	QChooseOperator.cpp
	QControlPanel.cpp
	QDisplayConfig.cpp
	QDynamicConfig.cpp
	QFenetrePrincipale.cpp
	QImageLabel.cpp
	QWidgetCentral.cpp
	ToneOperatorFactory.cpp
	hdrcomposer.cpp
	main.cpp
	
	ToneOperators/QToneOperator.cpp
	ToneOperators/QToneOperatorAbstract.cpp
	ToneOperators/QToneOperatorAshikm.cpp
	ToneOperators/QToneOperatorChui.cpp
	ToneOperators/QToneOperatorDrago.cpp
	ToneOperators/QToneOperatorExp.cpp
	ToneOperators/QToneOperatorFormAbstract.cpp
	ToneOperators/QToneOperatorLog.cpp
	ToneOperators/QToneOperatorPhotographic.cpp
	ToneOperators/QToneOperatorPhotographicBurn.cpp
	ToneOperators/QToneOperatorPhotographicLocal.cpp
	ToneOperators/QToneOperatorRetinex.cpp
	ToneOperators/QToneOperatorSchilck.cpp
	ToneOperators/QToneOperatorTumblin.cpp
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
	QWidgetCentral.h
	ToneOperatorFactory.h
	hdrcomposer.h
	
	ToneOperators/QToneOperator.h
	ToneOperators/QToneOperatorTumblin.h
	ToneOperators/QToneOperatorAbstract.h
	ToneOperators/QToneOperatorAshikm.h
	ToneOperators/QToneOperatorChui.h
	ToneOperators/QToneOperatorDrago.h
	ToneOperators/QToneOperatorExp.h
	ToneOperators/QToneOperatorFormAbstract.h
	ToneOperators/QToneOperatorLog.h
	ToneOperators/QToneOperatorPhotographic.h
	ToneOperators/QToneOperatorPhotographicBurn.h
	ToneOperators/QToneOperatorPhotographicLocal.h
	ToneOperators/QToneOperatorRetinex.h
	ToneOperators/QToneOperatorSchilck.h
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

