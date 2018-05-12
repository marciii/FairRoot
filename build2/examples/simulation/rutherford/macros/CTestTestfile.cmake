# CMake generated Testfile for 
# Source directory: /home/marci/fair_install/FairRoot/examples/simulation/rutherford/macros
# Build directory: /home/marci/fair_install/FairRoot/build2/examples/simulation/rutherford/macros
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(run_rutherford_TGeant3 "/home/marci/fair_install/FairRoot/build2/examples/simulation/rutherford/macros/run_rutherford.sh" "10" "\"TGeant3\"")
set_tests_properties(run_rutherford_TGeant3 PROPERTIES  PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(run_rad_TGeant3 "/home/marci/fair_install/FairRoot/build2/examples/simulation/rutherford/macros/run_rad.sh" "100" "\"TGeant3\"")
set_tests_properties(run_rad_TGeant3 PROPERTIES  PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(run_rutherford_TGeant4 "/home/marci/fair_install/FairRoot/build2/examples/simulation/rutherford/macros/run_rutherford.sh" "10" "\"TGeant4\"")
set_tests_properties(run_rutherford_TGeant4 PROPERTIES  PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(run_rad_TGeant4 "/home/marci/fair_install/FairRoot/build2/examples/simulation/rutherford/macros/run_rad.sh" "100" "\"TGeant4\"")
set_tests_properties(run_rad_TGeant4 PROPERTIES  PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
