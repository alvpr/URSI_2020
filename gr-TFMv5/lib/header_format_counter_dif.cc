/* -*- c++ -*- */
/*
 * Copyright 2021 gr-TFMv5 author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <gnuradio/digital/header_buffer.h>
#include <gnuradio/digital/diff_encoder_bb.h>
#include <gnuradio/math.h>
#include <string.h>
#include <volk/volk_alloc.hh>
#include <iomanip>
#include <iostream>

#include <gnuradio/io_signature.h>
#include <TFMv5/header_format_counter_dif.h>

#include <gnuradio/blocks/vector_source.h>
#include <gnuradio/blocks/vector_sink.h>
#include <gnuradio/blocks/unpack_k_bits_bb.h>
#include <gnuradio/top_block.h>


namespace gr {
namespace TFMv5 {

header_format_counter_dif::sptr
header_format_counter_dif::make(const std::string& access_code, int threshold, int bps)
{
    return header_format_counter_dif::sptr(
        new header_format_counter_dif(access_code, threshold, bps));
}

header_format_counter_dif::header_format_counter_dif(const std::string& access_code,
                                             int threshold,
                                             int bps)
    : header_format_default(access_code, threshold, bps)
{
    d_counter = 0;
}

header_format_counter_dif::~header_format_counter_dif() {}


int header_format_counter_dif::bits_set(uint8_t number){

    int count = 0;
    int temp = int(number);

    while (number){
      count += number & 1;
      number >>= 1;
   }
    return count;
}



bool header_format_counter_dif::format(int nbytes_in,
                                   const unsigned char* input,
                                   pmt::pmt_t& output,
                                   pmt::pmt_t& info)

{
    // Creating the output pmt copies data; free our own here when done.
    volk::vector<uint8_t> bytes_out(header_nbytes());

    /*
    uint16_t d_bps_16;
    switch(d_bps){
        case 1:
            d_bps_16 = (uint16_t)(60000);
        break;
        case 37:
            d_bps_16 = (uint16_t)(0);
        break;
        case 2:
            d_bps_16 = (uint16_t)(3855);
        break;
        case 4:
            d_bps_16 = (uint16_t)(65535);
        break;            
    }*/

    uint16_t d_bps_16 = (uint16_t)(d_bps);
    uint16_t d_counter_16 = (uint16_t)(d_counter);

    digital::header_buffer header(bytes_out.data());
    header.add_field64(d_access_code, d_access_code_len);
    header.add_field16((uint16_t)(nbytes_in));
    header.add_field16((uint16_t)(nbytes_in));
    header.add_field16((uint16_t)(d_bps_16));
    header.add_field16((uint16_t)(d_counter_16));

    int counter_s = 0;
    const uint8_t* h = header.header();
    
    for(int i = 0; i < header_nbits() / 8; i++){
        counter_s += bits_set(h[i]);
    }
    //std::cout << counter_s <<'\n';
    //counter_s += bits_set((uint8_t)(d_bps_16 >> 8));
    //counter_s += bits_set((uint8_t)(d_bps_16));
    //counter_s += bits_set((uint8_t)(d_counter_16 >> 8));
    //counter_s += bits_set((uint8_t)(d_counter_16));
 

    /*
    std::vector<uint8_t> h;
    h.push_back((uint8_t)(d_bps_16 >> 8));
    h.push_back((uint8_t)(d_bps_16));
    h.push_back((uint8_t)(d_counter_16 >> 8));
    h.push_back((uint8_t)(d_counter_16));
    for (std::vector<uint8_t>::const_iterator i = h.begin(); i != h.end(); ++i){
        std::cout << (int)(*i) << ' ';
    }
    std::cout << '\n';
    std::cout << '\n';
    blocks::vector_source_b::sptr vector_src = blocks::vector_source_b::make(h);
    digital::diff_encoder_bb::sptr diff_encod = digital::diff_encoder_bb::make(2);
    blocks::unpack_k_bits_bb::sptr unpack_bits = blocks::unpack_k_bits_bb::make(1);
    blocks::vector_sink_b::sptr vector_sink = blocks::vector_sink_b::make();
    top_block_sptr tb = make_top_block("diff_encoder");
    tb->connect(vector_src, 0, unpack_bits, 0);
    tb->connect(unpack_bits, 0, diff_encod, 0);
    tb->connect(diff_encod, 0, vector_sink, 0);
    tb->run();
    std::vector<uint8_t> pre = vector_sink->data();
    for (std::vector<uint8_t>::const_iterator i = pre.begin(); i != pre.end(); ++i){
        std::cout << (int)(*i) << ' ';
    }
    std::cout << '\n';
    */

    if((int)(counter_s) % 2 == 0){
        header.add_field16((uint16_t)(0));
    }else{
        header.add_field16((uint16_t)(32768));
    }

    // Package output data into a PMT vector
    output = pmt::init_u8vector(header_nbytes(), bytes_out.data());

    d_counter++;

    return true;
}

size_t header_format_counter_dif::header_nbits() const
{
    return d_access_code_len + 8 * 5 * sizeof(uint16_t);
}

bool header_format_counter_dif::header_ok()
{
    // confirm that two copies of header info are identical
    uint16_t len0 = d_hdr_reg.extract_field16(0);
    uint16_t len1 = d_hdr_reg.extract_field16(16);
    return (len0 ^ len1) == 0;
}

int header_format_counter_dif::header_payload()
{
    uint16_t len = d_hdr_reg.extract_field16(0);
    uint16_t bps = d_hdr_reg.extract_field16(32);
    uint16_t counter = d_hdr_reg.extract_field16(48);

    d_bps = bps;

    /*switch(bps){
        case 0:
            d_bps = 1;
        break; 
        case 3855:
            d_bps = 2;
        break;
        case 65535:
            d_bps = 4;
        break;           
    }*/

    d_info = pmt::make_dict();
    d_info = pmt::dict_add(
        d_info, pmt::intern("payload symbols"), pmt::from_long(8 * len / d_bps)); 
    d_info = pmt::dict_add(d_info, pmt::intern("bps"), pmt::from_long(bps));
    d_info = pmt::dict_add(d_info, pmt::intern("counter"), pmt::from_long(counter));
    //d_info = pmt::dict_add(d_info, pmt::intern("payload_offset"), pmt::from_long(20));
    return static_cast<int>(len);
}

} /* namespace TFMv5 */
} /* namespace gr */
