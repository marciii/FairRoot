#!/bin/bash

TRANSPORT="zeromq"
VERBOSE="DEBUG"

JSONCONFIGFILE="/home/marci/fair_install/FairRoot/build2/bin/config/ex1-sampler-sink.json"

########################## start DEVICE
DEVICE="runConfigExample --transport $TRANSPORT --severity $VERBOSE"
DEVICE+=" --id sampler1 --mq-config $JSONCONFIGFILE"
/home/marci/fair_install/FairRoot/build2/bin/$DEVICE
