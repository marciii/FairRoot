#!/bin/bash
ex4config="/home/marci/fair_install/FairRoot/build2/bin/config/ex4-copypush.json"

SAMPLER="ex4-sampler"
SAMPLER+=" --id sampler1"
SAMPLER+=" --mq-config $ex4config"
xterm -geometry 80x23+0+165 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/4-copypush/$SAMPLER &

SINK1="ex4-sink"
SINK1+=" --id sink1"
SINK1+=" --mq-config $ex4config"
xterm -geometry 80x23+500+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/4-copypush/$SINK1 &

SINK2="ex4-sink"
SINK2+=" --id sink2"
SINK2+=" --mq-config $ex4config"
xterm -geometry 80x23+500+330 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/4-copypush/$SINK2 &
