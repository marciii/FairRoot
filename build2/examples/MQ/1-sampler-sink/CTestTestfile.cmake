# CMake generated Testfile for 
# Source directory: /home/marci/fair_install/FairRoot/examples/MQ/1-sampler-sink
# Build directory: /home/marci/fair_install/FairRoot/build2/examples/MQ/1-sampler-sink
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(MQ.ex1-sampler-sink "/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/1-sampler-sink/testMQEx1.sh")
set_tests_properties(MQ.ex1-sampler-sink PROPERTIES  PASS_REGULAR_EXPRESSION " Received: \"Hello\"" RUN_SERIAL "true" TIMEOUT "30")
