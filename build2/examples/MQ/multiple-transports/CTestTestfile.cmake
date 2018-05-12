# CMake generated Testfile for 
# Source directory: /home/marci/fair_install/FairRoot/examples/MQ/multiple-transports
# Build directory: /home/marci/fair_install/FairRoot/build2/examples/MQ/multiple-transports
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(MQ.ex-multiple-transports "/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/multiple-transports/testMTEx.sh")
set_tests_properties(MQ.ex-multiple-transports PROPERTIES  PASS_REGULAR_EXPRESSION "Received messages from both sources." RUN_SERIAL "true" TIMEOUT "30")
