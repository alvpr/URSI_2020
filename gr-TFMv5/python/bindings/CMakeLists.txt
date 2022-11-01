# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT TFMv5_sources)
    MESSAGE(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT TFMv5_sources)

########################################################################
# Check for pygccxml
########################################################################
GR_PYTHON_CHECK_MODULE_RAW(
    "pygccxml"
    "import pygccxml"
    PYGCCXML_FOUND
    )

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND TFMv5_python_files
    header_format_counter_dif_python.cc
    header_payload_demux_am_python.cc
    energy_scale_python.cc
    dispersion_probe_python.cc
    tx_controller_python.cc
    per_probe_python.cc
    crc32_check_python.cc python_bindings.cc)

GR_PYBIND_MAKE_OOT(TFMv5 
   ../..
   gr::TFMv5
   "${TFMv5_python_files}")

install(TARGETS TFMv5_python DESTINATION ${GR_PYTHON_DIR}/TFMv5 COMPONENT pythonapi)
