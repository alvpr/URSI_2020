/* -*- c++ -*- */
/*
 * Copyright 2021 gr-TFMv5 author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_TFMV5_DISPERSION_PROBE_H
#define INCLUDED_TFMV5_DISPERSION_PROBE_H

#include <gnuradio/sync_block.h>
#include <TFMv5/api.h>

namespace gr {
namespace TFMv5 {

/*!
 * \brief <+description of block+>
 * \ingroup TFMv5
 *
 */
class TFMV5_API dispersion_probe : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<dispersion_probe> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of TFMv5::dispersion_probe.
     *
     * To avoid accidental use of raw pointers, TFMv5::dispersion_probe's
     * constructor is in a private implementation
     * class. TFMv5::dispersion_probe::make is the public interface for
     * creating new instances.
     */
    static sptr make(float constellation, float length, float length_init, float th1, float th2, float th3, float th4, float th5, float th6);
};

} // namespace TFMv5
} // namespace gr

#endif /* INCLUDED_TFMV5_DISPERSION_PROBE_H */
