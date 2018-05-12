/********************************************************************************
 *    Copyright (C) 2017 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    *
 *                                                                              *
 *              This software is distributed under the terms of the             *
 *              GNU Lesser General Public Licence (LGPL) version 3,             *
 *                  copied verbatim in the file "LICENSE"                       *
 ********************************************************************************/

#ifndef FAIR_MQ_TEST_PLUGIN_DUMMY2
#define FAIR_MQ_TEST_PLUGIN_DUMMY2

#include <fairmq/Plugin.h>

namespace fair
{
namespace mq
{
namespace test
{

class Dummy2Plugin : public fair::mq::Plugin
{
    public:

    Dummy2Plugin(const std::string name, const Version version, const std::string maintainer, const std::string homepage, PluginServices* pluginServices)
    : Plugin(name, version, maintainer, homepage, pluginServices)
    {
    }
}; /* class Dummy2Plugin */

REGISTER_FAIRMQ_PLUGIN(
    Dummy2Plugin,
    test_dummy2,
    (Plugin::Version{2,2,0}),
    "Mr. Dummy <dummy@test.net>",
    "https://git.test.net/dummy.git",
    fair::mq::Plugin::NoProgramOptions
)

} /* namespace test */
} /* namespace mq */
} /* namespace fair */

#endif /* FAIR_MQ_TEST_PLUGIN_DUMMY */
