import struct
import os
import sys
import random
import math
import numpy as np
import scipy as sp
import matplotlib.pyplot as plt

if len(sys.argv)<2:
    print "Missing data filename\n"
    sys.exit()

home=os.path.expanduser('~')
data_path=home+"/Projects/ProjectNeurogenesisOutput/recordings/"
data_file=sys.argv[1]
full_path=data_path+data_file

layer_sizes = []
all_data={}

with open(full_path, 'rb') as bdata:

    bnum_layers = bdata.read(8)
    num_layers = struct.unpack('@l',bnum_layers)[0]

    for i in range(num_layers):
        b_layer_size = bdata.read(8)
        layer_sizes.append(struct.unpack('@l',b_layer_size)[0])

    while(True):
        blayer_id=bdata.read(8)
        bneuron_id=bdata.read(8)
        btime=bdata.read(8)
        if(btime):
            layer_id=struct.unpack('@l',blayer_id)[0]
            neuron_id=struct.unpack('@l',bneuron_id)[0]
            time=struct.unpack('@l',btime)[0]

            if all_data.has_key(layer_id):
                if all_data[layer_id].has_key(neuron_id):
                    all_data[layer_id][neuron_id].append(time)
                else:
                    all_data[layer_id][neuron_id]=[time]
            else:
                all_data[layer_id]={ neuron_id:[time] }

        else:
            break
            
layer_counter=0
for lk,lv in all_data.items():
    max_time=0

    for nk,nv in lv.items():
        
        m = max(nv)
        if m > max_time:
            max_time=m

    print "Layer " + str(layer_counter) + " size: ", layer_sizes[layer_counter],max_time+1

    layer_data = np.zeros([layer_sizes[layer_counter],max_time+1])

    for nk,nv in lv.items():
        for t in nv:
            layer_data[nk][t]=1.0

    plt.imshow(layer_data,interpolation='nearest',aspect='auto')
    plt.title("Layer "+str(lk))
    plt.xlabel("Time")
    plt.ylabel("Neuron")
    plt.show()

    layer_counter+=1