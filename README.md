# Project Neurogenesis

Project concept is to create an architecture capable of generating new neurons on the fly to capture higher-level associations. It is believed that certain parts of the adult brain experience neurogenesis. It is theorized that neurogenesis facilitates the brain's ability to process/accept novel stimulii.

## Run Instructions
`make sim` to compile the simulator

`./sim [options]` to run

See the config.ini for defaults to the below options.

Options:\
-r <filename>: Record model output\
-t: Train the model\
-s <filename> save the model using the filename\
-l <filename> load a model\
-b <model id> <input size> NOTE: -l overrides -b\
-h Prints the help info (probably more up-to-date than this list).\
-d [ <dataset> <dataset> ... <dataset> ]

## Change Log
See changelog file under the notes directory.

## Milestones
<b>1/6/19:</b> Dendritic trees are working. Proto-synapses are gaining strength from coincidental activity to the point they cause spikes in the second layer. The second layer spiking patterns repeat and are fairly, if not perfectly, consistent. Next I need to check if synpases are actually moving to a mature state. If so, I need to examine the effects of post-maturity learning.
