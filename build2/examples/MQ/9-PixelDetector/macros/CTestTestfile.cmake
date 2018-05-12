# CMake generated Testfile for 
# Source directory: /home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/macros
# Build directory: /home/marci/fair_install/FairRoot/build2/examples/MQ/9-PixelDetector/macros
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(ex9_sim_TGeant3 "/home/marci/fair_install/FairRoot/build2/examples/MQ/9-PixelDetector/macros/run_sim.sh" "10000" "\"TGeant3\"")
set_tests_properties(ex9_sim_TGeant3 PROPERTIES  PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "120")
add_test(ex9_digi_TGeant3 "/home/marci/fair_install/FairRoot/build2/examples/MQ/9-PixelDetector/macros/run_digi.sh" "\"TGeant3\"")
set_tests_properties(ex9_digi_TGeant3 PROPERTIES  DEPENDS "ex9_sim_TGeant3" PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "30")
add_test(ex9_dbin_TGeant3 "/home/marci/fair_install/FairRoot/build2/examples/MQ/9-PixelDetector/macros/run_digiToBin.sh" "0" "\"TGeant3\"")
set_tests_properties(ex9_dbin_TGeant3 PROPERTIES  DEPENDS "ex9_digi_TGeant3" PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "30")
