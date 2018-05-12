#!/bin/bash
ex7config="/home/marci/fair_install/FairRoot/build2/bin/config/ex7-client.json"
parmqconfig="/home/marci/fair_install/FairRoot/build2/bin/config/parameter-server.json"

SAMPLER="ex7-client"
SAMPLER+=" --id parmq-client"
SAMPLER+=" --mq-config $ex7config"
xterm -geometry 80x23+0+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/7-parameters/$SAMPLER &

PARAMETERSERVER="parmq-server"
PARAMETERSERVER+=" --id parmq-server"
PARAMETERSERVER+=" --mq-config $parmqconfig"
PARAMETERSERVER+=" --first-input-name /home/marci/fair_install/FairRoot/build2/examples/MQ/7-parameters/mqexample7_param.root"
xterm -geometry 80x23+500+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/$PARAMETERSERVER &
