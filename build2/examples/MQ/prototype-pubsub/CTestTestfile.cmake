# CMake generated Testfile for 
# Source directory: /home/marci/fair_install/FairRoot/examples/MQ/prototype-pubsub
# Build directory: /home/marci/fair_install/FairRoot/build2/examples/MQ/prototype-pubsub
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(MQ.prototype-pubsub "/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/prototype-pubsub/testPrototype-pubsub.sh")
set_tests_properties(MQ.prototype-pubsub PROPERTIES  PASS_REGULAR_EXPRESSION "Received: " RUN_SERIAL "true" TIMEOUT "30")
