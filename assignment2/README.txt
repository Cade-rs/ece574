Brandon Kral 	bmkral
Cade Stephenson crstephenson
Alexander Krall	akrall3

ECE574

Program Description:
1. Read and save off string of text from textfile provided as input
2. One at a time, parse through each line, saving off information for each line into a component object such as the following. Entire list of components is stored inside dynamically allocated vector of components
	-Is the line an I/O/Wire/Register declaration?
	-Operation type along with inputs, outputs, datawidths, type
3. Using the vector of components, map out the possible downstream paths of each component, and then calculate latency estimates for each path using the provided latency values for each component type. last, return the max path latency - i.e. the critical path delay.
4. Looping through the vector of components, create one line of string for each component in the form of Verilog implementable code.
5. Write the vector of strings to an output file which is now ready to implement in Verilog.

Individual Contributions:
Brandon Kral (33% contribution) - file parsing and storing of information
Cade Stephenson (33% contribution) - latency calculations and component class
Alexander Krall (33% contribution) - writing and formatting information for verilog file