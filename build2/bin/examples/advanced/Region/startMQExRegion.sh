#!/bin/bash
exRegionConfig="/home/marci/fair_install/FairRoot/build2/bin/config/ex-region.json"

msgSize="1000000"

if [[ $1 =~ ^[0-9]+$ ]]; then
    msgSize=$1
fi

SAMPLER="ex-region-sampler"
SAMPLER+=" --id sampler1"
SAMPLER+=" --severity debug"
SAMPLER+=" --msg-size $msgSize"
# SAMPLER+=" --rate 10"
SAMPLER+=" --transport shmem"
SAMPLER+=" --mq-config $exRegionConfig"
xterm -geometry 80x23+0+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/advanced/Region/$SAMPLER &

SINK="ex-region-sink"
SINK+=" --id sink1"
SINK+=" --severity debug"
SINK+=" --transport shmem"
SINK+=" --mq-config $exRegionConfig"
xterm -geometry 80x23+500+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/advanced/Region/$SINK &
