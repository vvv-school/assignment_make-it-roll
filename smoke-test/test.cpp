/*
 * Copyright (C) 2016 iCub Facility - Istituto Italiano di Tecnologia
 * Author: Ugo Pattacini <ugo.pattacini@iit.it>
 * CopyPolicy: Released under the terms of the GNU GPL v3.0.
*/

#include <string>

#include <rtf/yarp/YarpTestCase.h>
#include <rtf/dll/Plugin.h>

#include <yarp/os/all.h>
#include <yarp/sig/all.h>
#include <yarp/math/Math.h>

using namespace std;
using namespace RTF;
using namespace yarp::os;
using namespace yarp::sig;
using namespace yarp::math;

/**********************************************************************/
class TestAssignmentMakeItRoll : public YarpTestCase
{
    RpcClient portBall;
    RpcClient portMIR;

public:
    /******************************************************************/
    TestAssignmentMakeItRoll() :
        YarpTestCase("TestAssignmentMakeItRoll")
    {
    }

    /******************************************************************/
    virtual ~TestAssignmentMakeItRoll()
    {
    }

    /******************************************************************/
    virtual bool setup(yarp::os::Property& property)
    {
        string portBallName("/"+getName()+"/ball:rpc");
        string portMIRName("/"+getName()+"/mir:rpc");

        portBall.open(portBallName);
        portMIR.open(portMIRName);

        RTF_TEST_REPORT("Connecting Ports");
        RTF_ASSERT_ERROR_IF(Network::connect(portBallName,"/icubSim/world"),
                            "Unable to connect to world!");
        RTF_ASSERT_ERROR_IF(Network::connect(portMIRName,"/service"),
                            "Unable to connect to world!");

        return true;
    }

    /******************************************************************/
    virtual void tearDown()
    {
        RTF_TEST_REPORT("Closing Ports");
        portBall.close();
        portMIR.close();
    }

    /******************************************************************/
    virtual void run()
    {
        Bottle cmd,reply;

        RTF_TEST_REPORT("Retrieving initial ball position");
        cmd.addString("world"); cmd.addString("get"); cmd.addString("ball");
        RTF_ASSERT_ERROR_IF(portBall.write(cmd,reply),"Unable to talk to world");
        RTF_ASSERT_ERROR_IF(reply.size()>=3,"Invalid reply from world");
        Vector initialBallPos(3);
        initialBallPos[0]=reply.get(0).asDouble();
        initialBallPos[1]=reply.get(1).asDouble();
        initialBallPos[2]=reply.get(2).asDouble();
        RTF_TEST_REPORT(Asserter::format("initial ball position = (%s) [m]",
                                         initialBallPos.toString(3,3).c_str()));
        cmd.clear(); reply.clear();

        cmd.addString("look_down");
        RTF_ASSERT_ERROR_IF(portMIR.write(cmd,reply),"Unable to talk to MIR");
        RTF_ASSERT_ERROR_IF(reply.get(0).asString()=="ack","Unable to look_down");
        cmd.clear(); reply.clear();

        cmd.addString("make_it_roll");
        RTF_ASSERT_ERROR_IF(portMIR.write(cmd,reply),"Unable to talk to MIR");
        RTF_ASSERT_ERROR_IF(reply.get(0).asString()=="ack","Unable to make_it_roll");
        cmd.clear(); reply.clear();

        RTF_TEST_REPORT("Retrieving final ball position");
        cmd.addString("world"); cmd.addString("get"); cmd.addString("ball");
        RTF_ASSERT_ERROR_IF(portBall.write(cmd,reply),"Unable to talk to world");
        RTF_ASSERT_ERROR_IF(reply.size()>=3,"Invalid reply from world");
        Vector finalBallPos(3);
        finalBallPos[0]=reply.get(0).asDouble();
        finalBallPos[1]=reply.get(1).asDouble();
        finalBallPos[2]=reply.get(2).asDouble();
        RTF_TEST_REPORT(Asserter::format("final ball position = (%s) [m]",
                                         finalBallPos.toString(3,3).c_str()));
        cmd.clear(); reply.clear();

        double dist=norm(finalBallPos-initialBallPos);
        RTF_TEST_CHECK(dist>0.01,Asserter::format("Ball has rolled for %g [m]!",dist));
    }
};

PREPARE_PLUGIN(TestAssignmentMakeItRoll)
