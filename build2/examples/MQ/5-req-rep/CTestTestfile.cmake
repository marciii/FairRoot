# CMake generated Testfile for 
# Source directory: /home/marci/fair_install/FairRoot/examples/MQ/5-req-rep
# Build directory: /home/marci/fair_install/FairRoot/build2/examples/MQ/5-req-rep
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(MQ.ex5-req-rep "/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/5-req-rep/testMQEx5.sh")
set_tests_properties(MQ.ex5-req-rep PROPERTIES  PASS_REGULAR_EXPRESSION "Received reply from server: " RUN_SERIAL "true" TIMEOUT "30")
