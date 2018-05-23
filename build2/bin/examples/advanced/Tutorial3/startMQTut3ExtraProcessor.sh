#!/bin/bash

echo "Supported data formats: binary, boost, boost-text, flatbuffers, msgpack, protobuf, tmessage"
dataFormat="binary"
if [ "$1" = "binary" ]; then
    echo "Using: binary"
elif [ "$1" = "boost" ]; then
    dataFormat="boost"
    echo "Using: boost (Boost binary)"
elif [ "$1" = "boost-text" ]; then
    dataFormat="boost-text"
    echo "Using: boost-text (Boost text)"
elif [ "$1" = "flatbuffers" ]; then
    if(true); then
        dataFormat="flatbuffers"
        echo "Using: flatbuffers (Google FlatBuffers)"
    else
        echo "Cannot use flatbuffers: library not found at build time"
        exit 1
    fi
elif [ "$1" = "msgpack" ]; then
    if(true); then
        dataFormat="msgpack"
        echo "Using: msgpack (MessagePack)"
    else
        echo "Cannot use msgpack: library not found at build time"
        exit 1
    fi
elif [ "$1" = "protobuf" ]; then
    dataFormat="protobuf"
    echo "Using: protobuf (Google Protocol Buffers)"
elif [ "$1" = "tmessage" ]; then
    dataFormat="tmessage"
    echo "Using: tmessage (Root TMessage)"
else
    echo "None or incorrect data format provided!"
    echo "Using: binary"
fi

ID="processorx"

tut3cfg="/home/marci/fair_install/FairRoot/build2/bin/config/tut3-extra-processor.json"

PROCESSOR2="tut3-processor"
PROCESSOR2+=" --id processor2"
PROCESSOR2+=" --severity debug"
PROCESSOR2+=" --data-format $dataFormat"
PROCESSOR2+=" --mq-config $tut3cfg"
PROCESSOR2+=" --config-key processor"
xterm -geometry 80x23+500+350 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/advanced/Tutorial3/$PROCESSOR2 &
