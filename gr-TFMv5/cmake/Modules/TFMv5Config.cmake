if(NOT PKG_CONFIG_FOUND)
    INCLUDE(FindPkgConfig)
endif()
PKG_CHECK_MODULES(PC_TFMV5 TFMv5)

FIND_PATH(
    TFMV5_INCLUDE_DIRS
    NAMES TFMv5/api.h
    HINTS $ENV{TFMV5_DIR}/include
        ${PC_TFMV5_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    TFMV5_LIBRARIES
    NAMES gnuradio-TFMv5
    HINTS $ENV{TFMV5_DIR}/lib
        ${PC_TFMV5_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/TFMv5Target.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(TFMV5 DEFAULT_MSG TFMV5_LIBRARIES TFMV5_INCLUDE_DIRS)
MARK_AS_ADVANCED(TFMV5_LIBRARIES TFMV5_INCLUDE_DIRS)
