
/**
  *
  * @file Launcher.cpp
  * @author Naoki Takahashi
  *
  **/

#include "Launcher.hpp"

#include <iostream>

namespace Core {
	Launcher::Launcher(int argc, char **argv) {
		robo_info = std::make_shared<RobotStatus::Information>(argc, argv);

		begin_point << 1e-6, 1e-6, 1e-6;
		goal_point << 1, 1e-6, 1e-6;

		robo_info->create_footprints_data_space();

		launch_up_kinematics();
		launch_up_humanoid_footprint_manager();
	}

	Launcher::~Launcher() {
	}

	void Launcher::launch_up_humanoid_footprint_manager() {
		footstep_planner = FootStepPlanner::HumanoidFootprintManager<float>::make_ptr();
		footstep_planner = std::make_unique<FootStepPlanner::HumanoidFootprintManager<float>>();

		footstep_planner->choice_footprint_planner("../../FootStepPlanner/build/footstep_planner.conf.json");

		footstep_planner->set_begin(begin_point.x(), begin_point.y(), begin_point.z(), 0, 0, 0);
		footstep_planner->set_goal(goal_point.x(), goal_point.y(), goal_point.z(), 0, 0, 0);

		footstep_planner->make_full_footprint();

		Tools::Math::MatrixX<float> left_footprint, right_footprint;
		{
			const auto footprint_list = footstep_planner->get_footprint_list();

			std::cout << std::endl;
			std::cout << "Footprint size " << footprint_list.size() << std::endl;;

			const auto footprint_size = 1 + footprint_list.size() / 2;

			left_footprint = left_footprint.Zero(3, footprint_size);
			right_footprint = right_footprint.Zero(3, footprint_size);
			Tools::Math::Vector3<float> left_cache, right_cache;

			unsigned int left_i = 0, right_i = 0;
			for(const auto &fp : footprint_list) {
				if(left_cache != fp.left) {
					left_footprint.block<3, 1>(0, left_i) = fp.left;
					left_cache = fp.left;
					left_i ++;
				}
				if(right_cache != fp.right) {
					right_footprint.block<3, 1>(0, right_i) = fp.right;
					right_cache = fp.right;
					right_i ++;
				}
			}
		}
		
		robo_info->left_footprint->set(left_footprint);
		robo_info->right_footprint->set(right_footprint);

		std::cout << std::endl;
		std::cout << left_footprint << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << right_footprint << std::endl;
		std::cout << std::endl;
	}

	void Launcher::launch_up_kinematics() {
		kinematics_launcher = std::make_unique<Kinematics::Launcher<double>>("../../Kinematics/build/", "kinematics.conf.json");
		/*
		kinematics_launcher->initialize();

		(*kinematics_launcher)();
		*/
		std::this_thread::sleep_for(std::chrono::milliseconds(10));

		//auto control_point_map = kinematics_launcher->get_control_point_map();
	}
}

