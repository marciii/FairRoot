# CMake generated Testfile for 
# Source directory: /home/marci/fair_install/FairRoot/examples/MQ/2-sampler-processor-sink
# Build directory: /home/marci/fair_install/FairRoot/build2/examples/MQ/2-sampler-processor-sink
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(MQ.ex2-sampler-processor-sink "/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/2-sampler-processor-sink/testMQEx2.sh")
set_tests_properties(MQ.ex2-sampler-processor-sink PROPERTIES  PASS_REGULAR_EXPRESSION "Received: " RUN_SERIAL "true" TIMEOUT "30")
