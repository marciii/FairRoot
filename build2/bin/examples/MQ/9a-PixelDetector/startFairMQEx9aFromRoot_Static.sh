#!/bin/bash

CHECK_BEFORE="$(ps -fea | grep Pixel9MQConfig_Multipart.json | grep -v grep)"
if [ -n "$CHECK_BEFORE" ];
then
    echo "some example/MQ/9-Pixel programs are still running:"
    echo $CHECK_BEFORE
    echo "quit them before proceeding."
    exit;
fi

MAXINDEX="--max-index -1"
TRANSPORT="--transport zeromq"
VERBOSE="--severity DEBUG"
FAIRTASKNAME="--task-name PixelAltFindHits"
WORKDIR="/home/marci/fair_install/FairRoot"
DATESTRING=`date +%Y%m%d_%H%M%S`

NOFPROCESSORS=5

while [[ $# > 1 ]]
do
key="$1"

case $key in
    -f|--task-name)
    FAIRTASKNAME="--task-name $2"
    shift
    ;;
    -m|--max-index)
    MAXINDEX="--max-index $2"
    shift
    ;;
    -t|--transport)
    TRANSPORT="--transport $2"
    shift
    ;;
    -p|--processors)
    NOFPROCESSORS="$2"
    shift
    ;;
    -v|--verbose)
    VERBOSE="--severity $2"
    shift
    ;;
esac
shift 
done

########################### Define some variables
# JSON file containing the configuration parameters of all FairMQ devices of this example
MQCONFIGFILE="/home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/run/options/Pixel9MQConfig_Multipart.json"
# ASCII and ROOT parameter files for the processor device
ROOTPARAM="/home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.params.root"
ASCIIPARAM="/home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/param/pixel_digi.par"

if [ "$FAIRTASKNAME" == "--task-name PixelAltFindHits" ] ; then
    # input file and branch for the sampler device
    INPUTFILE="/home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.digi.root"
    INPUTFILE+=" --file-name /home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.digi.root"
    INPUTFILE+=" --file-name /home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.digi.root"
    INPUTFILE+=" --file-name /home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.digi.root"
    INPUTFILE+=" --file-name /home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.digi.root"
    INPUTFILE+=" --file-name /home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.digi.root"
    INPUTFILE+=" --file-name /home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.digi.root"
    INPUTFILE+=" --file-name /home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.digi.root"
    INPUTFILE+=" --file-name /home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.digi.root"
    INPUTFILE+=" --file-name /home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.digi.root"
 #   INPUTFILE+=" --file-name /home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.digi.f1.root"
    INPUTBRANCH="PixelDigis"
    
    # output file for sink
    OUTPUTFILE="/home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/MQa.pixel_TGeant3.bin.hits.root"
    OUTPUTCLASS="--class-name TClonesArray(PixelHit)"
    OUTPUTBRANCH="--branch-name PixelHits"
else
    echo "TASK $FAIRTASKNAME UNKNOWN!!!"
    exit
fi
###########################



########################### Start the chain of the devices


########################## start Parameter server
SERVER="/home/marci/fair_install/FairRoot/build2/bin/"
SERVER+="parmq-server $TRANSPORT"
SERVER+=" --id parmq-server  --mq-config $MQCONFIGFILE"
SERVER+=" $VERBOSE "
SERVER+=" --first-input-name $ROOTPARAM --second-input-name $ASCIIPARAM --second-input-type ASCII --control static --color false"

########################## start SAMPLER
SAMPLER="/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/9-PixelDetector/"
SAMPLER+="ex9-samplerBin $TRANSPORT"
SAMPLER+=" --id sampler1  --mq-config $MQCONFIGFILE"
SAMPLER+=" --severity info --ack-channel ack "
SAMPLER+=" --file-name $INPUTFILE --branch-name EventHeader. --branch-name $INPUTBRANCH $MAXINDEX --control static --color false"

########################## start PROCESSORs
PROCESSOR1="/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/9a-PixelDetector/"
PROCESSOR1+="ex9a-processorBin $TRANSPORT"
PROCESSOR1+=" $VERBOSE"
PROCESSOR1+=" --id processor1 $FAIRTASKNAME --mq-config $MQCONFIGFILE --control static --color false"

PROCESSOR2="/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/9a-PixelDetector/"
PROCESSOR2+="ex9a-processorBin $TRANSPORT"
PROCESSOR2+=" $VERBOSE"
PROCESSOR2+=" --id processor2 $FAIRTASKNAME --mq-config $MQCONFIGFILE --control static --color false"

PROCESSOR3="/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/9a-PixelDetector/"
PROCESSOR3+="ex9a-processorBin $TRANSPORT"
PROCESSOR3+=" $VERBOSE"
PROCESSOR3+=" --id processor3 $FAIRTASKNAME --mq-config $MQCONFIGFILE --control static --color false"

PROCESSOR4="/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/9a-PixelDetector/"
PROCESSOR4+="ex9a-processorBin $TRANSPORT"
PROCESSOR4+=" $VERBOSE"
PROCESSOR4+=" --id processor4 $FAIRTASKNAME --mq-config $MQCONFIGFILE --control static --color false"

PROCESSOR5="/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/9a-PixelDetector/"
PROCESSOR5+="ex9a-processorBin $TRANSPORT"
PROCESSOR5+=" $VERBOSE"
PROCESSOR5+=" --id processor5 $FAIRTASKNAME --mq-config $MQCONFIGFILE --control static --color false"

