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
MQCONFIGFILE="/home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/run/options/Pixel9MQConfig_Multipart.json"
# ASCII and ROOT parameter files for the processor device
ROOTPARAM="/home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.params.root"
ASCIIPARAM="/home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/param/pixel_digi.par"

if [ "$FAIRTASKNAME" == "--task-name PixelFindHits" ] ; then
    # input file and branch for the sampler device
    INPUTFILE="/home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.digi.root"
 #   INPUTFILE+=" --file-name /home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/pixel_TGeant3.digi.f1.root"
    INPUTBRANCH="PixelDigis"
    
    # output file for sink
    OUTPUTFILE="/home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/MQ.pixel_TGeant3.hits.root"
    OUTPUTCLASS="--class-name TClonesArray(PixelHit)"
    OUTPUTBRANCH="--branch-name PixelHits"
elif [ "$FAIRTASKNAME" == "--task-name PixelFindTracks" ] ; then
    # input file and branch for the sampler device 
    FAIRTASKNAME+=" --keep-data PixelHits"
    INPUTFILE="/home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/MQ.pixel_TGeant3.hits.root"
    INPUTBRANCH="PixelHits"
    
    # output file for sink
    OUTPUTFILE="/home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/MQ.pixel_TGeant3.hits_tracks.root"
    OUTPUTCLASS="--class-name TClonesArray(PixelHit) --class-name TClonesArray(PixelTrack)"
    OUTPUTBRANCH="--branch-name PixelHits --branch-name PixelTracks"
elif [ "$FAIRTASKNAME" == "--task-name PixelFitTracks" ] ; then
    # input file and branch for the sampler device
    INPUTFILE="/home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/MQ.pixel_TGeant3.hits_tracks.root"
    INPUTBRANCH="PixelHits --branch-name PixelTracks"
    
    # output file for sink
    OUTPUTFILE="/home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros/MQ.pixel_TGeant3.fitTracks.root"
    OUTPUTCLASS="--class-name TClonesArray(PixelTrack)"
    OUTPUTBRANCH="--branch-name PixelFitTracks"
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
xterm -geometry 80x25+0+350 -hold -e /home/marci/fair_install/FairRoot/build2/bin/$SERVER &


########################## start SAMPLER
SAMPLER="ex9-sampler $TRANSPORT"
SAMPLER+=" --id sampler1  --mq-config $MQCONFIGFILE --severity info"
SAMPLER+=" --file-name $INPUTFILE --branch-name $INPUTBRANCH --branch-name EventHeader. $MAXINDEX"
xterm -geometry 80x25+0+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/9-PixelDetector/$SAMPLER &

########################## start PROCESSORs
PROCESSOR1="ex9-processor $TRANSPORT"
PROCESSOR1+=" $VERBOSE"
PROCESSOR1+=" --id processor1 $FAIRTASKNAME --mq-config $MQCONFIGFILE"
#xterm +aw -geometry 100x27+800+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/9-PixelDetector/$PROCESSOR1 &
xterm -geometry 80x25+500+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/9-PixelDetector/$PROCESSOR1 &

PROCESSOR2="ex9-processor $TRANSPORT"
PROCESSOR2+=" $VERBOSE"
PROCESSOR2+=" --id processor2 $FAIRTASKNAME --mq-config $MQCONFIGFILE"
xterm -geometry 80x25+500+350 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/9-PixelDetector/$PROCESSOR2 &

PROCESSOR3="ex9-processor $TRANSPORT"
PROCESSOR3+=" $VERBOSE"
PROCESSOR3+=" --id processor3 $FAIRTASKNAME --mq-config $MQCONFIGFILE"
xterm -geometry 80x25+500+700 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/9-PixelDetector/$PROCESSOR3 &

PROCESSOR4="ex9-processor $TRANSPORT"
PROCESSOR4+=" $VERBOSE"
PROCESSOR4+=" --id processor4 $FAIRTASKNAME --mq-config $MQCONFIGFILE"
xterm -geometry 80x25+1000+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/9-PixelDetector/$PROCESSOR4 &

PROCESSOR5="ex9-processor $TRANSPORT"
PROCESSOR5+=" $VERBOSE"
PROCESSOR5+=" --id processor5 $FAIRTASKNAME --mq-config $MQCONFIGFILE"
xterm -geometry 80x25+1000+350 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/9-PixelDetector/$PROCESSOR5 &

########################## start FILESINK
FILESINK="ex9-sink $TRANSPORT"
FILESINK+=" --id sink1 --mq-config $MQCONFIGFILE"
FILESINK+=" --file-name $OUTPUTFILE --class-name FairEventHeader --branch-name EventHeader. $OUTPUTCLASS $OUTPUTBRANCH"
xterm +aw -geometry 100x25+0+700 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/9-PixelDetector/$FILESINK &


