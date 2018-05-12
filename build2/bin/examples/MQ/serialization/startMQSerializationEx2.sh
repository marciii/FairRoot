#!/bin/bash

TRANSPORT="zeromq"
VERBOSE="DEBUG"

if [[ "$#" -eq 1 ]]; then
key="$1"
case $key in
    -h|--help)
    echo "possible command lines"
    echo "  -t or --transport"
    echo "  -v or --verbose"
    echo "  -h or --help"
    exit
    ;;
    *)
    echo "Unknown command line. Use -h or --help command"
    exit
    ;;
esac
fi

while [[ $# > 1 ]]
do
key="$1"

case $key in
    -t|--transport)
    TRANSPORT="$2"
    shift
    ;;
    -v|--verbose)
    VERBOSE="$2"
    shift
    ;;
    *)
    echo "Unknown command line. Use -h or --help command to list the commands"
    exit
    ;;
esac
shift 
done

INPUTFILE="/home/marci/fair_install/FairRoot/examples/MQ/serialization/data_io/inputEx.root"
OUTPUTFILE="/home/marci/fair_install/FairRoot/examples/MQ/serialization/data_io/outputEx2.root"
JSONCONFIGFILE="/home/marci/fair_install/FairRoot/examples/MQ/serialization/options/MQConfig.json"

########################## start SAMPLER
SAMPLER="serialization-Ex2-Sampler --transport $TRANSPORT --severity $VERBOSE"
SAMPLER+=" --id sampler1  --input-file $INPUTFILE --mq-config $JSONCONFIGFILE"
xterm -geometry 120x27+0+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/serialization/$SAMPLER &

########################## start three PROCESSORs
PROCESSOR1="serialization-Ex2-Processor --transport $TRANSPORT --severity $VERBOSE"
PROCESSOR1+=" --id processor1 --mq-config $JSONCONFIGFILE"
xterm -geometry 100x27+800+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/serialization/$PROCESSOR1 &

PROCESSOR2="serialization-Ex2-Processor --transport $TRANSPORT"
PROCESSOR2+=" --id processor2 --mq-config $JSONCONFIGFILE"
xterm -geometry 100x27+800+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/serialization/$PROCESSOR2 &

PROCESSOR3="serialization-Ex2-Processor --transport $TRANSPORT --severity $VERBOSE"
PROCESSOR3+=" --id processor3 --mq-config $JSONCONFIGFILE"
xterm -geometry 100x27+800+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/serialization/$PROCESSOR3 &

########################## start FILESINK
FILESINK="serialization-Ex2-Sink --transport $TRANSPORT --severity $VERBOSE"
FILESINK+=" --id sink1 --mq-config $JSONCONFIGFILE"
FILESINK+=" --output-file $OUTPUTFILE"
xterm +aw -geometry 120x27+0+500 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/serialization/$FILESINK &

