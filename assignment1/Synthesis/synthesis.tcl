

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


synth_design -top ADD -part xc7a100tcsg324-1 -generic DATAWIDTH=2
write_checkpoint -force -noxdef C:/Users/bmkra/Documents/GIT/ece574/assignment1/post_synth
report_utilization -file C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/utilizationADD2.txt
report_timing > C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/timingADD2.txt

synth_design -top ADD -part xc7a100tcsg324-1 -generic DATAWIDTH=8
write_checkpoint -force -noxdef C:/Users/bmkra/Documents/GIT/ece574/assignment1/post_synth
report_utilization -file C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/utilizationADD8.txt
report_timing > C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/timingADD8.txt

synth_design -top ADD -part xc7a100tcsg324-1 -generic DATAWIDTH=16
write_checkpoint -force -noxdef C:/Users/bmkra/Documents/GIT/ece574/assignment1/post_synth
report_utilization -file C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/utilizationADD16.txt
report_timing > C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/timingADD16.txt

synth_design -top ADD -part xc7a100tcsg324-1 -generic DATAWIDTH=32
write_checkpoint -force -noxdef C:/Users/bmkra/Documents/GIT/ece574/assignment1/post_synth
report_utilization -file C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/utilizationADD32.txt
report_timing > C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/timingADD32.txt

synth_design -top ADD -part xc7a100tcsg324-1 -generic DATAWIDTH=64
write_checkpoint -force -noxdef C:/Users/bmkra/Documents/GIT/ece574/assignment1/post_synth
report_utilization -file C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/utilizationADD64.txt
report_timing > C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/timingADD64.txt



synth_design -top COMP -part xc7a100tcsg324-1
write_checkpoint -force -noxdef C:/Users/bmkra/Documents/GIT/ece574/assignment1/post_synth
report_utilization -file C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/utilizationCOMP.txt
report_timing > C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/timingCOMP.txt

synth_design -top DEC -part xc7a100tcsg324-1
write_checkpoint -force C:/Users/bmkra/Documents/GIT/ece574/assignment1/post_synth
report_utilization -file C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/utilizationDEC.txt
report_timing > C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/timingDEC.txt

synth_design -top DIV -part xc7a100tcsg324-1
write_checkpoint -force C:/Users/bmkra/Documents/GIT/ece574/assignment1/post_synth
report_utilization -file C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/utilizationDIV.txt
report_timing > C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/timingDIV.txt

synth_design -top INC -part xc7a100tcsg324-1
write_checkpoint -force C:/Users/bmkra/Documents/GIT/ece574/assignment1/post_synth
report_utilization -file C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/utilizationINC.txt
report_timing > C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/timingINC.txt

synth_design -top MOD -part xc7a100tcsg324-1
write_checkpoint -force C:/Users/bmkra/Documents/GIT/ece574/assignment1/post_synth
report_utilization -file C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/utilizatioMOD.txt
report_timing > C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/timingMOD.txt

synth_design -top MUL -part xc7a100tcsg324-1
write_checkpoint -force C:/Users/bmkra/Documents/GIT/ece574/assignment1/post_synth
report_utilization -file C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/utilizationMUL.txt
report_timing > C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/timingMUL.txt

synth_design -top MUX2x1 -part xc7a100tcsg324-1
write_checkpoint -force C:/Users/bmkra/Documents/GIT/ece574/assignment1/post_synth
report_utilization -file C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/utilizationMUX2x1.txt
report_timing > C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/timingMUX2x1.txt

synth_design -top REG -part xc7a100tcsg324-1
write_checkpoint -force C:/Users/bmkra/Documents/GIT/ece574/assignment1/post_synth
report_utilization -file C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/utilizationREG.txt
report_timing > C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/timingREG.txt

synth_design -top SHL -part xc7a100tcsg324-1
write_checkpoint -force C:/Users/bmkra/Documents/GIT/ece574/assignment1/post_synth
report_utilization -file C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/utilizationSHL.txt
report_timing > C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/timingSHL.txt

synth_design -top SHR -part xc7a100tcsg324-1
write_checkpoint -force C:/Users/bmkra/Documents/GIT/ece574/assignment1/post_synth
report_utilization -file C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/utilizationSHR.txt
report_timing > C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/timingSHR.txt

synth_design -top SUB -part xc7a100tcsg324-1
write_checkpoint -force C:/Users/bmkra/Documents/GIT/ece574/assignment1/post_synth
report_utilization -file C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/utilizatioSUB.txt
report_timing > C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/timingSUB.txt


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