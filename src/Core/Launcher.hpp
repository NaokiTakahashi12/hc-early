
/**
  *
  * @file Launcher.hpp
  * @author Naoki Takahashi
  *
  **/

#pragma once

#include <RobotStatus/Information.hpp>
#include <IO/DeviceManager.hpp>
#include <FootStepPlanner/HumanoidFootprintManager.hpp>
#include <Kinematics/Launcher.hpp>

#include <Tools/Math/Matrix.hpp>

namespace Core {
	class Launcher {
		public :
			Launcher(int argc, char **argv);
			~Launcher();

		private :
			RobotStatus::InformationPtr robo_info;

			Tools::Math::Vector3<double> begin_point,
										 goal_point;

			std::unique_ptr<FootStepPlanner::HumanoidFootprintManager<float>> footstep_planner;
			std::unique_ptr<Kinematics::Launcher<double>> kinematics_launcher;

			void launch_up_humanoid_footprint_manager();
			void launch_up_io();
			void launch_up_kinematics();
	};
}

