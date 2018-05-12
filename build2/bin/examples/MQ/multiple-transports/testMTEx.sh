#!/bin/bash
config="/home/marci/fair_install/FairRoot/build2/bin/config/ex-multiple-transports.json"
SESSION="$(/home/marci/fair_install/FairRoot/build2/bin/uuidGen -h)"

trap 'kill -TERM $SAMPLER1_PID; kill -TERM $SAMPLER2_PID; kill -TERM $SINK_PID; wait $SAMPLER1_PID; wait $SAMPLER2_PID; wait $SINK_PID; /home/marci/fair_install/FairRoot/build2/bin/shmmonitor --cleanup --session $SESSION;' TERM

SINK="ex-mt-sink"
SINK+=" --id sink1"
SINK+=" --verbosity veryhigh"
SINK+=" --session $SESSION"
SINK+=" --max-iterations 1"
SINK+=" --control static --color false"
SINK+=" --transport shmem"
SINK+=" --mq-config $config"
/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/multiple-transports/$SINK &
SINK_PID=$!

SAMPLER1="ex-mt-sampler1"
SAMPLER1+=" --id sampler1"
SAMPLER1+=" --session $SESSION"
SAMPLER1+=" --verbosity veryhigh"
SAMPLER1+=" --max-iterations 1"
SAMPLER1+=" --control static --color false"
SAMPLER1+=" --transport shmem"
SAMPLER1+=" --mq-config $config"
/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/multiple-transports/$SAMPLER1 &
SAMPLER1_PID=$!

SAMPLER2="ex-mt-sampler2"
SAMPLER2+=" --id sampler2"
SAMPLER2+=" --session $SESSION"
SAMPLER2+=" --verbosity veryhigh"
SAMPLER2+=" --max-iterations 1"
SAMPLER2+=" --control static --color false"
SAMPLER2+=" --transport nanomsg"
SAMPLER2+=" --mq-config $config"
/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/multiple-transports/$SAMPLER2 &
SAMPLER2_PID=$!

wait $SAMPLER1_PID
wait $SAMPLER2_PID
wait $SINK_PID