/* -*- c++ -*- */
/*
 * Copyright 2021 gr-TFMv5 author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "dispersion_probe_impl.h"
#include <gnuradio/io_signature.h>
#include <math.h>

namespace gr {
namespace TFMv5 {

//#pragma message("set the following appropriately and remove this warning")
//using input_type = float;

dispersion_probe::sptr dispersion_probe::make(float constellation, float length, float length_init, float th1, float th2, float th3, float th4,
float th5, float th6)
{
    return gnuradio::make_block_sptr<dispersion_probe_impl>(constellation, length, length_init, th1, th2, th3, th4, th5, th6);
}


/*
 * The private constructor
 */
dispersion_probe_impl::dispersion_probe_impl(float constellation, float length, float length_init, float th1, float th2, float th3, float th4,
float th5, float th6)
    : gr::sync_block("dispersion_probe",
                     gr::io_signature::make(
                         1, 1, sizeof(gr_complex)),
                     gr::io_signature::make(0, 0, 0)),

        d_constellation(int(constellation)),
        d_length(int(length)),
        d_length_init(int(length_init)),
        d_th1(th1),
        d_th2(th2),
        d_th3(th3),
        d_th4(th4),
        d_th5(th5),
        d_th6(th6),
        d_counter(0),
        d_change_up(0),
        d_change_down(0),
        d_acum(0),
        run(false),
        d_port(pmt::mp("threshold"))
{
     message_port_register_out(d_port);
}

/*
 * Our virtual destructor.
 */
dispersion_probe_impl::~dispersion_probe_impl() {}

float dispersion_probe_impl::distance_2(float x1, float y1, float x2, float y2){
    return pow(x1 - x2, 2) + pow(y1 - y2, 2);
}

