#!/bin/bash
config="/home/marci/fair_install/FairRoot/build2/bin/config/ex-multiple-transports.json"

SAMPLER1="ex-mt-sampler1"
SAMPLER1+=" --id sampler1"
SAMPLER1+=" --severity debug"
SAMPLER1+=" --transport shmem"
SAMPLER1+=" --mq-config $config"
xterm -geometry 80x30+0+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/multiple-transports/$SAMPLER1 &

SAMPLER2="ex-mt-sampler2"
SAMPLER2+=" --id sampler2"
SAMPLER2+=" --severity debug"
SAMPLER2+=" --transport nanomsg"
SAMPLER2+=" --mq-config $config"
xterm -geometry 80x30+0+450 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/multiple-transports/$SAMPLER2 &

SINK="ex-mt-sink"
SINK+=" --id sink1"
SINK+=" --severity debug"
SINK+=" --transport shmem"
SINK+=" --mq-config $config"
xterm -geometry 80x30+500+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/multiple-transports/$SINK &