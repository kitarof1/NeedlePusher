CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(GalilController)

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Debug CACHE STRING
       "Choose the type of build, options are: None Debug Release RelWithDebInfo
MinSizeRel."
       FORCE )
endif()

###### Environment specific #######
SET(CMAKE_OSX_ARCHITECTURES "x86_64"
			    CACHE STRING "Build architectures for OSX" FORCE)
SET(CMAKE_OSX_DEPLOYMENT_TARGET "10.8"
				CACHE STRING "Build deployment target for 10.8" FORCE)
SET(QT_QMAKE_EXECUTABLE /Users/SNR/Slicer4/Qt-build/bin/qmake)
##################################

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

FIND_PACKAGE(Qt4 REQUIRED)
INCLUDE(${QT_USE_FILE})
SET(QT_USE_QTNETWORK TRUE)

ADD_DEFINITIONS(${QT_DEFINITIONS})
ADD_SUBDIRECTORY(src)
