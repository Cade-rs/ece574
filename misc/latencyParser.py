# -*- coding: utf-8 -*-
"""
Parse timing reports for component latencies and write to DPCL_LAT.txt file
"""

import re
import os

dir1 = "C:\\Users\\cader\\Documents\\school\\ECE574\\workspace\\git\\ece574\\assignment1\\Timing"
os.chdir(dir1)

comps = ['REG','ADD','SUB','MUL','COMP','MUX2x1','SHR','SHL','DIV','MOD','INC','DEC']
nbits = ['2','8','16','32','64']

regexp = re.compile(r'Data Path Delay:.*?([0-9.-]+)')
txt = ''

for comp in comps:
    
    #reset latencies array
    latency = []
    for nbit in nbits:
        fname = 'timing' + comp + nbit + '.txt'
        
        #grab latencies for each bitwidth
        with open(fname) as f:
            match = re.search(regexp, f.read())
            latency.append(match.group(1))
    
    #form appendix
    txt = txt + comp+' : '+latency[0]+', '+latency[1]+', '+latency[2]+', '+latency[3]+', '+latency[4]+'\n'
                 
#create text file (wrong directory though)
file = open('DPCL_LAT.txt', "w")

file.write(txt)

file.close()