/* -*- c++ -*- */
/*
 * Copyright 2021 gr-TFMv5 author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_TFMV5_PER_PROBE_H
#define INCLUDED_TFMV5_PER_PROBE_H

#include <gnuradio/block.h>
#include <TFMv5/api.h>

namespace gr {
namespace TFMv5 {

/*!
 * \brief <+description of block+>
 * \ingroup TFMv5
 *
 */
class TFMV5_API per_probe : virtual public block
{
public:
    typedef std::shared_ptr<per_probe> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of TFMv5::per_probe.
     *
     * To avoid accidental use of raw pointers, TFMv5::per_probe's
     * constructor is in a private implementation
     * class. TFMv5::per_probe::make is the public interface for
     * creating new instances.
     */
    static sptr make(float npackets);
};

} // namespace TFMv5
} // namespace gr

#endif /* INCLUDED_TFMV5_PER_PROBE_H */
