/**
 * Performs dispatch for RC switch messages.
 *
 * (C) 2015 Andrew Barry <abarry@csail.mit.edu>
 */

#ifndef RC_SWITCH_DISPATH_HPP
#define RC_SWITCH_DISPATH_HPP


#include <iostream>
#include <lcm/lcm-cpp.hpp>
#include "../../LCM/lcmt/tvlqr_controller_action.hpp"
#include "../../LCM/lcmt/rc_switch_action.hpp"
#include "../../LCM/lcmt/stereo.hpp"

#include "../../utils/utils/RealtimeUtils.hpp"
#include <bot_param/param_client.h>
#include <vector>

#define MAX_PARAM_SIZE 100

class RcSwitchDispatch {

    public:
        RcSwitchDispatch(lcm::LCM *lcm, std::string rc_trajectory_commands_channel, std::string stereo_channel);

        void ProcessRcMsg(const lcm::ReceiveBuffer *rbus, const std::string &chan, const lcmt::rc_switch_action *msg);

    private:
        void SendTrajectoryRequest(int traj_num) const;
        void SendStereoMsg(int stereo_msg_num) const;
        void GlobalToCameraFrame(double point_in[], double point_out[]) const;
        void SendStereoManyPoints(std::vector<float> x_in, std::vector<float> y_in, std::vector<float> z_in) const;

        std::string stereo_channel_, rc_trajectory_commands_channel_;

        int stable_traj_num_, climb_traj_num_;
        int num_trajs_, num_stereo_actions_;

        int trajectory_mapping_[MAX_PARAM_SIZE];
        int stereo_mapping_[MAX_PARAM_SIZE];

        lcm::LCM *lcm_;

        BotParam *param_;
        BotFrames *bot_frames_;

        std::vector<float> x_points0_ = {5};
        std::vector<float> y_points0_ = {0};
        std::vector<float> z_points0_ = {0};


};

#endif
