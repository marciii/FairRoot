#!/bin/bash

source /home/marci/fair_install/FairRoot/build2/config.sh

ex7config="/home/marci/fair_install/FairRoot/build2/bin/config/ex7-client.json"
parmqconfig="/home/marci/fair_install/FairRoot/build2/bin/config/parameter-server.json"

# setup a trap to kill everything if the test fails/timeouts
trap 'kill -TERM $CLIENT_PID; kill -TERM $PARAMETERSERVER_PID; wait $CLIENT_PID; wait $PARAMETERSERVER_PID;' TERM

CLIENT="ex7-client"
CLIENT+=" --id parmq-client"
CLIENT+=" --verbosity veryhigh"
CLIENT+=" --control static --color false"
CLIENT+=" --max-iterations 1"
CLIENT+=" --mq-config $ex7config"
/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/7-parameters/$CLIENT &
CLIENT_PID=$!

PARAMETERSERVER="parmq-server"
PARAMETERSERVER+=" --id parmq-server"
PARAMETERSERVER+=" --verbosity veryhigh"
PARAMETERSERVER+=" --control static --color false"
PARAMETERSERVER+=" --mq-config $parmqconfig"
PARAMETERSERVER+=" --first-input-name /home/marci/fair_install/FairRoot/build2/examples/MQ/7-parameters/mqexample7_param.root"
/home/marci/fair_install/FairRoot/build2/bin/$PARAMETERSERVER &
PARAMETERSERVER_PID=$!

wait $CLIENT_PID

# stop parameter server
kill -SIGINT $PARAMETERSERVER_PID
