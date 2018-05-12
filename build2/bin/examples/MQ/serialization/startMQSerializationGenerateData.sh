#!/bin/bash

opt=""

if [ "$#" -gt 0 ]; then
        opt=" $*"
fi

GENERATE="serialization-Ex-generate-data$opt --id test"
GENERATE+=" --output-file /home/marci/fair_install/FairRoot/examples/MQ/serialization/data_io/inputEx.root"
GENERATE+=" --tree cbmsim"
# output file -> InputFile of sampler

/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/serialization/$GENERATE
