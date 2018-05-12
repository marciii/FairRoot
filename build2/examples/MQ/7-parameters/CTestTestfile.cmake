# CMake generated Testfile for 
# Source directory: /home/marci/fair_install/FairRoot/examples/MQ/7-parameters
# Build directory: /home/marci/fair_install/FairRoot/build2/examples/MQ/7-parameters
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(MQ.ex7-parameters "/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/7-parameters/testMQEx7.sh")
set_tests_properties(MQ.ex7-parameters PROPERTIES  PASS_REGULAR_EXPRESSION "Received parameter from the server:" RUN_SERIAL "true" TIMEOUT "30")
