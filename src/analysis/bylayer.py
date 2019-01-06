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

all_data={}

with open(full_path, 'rb') as bdata:
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
            

for lk,lv in all_data.items():

    num_neurons=0
    max_time=0

    for nk,nv in lv.items():

        if nk > num_neurons:
            num_neurons = nk
        
        m = max(nv)
        if m > max_time:
            max_time=m

    layer_data = np.zeros([num_neurons+1,max_time+1])

    for nk,nv in lv.items():
        for t in nv:
            layer_data[nk][t]=1.0

    plt.imshow(layer_data,interpolation='nearest',aspect='auto')
    plt.title("Layer "+str(lk))
    plt.xlabel("Time")
    plt.ylabel("Neuron")
    plt.show()