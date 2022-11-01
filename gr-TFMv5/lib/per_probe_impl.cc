/* -*- c++ -*- */
/*
 * Copyright 2021 gr-TFMv5 author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "per_probe_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace TFMv5 {

per_probe::sptr per_probe::make(float npackets) { return gnuradio::make_block_sptr<per_probe_impl>(npackets); }


/*
 * The private constructor
 */
per_probe_impl::per_probe_impl(float npackets)
    : block("per_probe",
                     gr::io_signature::make(0,0,0),
                     gr::io_signature::make(0,0,0)),
                     d_npackets (int(npackets)),
                     d_packet_counter(0),
                     d_crc_packet_counter(0)

{
    message_port_register_in(pmt::mp("packets"));
    message_port_register_in(pmt::mp("crc_packets"));
    set_msg_handler(pmt::mp("packets"), [this](pmt::pmt_t msg) { this->packet(msg); });
    set_msg_handler(pmt::mp("crc_packets"), [this](pmt::pmt_t msg) { this->crc_packet(msg); });
}

/*
 * Our virtual destructor.
 */
per_probe_impl::~per_probe_impl() {}


void per_probe_impl::packet(pmt::pmt_t msg){
    d_packet_counter += 1; 
}

void per_probe_impl::crc_packet(pmt::pmt_t msg){
    d_crc_packet_counter += 1;
    if (d_packet_counter >= d_npackets){
        std::cout << "Rate: " << d_crc_packet_counter << "/" << d_packet_counter <<"\n";
        d_crc_packet_counter = 0;
        d_packet_counter = 0;
    }
}


} /* namespace TFMv5 */
} /* namespace gr */
