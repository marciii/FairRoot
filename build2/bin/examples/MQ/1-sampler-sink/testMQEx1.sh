#!/bin/bash

ex1config="/home/marci/fair_install/FairRoot/build2/bin/config/ex1-sampler-sink.json"

# setup a trap to kill everything if the test fails/timeouts
trap 'kill -TERM $SAMPLER_PID; kill -TERM $SINK_PID; wait $SAMPLER_PID; wait $SINK_PID;' TERM

SAMPLER="ex1-sampler"
SAMPLER+=" --id sampler1"
SAMPLER+=" --verbosity veryhigh"
SAMPLER+=" --control static --color false"
SAMPLER+=" --max-iterations 1"
SAMPLER+=" --mq-config $ex1config"
/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/1-sampler-sink/$SAMPLER &
SAMPLER_PID=$!

SINK="ex1-sink"
SINK+=" --id sink1"
SINK+=" --verbosity veryhigh"
SINK+=" --control static --color false"
SINK+=" --max-iterations 1"
SINK+=" --mq-config $ex1config"
/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/1-sampler-sink/$SINK &
SINK_PID=$!

# wait for sampler and sink to finish
wait $SAMPLER_PID
wait $SINK_PID