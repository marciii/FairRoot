/********************************************************************************
 *    Copyright (C) 2017 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#include "runner.h"

#include <gtest/gtest.h>

#include <string>
#include <iostream>

namespace fair
{
namespace mq
{
namespace test
{

using namespace std;

string runTestDevice = "/home/marci/fair_install/FairRoot/build2/bin/testhelper_runTestDevice";
string mqConfig = "/home/marci/fair_install/FairRoot/build2/bin/testsuite_FairMQ.IOPatterns_config.json";

} /* namespace test */
} /* namespace mq */
} /* namespace fair */

auto main(int argc, char** argv) -> int
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::FLAGS_gtest_death_test_style = "threadsafe";
    return RUN_ALL_TESTS();
}
