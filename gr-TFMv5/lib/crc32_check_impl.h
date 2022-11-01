/* -*- c++ -*- */
/*
 * Copyright 2021 gr-TFMv5 author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_TFMV5_CRC32_CHECK_IMPL_H
#define INCLUDED_TFMV5_CRC32_CHECK_IMPL_H

#include <TFMv5/crc32_check.h>
#include <boost/crc.hpp>

namespace gr {
namespace TFMv5 {

class crc32_check_impl : public crc32_check
{
private:
    boost::crc_optimal<32, 0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, true> d_crc_impl;

    pmt::pmt_t d_in_port;
    pmt::pmt_t d_inst_port;
    pmt::pmt_t d_outst_port;
    pmt::pmt_t d_out_port;

    void check(pmt::pmt_t msg);
    void change_state(pmt::pmt_t msg);

    int d_npass;
    int d_ntotal;
    int d_npackets;
    float d_r1;
    float d_r2;
    float d_r3;
    int state;
    int state_max;
    int counter;

public:
    crc32_check_impl(float npackets,float r1, float r2, float r3);
    ~crc32_check_impl();

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items);
};

} // namespace TFMv5
} // namespace gr

#endif /* INCLUDED_TFMV5_CRC32_CHECK_IMPL_H */
