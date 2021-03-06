#ifndef ORTF_H_
#define ORTF_H_

#include <map>
#include <set>
#include <openrave/openrave.h>
#include <ros/ros.h>
#include <ros/spinner.h>
#include <tf/transform_listener.h>

class OrTf : public OpenRAVE::SensorBase {
public:
    OrTf(OpenRAVE::EnvironmentBasePtr env, std::string const &openrave_tf_frame);
    virtual ~OrTf(void);

    virtual void Reset(void);
    virtual void Destroy(void);
    virtual bool SimulationStep(OpenRAVE::dReal fTimeElapsed);

    virtual bool Init(const std::string& cmd);
    virtual bool Connect(std::ostream &output, std::istream &input);
    virtual void Reset(int options);
    virtual int Configure(OpenRAVE::SensorBase::ConfigureCommand command, bool blocking=false);
    virtual OpenRAVE::SensorBase::SensorGeometryConstPtr GetSensorGeometry(OpenRAVE::SensorBase::SensorType type=OpenRAVE::SensorBase::ST_Invalid);
    virtual OpenRAVE::SensorBase::SensorDataPtr CreateSensorData(OpenRAVE::SensorBase::SensorType type=OpenRAVE::SensorBase::ST_Invalid);
    virtual bool GetSensorData(OpenRAVE::SensorBase::SensorDataPtr psensordata);
    virtual bool Supports(OpenRAVE::SensorBase::SensorType type);
    virtual OpenRAVE::Transform GetTransform();
    virtual void SetTransform(OpenRAVE::Transform const &transform);

    bool RegisterBody(std::ostream& sout, std::istream& sinput);
    bool RegisterRobotHand(std::ostream& sout, std::istream& sinput);

    bool UnregisterBody(std::ostream& sout, std::istream& sinput);
    bool Pause(std::ostream& sout, std::istream& sinput);
    bool Resume(std::ostream& sout, std::istream& sinput);
    bool Clear(std::ostream& sout, std::istream& sinput);

    bool UnregisterBodyHelper(std::string const &body_name);

    OpenRAVE::Transform GetPlanarPose(const OpenRAVE::Transform & pose, const double fixed_z_translation);

private:
    std::string openrave_tf_frame_;

    ros::NodeHandle nh_;
    tf::TransformListener tf_;

    boost::mutex mutex_;
    std::map<std::string, std::string> bodies_;
    std::map<std::string, OpenRAVE::Transform> offsets_;
    std::map<std::string, bool> planar_;
    std::map<std::string, double> fixed_z_translation_;
    std::map<std::string, std::string> hands_;
    bool paused_;

    bool IsBodyRegistered(std::string const &body_name);
    bool IsHandRegistered(std::string const &body_name);
    OpenRAVE::Transform GetOrTransform(tf::StampedTransform const &transform);


};

#endif // ORTF_H_
