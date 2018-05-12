#!/bin/bash
ex6config="/home/marci/fair_install/FairRoot/build2/bin/config/ex6-multiple-channels.json"

# setup a trap to kill everything if the test fails/timeouts
trap 'kill -TERM $SAMPLER_PID; kill -TERM $SINK_PID; kill -TERM $BROADCASTER_PID; wait $SAMPLER_PID; wait $SINK_PID; wait $BROADCASTER_PID;' TERM


SINK="ex6-sink"
SINK+=" --id sink1"
SINK+=" --verbosity veryhigh"
SINK+=" --max-iterations 1"
SINK+=" --control static --color false"
SINK+=" --mq-config $ex6config"
/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/6-multiple-channels/$SINK &
SINK_PID=$!

sleep 1

SAMPLER="ex6-sampler"
SAMPLER+=" --id sampler1"
SAMPLER+=" --verbosity veryhigh"
SAMPLER+=" --max-iterations 1"
SAMPLER+=" --control static --color false"
SAMPLER+=" --mq-config $ex6config"
/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/6-multiple-channels/$SAMPLER &
SAMPLER_PID=$!

BROADCASTER="ex6-broadcaster"
BROADCASTER+=" --id broadcaster1"
BROADCASTER+=" --verbosity veryhigh"
BROADCASTER+=" --control static --color false"
BROADCASTER+=" --mq-config $ex6config"
/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/6-multiple-channels/$BROADCASTER &
BROADCASTER_PID=$!

wait $SAMPLER_PID
wait $SINK_PID

# stop broadcaster
kill -SIGINT $BROADCASTER_PID

# wait for broadcaster to finish
wait $BROADCASTER_PID
