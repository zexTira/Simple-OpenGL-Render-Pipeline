#include "Shader.h"

/// <summary>
/// A test shader that renders the same color for every pixel
/// </summary>
/// <param name="assigned_color"> A 3D vector that defines an RGB color </param>
/// <returns> The assigned color </returns>
std::vector<float> Shader::TestPureColorShader(std::vector<float> assigned_color)
{
	return this->shaded_color = assigned_color;
}

/// <summary>
/// A normal shader that renders the color based on the normal vector of current pixel
/// </summary>
/// <param name="barycentric_factors"> Computed barycentric factor array for interpolaton</param>
/// /// <param name="vnormal"> A vector that stores 3 vertex normals of current triangle </param>
/// <returns> The assigned color </returns>
std::vector<float> Shader::NormalShader(std::vector<float> barycentric_factors, std::vector<std::vector<float>> vnormal)
{
	// compute normal for current coord based on barycentric
	std::vector<float> normal = { barycentric_factors[0] * vnormal[0][0] + barycentric_factors[1] * vnormal[1][0] + barycentric_factors[2] * vnormal[2][0],
												barycentric_factors[0] * vnormal[0][1] + barycentric_factors[1] * vnormal[1][1] + barycentric_factors[2] * vnormal[2][1], 
												barycentric_factors[0] * vnormal[0][2] + barycentric_factors[1] * vnormal[1][2] + barycentric_factors[2] * vnormal[2][2]};
	
	// Normalize the normal vector
	float magn = sqrt(normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2]);
	normal[0] /= magn;
	normal[1] /= magn;
	normal[2] /= magn;

	// Get color value by color = (normal + 1) / 2
	this->shaded_color[0] = (normal[0] + 1.0) / 2.0;
	this->shaded_color[1] = (normal[1] + 1.0) / 2.0;
	this->shaded_color[2] = (normal[2] + 1.0) / 2.0;

	return this->shaded_color;
}
