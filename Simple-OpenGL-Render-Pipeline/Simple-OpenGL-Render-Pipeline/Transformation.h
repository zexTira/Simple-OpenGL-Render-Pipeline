// The header file defines the behaviors that manipulate the matrices of MVP transformation 
#pragma once

#include <GL/glut.h>
#include <vector>

#include "Global.h"

class TransformationController
{
	public:
		// Parameters for model transformation
		static const int rotation_angle;

		// Parameters for view transformation
		static const std::vector<float> eye_pos;
		static const std::vector<float> center_pos;
		static const std::vector<float> up_dir;

		// Parameters for projection transformation
		static const float fovy;
		static const float aspect;
		static const float near_distance;
		static const float far_distance;

		// Functions
		static int UpdateRotationAngle(int angle);
		static void SetModelMatrix(int angle);
		static void SetViewMatrix();
		static void SetProjectionMatrix();

		TransformationController() = delete;	// Static class: Disable instantialization
};
