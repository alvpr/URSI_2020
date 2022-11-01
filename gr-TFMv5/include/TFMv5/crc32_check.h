/* -*- c++ -*- */
/*
 * Copyright 2021 gr-TFMv5 author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_TFMV5_CRC32_CHECK_H
#define INCLUDED_TFMV5_CRC32_CHECK_H

#include <gnuradio/block.h>
#include <gnuradio/digital/api.h>
#include <TFMv5/api.h>

namespace gr {
namespace TFMv5 {

/*!
 * \brief <+description of block+>
 * \ingroup TFMv5
 *
 */
class TFMV5_API crc32_check : virtual public gr::block
{
public:
    typedef std::shared_ptr<crc32_check> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of TFMv5::crc32_check.
     *
     * To avoid accidental use of raw pointers, TFMv5::crc32_check's
     * constructor is in a private implementation
     * class. TFMv5::crc32_check::make is the public interface for
     * creating new instances.
     */
    static sptr make(float npackets,float r1, float r2, float r3);
};

} // namespace TFMv5
} // namespace gr

#endif /* INCLUDED_TFMV5_CRC32_CHECK_H */
