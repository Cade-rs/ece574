# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""

import re
import os

dir1 = "C:\\Users\\cader\\Documents\\school\\ECE574\\workspace\\git\\ece574\\assignment1\\Timing"
os.chdir(dir1)

#
comps = ['REG','ADD','SUB','MUL','COMP','MUX2x1','SHR','SHL','DIV','MOD','INC','DEC']
nbits = ['2','8','16','32','64']

culprit = 'Data Path Delay:'     
regexp = re.compile(r'Data Path Delay:.*?([0-9.-]+)')
txt = ''

for comp in comps:
    
    latency = []
    for nbit in nbits:
        fname = 'timing' + comp + nbit + '.txt'
        
        #grab latencies for each bitwidth
        with open(fname) as f:
            match = re.search(regexp, f.read())
            latency.append(match.group(1))
    
    #form appendix
    txt = txt + comp+' : '+latency[0]+', '+latency[1]+', '+latency[2]+', '+latency[3]+', '+latency[4]+'\n'
    
            #for line in f:
            #    match = regexp.match(line)
            #   if match:
            #        latency = match.group(1)
            #        print(latency)
                    
        #print re.search(r'Data Path Delay:.*?=,(.+)', f.read()).group(1)                
        #print re.search(' Data Path Delay:*', f.read())                
    
file = open('DPCL_LAT.txt', "w")

file.write(txt)

file.close()