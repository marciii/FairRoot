#!/bin/bash
ex5config="/home/marci/fair_install/FairRoot/build2/bin/config/ex5-req-rep.json"

CLIENT="ex5-client"
CLIENT+=" --id client"
CLIENT+=" --mq-config $ex5config"
xterm -geometry 80x23+0+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/5-req-rep/$CLIENT &

SERVER="ex5-server"
SERVER+=" --id server"
SERVER+=" --mq-config $ex5config"
xterm -geometry 80x23+500+0 -hold -e /home/marci/fair_install/FairRoot/build2/bin/examples/MQ/5-req-rep/$SERVER &
