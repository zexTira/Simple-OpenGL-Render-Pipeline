#include "ModelReader.h"

/// <summary>
/// Assign an .obj file to read (should be put in Models folder) and get related data like normals and vertex coordinates
/// </summary>
/// <param name="file path:"> File path string </param>
ObjReader::ObjReader(std::string file_path)
{
    std::ifstream file(file_path);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        // Read vertex coordinates and write it to the vertex attribute of current ObjReader object
        if (line.substr(0, 2) == "v ")
        {
            std::stringstream ss(line.substr(2));
            std::vector<float> vertex;
            float coordinate;
            while (ss >> coordinate) {
                vertex.push_back(coordinate);
            }
            this->vertices.push_back(vertex);
        }

        // Read vertex normals and write it to the vertex_normal attribute of current ObjReader object
        if (line.substr(0, 3) == "vn ")
        {
            std::stringstream ss(line.substr(3));
            std::vector<float> vertex_normal;
            float coordinate;
            while (ss >> coordinate) {
                vertex_normal.push_back(coordinate);
            }
            this->vertex_normals.push_back(vertex_normal);
        }

        // Read vertex and normal indices of each face and write it to the vector face_vertice_info and face_normal_info of current ObjReader object

        if (line.substr(0, 2) == "f ")
        {
            std::stringstream ss(line.substr(2));
            std::vector<int> vertex_index;
            std::vector<int> vertex_normal_index;

            int idx;
            ss >> idx;
            vertex_index.push_back(idx);
            ss.ignore(256, '/');
            ss.ignore(256, '/');
            ss >> idx;
            vertex_normal_index.push_back(idx);

            ss >> idx;
            vertex_index.push_back(idx);
            ss.ignore(256, '/');
            ss.ignore(256, '/');
            ss >> idx;
            vertex_normal_index.push_back(idx);

            ss >> idx;
            vertex_index.push_back(idx);
            ss.ignore(256, '/');
            ss.ignore(256, '/');
            ss >> idx;
            vertex_normal_index.push_back(idx);

            this->face_vertice_info.push_back(vertex_index);
            this->face_normal_info.push_back(vertex_normal_index);
        }
    }

    file.close();
}
