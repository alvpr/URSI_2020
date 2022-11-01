# URSI_2020
URSI_2020 Paper code

## About this repo
This is the GNU Radio out-of-tree module and the grc and Python files for the paper presented in the National (Spain) URSI Congress: "Mock-up digital communication system based on the use of USRP over Linux". The code has been updated inn 2022. It includes:
* Schemes with one Tx and one Rx with BPSK, QPSK, 16-QAM and 64-QAM. 
* The most common effects in a mobile channel such as Doppler Effect, multipath or fast fading are considered. Time/symbol synchronization, channel equalization (although just blind equalizers are used) and adaptive decision boundaries are implemented.
* Control panel to modify the channel interference in real-time (noise, multipath, clock sync and Doppler effect) and visualise the effects in the received constellation. The configuration parameters of both Tx and Rx can also be modified in real-time. For example, carrier frequency, Tx gain, Rx gain, equalizer factor, etc.

## Pre-requisites
GNU Radio 3.9. Two USRP B210 were used for development and testing, although this work can be implemented with any full-duplex USRP model with no changes, and even with any other Software Defined Radio device GNU-Radio-compatible with few modifications.

For installation of the out-of-tree firs remove the build folder:

```console
$ cd gr-TFMv5
$ rm -r build
$ mkdir build
$ cd build
$ cmake ../
$ make
$ sudo ldconfig
```
For more info: https://wiki.gnuradio.org/index.php/OutOfTreeModules
