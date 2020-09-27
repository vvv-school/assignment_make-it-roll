// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-
//
// A tutorial on how to use the Gaze Interface.
//
// Author: Ugo Pattacini - <ugo.pattacini@iit.it>

#include <string>
#include <cmath>

#include <gazebo/common/Plugin.hh>
#include <gazebo/physics/World.hh>
#include <gazebo/physics/Model.hh>
#include <ignition/math/Pose3.hh>

#include <yarp/os/ConnectionReader.h>
#include <yarp/os/ConnectionWriter.h>
#include <yarp/os/PortReader.h>
#include <yarp/os/Port.h>
#include <yarp/os/Bottle.h>
#include <yarp/os/Vocab.h>

namespace gazebo {

/******************************************************************************/
class WorldHandler : public gazebo::WorldPlugin
{
    gazebo::physics::WorldPtr world;
    gazebo::physics::ModelPtr ball;
    gazebo::event::ConnectionPtr renderer_connection;

    yarp::os::Port rpcPort;
    /**************************************************************************/
    class DataProcessor : public yarp::os::PortReader {
        WorldHandler* hdl;
        /**********************************************************************/
        bool read(yarp::os::ConnectionReader& connection) override {
            yarp::os::Bottle cmd;
            cmd.read(connection);
            auto* returnToSender = connection.getWriter();
            if (returnToSender != nullptr) {
                yarp::os::Bottle rep;
                if (cmd.get(0).asVocab() == yarp::os::Vocab::encode("get")) {
                    const auto& p = hdl->ball->WorldPose().Pos();
                    rep.addVocab(yarp::os::Vocab::encode("ack"));
                    rep.addDouble(p.X());
                    rep.addDouble(p.Y());
                    rep.addDouble(p.Z());
                } else if (cmd.get(0).asVocab() == yarp::os::Vocab::encode("set")) {
                    if (cmd.size() >= 4) {
                        const auto x = cmd.get(1).asDouble();
                        const auto y = cmd.get(2).asDouble();
                        const auto z = cmd.get(3).asDouble();
                        const auto& q = hdl->ball->WorldPose().Rot();
                        ignition::math::Pose3d pose(x, y, z, q.W(), q.X(), q.Y(), q.Z());
                        hdl->ball->SetWorldPose(pose);
                        rep.addVocab(yarp::os::Vocab::encode("ack"));
                    } else {
                        rep.addVocab(yarp::os::Vocab::encode("nack"));
                    }
                } else {
                    rep.addVocab(yarp::os::Vocab::encode("nack"));
                }
                rep.write(*returnToSender);
            }
            return true;
        }
    public:
        /**********************************************************************/
        DataProcessor(WorldHandler* hdl_) : hdl(hdl_) { } 
    } processor;
    friend class DataProcessor;

public:
    /**************************************************************************/
    WorldHandler() : processor(this) { }
    
    /**************************************************************************/
    void Load(gazebo::physics::WorldPtr world, sdf::ElementPtr) {
        std::string ball_name = "assignment_make-it-roll-ball";

        this->world = world;
        ball = world->ModelByName(ball_name);

        rpcPort.setReader(processor);
        rpcPort.open("/" + ball_name + "/rpc");
    }

    /**************************************************************************/
    virtual ~WorldHandler() {
        if (rpcPort.isOpen()) {
            rpcPort.close();
        }
    }
};

}

GZ_REGISTER_WORLD_PLUGIN(gazebo::WorldHandler)
