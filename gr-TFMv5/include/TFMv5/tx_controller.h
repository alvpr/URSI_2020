/* -*- c++ -*- */
/*
 * Copyright 2021 gr-TFMv5 author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_TFMV5_TX_CONTROLLER_H
#define INCLUDED_TFMV5_TX_CONTROLLER_H

#include <gnuradio/sync_block.h>
#include <TFMv5/api.h>

namespace gr {
namespace TFMv5 {

/*!
 * \brief <+description of block+>
 * \ingroup TFMv5
 *
 */
class TFMV5_API tx_controller : virtual public gr::block
{
public:
    typedef std::shared_ptr<tx_controller> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of TFMv5::tx_controller.
     *
     * To avoid accidental use of raw pointers, TFMv5::tx_controller's
     * constructor is in a private implementation
     * class. TFMv5::tx_controller::make is the public interface for
     * creating new instances.
     */
    static sptr make();
};

} // namespace TFMv5
} // namespace gr

#endif /* INCLUDED_TFMV5_TX_CONTROLLER_H */
