/*
 * Copyright (C) 2016 iCub Facility - Istituto Italiano di Tecnologia
 * Author: Ugo Pattacini <ugo.pattacini@iit.it>
 * CopyPolicy: Released under the terms of the GNU GPL v3.0.
*/

#include <string>

#include <rtf/yarp/YarpTestCase.h>
#include <rtf/dll/Plugin.h>

#include <yarp/os/all.h>
#include <yarp/dev/all.h>
#include <yarp/sig/all.h>
#include <yarp/math/Math.h>

using namespace std;
using namespace RTF;
using namespace yarp::os;
using namespace yarp::dev;
using namespace yarp::sig;
using namespace yarp::math;

/**********************************************************************/
class TestAssignmentMakeItRoll : public YarpTestCase,
                                 public CartesianEvent
{
    PolyDriver drvCartArm;
    ICartesianControl *iarm;

    RpcClient portBall;
    RpcClient portMIR;
    
    Vector ballPosRobFrame;
    bool hit;

public:
    /******************************************************************/
    TestAssignmentMakeItRoll() :
        YarpTestCase("TestAssignmentMakeItRoll"),
        hit(false)
    {        
        cartesianEventParameters.type="motion-done";
    }

    /******************************************************************/
    virtual ~TestAssignmentMakeItRoll()
    {
    }

    /******************************************************************/
    virtual void cartesianEventCallback()
    {
        Vector x,o;
        iarm->getPose(x,o);
        
        double dist=norm(ballPosRobFrame-x);
        if (dist<0.1)
            hit=true;
            
        RTF_TEST_REPORT(Asserter::format("We're at %g [m] from the ball ==> %s",
                                         dist,hit?"we hit it!":"we didn't hit it yet"));
    }
    
    /******************************************************************/
    virtual bool setup(yarp::os::Property& property)
    {
        string robot=property.check("robot",Value("icubSim")).asString();
        double rpcTmo=property.check("rpc-timeout",Value(60.0)).asDouble();
       
        Property option;
        option.put("device","cartesiancontrollerclient");
        option.put("remote","/"+robot+"/"+"cartesianController/right_arm");
        option.put("local","/"+getName()+"/cartesian");

        RTF_TEST_REPORT("Opening Clients");        
        RTF_ASSERT_ERROR_IF(drvCartArm.open(option),"Unable to open Clients!");
        
        drvCartArm.view(iarm);
        iarm->registerEvent(*this);
        
        string portBallName("/"+getName()+"/ball:rpc");
        string portMIRName("/"+getName()+"/mir:rpc");

        portBall.open(portBallName);
        portMIR.open(portMIRName);
        
        RTF_TEST_REPORT(Asserter::format("Set rpc timeout = %g [s]",rpcTmo));
        portBall.asPort().setTimeout(rpcTmo);
        portMIR.asPort().setTimeout(rpcTmo);
        
        RTF_TEST_REPORT("Connecting Ports");
        RTF_ASSERT_ERROR_IF(Network::connect(portBallName,"/icubSim/world"),
                            "Unable to connect to /icubSim/world");        
        RTF_ASSERT_ERROR_IF(Network::connect(portMIRName,"/service"),
                            "Unable to connect to /service");

        return true;
    }

    /******************************************************************/
    virtual void tearDown()
    {
        RTF_TEST_REPORT("Closing Ports");
        portBall.close();
        portMIR.close();
        
        RTF_TEST_REPORT("Closing Clients");
        RTF_ASSERT_ERROR_IF(drvCartArm.close(),"Unable to close Clients!");        
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
        
        // compute ball position in robot's root reference frame
        Matrix T=zeros(4,4);
        T(0,1)=-1.0;
        T(1,2)=1.0;  T(1,3)=0.5976;
        T(2,0)=-1.0; T(2,3)=-0.026;
        T(3,3)=1.0;
        Vector initBallPosHomo=initialBallPos;
        initBallPosHomo.push_back(1.0);
        ballPosRobFrame=SE3inv(T)*initBallPosHomo;
        ballPosRobFrame.pop_back();

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
        RTF_TEST_CHECK(hit,"We hit the ball!");
        RTF_TEST_CHECK(dist>0.01,Asserter::format("Ball has rolled for at least %g [m]!",dist));
    }
};

PREPARE_PLUGIN(TestAssignmentMakeItRoll)
