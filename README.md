# CoAP library for embedded targets

It may sound redundant to indicate this is a CoAP library for *embedded* targets, but 
it is my finding most CoAP libraries make curious and liberal use of dynamic allocation.
Last I checked, dynamic allocation was regarded as a practice to be avoided in most
embedded scenarios.  As such, I've developed this library which very specifically avoids
such shenanigans.

## library.json

This file is specifically to assist the very excellent platform.io tooling in utilizing
this lib