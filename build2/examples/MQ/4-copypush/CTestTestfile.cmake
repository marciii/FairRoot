# CMake generated Testfile for 
# Source directory: /home/marci/fair_install/FairRoot/examples/MQ/4-copypush
# Build directory: /home/marci/fair_install/FairRoot/build2/examples/MQ/4-copypush
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(MQ.ex4-copypush "/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/4-copypush/testMQEx4.sh")
set_tests_properties(MQ.ex4-copypush PROPERTIES  PASS_REGULAR_EXPRESSION "Received message: " RUN_SERIAL "true" TIMEOUT "30")
