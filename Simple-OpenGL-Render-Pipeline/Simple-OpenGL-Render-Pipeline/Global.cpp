#include "Global.h"

// Static attribute setters
const int GlobalSettings::window_width = 600;	
const int GlobalSettings::window_height = 600;	
const unsigned int GlobalSettings::update_time_interval = 1000 / 60; 
const char* const GlobalSettings::window_title = "A Toy Render Pipeline";


/// <summary>
/// Computes cross product result of two 3D vectors 
/// </summary>
/// <param name="v1:"> A 3D vector </param>
/// <param name="v2:"> Another 3D vector </param>
/// <returns> A 3D vector after cross product </returns>
std::vector<float> MathUtility::VecCrossProduct(std::vector<float> v1, std::vector<float> v2)
{
	std::vector<float> result = { v1[1] * v2[2] - v2[1] * v1[2] , v1[2] * v2[0] - v2[2] * v1[0] , v1[0] * v2[1] - v1[1] * v2[0] };
	return result;
}

/// <summary>
/// Computes 2D barycentric factor for a point which lies in a triangle
/// </summary>
/// <param name=" vertex1_coor: "> Coordinates of a triangle vertex</param>
/// <param name=" vertex1_coor: "> Coordinates of a triangle vertex </param>
/// <param name=" vertex1_coor: "> Coordinates of a triangle vertex </param>
/// <param name=" current_coor: "> Coordinates of the testing point </param>
/// <returns> A vector including barycentric factor in the sequence of ¦Á, ¦Â and ¦Ã </returns>
std::vector<float> MathUtility::Compute2DBarycentricFactor(std::vector<float> vertex1_coor, std::vector<float> vertex2_coor, std::vector<float> vertex3_coor, std::vector<float> current_coor)
{
	float alpha = (current_coor[0] * (vertex2_coor[1] - vertex3_coor[1]) + (vertex3_coor[0] - vertex2_coor[0]) * current_coor[1] + vertex2_coor[0] * vertex3_coor[1] - vertex3_coor[0] * vertex2_coor[1]) / (vertex1_coor[0] * (vertex2_coor[1] - vertex3_coor[1]) + (vertex3_coor[0] - vertex2_coor[0]) * vertex1_coor[1] + vertex2_coor[0] * vertex3_coor[1] - vertex3_coor[0] * vertex2_coor[1]);
	float beta = (current_coor[0] * (vertex3_coor[1] - vertex1_coor[1]) + (vertex1_coor[0] - vertex3_coor[0]) * current_coor[1] + vertex3_coor[0] * vertex1_coor[1] - vertex1_coor[0] * vertex3_coor[1]) / (vertex2_coor[0] * (vertex3_coor[1] - vertex1_coor[1]) + (vertex1_coor[0] - vertex3_coor[0]) * vertex2_coor[1] + vertex3_coor[0] * vertex1_coor[1] - vertex1_coor[0] * vertex3_coor[1]);
	float gamma = 1 - alpha - beta;
	return { alpha, beta, gamma };
}
