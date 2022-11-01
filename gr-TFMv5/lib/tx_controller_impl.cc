/* -*- c++ -*- */
/*
 * Copyright 2021 gr-TFMv5 author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "tx_controller_impl.h"
#include <gnuradio/io_signature.h>
#include <cstdlib>

namespace gr {
namespace TFMv5 {

//#pragma message("set the following appropriately and remove this warning")
//using output_type = float;

tx_controller::sptr tx_controller::make()
{
    return gnuradio::make_block_sptr<tx_controller_impl>();
}


/*
 * The private constructor
 */
tx_controller_impl::tx_controller_impl()
    : gr::block("tx_controller",
                     gr::io_signature::make(0, 0, 0),
                     gr::io_signature::make(0, 0, 0)),
                     d_state(0),
                     d_pstate(0),
                     d_port(pmt::mp("index"))
{
    message_port_register_out(d_port);
    message_port_register_in(pmt::mp("state"));
    set_msg_handler(pmt::mp("state"), [this](pmt::pmt_t msg) { this->handle_msg_state(msg); });
}

/*
 * Our virtual destructor.
 */
tx_controller_impl::~tx_controller_impl() {}

void tx_controller_impl::handle_msg_state(pmt::pmt_t msg){
    
    if (pmt::is_pdu(msg)) {
        size_t offset = 0;
        int val_1 = 0;
        int val_2= 0;
        const auto& meta = pmt::car(msg);
        const auto& vector = pmt::cdr(msg);
        const uint8_t* d =(const uint8_t*)pmt::uniform_vector_elements(vector, offset);
        size_t len = pmt::length(vector);
        val_1= static_cast<unsigned int>(d[len-2]);
        val_2 = static_cast<unsigned int>(d[len-1]);
        if(val_1 == 0 && val_2 == 0&& d_pstate != 0){
            d_pstate = 0;
        }else if (val_1 == 85 && val_2 == 85 && d_pstate != 1){
            d_pstate = 1;
        }else if (val_1 == 170 && val_2 == 170 && d_pstate != 2){
            d_pstate = 2;
        }else if (val_1 == 255 && val_2 == 255 && d_pstate != 3){
            d_pstate = 3;
        }
        if(d_state != d_pstate){
                d_state = d_pstate;
                message_port_pub(d_port, pmt::cons(pmt::string_to_symbol("Index"), pmt::from_long(d_state)));
        }
    }
}

int tx_controller_impl::general_work(int noutput_items,
                                   gr_vector_int& ninput_items,
                                   gr_vector_const_void_star& input_items,
                                   gr_vector_void_star& output_items)
{
    return noutput_items;
}

} /* namespace TFMv5 */
} /* namespace gr */