########################## start FILESINK
FILESINK="/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/9-PixelDetector/"
FILESINK+="ex9-sinkBin $TRANSPORT"
FILESINK+=" $VERBOSE --ack-channel ack "
FILESINK+=" --id sink1 --mq-config $MQCONFIGFILE"
FILESINK+=" --file-name $OUTPUTFILE --class-name FairEventHeader --branch-name EventHeader. $OUTPUTCLASS $OUTPUTBRANCH --control static --color false"

$SERVER &> server_$DATESTRING.out.log &
SERVER_PID=$!

$SAMPLER &> sampler_$DATESTRING.out.log &
SAMPLER_PID=$!

$PROCESSOR1 &> processor1_$DATESTRING.out.log &
PROCESSOR1_PID=$!

if [ "$NOFPROCESSORS" -gt 1 ]; then
    $PROCESSOR2 &> processor2_$DATESTRING.out.log &
    PROCESSOR2_PID=$!
fi

if [ "$NOFPROCESSORS" -gt 2 ]; then
    $PROCESSOR3 &> processor3_$DATESTRING.out.log &
    PROCESSOR3_PID=$!
fi

if [ "$NOFPROCESSORS" -gt 3 ]; then
    $PROCESSOR4 &> processor4_$DATESTRING.out.log &
    PROCESSOR4_PID=$!
fi

if [ "$NOFPROCESSORS" -gt 4 ]; then
    $PROCESSOR5 &> processor5_$DATESTRING.out.log &
    PROCESSOR5_PID=$!
fi


$FILESINK &> fileSink_$DATESTRING.out.log &
FILESINK_PID=$!

RUN_STRING="Running"

echo   "_________________________________________________________________________________________________________________________"
echo   "|     server   |    sampler   |   processor1 |   processor2 |   processor3 |   processor4 |   processor5 |   file sink  |"
printf "| pid = %6d | pid = %6d | pid = %6d | pid = %6d | pid = %6d | pid = %6d | pid = %6d | pid = %6d |\n" $SERVER_PID $SAMPLER_PID $PROCESSOR1_PID $PROCESSOR2_PID $PROCESSOR3_PID $PROCESSOR4_PID $PROCESSOR5_PID $FILESINK_PID
echo   "|  %CPU    mem |  %CPU    mem |  %CPU    mem |  %CPU    mem |  %CPU    mem |  %CPU    mem |  %CPU    mem |  %CPU    mem |"
for ((i = 0 ; i < 200 ; i++ ));
do
    CHECK_SAMPLER="$(kill -0 $SAMPLER_PID &> /dev/null && echo $RUN_STRING)";
    if [ "$CHECK_SAMPLER" != "$RUN_STRING" ];
    then
        break;
    fi
    SERVER_INFO="$(ps -o %cpu -o rss $SERVER_PID | tail -1)"
    SAMPLER_INFO="$(ps -o %cpu -o rss $SAMPLER_PID | tail -1)"
    PROCESSOR1_INFO="$(ps -o %cpu -o rss $PROCESSOR1_PID | tail -1)"
    PROCESSOR2_INFO="$(ps -o %cpu -o rss $PROCESSOR2_PID | tail -1)"
    PROCESSOR3_INFO="$(ps -o %cpu -o rss $PROCESSOR3_PID | tail -1)"
    PROCESSOR4_INFO="$(ps -o %cpu -o rss $PROCESSOR4_PID | tail -1)"
    PROCESSOR5_INFO="$(ps -o %cpu -o rss $PROCESSOR5_PID | tail -1)"
    FILESINK_INFO="$(ps -o %cpu -o rss $FILESINK_PID | tail -1)"
    printf   "| %5s %6s | %5s %6s | %5s %6s | %5s %6s | %5s %6s | %5s %6s | %5s %6s | %5s %6s |\r" $SERVER_INFO $SAMPLER_INFO $PROCESSOR1_INFO $PROCESSOR2_INFO $PROCESSOR3_INFO $PROCESSOR4_INFO $PROCESSOR5_INFO $FILESINK_INFO
    sleep 1;
done;
echo;
echo   "-------------------------------------------------------------------------------------------"
echo "Jobs finished in $i seconds."


kill $SERVER_PID
CHECK_SAMPLER="$(kill -0 $SAMPLER_PID &> /dev/null && echo $RUN_STRING)";
if [ "$CHECK_SAMPLER" == "$RUN_STRING" ];
then
    kill $SAMPLER_PID
fi
kill $PROCESSOR1_PID
kill $PROCESSOR2_PID
kill $PROCESSOR3_PID
kill $PROCESSOR4_PID
kill $PROCESSOR5_PID
kill $FILESINK_PID

echo "Finished gracefully."

# have to wait for the FILESINK process to finish
wait $FILESINK_PID

INPUT_EVENTS="$(echo "cout<<cbmsim->GetEntries()<<endl;" | root -l -b $INPUTFILE | tail -1)"
OUTPUT_EVENTS="$(echo "cout<<cbmsim->GetEntries()<<endl;" | root -l -b $OUTPUTFILE | tail -1)"
echo "There are $INPUT_EVENTS in the input file."
echo "There are $OUTPUT_EVENTS in the output file."

if [ "$OUTPUT_EVENTS" -eq "$INPUT_EVENTS" ];
then
    echo "Shell script finished successfully.";
fi
