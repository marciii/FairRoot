# CMake generated Testfile for 
# Source directory: /home/marci/fair_install/FairRoot/examples/MQ/8-multipart
# Build directory: /home/marci/fair_install/FairRoot/build2/examples/MQ/8-multipart
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(MQ.ex8-multipart "/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/8-multipart/testMQEx8.sh")
set_tests_properties(MQ.ex8-multipart PROPERTIES  PASS_REGULAR_EXPRESSION "Received message with 2 parts" RUN_SERIAL "true" TIMEOUT "30")
