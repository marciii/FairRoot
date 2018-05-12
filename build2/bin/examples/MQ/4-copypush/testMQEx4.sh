#!/bin/bash

ex4config="/home/marci/fair_install/FairRoot/build2/bin/config/ex4-copypush.json"

# setup a trap to kill everything if the test fails/timeouts
trap 'kill -TERM $SAMPLER_PID; kill -TERM $SINK1_PID; kill -TERM $SINK2_PID; wait $SAMPLER_PID; wait $SINK1_PID; wait $SINK2_PID;' TERM

SAMPLER="ex4-sampler"
SAMPLER+=" --id sampler1"
SAMPLER+=" --verbosity veryhigh"
SAMPLER+=" --control static --color false"
SAMPLER+=" --max-iterations 1"
SAMPLER+=" --mq-config $ex4config"
/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/4-copypush/$SAMPLER &
SAMPLER_PID=$!

SINK1="ex4-sink"
SINK1+=" --id sink1"
SINK1+=" --verbosity veryhigh"
SINK1+=" --control static --color false"
SINK1+=" --max-iterations 1"
SINK1+=" --mq-config $ex4config"
/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/4-copypush/$SINK1 &
SINK1_PID=$!

SINK2="ex4-sink"
SINK2+=" --id sink2"
SINK2+=" --verbosity veryhigh"
SINK2+=" --control static --color false"
SINK2+=" --max-iterations 1"
SINK2+=" --mq-config $ex4config"
/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/4-copypush/$SINK2 &
SINK2_PID=$!

# wait for everything to finish
wait $SAMPLER_PID
wait $SINK1_PID
wait $SINK2_PID