void dispersion_probe_impl::dispersion(gr_complex sample){
    float r = sample.real();
    float i = sample.imag();
    float d = 0;
    float dispersion = 0;
    d_counter ++;

    if (!run){
        if (d_counter >= d_length_init){
            d_counter = 0;
            run = true;
        }
        return;
    }

    switch(d_constellation){

        case 1:
            d = 1/sqrt(2);
            if(r >= 0 && i >= 0){
                d_acum += distance_2(r, i, d, d);
            }
            else if (r > 0 && i < 0){
                d_acum += distance_2(r, i, d, -1*d);
            }
            else if (r < 0 && i > 0){
                d_acum += distance_2(r, i, -d, 1*d);
            }
            else{
                d_acum += distance_2(r, i, -d, -1*d);
            }
        break;

        case 2:
            //d = sqrt(10)/10.0;
            d = 0.3339;
            if(r >= 0 && i >= 0){
                if(r >= 2*d && i >= 2*d){
                    d_acum += distance_2(r, i, 3*d, 3*d);
                }
                else if(r > 2*d && i < 2*d){
                    d_acum += distance_2(r, i, 3*d, d);
                }
                else if(r < 2*d && i > 2*d){
                    d_acum += distance_2(r, i, d, 3*d);
                }
                else{
                    d_acum += distance_2(r, i, d, d);
                }
            }
            else if(r > 0 && i < 0){
                if(r >= 2*d && i >= -2*d){
                    d_acum += distance_2(r, i, 3*d, -1*d);
                }
                else if(r > 2*d && i < -2*d){
                    d_acum += distance_2(r, i, 3*d, -3*d);
                }
                else if(r < 2*d && i > -2*d){
                    d_acum += distance_2(r, i, d, -1*d);
                }
                else{
                    d_acum += distance_2(r, i, d, -3*d);
                }
            }
            else if(r < 0 && i > 0){
                if(r >= -2*d && i >= 2*d){
                    d_acum += distance_2(r, i, -1*d, 3*d);
                }
                else if(r > -2*d && i < 2*d){
                    d_acum += distance_2(r, i, -1*d, d);
                }
                else if(r < -2*d && i > 2*d){
                    d_acum += distance_2(r, i, -3*d, 3*d);
                }
                else{
                    d_acum += distance_2(r, i, -3*d, d);
                }
            }
            else{
                if(r >= -2*d && i >= -2*d){
                    d_acum += distance_2(r, i, -1*d, -1*d);
                }
                else if(r > -2*d && i < -2*d){
                    d_acum += distance_2(r, i, -1*d, -3*d);
                }
                else if(r < -2*d && i > -2*d){
                    d_acum += distance_2(r, i, -3*d, -1*d);
                }
                else{
                    d_acum += distance_2(r, i, -3*d, -3*d);
                }
            }
        break;

        case 3:
            d = 0.164288;
            if(r >= 0 && i >= 0){
                if(r >= 4*d && i >= 4*d){
                    if(r >= 6*d && i >= 6*d){
                        d_acum += distance_2(r, i, 7*d, 7*d);
                    }
                    else if(r >= 6*d && i < 6*d){
                        d_acum += distance_2(r, i, 7*d, 5*d);
                    }
                    else if(r < 6*d && i > 6*d){
                        d_acum += distance_2(r, i, 5*d, 7*d);
                    }
                    else{
                        d_acum += distance_2(r, i, 5*d, 5*d);
                    }
                }
                else if(r > 4*d && i < 4*d){
                    if(r >= 6*d && i >= 2*d){
                        d_acum += distance_2(r, i, 7*d, 3*d);
                    }
                    else if(r >= 6*d && i < 2*d){
                        d_acum += distance_2(r, i, 7*d, 1*d);
                    }
                    else if(r < 6*d && i > 2*d){
                        d_acum += distance_2(r, i, 5*d, 3*d);
                    }
                    else{
                        d_acum += distance_2(r, i, 5*d, 1*d);
                    }
                }
                else if(r < 4*d && i > 4*d){
                    if(r >= 2*d && i >= 6*d){
                        d_acum += distance_2(r, i, 3*d, 7*d);
                    }
                    else if(r >= 2*d && i < 6*d){
                        d_acum += distance_2(r, i, 3*d, 5*d);
                    }
                    else if(r < 2*d && i > 6*d){
                        d_acum += distance_2(r, i, 1*d, 7*d);
                    }
                    else{
                        d_acum += distance_2(r, i, 1*d, 5*d);
                    }
                }
                else{
                    if(r >= 2*d && i >= 2*d){
                        d_acum += distance_2(r, i, 3*d, 3*d);
                    }
                    else if(r >= 2*d && i < 2*d){
                        d_acum += distance_2(r, i, 3*d, 1*d);
                    }
                    else if(r < 2*d && i > 2*d){
                        d_acum += distance_2(r, i, 1*d, 3*d);
                    }
                    else{
                        d_acum += distance_2(r, i, 1*d, 1*d);
                    }
                }          
            }
            else if(r >= 0 && i < 0){
                if(r >= 4*d && i >= -4*d){
                    if(r >= 6*d && i >= -2*d){
                        d_acum += distance_2(r, i, 7*d, -1*d);
                    }
                    else if(r >= 6*d && i < -2*d){
                        d_acum += distance_2(r, i, 7*d, -3*d);
                    }
                    else if(r < 6*d && i > -2*d){
                        d_acum += distance_2(r, i, 5*d, -1*d);
                    }
                    else{
                        d_acum += distance_2(r, i, 5*d, -3*d);
                    }
                }
                else if(r > 4*d && i < -4*d){
                    if(r >= 6*d && i >= -6*d){
                        d_acum += distance_2(r, i, 7*d, -5*d);
                    }
                    else if(r >= 6*d && i < -6*d){
                        d_acum += distance_2(r, i, 7*d, -7*d);
                    }
                    else if(r < 6*d && i > -6*d){
                        d_acum += distance_2(r, i, 5*d, -5*d);
                    }
                    else{
                        d_acum += distance_2(r, i, 5*d, -7*d);
                    }
                }
                else if(r < 4*d && i > -4*d){
                    if(r >= 2*d && i >= -2*d){
                        d_acum += distance_2(r, i, 3*d, -1*d);
                    }
                    else if(r >= 2*d && i < -2*d){
                        d_acum += distance_2(r, i, 3*d, -3*d);
                    }
                    else if(r < 2*d && i > -2*d){
                        d_acum += distance_2(r, i, 1*d, -1*d);
                    }
                    else{
                        d_acum += distance_2(r, i, 1*d, -3*d);
                    }
                }
                else{
                    if(r >= 2*d && i >= -6*d){
                        d_acum += distance_2(r, i, 3*d, -5*d);
                    }
                    else if(r >= 2*d && i < -6*d){
                        d_acum += distance_2(r, i, 3*d, -7*d);
                    }
                    else if(r < 2*d && i > -6*d){
                        d_acum += distance_2(r, i, 1*d, -5*d);
                    }
                    else{
                        d_acum += distance_2(r, i, 1*d, -7*d);
                    }
                }          
            }
            else if(r < 0 && i > 0){
                if(r >= -4*d && i >= 4*d){
                    if(r >= -2*d && i >= 6*d){
                        d_acum += distance_2(r, i, -1*d, 7*d);
                    }
                    else if(r >= -2*d && i < 6*d){
                        d_acum += distance_2(r, i, -1*d, 5*d);
                    }
                    else if(r < -2*d && i > 6*d){
                        d_acum += distance_2(r, i, -3*d, 7*d);
                    }
                    else{
                        d_acum += distance_2(r, i, -3*d, 5*d);
                    }
                }
                else if(r > -4*d && i < 4*d){
                    if(r >= -2*d && i >= 2*d){
                        d_acum += distance_2(r, i, -1*d, 3*d);
                    }
                    else if(r >= -2*d && i < 2*d){
                        d_acum += distance_2(r, i, -1*d, 1*d);
                    }
                    else if(r < -2*d && i > 2*d){
                        d_acum += distance_2(r, i, -3*d, 3*d);
                    }
                    else{
                        d_acum += distance_2(r, i, -3*d, 1*d);
                    }
                }
                else if(r < -4*d && i > 4*d){
                    if(r >= -6*d && i >= 6*d){
                        d_acum += distance_2(r, i, -5*d, 7*d);
                    }
                    else if(r >= -6*d && i < 6*d){
                        d_acum += distance_2(r, i, -5*d, 5*d);
                    }
                    else if(r < -6*d && i > 6*d){
                        d_acum += distance_2(r, i, -7*d, 7*d);
                    }
                    else{
                        d_acum += distance_2(r, i, -7*d, 5*d);
                    }
                }
                else{
                    if(r >= -6*d && i >= 2*d){
                        d_acum += distance_2(r, i, -5*d, 3*d);
                    }
                    else if(r >= -6*d && i < 2*d){
                        d_acum += distance_2(r, i, -5*d, 1*d);
                    }
                    else if(r < -6*d && i > 2*d){
                        d_acum += distance_2(r, i, -7*d, 3*d);
                    }
                    else{
                        d_acum += distance_2(r, i, -7*d, 1*d);
                    }
                }          
            }
            else{
                if(r >= -4*d && i >= -4*d){
                    if(r >= -2*d && i >= -2*d){
                        d_acum += distance_2(r, i, -1*d, -1*d);
                    }
                    else if(r >= -2*d && i < -2*d){
                        d_acum += distance_2(r, i, -1*d, -3*d);
                    }
                    else if(r < -2*d && i > -2*d){
                        d_acum += distance_2(r, i, -3*d, -1*d);
                    }
                    else{
                        d_acum += distance_2(r, i, -3*d, -3*d);
                    }
                }
                else if(r > -4*d && i < -4*d){
                    if(r >= -2*d && i >= -6*d){
                        d_acum += distance_2(r, i, -1*d, -5*d);
                    }
                    else if(r >= -2*d && i < -6*d){
                        d_acum += distance_2(r, i, -1*d, -7*d);
                    }
                    else if(r < -2*d && i > -6*d){
                        d_acum += distance_2(r, i, -3*d, -5*d);
                    }
                    else{
                        d_acum += distance_2(r, i, -3*d, -7*d);
                    }
                }
                else if(r < -4*d && i > -4*d){
                    if(r >= -6*d && i >= -2*d){
                        d_acum += distance_2(r, i, -5*d, -1*d);
                    }
                    else if(r >= -6*d && i < -2*d){
                        d_acum += distance_2(r, i, -5*d, -3*d);
                    }
                    else if(r < -6*d && i > -2*d){
                        d_acum += distance_2(r, i, -7*d, -1*d);
                    }
                    else{
                        d_acum += distance_2(r, i, -7*d, -3*d);
                    }
                }
                else{
                    if(r >= -6*d && i >= -6*d){
                        d_acum += distance_2(r, i, -5*d, -5*d);
                    }
                    else if(r >= -6*d && i < -6*d){
                        d_acum += distance_2(r, i, -5*d, -7*d);
                    }
                    else if(r < -6*d && i > -6*d){
                        d_acum += distance_2(r, i, -7*d, -5*d);
                    }
                    else{
                        d_acum += distance_2(r, i, -7*d, -7*d);
                    }
                }          
            }

        break;

        default:
            d = 1;
            if(r < 0){
                d_acum += distance_2(r, i, -1*d, 0);
            }
            else{
                d_acum += distance_2(r, i, d, 0);
            }
        break;
    }

    if (d_counter >= d_length){
        d_counter = 0;
        dispersion = d_acum/d_length;
        if(d_constellation == 2){
            dispersion *= 0.9471; //Ajuste por la definición de 16QAM
        }
        else if (d_constellation == 3){
            dispersion *= 0.9393; //Ajuste por la definición de 64QAM
        }
        d_acum = 0;
        std::cout << dispersion <<"\n";
        switch(d_constellation){
            case 1:
                if(dispersion > d_th6){
                    d_change_down ++;
                    if (d_change_down >= 2){
                        d_change_down = 0;
                        message_port_pub(d_port, pmt::cons(pmt::string_to_symbol("Index"), pmt::from_long(0)));
                    }
                }
                else if (dispersion < d_th3){
                    d_change_up ++;
                    if(d_change_up >= 2){
                        d_change_up = 0;
                        message_port_pub(d_port, pmt::cons(pmt::string_to_symbol("Index"), pmt::from_long(2)));
                    }
                }
                else{
                    d_change_down = 0;
                    d_change_up = 0;
                }
            break;
                
            case 2:
                if(dispersion > d_th4){
                    d_change_down ++;
                    if (d_change_down >= 2){
                        d_change_down = 0;
                        message_port_pub(d_port, pmt::cons(pmt::string_to_symbol("Index"), pmt::from_long(1)));
                    }
                }
                else if (dispersion < d_th1){
                    d_change_up ++;
                    if(d_change_up >= 2){
                        d_change_up = 0;
                        message_port_pub(d_port, pmt::cons(pmt::string_to_symbol("Index"), pmt::from_long(3)));
                    }
                }
                else{
                    d_change_down = 0;
                    d_change_up = 0;
                }
            break;

            case 3:
                if(dispersion > d_th2){
                    d_change_down ++;
                    if (d_change_down >= 2){
                        d_change_down = 0;
                        message_port_pub(d_port, pmt::cons(pmt::string_to_symbol("Index"), pmt::from_long(2)));
                    }
                }
                else{
                    d_change_down = 0;
                }
            break;

            default:
                if(dispersion < d_th5){
                    d_change_up ++;
                    if (d_change_up >= 2){
                        d_change_up = 0;
                        message_port_pub(d_port, pmt::cons(pmt::string_to_symbol("Index"), pmt::from_long(1)));
                    }
                }
                else{
                    d_change_up = 0;
                }
            break;
        }
    }
}

int dispersion_probe_impl::work(int noutput_items,
                                gr_vector_const_void_star& input_items,
                                gr_vector_void_star& output_items)
{
    const gr_complex* in = (const gr_complex*)input_items[0];

    for (int i; i < noutput_items; i++){
        dispersion(in[i]);
    }

    return noutput_items;
}

} /* namespace TFMv5 */
} /* namespace gr */
