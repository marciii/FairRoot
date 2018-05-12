#!/bin/bash

prototypeconfig="/home/marci/fair_install/FairRoot/build2/bin/config/prototype-pair.json"

# setup a trap to kill everything if the test fails/timeouts
trap 'kill -TERM $PROCESSOR1_PID; kill -TERM $PROCESSOR2_PID; kill -TERM $PROCESSOR3_PID; wait $PROCESSOR1_PID; wait $PROCESSOR2_PID; wait $PROCESSOR3_PID;' TERM



PROCESSOR1="flpprocessorpair"
PROCESSOR1+=" --id flpprocessorpair"
PROCESSOR1+=" --verbosity veryhigh"
PROCESSOR1+=" --control static --color false"
PROCESSOR1+=" --mq-config $prototypeconfig"
PROCESSOR1+=" --config-key processor"
/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/prototype-pair/$PROCESSOR1 &
PROCESSOR1_PID=$!

PROCESSOR2="scheduleprocessorpair"
PROCESSOR2+=" --id scheduleprocessorpair"
PROCESSOR2+=" --verbosity veryhigh"
PROCESSOR2+=" --control static --color false"
PROCESSOR2+=" --mq-config $prototypeconfig"
PROCESSOR2+=" --config-key processor"
/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/prototype-pair/$PROCESSOR2 &
PROCESSOR2_PID=$!

PROCESSOR3="epnprocessorpair"
PROCESSOR3+=" --id epnprocessorpair"
PROCESSOR3+=" --verbosity veryhigh"
PROCESSOR3+=" --control static --color false"
PROCESSOR3+=" --mq-config $prototypeconfig"
PROCESSOR3+=" --config-key processor"
/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/prototype-pair/$PROCESSOR3 &
PROCESSOR3_PID=$!



# stop processors
kill -SIGINT $PROCESSOR1_PID
kill -SIGINT $PROCESSOR2_PID
kill -SIGINT $PROCESSOR3_PID

# wait for everything to finish
wait $PROCESSOR1_PID
wait $PROCESSOR2_PID
wait $PROCESSOR3_PID
