

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



synth_design -top circuit1 -part xc7a100tcsg324-1
write_checkpoint -force C:/Users/bmkra/Documents/GIT/ece574/assignment1/post_synth
report_utilization -file C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/utilization1.txt
report_timing > C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/timing1.txt

synth_design -top circuit2 -part xc7a100tcsg324-1
write_checkpoint -force C:/Users/bmkra/Documents/GIT/ece574/assignment1/post_synth
report_utilization -file C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/utilization2.txt
report_timing > C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/timing2.txt

synth_design -top circuit3 -part xc7a100tcsg324-1
write_checkpoint -force C:/Users/bmkra/Documents/GIT/ece574/assignment1/post_synth
report_utilization -file C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/utilization3.txt
report_timing > C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/timing3.txt

synth_design -top circuit4 -part xc7a100tcsg324-1
write_checkpoint -force C:/Users/bmkra/Documents/GIT/ece574/assignment1/post_synth
report_utilization -file C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/utilization4.txt
report_timing > C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/timing4.txt

synth_design -top circuit5 -part xc7a100tcsg324-1
write_checkpoint -force C:/Users/bmkra/Documents/GIT/ece574/assignment1/post_synth
report_utilization -file C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/utilization5.txt
report_timing > C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/timing5.txt

synth_design -top circuit6 -part xc7a100tcsg324-1
write_checkpoint -force C:/Users/bmkra/Documents/GIT/ece574/assignment1/post_synth
report_utilization -file C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/utilization6.txt
report_timing > C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/timing6.txt