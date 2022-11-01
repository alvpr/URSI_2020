/* -*- c++ -*- */
/*
 * Copyright 2021 gr-TFMv5 author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "energy_scale_impl.h"
#include <gnuradio/io_signature.h>
#include <volk/volk.h>
#include <math.h>

namespace gr {
namespace TFMv5 {

//#pragma message("set the following appropriately and remove this warning")
//using input_type = float;
//#pragma message("set the following appropriately and remove this warning")
//using output_type = float;

energy_scale::sptr energy_scale::make(float eavg, float length, float init_scale)
{
    return gnuradio::make_block_sptr<energy_scale_impl>(eavg, length, init_scale);
}


/*
 * The private constructor
 */
energy_scale_impl::energy_scale_impl(float eavg, float length, float init_scale)
    : gr::sync_block("energy_scale",
                     gr::io_signature::make(
                         1 , 1, sizeof(gr_complex)),
                     gr::io_signature::make(
                         1, 1 , sizeof(gr_complex))),
        d_length(length),
        d_eavg(eavg),
        d_scale(init_scale),
        d_counter(0),
        d_acum(0)
{
}

/*
 * Our virtual destructor.
 */
energy_scale_impl::~energy_scale_impl() {}

int energy_scale_impl::work(int noutput_items,
                            gr_vector_const_void_star& input_items,
                            gr_vector_void_star& output_items)
{
    const gr_complex* in = (const gr_complex*)input_items[0];
    gr_complex* out = (gr_complex*)output_items[0];

    
    volk_32fc_s32fc_multiply_32fc(out, in, d_scale, noutput_items);

    for (int i; i < noutput_items; i++){
        d_acum += pow(in[i].real(), 2) + pow(in[i].imag(), 2);
    }

    d_counter += noutput_items;
    if(d_counter >= d_length){
        d_scale = sqrt(d_eavg / (d_acum/d_counter));
        d_counter = 0;
        d_acum = 0;
    }

    // Tell runtime system how many output items we produced.
    return noutput_items;
}

} /* namespace TFMv5 */
} /* namespace gr */
