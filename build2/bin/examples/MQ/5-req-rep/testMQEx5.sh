#!/bin/bash

ex5config="/home/marci/fair_install/FairRoot/build2/bin/config/ex5-req-rep.json"

# setup a trap to kill everything if the test fails/timeouts
trap 'kill -TERM $CLIENT_PID; kill -TERM $SERVER_PID; wait $CLIENT_PID; wait $SERVER_PID;' TERM

CLIENT="ex5-client"
CLIENT+=" --id client"
CLIENT+=" --verbosity veryhigh"
CLIENT+=" --control static --color false"
CLIENT+=" --max-iterations 1"
CLIENT+=" --mq-config $ex5config"
/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/5-req-rep/$CLIENT &
CLIENT_PID=$!

SERVER="ex5-server"
SERVER+=" --id server"
SERVER+=" --verbosity veryhigh"
SERVER+=" --control static --color false"
SERVER+=" --max-iterations 1"
SERVER+=" --mq-config $ex5config"
/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/5-req-rep/$SERVER &
SERVER_PID=$!

# wait for everything to finish
wait $CLIENT_PID
wait $SERVER_PID
