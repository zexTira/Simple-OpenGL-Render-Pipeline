#include "Transformation.h"

// Attribute initializing
const int TransformationController::rotation_angle = 1;	// Initial rotation angle

// if reading Cow.obj / Rock.obj set eye_pos.z to -2.0 / -4.0 
const std::vector<float> TransformationController::eye_pos = { 0.0, 0.0, -2.0 }; // Clip screen plane: z = -4.0 + 1.0 = -3.0 (an OpenGL feature) 
const std::vector<float> TransformationController::center_pos = { 0.0, 0.0, 0.0 };
const std::vector<float> TransformationController::up_dir = { 0.0, 1.0, 0.0 };

const float TransformationController::fovy = 90.0; // An angle makes compution easier, where tan(90/2) = 1
const float TransformationController::aspect = (float) GlobalSettings::window_width / GlobalSettings::window_height;	// Dynamic aspect ration that revent stretching
const float TransformationController::near_distance = 0.1;
const float TransformationController::far_distance = 200.0;

/// <summary>
/// Defines rotation angle for each frame
/// </summary>
/// <param name="angle:"> Angle for computation </param>
/// <returns> Computed angle for rotation </returns>
int TransformationController::UpdateRotationAngle(int angle)
{
	angle += 5;
	angle %= 360;
	return angle;
}

/// <summary>
/// Sets model transformation matrix with OpenGL
/// </summary>
/// <param name="angle:"> "Rotation Angle" </param>
void TransformationController::SetModelMatrix(int angle)
{
	glMatrixMode(GL_MODELVIEW);
	glRotatef(angle, 0.0, 0.0, 1.0);

	return;
}

/// <summary>
/// Sets view transformation matrix with OpenGL
/// </summary>
void TransformationController::SetViewMatrix()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye_pos[0], eye_pos[1], eye_pos[2],
					center_pos[0], center_pos[1], center_pos[2],
					up_dir[0], up_dir[1], up_dir[2]);

	return;
}

/// <summary>
/// Sets projection transformation matrix with OpenGL
/// </summary>
void TransformationController::SetProjectionMatrix()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fovy, aspect, near_distance, far_distance);

	return;
}