#!/bin/bash

exRegionConfig="/home/marci/fair_install/FairRoot/build2/bin/config/ex-region.json"
msgSize="1000000"
SESSION="$(/home/marci/fair_install/FairRoot/build2/bin/uuidGen -h)"

# setup a trap to kill everything if the test fails/timeouts
trap 'kill -TERM $SAMPLER_PID; kill -TERM $SINK_PID; wait $SAMPLER_PID; wait $SINK_PID; /home/marci/fair_install/FairRoot/build2/bin/shmmonitor --cleanup --session $SESSION' TERM

SAMPLER="ex-region-sampler"
SAMPLER+=" --id sampler1"
SAMPLER+=" --severity debug"
SAMPLER+=" --session $SESSION"
SAMPLER+=" --control static --color false"
SAMPLER+=" --max-iterations 1"
SAMPLER+=" --msg-size $msgSize"
SAMPLER+=" --transport shmem"
SAMPLER+=" --mq-config $exRegionConfig"
/home/marci/fair_install/FairRoot/build2/bin/examples/advanced/Region/$SAMPLER &
SAMPLER_PID=$!

SINK="ex-region-sink"
SINK+=" --id sink1"
SINK+=" --session $SESSION"
SINK+=" --verbosity veryhigh"
SINK+=" --control static --color false"
SINK+=" --max-iterations 1"
SINK+=" --transport shmem"
SINK+=" --mq-config $exRegionConfig"
/home/marci/fair_install/FairRoot/build2/bin/examples/advanced/Region/$SINK &
SINK_PID=$!

# wait for sampler and sink to finish
wait $SAMPLER_PID
wait $SINK_PID
