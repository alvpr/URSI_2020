/* -*- c++ -*- */
/*
 * Copyright 2021 gr-TFMv5 author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_TFMV5_ENERGY_SCALE_H
#define INCLUDED_TFMV5_ENERGY_SCALE_H

#include <gnuradio/sync_block.h>
#include <TFMv5/api.h>

namespace gr {
namespace TFMv5 {

/*!
 * \brief <+description of block+>
 * \ingroup TFMv5
 *
 */
class TFMV5_API energy_scale : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<energy_scale> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of TFMv5::energy_scale.
     *
     * To avoid accidental use of raw pointers, TFMv5::energy_scale's
     * constructor is in a private implementation
     * class. TFMv5::energy_scale::make is the public interface for
     * creating new instances.
     */
    static sptr make(float eavg, float length, float init_scale);
};

} // namespace TFMv5
} // namespace gr

#endif /* INCLUDED_TFMV5_ENERGY_SCALE_H */
