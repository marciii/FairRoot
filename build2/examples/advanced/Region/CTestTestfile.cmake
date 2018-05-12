# CMake generated Testfile for 
# Source directory: /home/marci/fair_install/FairRoot/examples/advanced/Region
# Build directory: /home/marci/fair_install/FairRoot/build2/examples/advanced/Region
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(MQ.ex-advanced-region "/home/marci/fair_install/FairRoot/build2/bin/examples/advanced/Region/testMQExRegion.sh")
set_tests_properties(MQ.ex-advanced-region PROPERTIES  PASS_REGULAR_EXPRESSION "Received ack" RUN_SERIAL "true" TIMEOUT "30")
