#!/bin/bash

maxIterations="0"
msgSize="1000000"
transport="zeromq"
sameMsg="true"
affinity="false"
affinitySamp=""
affinitySink=""


if [[ $1 =~ ^[0-9]+$ ]]; then
    msgSize=$1
fi

if [[ $2 =~ ^[0-9]+$ ]]; then
    maxIterations=$2
fi

if [[ $3 =~ ^[a-z]+$ ]]; then
    transport=$3
fi

if [[ $4 =~ ^[a-z]+$ ]]; then
    sameMsg=$4
fi

if [[ $5 =~ ^[a-z]+$ ]]; then
    affinity=$5
fi


echo "Starting benchmark with following settings:"

echo ""
echo "message size: $msgSize bytes"

if [ $maxIterations = 0 ]; then
    echo "number of iterations: unlimited"
else
    echo "number of iterations: $maxIterations"
fi

echo "transport: $transport"

if [ $sameMsg = "true" ]; then
    echo "resend same message: yes, using Copy() method to resend the same message"
else
    echo "resend same message: no, allocating each message separately"
fi

if [ $affinity = "true" ]; then
    affinitySamp="taskset -c 0"
    affinitySink="taskset -c 1"
    echo "affinity: assigning sampler to core 0, sink to core 1"
else
    echo ""
fi

echo ""
echo "Usage: startBenchmark [message size=1000000] [number of iterations=0] [transport=zeromq/nanomsg/shmem] [resend same message=true] [affinity=false]"

SAMPLER="bsampler"
SAMPLER+=" --id bsampler1"
#SAMPLER+=" --io-threads 2"
#SAMPLER+=" --control static"
SAMPLER+=" --transport $transport"
SAMPLER+=" --severity debug"
SAMPLER+=" --msg-size $msgSize"
SAMPLER+=" --same-msg $sameMsg"
# SAMPLER+=" --msg-rate 1000"
SAMPLER+=" --max-iterations $maxIterations"
SAMPLER+=" --mq-config /home/marci/fair_install/FairRoot/build2/bin/config/benchmark.json"
xterm -geometry 90x50+0+0 -hold -e $affinitySamp /home/marci/fair_install/FairRoot/build2/bin/$SAMPLER &
echo ""
echo "started: xterm -geometry 90x50+0+0 -hold -e $affinitySamp /home/marci/fair_install/FairRoot/build2/bin/$SAMPLER"
echo "pid: $!"

SINK="sink"
SINK+=" --id sink1"
#SINK+=" --io-threads 2"
#SINK+=" --control static"
SINK+=" --transport $transport"
SINK+=" --severity debug"
SINK+=" --max-iterations $maxIterations"
SINK+=" --mq-config /home/marci/fair_install/FairRoot/build2/bin/config/benchmark.json"
xterm -geometry 90x50+550+0 -hold -e $affinitySink /home/marci/fair_install/FairRoot/build2/bin/$SINK &
echo ""
echo "started: xterm -geometry 90x50+550+0 -hold -e $affinitySink /home/marci/fair_install/FairRoot/build2/bin/$SINK"
echo "pid: $!"
echo ""
