# CMake generated Testfile for 
# Source directory: /home/marci/fair_install/FairRoot/examples/MQ/9a-PixelDetector/run
# Build directory: /home/marci/fair_install/FairRoot/build2/examples/MQ/9a-PixelDetector/run
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(ex9a_static "/home/marci/fair_install/FairRoot/build2/examples/MQ/9a-PixelDetector/run/startFairMQEx9aFromBin_Static.sh" "--work-dir" "/home/marci/fair_install/FairRoot/build2" "--max-index" "10000" "--aggregate" "100" "--processors" "5" "--force-kill" "true")
set_tests_properties(ex9a_static PROPERTIES  DEPENDS "ex9_static" PASS_REGULAR_EXPRESSION "Shell script finished successfully" TIMEOUT "30")
