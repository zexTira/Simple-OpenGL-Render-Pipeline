#include "Rasterizer.h"

// Initialize static attributes
std::vector<std::vector<float>> Rasterizer::depth_buffer(GlobalSettings::window_width, std::vector<float>(GlobalSettings::window_height, std::numeric_limits<float>::infinity()));
Shader* Rasterizer::shader = new Shader();

/// <summary>
/// Reset all values in depth buffer to infinity
/// </summary>
/// <param name="depth_buffer:"> Reference of depth buffer defined in class Rasterizer </param>
void Rasterizer::ResetDepthBuffer(std::vector<std::vector<float>>& depth_buffer)
{
	for (int i = 0; i < depth_buffer.size(); ++i)
	{
		for (int j = 0; j < depth_buffer[i].size(); ++j)
		{
			depth_buffer[i][j] = std::numeric_limits<float>::infinity();
		}
	}

	return;
}

/// <summary>
/// Judge if a point is inside the triangle in a 2D plane 
/// </summary>
/// <param name="vertex1_coor:"> A 3D vector reprenseting the coordinates of a vertex of triange </param>
/// <param name="vertex2_coor:"> A 3D vector reprenseting the coordinates of a vertex of triange </param>
/// <param name="vertex3_coor:"> A 3D vector reprenseting the coordinates of a vertex of triange </param>
/// <param name="current_coor:"> A 3D vector reprenseting the coordinates of a point used for judging </param>
/// <returns> A bool value indicates current point is in the triangle if it's true or not if it's false  </returns>
bool Rasterizer::IsInsideTriangle(std::vector<float> vertex1_coor, std::vector<float> vertex2_coor, std::vector<float> vertex3_coor, std::vector<float> current_coor)
{
	std::vector<float> v1 = { current_coor[0] - vertex1_coor[0], current_coor[1] - vertex1_coor[1],0 };
	std::vector<float> v2 = { current_coor[0] - vertex2_coor[0], current_coor[1] - vertex2_coor[1],0 };
	std::vector<float> v3 = { current_coor[0] - vertex3_coor[0], current_coor[1] - vertex3_coor[1],0 };
	std::vector<float> e1 = { vertex2_coor[0] - vertex1_coor[0],vertex2_coor[1] - vertex1_coor[1],0 };
	std::vector<float> e2 = { vertex3_coor[0] - vertex2_coor[0],vertex3_coor[1] - vertex2_coor[1],0 };
	std::vector<float> e3 = { vertex1_coor[0] - vertex3_coor[0],vertex1_coor[1] - vertex3_coor[1],0 };

	// Compute z direction of the result of 3 pairs of cross products
	if (MathUtility::VecCrossProduct(v1, e1)[2] > 0 && MathUtility::VecCrossProduct(v2, e2)[2] > 0 && MathUtility::VecCrossProduct(v3, e3)[2] > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/// <summary>
/// Rasterizer for a triangle fragment
/// </summary>
/// <param name="triangle:"> A 3x3 vector represents 3 vertices of a triangle and their coordinates </param>
/// <param name="vnormal"> A vector that stores 3 vertex normals of current triangle (For normal shader computation) </param>
/// <param name="depth_buffer:"> Reference of depth buffer defined in class Rasterizer </param>
void Rasterizer::Renderer(std::vector<std::vector<float>> triangle, std::vector<std::vector<float>> vnormal, std::vector<std::vector<float>>& depth_buffer)
{
	float col_interval = 1.0 / GlobalSettings::window_width;	// pixelwise distance of screen space
	float row_interval = 1.0 / GlobalSettings::window_height;
	float eye_pos_zval = TransformationController::eye_pos[2];
	
	// Project the triangle onto render screen space
	std::vector<float> screen_coor1 = { triangle[0][0] / fabs(triangle[0][2] - eye_pos_zval),
															triangle[0][1] / fabs(triangle[0][2] - eye_pos_zval),
															eye_pos_zval + 1 };
	std::vector<float> screen_coor2 = { triangle[1][0] / fabs(triangle[1][2] - eye_pos_zval),
															triangle[1][1] / fabs(triangle[1][2] - eye_pos_zval),
															eye_pos_zval + 1 };
	std::vector<float> screen_coor3 = { triangle[2][0] / fabs(triangle[2][2] - eye_pos_zval),
															triangle[2][1] / fabs(triangle[2][2] - eye_pos_zval),
															eye_pos_zval + 1 };

	// Get bounding box of current triangle to reduce computational overhead
	float right = std::max(std::max(screen_coor1[0], screen_coor2[0]), screen_coor3[0]); right = right > 1 ? 1 : right;
	float left = std::min(std::min(screen_coor1[0], screen_coor2[0]), screen_coor3[0]); left = left < -1 ? -1 : left;
	float top = std::max(std::max(screen_coor1[1], screen_coor2[1]), screen_coor3[1]); top = top > 1 ? 1 : top;
	float bottom = std::min(std::min(screen_coor1[1], screen_coor2[1]), screen_coor3[1]); bottom = bottom < -1 ? -1 : bottom;

	for (float i = left; i < right; i += col_interval)
	{
		for (float j = bottom; j < top; j += row_interval)
		{
			// compute float current_depth
			std::vector<float> screen_coor_curr = { i , j, eye_pos_zval + 1 };  // Current pixel position
			if (Rasterizer::IsInsideTriangle(screen_coor1, screen_coor2, screen_coor3, screen_coor_curr) )
			{
				// Compute interpolated depth
				std::vector<float> barycentric_factors = MathUtility::Compute2DBarycentricFactor(triangle[0], triangle[1], triangle[2], screen_coor_curr);
				float current_depth = barycentric_factors[0] * triangle[0][2] + barycentric_factors[1] * triangle[1][2] + barycentric_factors[2] * triangle[2][2];
				if (current_depth < depth_buffer[std::round((i + 1) * GlobalSettings::window_width / 2.0)][std::round((j + 1) * GlobalSettings::window_height / 2.0)])
				{
					// Render the pixel if it is inside the triangle and depth is smaller than current depth value that at corresponding position in depth buffer
					// std::vector<float> color = Rasterizer::shader->TestPureColorShader({1.0,1.0,0.0});	
					std::vector<float> color = Rasterizer::shader->NormalShader(barycentric_factors, vnormal);	// Get the assigned color for current pixel with normal shader
					glColor3f(color[0], color[1], color[2]);
					glVertex3f(screen_coor_curr[0], screen_coor_curr[1], eye_pos_zval + 1);		// Draw the colored pixel on screen space
					depth_buffer[std::round((i + 1) * GlobalSettings::window_width / 2.0)][std::round((j + 1) * GlobalSettings::window_height / 2.0)] = current_depth;	// Update depth buffer
				}
			}
		}
	}

	return;
}

