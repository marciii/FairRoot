 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################

configure_file(${CMAKE_SOURCE_DIR}/examples/MQ/prototype-pair/prototype-pair.json ${CMAKE_BINARY_DIR}/bin/config/prototype-pair.json)
configure_file(${CMAKE_SOURCE_DIR}/examples/MQ/prototype-pair/startPrototype-pair.sh.in ${CMAKE_BINARY_DIR}/bin/examples/MQ/prototype-pair/startPrototype-pair.sh)
configure_file(${CMAKE_SOURCE_DIR}/examples/MQ/prototype-pair/testPrototype-pair.sh.in ${CMAKE_BINARY_DIR}/bin/examples/MQ/prototype-pair/testPrototype-pair.sh)

set(INCLUDE_DIRECTORIES
  ${CMAKE_SOURCE_DIR}/fairmq
  ${CMAKE_SOURCE_DIR}/fairmq/devices
  ${CMAKE_SOURCE_DIR}/fairmq/tools
  ${CMAKE_SOURCE_DIR}/fairmq/options
  ${CMAKE_SOURCE_DIR}/examples/MQ/prototype-pair
  ${CMAKE_CURRENT_BINARY_DIR}
)

set(SYSTEM_INCLUDE_DIRECTORIES
  ${Boost_INCLUDE_DIR}
  ${ZeroMQ_INCLUDE_DIR}
)

include_directories(${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
  ${Boost_LIBRARY_DIRS}
)

link_directories(${LINK_DIRECTORIES})

set(SRCS
"HardwareInformation.cxx"
  "PrototypeFlpProcessor.cxx"
  "PrototypeSchedulerProcessor.cxx"
  "PrototypeEpnProcessor.cxx"
)

set(DEPENDENCIES
  ${DEPENDENCIES}
  FairMQ
)

set(LIBRARY_NAME Prototypepair)

GENERATE_LIBRARY()

set(Exe_Names
  flpprocessorpair
  schedulerprocessorpair
  epnprocessorpair
)

set(Exe_Source
  runPrototypeFlpProcessor.cxx
  runPrototypeSchedulerProcessor.cxx
  runPrototypeEpnProcessor.cxx
)

list(LENGTH Exe_Names _length)
math(EXPR _length ${_length}-1)

set(BIN_DESTINATION share/fairbase/examples/MQ/prototype-pair/bin)
set(EXECUTABLE_OUTPUT_PATH "${EXECUTABLE_OUTPUT_PATH}/examples/MQ/prototype-pair")

foreach(_file RANGE 0 ${_length})
  list(GET Exe_Names ${_file} _name)
  list(GET Exe_Source ${_file} _src)
  set(EXE_NAME ${_name})
  set(SRCS ${_src})
  set(DEPENDENCIES Prototypepair)
  GENERATE_EXECUTABLE()
endforeach(_file RANGE 0 ${_length})

add_test(NAME MQ.prototype-pair COMMAND ${CMAKE_BINARY_DIR}/bin/examples/MQ/prototype-pair/testPrototype-pair.sh)
set_tests_properties(MQ.prototype-pair PROPERTIES TIMEOUT "30")
set_tests_properties(MQ.prototype-pair PROPERTIES RUN_SERIAL true)
set_tests_properties(MQ.prototype-pair PROPERTIES PASS_REGULAR_EXPRESSION "Received: ")

install(
  FILES prototype-pair.json
  DESTINATION share/fairbase/examples/MQ/prototype-pair/config/
)
