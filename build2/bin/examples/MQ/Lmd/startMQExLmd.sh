#!/bin/bash

MQCONFIGFILE="/home/marci/fair_install/FairRoot/build2/bin/config/ex-lmd.json"
LMDFILE="/home/marci/fair_install/FairRoot/examples/advanced/MbsTutorial/data/sample_data_2.lmd"
SEVERITY="DEBUG"

########################## start SAMPLER
SAMPLER="ex-lmd-sampler"
SAMPLER+=" --id LmdSampler"
SAMPLER+=" --mq-config $MQCONFIGFILE"
SAMPLER+=" --lmd-type 94"
SAMPLER+=" --lmd-sub-type 9400"
SAMPLER+=" --lmd-proc-id 12"
SAMPLER+=" --lmd-sub-crate 0"
SAMPLER+=" --lmd-control 3"
SAMPLER+=" --lmd-chan-name ToMBSUnpacker"
SAMPLER+=" --input-file-name $LMDFILE"
SAMPLER+=" --severity $SEVERITY"
xterm -geometry 80x30+0+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/Lmd/$SAMPLER &

########################## start Unpacker
UNPACKER="ex-lmd-mbs-unpacker"
UNPACKER+=" --id unpacker1"
UNPACKER+=" --mq-config $MQCONFIGFILE"
UNPACKER+=" --lmd-type 94"
UNPACKER+=" --lmd-sub-type 9400"
UNPACKER+=" --lmd-proc-id 12"
UNPACKER+=" --lmd-sub-crate 0"
UNPACKER+=" --lmd-control 3"
UNPACKER+=" --lmd-chan-name ToMBSUnpacker"
UNPACKER+=" --severity $SEVERITY"
xterm -geometry 80x30+500+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/Lmd/$UNPACKER &

########################## start FILESINK
FILESINK="ex-lmd-mbs-sink"
FILESINK+=" --id sink1 --mq-config $MQCONFIGFILE"
FILESINK+=" --output-file-name /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/Lmd/ex-lmd-output.root"
FILESINK+=" --severity $SEVERITY"
xterm -geometry 80x30+1000+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/Lmd/$FILESINK &
