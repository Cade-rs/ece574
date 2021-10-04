Brandon Kral 	bmkral
Cade Stephenson crstephenson
Alexander Krall	akrall3

Xilinx synthesis tool version: Vivado v2020.2 (64-bit)

target FPGA and speed grade: xc7a100tcsg324-1

Method of calculating critical path:
Using the vivado measured critical paths for each component, we summed the latencies at each step in the logic flow. After the timelines for all paths had been defined, we found the critical path as the path with the longest timeline.

When estimating the critical path of our schematic, we did the same process but used the components listed in the schematic - not the components written in the .V file.