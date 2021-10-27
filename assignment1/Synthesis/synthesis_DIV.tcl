

read_verilog  {
  C:/Users/bmkra/Documents/GIT/ece574/assignment1/Source/ADD.v
  C:/Users/bmkra/Documents/GIT/ece574/assignment1/Source/COMP.v
  C:/Users/bmkra/Documents/GIT/ece574/assignment1/Source/DEC.v
  C:/Users/bmkra/Documents/GIT/ece574/assignment1/Source/DIV.v
  C:/Users/bmkra/Documents/GIT/ece574/assignment1/Source/INC.v
  C:/Users/bmkra/Documents/GIT/ece574/assignment1/Source/MOD.v
  C:/Users/bmkra/Documents/GIT/ece574/assignment1/Source/MUL.v
  C:/Users/bmkra/Documents/GIT/ece574/assignment1/Source/MUX2x1.v
  C:/Users/bmkra/Documents/GIT/ece574/assignment1/Source/REG.v
  C:/Users/bmkra/Documents/GIT/ece574/assignment1/Source/SHL.v
  C:/Users/bmkra/Documents/GIT/ece574/assignment1/Source/SHR.v
  C:/Users/bmkra/Documents/GIT/ece574/assignment1/Source/SUB.v
  C:/Users/bmkra/Documents/GIT/ece574/assignment1/Source/circuit1.v
  C:/Users/bmkra/Documents/GIT/ece574/assignment1/Source/circuit2.v
  C:/Users/bmkra/Documents/GIT/ece574/assignment1/Source/circuit3.v
  C:/Users/bmkra/Documents/GIT/ece574/assignment1/Source/circuit4.v
  C:/Users/bmkra/Documents/GIT/ece574/assignment1/Source/circuit5.v
  C:/Users/bmkra/Documents/GIT/ece574/assignment1/Source/circuit6.v
}


synth_design -top DIV -part xc7a100tcsg324-1 -generic DATAWIDTH=2
write_checkpoint -force -noxdef C:/Users/bmkra/Documents/GIT/ece574/assignment1/post_synth
report_utilization -file C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/utilizationDIV2.txt
report_timing > C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/timingDIV2.txt

synth_design -top DIV -part xc7a100tcsg324-1 -generic DATAWIDTH=8
write_checkpoint -force -noxdef C:/Users/bmkra/Documents/GIT/ece574/assignment1/post_synth
report_utilization -file C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/utilizationDIV8.txt
report_timing > C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/timingDIV8.txt

synth_design -top DIV -part xc7a100tcsg324-1 -generic DATAWIDTH=16
write_checkpoint -force -noxdef C:/Users/bmkra/Documents/GIT/ece574/assignment1/post_synth
report_utilization -file C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/utilizationDIV16.txt
report_timing > C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/timingDIV16.txt

synth_design -top DIV -part xc7a100tcsg324-1 -generic DATAWIDTH=32
write_checkpoint -force -noxdef C:/Users/bmkra/Documents/GIT/ece574/assignment1/post_synth
report_utilization -file C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/utilizationDIV32.txt
report_timing > C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/timingDIV32.txt

synth_design -top DIV -part xc7a100tcsg324-1 -generic DATAWIDTH=64
write_checkpoint -force -noxdef C:/Users/bmkra/Documents/GIT/ece574/assignment1/post_synth
report_utilization -file C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/utilizationDIV64.txt
report_timing > C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/timingDIV64.txt

