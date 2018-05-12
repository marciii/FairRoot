# CMake generated Testfile for 
# Source directory: /home/marci/fair_install/FairRoot/examples/simulation/Tutorial2/macros
# Build directory: /home/marci/fair_install/FairRoot/build2/examples/simulation/Tutorial2/macros
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(run_tutorial2 "/home/marci/fair_install/FairRoot/build2/examples/simulation/Tutorial2/macros/run_tutorial2.sh")
set_tests_properties(run_tutorial2 PROPERTIES  PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(create_digis "/home/marci/fair_install/FairRoot/build2/examples/simulation/Tutorial2/macros/create_digis.sh")
set_tests_properties(create_digis PROPERTIES  DEPENDS "run_tutorial2" PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(read_digis "/home/marci/fair_install/FairRoot/build2/examples/simulation/Tutorial2/macros/read_digis.sh")
set_tests_properties(read_digis PROPERTIES  DEPENDS "create_digis" PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(run_bg "/home/marci/fair_install/FairRoot/build2/examples/simulation/Tutorial2/macros/run_bg.sh")
set_tests_properties(run_bg PROPERTIES  DEPENDS "read_digis" PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(run_sg "/home/marci/fair_install/FairRoot/build2/examples/simulation/Tutorial2/macros/run_sg.sh")
set_tests_properties(run_sg PROPERTIES  DEPENDS "run_bg" PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(run_sg1 "/home/marci/fair_install/FairRoot/build2/examples/simulation/Tutorial2/macros/run_sg1.sh")
set_tests_properties(run_sg1 PROPERTIES  DEPENDS "run_sg" PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(create_digis_mixed "/home/marci/fair_install/FairRoot/build2/examples/simulation/Tutorial2/macros/create_digis_mixed.sh")
set_tests_properties(create_digis_mixed PROPERTIES  DEPENDS "run_sg1" PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
