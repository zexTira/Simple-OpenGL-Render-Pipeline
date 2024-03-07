// The header file defines the behaviors of rasterization
#pragma once

#include <GL/glut.h>
#include <iostream>
#include <vector>

#include "Global.h"
#include "Transformation.h"
#include "Shader.h"

class Rasterizer 
{
	public:
		//Attributes
		static std::vector<std::vector<float>> depth_buffer; // Defines depth buffer
		static Shader* shader;	// Defines current shader

		// Functions
		static void ResetDepthBuffer(std::vector<std::vector<float>>& depth_buffer);
		static bool IsInsideTriangle(std::vector<float> vertex1_coor, std::vector<float> vertex2_coor, std::vector<float> vertex3_coor, std::vector<float> current_coor);
		static void Renderer(std::vector<std::vector<float>> vertex_coor, std::vector<std::vector<float>> vnormal, std::vector<std::vector<float>>& depth_buffer);
		
		Rasterizer() = delete;	// Static class: Disable instantialization
};
