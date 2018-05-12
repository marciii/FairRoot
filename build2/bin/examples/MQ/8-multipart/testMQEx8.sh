#!/bin/bash
ex8config="/home/marci/fair_install/FairRoot/build2/bin/config/ex8-multipart.json"

# setup a trap to kill everything if the test fails/timeouts
trap 'kill -TERM $SAMPLER_PID; kill -TERM $SINK_PID; wait $SAMPLER_PID; wait $SINK_PID;' TERM

SAMPLER="ex8-sampler"
SAMPLER+=" --id sampler1"
SAMPLER+=" --verbosity veryhigh"
SAMPLER+=" --max-iterations 1"
SAMPLER+=" --control static --color false"
SAMPLER+=" --mq-config $ex8config"
/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/8-multipart/$SAMPLER &
SAMPLER_PID=$!

SINK="ex8-sink"
SINK+=" --id sink1"
SINK+=" --verbosity veryhigh"
SINK+=" --control static --color false"
SINK+=" --mq-config $ex8config"
/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/8-multipart/$SINK &
SINK_PID=$!

wait $SAMPLER_PID
wait $SINK_PID