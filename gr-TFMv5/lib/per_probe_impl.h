/* -*- c++ -*- */
/*
 * Copyright 2021 gr-TFMv5 author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_TFMV5_PER_PROBE_IMPL_H
#define INCLUDED_TFMV5_PER_PROBE_IMPL_H

#include <TFMv5/per_probe.h>

namespace gr {
namespace TFMv5 {

class per_probe_impl : public per_probe
{
private:
    int d_npackets;
    int d_packet_counter;
    int d_crc_packet_counter;
    void packet(pmt::pmt_t msg);
    void crc_packet(pmt::pmt_t msg);

public:
    per_probe_impl(float npackets);
    ~per_probe_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace TFMv5
} // namespace gr

#endif /* INCLUDED_TFMV5_PER_PROBE_IMPL_H */
