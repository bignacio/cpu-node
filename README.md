# CPU-node tool
Linux utility for identifying CPU cores and respective NUMA nodes.

## Overview
This utility will scan all CPU cores, determine the NUMA node associated to the core (if any) and output the core and node ids.

For example
```
$ ./cpu-nodes
Current process affinity list: 0 1 2 3 4 5 6 7

Finding NUMA nodes for a maximum of 8192 cores
Core 0 on node 0
Core 1 on node 0
Core 2 on node 0
Core 3 on node 0
Core 4 on node 0
Core 5 on node 0
Core 6 on node 0
Core 7 on node 0

Found 8 cores
```

## Building and installation

### Pre-requisites
To build the `cpu-node` tool, you'll need:
* A relatively recent C compiler
* CMake
* Linux kernel headers

### Building the sources
From the source directory, execute
```
mkdir -p build && cmake -B build -DCMAKE_BUILD_TYPE=Release

make -C build
```

This will create the binary in `build/cpu-nodes`. There are no external library dependencies and `cpu-nodes` can be copied to your preferred target location.


## Issues and feedback

Open a Github issue for reporting problems and providing feedback. Thanks for contributing!