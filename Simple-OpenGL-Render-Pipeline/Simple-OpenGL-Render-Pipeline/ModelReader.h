// The header file defines the behaviors for reading .obj models
#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class ObjReader
{
	public:
		// Attributes
		std::vector<std::vector<float>> vertices;	// Stores vertex coordinates
		std::vector<std::vector<float>> vertex_normals;	// Stores vertex normals
		std::vector<std::vector<int>> face_vertice_info; // Stores 3 vertex indices of each face
		std::vector<std::vector<int>> face_normal_info; // Stores 3 vertex normal indices of each face

		// Functions 
		ObjReader(std::string file_path);
};