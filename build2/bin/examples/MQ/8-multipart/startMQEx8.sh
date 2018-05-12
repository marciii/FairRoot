#!/bin/bash
ex8config="/home/marci/fair_install/FairRoot/build2/bin/config/ex8-multipart.json"

SAMPLER="ex8-sampler"
SAMPLER+=" --id sampler1"
SAMPLER+=" --mq-config $ex8config"
xterm -geometry 80x23+0+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/8-multipart/$SAMPLER &

SINK="ex8-sink"
SINK+=" --id sink1"
SINK+=" --mq-config $ex8config"
xterm -geometry 80x23+500+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/8-multipart/$SINK &
