#!/bin/bash

trap 'kill -TERM $GENERATE_PID; kill -TERM $SAMPLER_PID; kill -TERM $PROCESSOR1_PID; kill -TERM $FILESINK_PID; wait $GENERATE_PID; wait $SAMPLER_PID; wait $PROCESSOR1_PID; wait $FILESINK_PID;' TERM


########################## some def

SEVERITY="DEBUG"
INPUTFILE="/home/marci/fair_install/FairRoot/examples/MQ/serialization/data_io/testinput2.root"
OUTPUTFILE="/home/marci/fair_install/FairRoot/examples/MQ/serialization/data_io/outputEx2Test.root"
#JSONCONFIGFILE="/home/marci/fair_install/FairRoot/examples/MQ/serialization/options/MQConfig.json"
JSONCONFIGFILE="/home/marci/fair_install/FairRoot/examples/MQ/serialization/test/testSerializationEx2Config.json"


########################## start dummy data generator
GENERATE="serialization-Ex-generate-data --id generator"
GENERATE+=" --output-file $INPUTFILE"
GENERATE+=" --tree cbmsim --color false"
/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/serialization/$GENERATE &
GENERATE_PID=$!
wait $GENERATE_PID

########################## start SAMPLER
SAMPLER="serialization-Ex2-Sampler"
SAMPLER+=" --id sampler1 --mq-config $JSONCONFIGFILE --severity $SEVERITY"
SAMPLER+=" --input-file $INPUTFILE --color false --control static"
/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/serialization/$SAMPLER &
SAMPLER_PID=$!

########################## start PROCESSOR
PROCESSOR1="serialization-Ex2-Processor"
PROCESSOR1+=" --id processor1 --mq-config $JSONCONFIGFILE --severity $SEVERITY --color false --control static --num-msgs 100"
/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/serialization/$PROCESSOR1 &
PROCESSOR1_PID=$!

########################## start FILESINK
FILESINK="serialization-Ex2-Sink"
FILESINK+=" --id sink1 --mq-config $JSONCONFIGFILE --severity $SEVERITY --color false --control static --num-msgs 100"
FILESINK+=" --output-file $OUTPUTFILE"
/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/serialization/$FILESINK &
FILESINK_PID=$!

wait $SAMPLER_PID
wait $PROCESSOR1_PID
wait $FILESINK_PID
