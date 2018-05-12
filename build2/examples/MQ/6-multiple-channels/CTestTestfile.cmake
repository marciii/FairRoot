# CMake generated Testfile for 
# Source directory: /home/marci/fair_install/FairRoot/examples/MQ/6-multiple-channels
# Build directory: /home/marci/fair_install/FairRoot/build2/examples/MQ/6-multiple-channels
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(MQ.ex6-multiple-channels "/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/6-multiple-channels/testMQEx6.sh")
set_tests_properties(MQ.ex6-multiple-channels PROPERTIES  PASS_REGULAR_EXPRESSION "Received messages from both sources." RUN_SERIAL "true" TIMEOUT "30")
