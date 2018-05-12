#!/bin/bash

MAXINDEX="--max-index -1"
TRANSPORT="--transport zeromq"
VERBOSE="--severity INFO"
FAIRTASKNAME="--task-name PixelFindHits"

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
    -v|--verbose)
    VERBOSE="--severity $2"
    shift
    ;;
esac
shift 
done

########################### Define some variables
# JSON file containing the configuration parameters of all FairMQ devices of this example
MQCONFIGFILE="/home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/run/options/Pixel9MQConfig_Proxy.json"
# ASCII and ROOT parameter files for the processor device
ROOTPARAM="/home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.params.root"
ASCIIPARAM="/home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/param/pixel_digi.par"

if [ "$FAIRTASKNAME" == "--task-name PixelFindHits" ] ; then
    # input file and branch for the sampler device
    INPUTFILE1="/home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.digi.root"
    INPUTFILE1+=" --file-name /home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.digi.root"
    INPUTFILE1+=" --file-name /home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.digi.root"
    INPUTFILE1+=" --file-name /home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.digi.root"
    INPUTFILE1+=" --file-name /home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.digi.root"

    cp /home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.digi.root /home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.digi.2.root
   
    INPUTFILE2="/home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.digi.2.root"
    INPUTFILE2+=" --file-name /home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.digi.2.root"
    INPUTFILE2+=" --file-name /home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.digi.2.root"
    INPUTFILE2+=" --file-name /home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.digi.2.root"
    INPUTFILE2+=" --file-name /home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.digi.2.root"
 #   INPUTFILE+=" --file-name /home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.digi.f1.root"
    INPUTBRANCH="PixelDigis"
    
    # output file for sink
    OUTPUTFILE1="/home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/MQ.pixel_TGeant3.bin.hits1.root"
    OUTPUTFILE2="/home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/MQ.pixel_TGeant3.bin.hits2.root"
    OUTPUTCLASS="--class-name TClonesArray(PixelHit)"
    OUTPUTBRANCH="--branch-name PixelHits"
else
    echo "TASK $FAIRTASKNAME UNKNOWN!!!"
    exit
fi
###########################



########################### Start the chain of the devices


########################## start Parameter server
SERVER="parmq-server $TRANSPORT"
SERVER+=" --id parmq-server  --mq-config $MQCONFIGFILE"
SERVER+=" --first-input-name $ROOTPARAM --second-input-name $ASCIIPARAM --second-input-type ASCII"
xterm -geometry 80x24+0+350 -hold -e /home/marci/fair_install/FairRoot/build2/bin/$SERVER &


########################## start SAMPLE
SAMPLER1="ex9-samplerBin $TRANSPORT"
SAMPLER1+=" --id sampler1  --mq-config $MQCONFIGFILE --severity info"
SAMPLER1+=" --file-name $INPUTFILE1 --branch-name EventHeader. --branch-name $INPUTBRANCH $MAXINDEX"
xterm -geometry 80x24+0+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/9-PixelDetector/$SAMPLER1 &

SAMPLER2="ex9-samplerBin $TRANSPORT"
SAMPLER2+=" --id sampler1  --mq-config $MQCONFIGFILE --severity info"
SAMPLER2+=" --file-name $INPUTFILE2 --branch-name EventHeader. --branch-name $INPUTBRANCH $MAXINDEX"
xterm -geometry 80x24+0+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/9-PixelDetector/$SAMPLER2 &

########################## start PROXY SAMPLER
PROXYS="proxy $TRANSPORT"
PROXYS+=" --id proxysampler --mq-config $MQCONFIGFILE"
xterm -geometry 80x24+0+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/$PROXYS &

########################## start PROCESSORs
PROCESSOR1="ex9-processorBin $TRANSPORT"
PROCESSOR1+=" $VERBOSE"
PROCESSOR1+=" --id processor1 $FAIRTASKNAME --mq-config $MQCONFIGFILE"
#xterm +aw -geometry 100x27+700+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/9-PixelDetector/$PROCESSOR1 &
xterm -geometry 80x24+500+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/9-PixelDetector/$PROCESSOR1 &

PROCESSOR2="ex9-processorBin $TRANSPORT"
PROCESSOR2+=" $VERBOSE"
PROCESSOR2+=" --id processor2 $FAIRTASKNAME --mq-config $MQCONFIGFILE"
xterm -geometry 80x24+500+350 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/9-PixelDetector/$PROCESSOR2 &

PROCESSOR3="ex9-processorBin $TRANSPORT"
PROCESSOR3+=" $VERBOSE"
PROCESSOR3+=" --id processor3 $FAIRTASKNAME --mq-config $MQCONFIGFILE"
xterm -geometry 80x24+500+700 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/9-PixelDetector/$PROCESSOR3 &

PROCESSOR4="ex9-processorBin $TRANSPORT"
PROCESSOR4+=" $VERBOSE"
PROCESSOR4+=" --id processor4 $FAIRTASKNAME --mq-config $MQCONFIGFILE"
xterm -geometry 80x24+1000+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/9-PixelDetector/$PROCESSOR4 &

PROCESSOR5="ex9-processorBin $TRANSPORT"
PROCESSOR5+=" $VERBOSE"
PROCESSOR5+=" --id processor5 $FAIRTASKNAME --mq-config $MQCONFIGFILE"
xterm -geometry 80x24+1000+350 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/9-PixelDetector/$PROCESSOR5 &

########################## start PROXY SAMPLER
PROXYF="proxy $TRANSPORT"
PROXYF+=" --id proxysink --mq-config $MQCONFIGFILE"
xterm -geometry 80x24+0+700 -hold -e /home/marci/fair_install/FairRoot/build2/bin/$PROXYF &

########################## start FILESINK
FILESINK1="ex9-sinkBin $TRANSPORT"
FILESINK1+=" --id sink1 --mq-config $MQCONFIGFILE"
FILESINK1+=" --file-name $OUTPUTFILE1 $OUTPUTCLASS $OUTPUTBRANCH"
xterm +aw -geometry 80x24+0+700 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/9-PixelDetector/$FILESINK1 &

FILESINK2="ex9-sinkBin $TRANSPORT"
FILESINK2+=" --id sink1 --mq-config $MQCONFIGFILE"
FILESINK2+=" --file-name $OUTPUTFILE2 $OUTPUTCLASS $OUTPUTBRANCH"
xterm +aw -geometry 80x24+0+700 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/9-PixelDetector/$FILESINK2 &


