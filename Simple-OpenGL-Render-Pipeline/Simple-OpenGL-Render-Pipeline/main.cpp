#include <GL/glut.h>
#include <iostream>
#include <string>

#include "Global.h"
#include "ModelReader.h"
#include "Transformation.h"
#include "Rasterizer.h"

int angle = TransformationController::rotation_angle;	// Initial rotation angle

// Read model file
std::string file_name = "Cow.obj";
ObjReader * obj = new ObjReader("Models/" + file_name);

/// <summary>
/// Initialize trnasformation and misc settings for OpenGL panal
/// </summary>
void GLInit()
{
	glClearColor(0.5, 0.5, 0.5, 0);	// Set background color

	TransformationController::SetViewMatrix();	// Set view transformation
	TransformationController::SetProjectionMatrix();	// Set projection transformation
}

/// <summary>
/// Customized OpenGL display function
/// </summary>
void GLDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Set clear mode
	glPointSize(2);	// Set pixel size
	
	glPushMatrix();
	TransformationController::SetModelMatrix(angle);	// Set model transformation

	glBegin(GL_POINTS);
	//	Render every face
	auto face_num = obj->face_vertice_info.size();
	for (decltype(face_num) i = 0; i < face_num; ++i)
	{
		Rasterizer::Renderer({ obj->vertices[obj->face_vertice_info[i][0] - 1],
											obj->vertices[obj->face_vertice_info[i][1] - 1],
											obj->vertices[obj->face_vertice_info[i][2] - 1] },
										   { obj->vertices[obj->face_normal_info[i][0] - 1],
											obj->vertices[obj->face_normal_info[i][1] - 1],
											obj->vertices[obj->face_normal_info[i][2] - 1] }, Rasterizer::depth_buffer);
	}
	glEnd();

	glPopMatrix();

	Rasterizer::ResetDepthBuffer(Rasterizer::depth_buffer);	// Reset depth buffer for next frame
	glutSwapBuffers();
}

/// <summary>
/// Customized OpenGL update function 
/// <param name="value: "> Some value user wants to pass during each update  </param> 
/// </summary>
void Update(int value)
{
	// update rotation in each frame (current maximum fps: 60)
	angle = TransformationController::UpdateRotationAngle(angle);
	glutPostRedisplay();
	glutTimerFunc(GlobalSettings::update_time_interval, Update, 0);
}

/// <summary>
/// Main function
/// </summary>
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);	// Set display mode

	// Set window parameters
	glutInitWindowSize(GlobalSettings::window_width, GlobalSettings::window_height);
	glutInitWindowPosition(160, 90);
	glutCreateWindow(GlobalSettings::window_title);

	// Initialize, display and update
	GLInit();
	glutDisplayFunc(GLDisplay);
	glutTimerFunc(GlobalSettings::update_time_interval, Update, 0);
	glutMainLoop();

	return 0;
}
