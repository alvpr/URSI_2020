/* -*- c++ -*- */
/*
 * Copyright 2021 gr-TFMv5 author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_TFMV5_TX_CONTROLLER_IMPL_H
#define INCLUDED_TFMV5_TX_CONTROLLER_IMPL_H

#include <TFMv5/tx_controller.h>

namespace gr {
namespace TFMv5 {

class tx_controller_impl : public tx_controller
{
private:
    int d_state;
    int d_pstate;
    const pmt::pmt_t d_port;
    void handle_msg_state(pmt::pmt_t msg);

public:
    tx_controller_impl();
    ~tx_controller_impl();

    // Where all the action really happens
    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items);
};

} // namespace TFMv5
} // namespace gr

#endif /* INCLUDED_TFMV5_TX_CONTROLLER_IMPL_H */
