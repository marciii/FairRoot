#!/bin/bash
ex1config="/home/marci/fair_install/FairRoot/build2/bin/config/ex1-sampler-sink.json"

SAMPLER="ex1-sampler"
SAMPLER+=" --id sampler1"
SAMPLER+=" --mq-config $ex1config"
xterm -geometry 80x23+0+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/1-sampler-sink/$SAMPLER &

SINK="ex1-sink"
SINK+=" --id sink1"
SINK+=" --mq-config $ex1config"
xterm -geometry 80x23+500+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/1-sampler-sink/$SINK &