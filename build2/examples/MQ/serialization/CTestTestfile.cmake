# CMake generated Testfile for 
# Source directory: /home/marci/fair_install/FairRoot/examples/MQ/serialization
# Build directory: /home/marci/fair_install/FairRoot/build2/examples/MQ/serialization
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(MQ.ex-serialization1 "/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/serialization/startTestSerializationEx1.sh")
set_tests_properties(MQ.ex-serialization1 PROPERTIES  PASS_REGULAR_EXPRESSION "Received 100 messages!" TIMEOUT "30")
add_test(MQ.ex-serialization2 "/home/marci/fair_install/FairRoot/build2/bin/examples/MQ/serialization/startTestSerializationEx2.sh")
set_tests_properties(MQ.ex-serialization2 PROPERTIES  DEPENDS "MQ.ex-serialization1" PASS_REGULAR_EXPRESSION "Received 100 messages!" TIMEOUT "30")
