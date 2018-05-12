# CMake generated Testfile for 
# Source directory: /home/marci/fair_install/FairRoot/examples/MQ/9-PixelDetector/run
# Build directory: /home/marci/fair_install/FairRoot/build2/examples/MQ/9-PixelDetector/run
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(ex9_static "/home/marci/fair_install/FairRoot/build2/examples/MQ/9-PixelDetector/run/startFairMQEx9_Static.sh" "--work-dir" "/home/marci/fair_install/FairRoot/build2" "--force-kill" "true")
set_tests_properties(ex9_static PROPERTIES  DEPENDS "ex9_dbin_TGeant3" PASS_REGULAR_EXPRESSION "Shell script finished successfully" TIMEOUT "30")
