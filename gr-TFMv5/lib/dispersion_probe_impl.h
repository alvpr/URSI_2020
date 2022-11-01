/* -*- c++ -*- */
/*
 * Copyright 2021 gr-TFMv5 author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_TFMV5_DISPERSION_PROBE_IMPL_H
#define INCLUDED_TFMV5_DISPERSION_PROBE_IMPL_H

#include <TFMv5/dispersion_probe.h>

namespace gr {
namespace TFMv5 {

class dispersion_probe_impl : public dispersion_probe
{
private:
    const int d_constellation;
    const int d_length;
    const int d_length_init;
    const float d_th1;
    const float d_th2;
    const float d_th3;
    const float d_th4;
    const float d_th5;
    const float d_th6;
    int d_counter;
    int d_change_up;
    int d_change_down;
    float d_acum;
    bool run;
    const pmt::pmt_t d_port;
    void dispersion(gr_complex sample);
    float distance_2(float x1, float x2, float y1, float y2);
public:
    dispersion_probe_impl(float constellation, float length,float length_init, float th1, float th2, float th3, float th4, float th5, float th6);
    ~dispersion_probe_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace TFMv5
} // namespace gr

#endif /* INCLUDED_TFMV5_DISPERSION_PROBE_IMPL_H */
