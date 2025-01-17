# libiec61850

This file is part of the documentation of `libiec61850`.

Content:
- Overview
- Building and running the example server
- Implementing your own IEC61850 MMS devices

## Overview

`libiec61850` is an open-source (GPLv3) implementation of an IEC 61850 client and server library. It is implemented in C to provide maximum portability. It can be used to implement IEC 61850 compliant client and server applications on embedded systems and PCs running Linux and Windows. Included is a set of simple example applications that can be used as a starting point to implement your own IEC 61850 compliant devices or to communicate with IEC 61850 devices.

The library implements parts of the IEC 61850 specification on top of the MMS mapping. It provides the MMS protocol stack on top of TCP/IP.

The goal of this project is to provide an implementation that can run on memory constrained microcontrollers. But currently the library only runs on embedded linux systems as well as Desktop PCs running Linux or Windows.

## Building and running the examples

In the project root directory type

```bash
make examples
```

If the build succeeds you can find a few binary files in the projects root directory. You can also find a binary version of the library (`libiec61850.a`) in the "build" directory.

Run the sample application by typing

```bash
sudo ./simple_server_example1
```

on the Linux command line.

The example server is tested against the openIEC61850 client example. You can find and download openIEC61850 a Java implementation of IEC 61590 MMS for client and server applications at http://www.openmuc.org.

## Implementing your own IEC61850 MMS devices

Until now `libiec61850` uses a static server model. That means that the IEC61850 data model is not generated at runtime by reading an ICD file, but by converting an ICD file to static C data structures at compile time.

To provide your own IEC 61850 compliant device model a tool is provided that translates an IED file to C code that can be compiled into the server application.



## Random Notes

```bash
make lib


```
