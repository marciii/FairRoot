# CMake generated Testfile for 
# Source directory: /home/marci/fair_install/FairRoot/fairmq/test
# Build directory: /home/marci/fair_install/FairRoot/build2/fairmq/test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(FairMQ.Protocols "/home/marci/fair_install/FairRoot/build2/bin/testsuite_FairMQ.Protocols")
set_tests_properties(FairMQ.Protocols PROPERTIES  RUN_SERIAL "ON" TIMEOUT "30" WORKING_DIRECTORY "/home/marci/fair_install/FairRoot/build2")
add_test(FairMQ.Parts "/home/marci/fair_install/FairRoot/build2/bin/testsuite_FairMQ.Parts")
set_tests_properties(FairMQ.Parts PROPERTIES  TIMEOUT "5" WORKING_DIRECTORY "/home/marci/fair_install/FairRoot/build2")
add_test(FairMQ.MessageResize "/home/marci/fair_install/FairRoot/build2/bin/testsuite_FairMQ.MessageResize")
set_tests_properties(FairMQ.MessageResize PROPERTIES  TIMEOUT "5" WORKING_DIRECTORY "/home/marci/fair_install/FairRoot/build2")
add_test(FairMQ.Device "/home/marci/fair_install/FairRoot/build2/bin/testsuite_FairMQ.Device")
set_tests_properties(FairMQ.Device PROPERTIES  RUN_SERIAL "ON" TIMEOUT "5" WORKING_DIRECTORY "/home/marci/fair_install/FairRoot/build2")
add_test(FairMQ.Plugins "/home/marci/fair_install/FairRoot/build2/bin/testsuite_FairMQ.Plugins")
set_tests_properties(FairMQ.Plugins PROPERTIES  TIMEOUT "10" WORKING_DIRECTORY "/home/marci/fair_install/FairRoot/build2")
add_test(FairMQ.PluginsPrelinked "/home/marci/fair_install/FairRoot/build2/bin/testsuite_FairMQ.PluginsPrelinked")
set_tests_properties(FairMQ.PluginsPrelinked PROPERTIES  TIMEOUT "10" WORKING_DIRECTORY "/home/marci/fair_install/FairRoot/build2")
add_test(FairMQ.PluginServices "/home/marci/fair_install/FairRoot/build2/bin/testsuite_FairMQ.PluginServices")
set_tests_properties(FairMQ.PluginServices PROPERTIES  TIMEOUT "10" WORKING_DIRECTORY "/home/marci/fair_install/FairRoot/build2")
add_test(FairMQ.EventManager "/home/marci/fair_install/FairRoot/build2/bin/testsuite_FairMQ.EventManager")
set_tests_properties(FairMQ.EventManager PROPERTIES  TIMEOUT "10" WORKING_DIRECTORY "/home/marci/fair_install/FairRoot/build2")
add_test(FairMQ.StateMachine "/home/marci/fair_install/FairRoot/build2/bin/testsuite_FairMQ.StateMachine")
set_tests_properties(FairMQ.StateMachine PROPERTIES  TIMEOUT "10" WORKING_DIRECTORY "/home/marci/fair_install/FairRoot/build2")
