

read_verilog -library xil_defaultlib {
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
write_checkpoint -force $outputDir/post_synth
report_utilization -file C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/utilization.txt
report_timing > C:/Users/bmkra/Documents/GIT/ece574/assignment1/Timing/timing.txt
synth_design -top circuit2 -part xc7a100tcsg324-1
synth_design -top circuit3 -part xc7a100tcsg324-1
synth_design -top circuit4 -part xc7a100tcsg324-1
synth_design -top circuit5 -part xc7a100tcsg324-1
synth_design -top circuit6 -part xc7a100tcsg324-1