/* -*- c++ -*- */
/*
 * Copyright 2021 gr-TFMv5 author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_TFMV5_ENERGY_SCALE_IMPL_H
#define INCLUDED_TFMV5_ENERGY_SCALE_IMPL_H
#include <TFMv5/energy_scale.h>

namespace gr {
namespace TFMv5 {

class energy_scale_impl : public energy_scale
{
private:
    const float d_length;
    const float d_eavg;
    float d_scale;
    float d_counter;
    float d_acum;


public:
    energy_scale_impl(float eavg, float length, float init_scale);
    ~energy_scale_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace TFMv5
} // namespace gr

#endif /* INCLUDED_TFMV5_ENERGY_SCALE_IMPL_H */
