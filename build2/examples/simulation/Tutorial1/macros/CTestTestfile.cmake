# CMake generated Testfile for 
# Source directory: /home/marci/fair_install/FairRoot/examples/simulation/Tutorial1/macros
# Build directory: /home/marci/fair_install/FairRoot/build2/examples/simulation/Tutorial1/macros
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(load_all_libs "/home/marci/fair_install/FairRoot/build2/examples/simulation/Tutorial1/macros/load_all_libs.sh")
set_tests_properties(load_all_libs PROPERTIES  PASS_REGULAR_EXPRESSION "Macro finished succesfully" TIMEOUT "60")
add_test(run_tutorial1_TGeant3 "/home/marci/fair_install/FairRoot/build2/examples/simulation/Tutorial1/macros/run_tutorial1.sh" "10" "\"TGeant3\"")
set_tests_properties(run_tutorial1_TGeant3 PROPERTIES  PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(run_tutorial1_pythia6_TGeant3 "/home/marci/fair_install/FairRoot/build2/examples/simulation/Tutorial1/macros/run_tutorial1_pythia6.sh" "10" "\"TGeant3\"")
set_tests_properties(run_tutorial1_pythia6_TGeant3 PROPERTIES  PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(run_tutorial1_pythia8_TGeant3 "/home/marci/fair_install/FairRoot/build2/examples/simulation/Tutorial1/macros/run_tutorial1_pythia8.sh" "10" "\"TGeant3\"")
set_tests_properties(run_tutorial1_pythia8_TGeant3 PROPERTIES  PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(run_tutorial1_mesh_TGeant3 "/home/marci/fair_install/FairRoot/build2/examples/simulation/Tutorial1/macros/run_tutorial1_mesh.sh" "10" "\"TGeant3\"")
set_tests_properties(run_tutorial1_mesh_TGeant3 PROPERTIES  PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(run_tutorial1_urqmd_TGeant3 "/home/marci/fair_install/FairRoot/build2/examples/simulation/Tutorial1/macros/run_tutorial1_urqmd.sh" "2" "\"TGeant3\"")
set_tests_properties(run_tutorial1_urqmd_TGeant3 PROPERTIES  PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(run_tutorial1_TGeant4 "/home/marci/fair_install/FairRoot/build2/examples/simulation/Tutorial1/macros/run_tutorial1.sh" "10" "\"TGeant4\"")
set_tests_properties(run_tutorial1_TGeant4 PROPERTIES  PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(run_tutorial1_pythia6_TGeant4 "/home/marci/fair_install/FairRoot/build2/examples/simulation/Tutorial1/macros/run_tutorial1_pythia6.sh" "10" "\"TGeant4\"")
set_tests_properties(run_tutorial1_pythia6_TGeant4 PROPERTIES  PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(run_tutorial1_pythia8_TGeant4 "/home/marci/fair_install/FairRoot/build2/examples/simulation/Tutorial1/macros/run_tutorial1_pythia8.sh" "10" "\"TGeant4\"")
set_tests_properties(run_tutorial1_pythia8_TGeant4 PROPERTIES  PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(run_tutorial1_mesh_TGeant4 "/home/marci/fair_install/FairRoot/build2/examples/simulation/Tutorial1/macros/run_tutorial1_mesh.sh" "10" "\"TGeant4\"")
set_tests_properties(run_tutorial1_mesh_TGeant4 PROPERTIES  PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
add_test(run_tutorial1_urqmd_TGeant4 "/home/marci/fair_install/FairRoot/build2/examples/simulation/Tutorial1/macros/run_tutorial1_urqmd.sh" "2" "\"TGeant4\"")
set_tests_properties(run_tutorial1_urqmd_TGeant4 PROPERTIES  PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "60")
