# CMake generated Testfile for 
# Source directory: /home/marci/fair_install/FairRoot/examples/advanced/MbsTutorial/macros
# Build directory: /home/marci/fair_install/FairRoot/build2/examples/advanced/MbsTutorial/macros
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(unpack_mbs "/home/marci/fair_install/FairRoot/build2/examples/advanced/MbsTutorial/macros/unpack_mbs.sh")
set_tests_properties(unpack_mbs PROPERTIES  PASS_REGULAR_EXPRESSION "Macro finished successfully" TIMEOUT "30")
