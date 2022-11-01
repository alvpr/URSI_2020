/*
 * Copyright 2020 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

#include <pybind11/pybind11.h>

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <numpy/arrayobject.h>

namespace py = pybind11;

// Headers for binding functions
/**************************************/
// The following comment block is used for
// gr_modtool to insert function prototypes
// Please do not delete
/**************************************/
// BINDING_FUNCTION_PROTOTYPES(
    void bind_header_format_counter_dif(py::module& m);
    void bind_header_payload_demux_am(py::module& m);
    void bind_energy_scale(py::module& m);
    void bind_dispersion_probe(py::module& m);
    void bind_tx_controller(py::module& m);
    void bind_per_probe(py::module& m);
    void bind_crc32_check(py::module& m);
// ) END BINDING_FUNCTION_PROTOTYPES


// We need this hack because import_array() returns NULL
// for newer Python versions.
// This function is also necessary because it ensures access to the C API
// and removes a warning.
void* init_numpy()
{
    import_array();
    return NULL;
}

PYBIND11_MODULE(TFMv5_python, m)
{
    // Initialize the numpy C API
    // (otherwise we will see segmentation faults)
    init_numpy();

    // Allow access to base block methods
    py::module::import("gnuradio.gr");

    /**************************************/
    // The following comment block is used for
    // gr_modtool to insert binding function calls
    // Please do not delete
    /**************************************/
    // BINDING_FUNCTION_CALLS(
    bind_header_format_counter_dif(m);
    bind_header_payload_demux_am(m);
    bind_energy_scale(m);
    bind_dispersion_probe(m);
    bind_tx_controller(m);
    bind_per_probe(m);
    bind_crc32_check(m);
    // ) END BINDING_FUNCTION_CALLS
}