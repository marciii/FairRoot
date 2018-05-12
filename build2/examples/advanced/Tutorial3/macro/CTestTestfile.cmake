# CMake generated Testfile for 
# Source directory: /home/marci/fair_install/FairRoot/examples/advanced/Tutorial3/macro
# Build directory: /home/marci/fair_install/FairRoot/build2/examples/advanced/Tutorial3/macro
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(run_sim_TGeant3 "/home/marci/fair_install/FairRoot/build2/examples/advanced/Tutorial3/macro/run_sim.sh" "100" "\"TGeant3\"")
set_tests_properties(run_sim_TGeant3 PROPERTIES  PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "180")
add_test(run_digi_TGeant3 "/home/marci/fair_install/FairRoot/build2/examples/advanced/Tutorial3/macro/run_digi.sh" "\"TGeant3\"")
set_tests_properties(run_digi_TGeant3 PROPERTIES  DEPENDS "run_sim_TGeant3" PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(run_reco_TGeant3 "/home/marci/fair_install/FairRoot/build2/examples/advanced/Tutorial3/macro/run_reco.sh" "\"TGeant3\"")
set_tests_properties(run_reco_TGeant3 PROPERTIES  DEPENDS "run_digi_TGeant3" PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(run_digi_timebased_TGeant3 "/home/marci/fair_install/FairRoot/build2/examples/advanced/Tutorial3/macro/run_digi_timebased.sh" "\"TGeant3\"")
set_tests_properties(run_digi_timebased_TGeant3 PROPERTIES  DEPENDS "run_sim_TGeant3" PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(run_reco_timebased_TGeant3 "/home/marci/fair_install/FairRoot/build2/examples/advanced/Tutorial3/macro/run_reco_timebased.sh" "\"TGeant3\"")
set_tests_properties(run_reco_timebased_TGeant3 PROPERTIES  DEPENDS "run_digi_timebased_TGeant3" PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(run_sim_TGeant4 "/home/marci/fair_install/FairRoot/build2/examples/advanced/Tutorial3/macro/run_sim.sh" "100" "\"TGeant4\"")
set_tests_properties(run_sim_TGeant4 PROPERTIES  PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "180")
add_test(run_digi_TGeant4 "/home/marci/fair_install/FairRoot/build2/examples/advanced/Tutorial3/macro/run_digi.sh" "\"TGeant4\"")
set_tests_properties(run_digi_TGeant4 PROPERTIES  DEPENDS "run_sim_TGeant4" PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(run_reco_TGeant4 "/home/marci/fair_install/FairRoot/build2/examples/advanced/Tutorial3/macro/run_reco.sh" "\"TGeant4\"")
set_tests_properties(run_reco_TGeant4 PROPERTIES  DEPENDS "run_digi_TGeant4" PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(run_digi_timebased_TGeant4 "/home/marci/fair_install/FairRoot/build2/examples/advanced/Tutorial3/macro/run_digi_timebased.sh" "\"TGeant4\"")
set_tests_properties(run_digi_timebased_TGeant4 PROPERTIES  DEPENDS "run_sim_TGeant4" PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(run_reco_timebased_TGeant4 "/home/marci/fair_install/FairRoot/build2/examples/advanced/Tutorial3/macro/run_reco_timebased.sh" "\"TGeant4\"")
set_tests_properties(run_reco_timebased_TGeant4 PROPERTIES  DEPENDS "run_digi_timebased_TGeant4" PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
