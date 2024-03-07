// The header file that defines some shaders
#pragma once

#include <vector>

#include "Global.h"

class Shader
{
	private:
		// Attributes
		std::vector<float> shaded_color;	// Color vector for each pixel computed by shader

	public:
		// Functions
		Shader() { 
			this->shaded_color = { 0.0,0.0,0.0 };		// Initialized to black (default color)
		}

		std::vector<float> TestPureColorShader(std::vector<float> assigned_color);
		std::vector<float> NormalShader(std::vector<float> barycentric_factors, std::vector<std::vector<float>> vnormal);
};