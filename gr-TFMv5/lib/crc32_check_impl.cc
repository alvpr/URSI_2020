/* -*- c++ -*- */
/*
 * Copyright 2021 gr-TFMv5 author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "crc32_check_impl.h"
#include <gnuradio/io_signature.h>
#include <volk/volk.h>

namespace gr {
namespace TFMv5 {


crc32_check::sptr crc32_check::make(float npackets,float r1, float r2, float r3)
{
    return gnuradio::make_block_sptr<crc32_check_impl>(npackets, r1, r2, r3);
}


/*
 * The private constructor
 */
crc32_check_impl::crc32_check_impl(float npackets, float r1, float r2, float r3)
    : gr::block("crc32_check", io_signature::make(0, 0, 0), io_signature::make(0, 0, 0)),
    d_npass(0),
    d_ntotal(0),
    d_npackets(int(npackets)),
    d_r1(r1),
    d_r2(r2),
    d_r3(r3)
    
{
    state = 0;
    state_max = 3;
    counter = 0;

    d_in_port = pmt::mp("in");
    d_inst_port = pmt::mp("in_state");
    d_out_port = pmt::mp("out");
    d_outst_port = pmt::mp("out_state");

    message_port_register_in(d_in_port);
    message_port_register_in(d_inst_port);
    message_port_register_out(d_outst_port);
    message_port_register_out(d_out_port);

    set_msg_handler(d_in_port, [this](pmt::pmt_t msg) { this->check(msg); });
    set_msg_handler(d_inst_port, [this](pmt::pmt_t msg) { this->change_state(msg); });
}

/*
 * Our virtual destructor.
 */
crc32_check_impl::~crc32_check_impl() {}

void crc32_check_impl::check(pmt::pmt_t msg)
{
    // extract input pdu
    pmt::pmt_t meta(pmt::car(msg));
    pmt::pmt_t bytes(pmt::cdr(msg));

    unsigned int crc;
    float rate;
    size_t pkt_len(0);
    const uint8_t* bytes_in = pmt::u8vector_elements(bytes, pkt_len);

    d_crc_impl.reset();
    d_crc_impl.process_bytes(bytes_in, pkt_len - 4);
    crc = d_crc_impl();
    d_ntotal++;

    if (crc == *(unsigned int*)(bytes_in + pkt_len - 4)) { 
        d_npass++;
        pmt::pmt_t output = pmt::init_u8vector(pkt_len - 4, bytes_in);
        pmt::pmt_t msg_pair = pmt::cons(meta, output);
        message_port_pub(d_out_port, msg_pair);
    }

    if(d_ntotal >= d_npackets){
        rate = float(d_npass) / float(d_ntotal);
        std::cout << "Rate: " << d_npass << "/" << d_ntotal <<"\n";
        d_npass = 0;
        d_ntotal = 0;
        switch (state){
        case 1:
            if (rate < d_r1){
                counter ++;
                if (counter >= 2){
                    counter = 0;
                    state = 0;
                    state_max = 0;
                    message_port_pub(d_outst_port, pmt::cons(pmt::string_to_symbol("Index"), pmt::from_long(state)));
                }
            }else{counter = 0;}
        break;
        case 2:
            if (rate < d_r2){
                counter ++;
                if (counter >= 2){
                    counter = 0;
                    state = 1;
                    state_max = 1;
                    message_port_pub(d_outst_port, pmt::cons(pmt::string_to_symbol("Index"), pmt::from_long(state)));
                }
            }else{counter = 0;}
        break;
        case 3:
            if (rate < d_r3){
                counter ++;
                if (counter >= 2){
                    counter = 0;
                    state = 2;
                    state_max = 2;
                    message_port_pub(d_outst_port, pmt::cons(pmt::string_to_symbol("Index"), pmt::from_long(state)));
                }
            }else{counter = 0;}
        break;
        }
    }


    
}

void crc32_check_impl::change_state(pmt::pmt_t msg)
{
    pmt::pmt_t data = pmt::cdr(msg);
    state = pmt::to_long(data);
    if(state <= state_max){
        message_port_pub(d_outst_port, pmt::cons(pmt::string_to_symbol("Index"), pmt::from_long(state)));
    }
    else{
        message_port_pub(d_outst_port, pmt::cons(pmt::string_to_symbol("Index"), pmt::from_long(state_max)));
    }
}



int crc32_check_impl::general_work(int noutput_items,
                                   gr_vector_int& ninput_items,
                                   gr_vector_const_void_star& input_items,
                                   gr_vector_void_star& output_items)
{
    return noutput_items;
}

} /* namespace TFMv5 */
} /* namespace gr */
