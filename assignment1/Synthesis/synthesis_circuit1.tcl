

<<<<<<< HEAD:assignment1/synthesis.tcl
read_verilog -library xil_defaultlib {
  C:/Users/alexa/Documents/GitHub/ece574/assignment1/Source/ADD.v
  C:/Users/alexa/Documents/GitHub/ece574/assignment1/Source/COMP.v
  C:/Users/alexa/Documents/GitHub/ece574/assignment1/Source/DEC.v
  C:/Users/alexa/Documents/GitHub/ece574/assignment1/Source/DIV.v
  C:/Users/alexa/Documents/GitHub/ece574/assignment1/Source/INC.v
  C:/Users/alexa/Documents/GitHub/ece574/assignment1/Source/MOD.v
  C:/Users/alexa/Documents/GitHub/ece574/assignment1/Source/MUL.v
  C:/Users/alexa/Documents/GitHub/ece574/assignment1/Source/MUX2X1.v
  C:/Users/alexa/Documents/GitHub/ece574/assignment1/Source/REG.v
  C:/Users/alexa/Documents/GitHub/ece574/assignment1/Source/SHL.v
  C:/Users/alexa/Documents/GitHub/ece574/assignment1/Source/SHR.v
  C:/Users/alexa/Documents/GitHub/ece574/assignment1/Source/SUB.v
  C:/Users/alexa/Documents/GitHub/ece574/assignment1/Source/circuit1.v
  C:/Users/alexa/Documents/GitHub/ece574/assignment1/Source/circuit2.v
  C:/Users/alexa/Documents/GitHub/ece574/assignment1/Source/circuit3.v
  C:/Users/alexa/Documents/GitHub/ece574/assignment1/Source/circuit4.v
  C:/Users/alexa/Documents/GitHub/ece574/assignment1/Source/circuit5.v
  C:/Users/alexa/Documents/GitHub/ece574/assignment1/Source/circuit6.v
}

#Run Synthesis
synth_design -top circuit1 -part xc7a100tcsg324-1

#Write Design Checkpoints
write_checkpoint -force C:/Users/alexa/Documents/Arizona/ECE 574-Computer Aided Logic Design/Assignment_1/post_synth

#with report utilization and timing estimates
report_utilization -file C:Users/alexa/Documents/Arizona/ECE 574-Computer Aided Logic Design/Assignment_1/timing/utilization.txt
report_timing > C:/Users/alexa/Documents/Arizona/ECE 574-Computer Aided Logic Design/Assignment_1/timing/timing.txt
synth_design -top circuit1 -part xc7a100tcsg324-1
synth_design -top circuit2 -part xc7a100tcsg324-1
synth_design -top circuit3 -part xc7a100tcsg324-1
synth_design -top circuit4 -part xc7a100tcsg324-1
synth_design -top circuit5 -part xc7a100tcsg324-1
synth_design -top circuit6 -part xc7a100tcsg324-1
=======
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
>>>>>>> 579313bda31a59af724951b788905f85a3a74dc5:assignment1/Synthesis/synthesis_circuit1.tcl
