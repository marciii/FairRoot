#!/bin/bash

ex2config="/home/marci/fair_install/FairRoot/build2/bin/config/ex2-sampler-processor-sink.json"

# setup a trap to kill everything if the test fails/timeouts
trap 'kill -TERM $SAMPLER_PID; kill -TERM $SINK_PID; kill -TERM $PROCESSOR1_PID; kill -TERM $PROCESSOR2_PID; wait $SAMPLER_PID; wait $SINK_PID; wait $PROCESSOR1_PID; wait $PROCESSOR2_PID;' TERM

SAMPLER="ex2-sampler"
SAMPLER+=" --id sampler1"
SAMPLER+=" --verbosity veryhigh"
SAMPLER+=" --control static --color false"
SAMPLER+=" --max-iterations 2"
SAMPLER+=" --mq-config $ex2config"
/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/2-sampler-processor-sink/$SAMPLER &
SAMPLER_PID=$!

PROCESSOR1="ex2-processor"
PROCESSOR1+=" --id processor1"
PROCESSOR1+=" --verbosity veryhigh"
PROCESSOR1+=" --control static --color false"
PROCESSOR1+=" --mq-config $ex2config"
PROCESSOR1+=" --config-key processor"
/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/2-sampler-processor-sink/$PROCESSOR1 &
PROCESSOR1_PID=$!

PROCESSOR2="ex2-processor"
PROCESSOR2+=" --id processor2"
PROCESSOR2+=" --verbosity veryhigh"
PROCESSOR2+=" --control static --color false"
PROCESSOR2+=" --mq-config $ex2config"
PROCESSOR2+=" --config-key processor"
/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/2-sampler-processor-sink/$PROCESSOR2 &
PROCESSOR2_PID=$!

SINK="ex2-sink"
SINK+=" --id sink1"
SINK+=" --verbosity veryhigh"
SINK+=" --control static --color false"
SINK+=" --max-iterations 2"
SINK+=" --mq-config $ex2config"
/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/2-sampler-processor-sink/$SINK &
SINK_PID=$!

# wait for sampler and sink to finish
wait $SAMPLER_PID
wait $SINK_PID

# stop processors
kill -SIGINT $PROCESSOR1_PID
kill -SIGINT $PROCESSOR2_PID

# wait for everything to finish
wait $PROCESSOR1_PID
wait $PROCESSOR2_PID
