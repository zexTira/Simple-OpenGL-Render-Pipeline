// The header file defines the variables of some global settings
#pragma once

#include <vector>

class GlobalSettings
{
	public:
		static const int window_width;		// Render window width
		static const int window_height;	// Render window height
		static const unsigned int update_time_interval;	// Maximum fixed time interval of updating each frame
		static const char* const window_title;		// Title for render window

		GlobalSettings() = delete;	// Static class: disable instantialization
};

class MathUtility
{
	public:
		// Math functions
		static std::vector<float> VecCrossProduct(std::vector<float> v1, std::vector<float> v2);
		static std::vector<float> Compute2DBarycentricFactor(std::vector<float> vertex1_coor, std::vector<float> vertex2_coor, std::vector<float> vertex3_coor, std::vector<float> current_coor);
};
