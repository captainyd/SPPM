#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "../objects/quad.h"
#include "../objects/sphere.h"
#include "../render/renderer.h"
#include "../objects/triangle.h"
#include "../objects/mesh.h"
using namespace Orchid;
int main(int argc, char *argv[])
{
	time_t start, stop;
	time(&start);               // Start execution timer
	int samples = 1000;            // Default samples per pixel
	if (argc == 2) samples = atoi(argv[1]);
	Camera camera = Camera
	(
		Vector3d(278.0f, 273.0f, -800.0f),
		Vector3d(278.0f, 273.0f, 0.0f),
		Vector3d(0, 1, 0),
		300, 300,
		0.1,
		40
	);     // Create camera

	Scene scene = Scene();
	scene.add
	(
		dynamic_cast<Object*>
		(
			new Quad
			(
	{ 552.8f, 0.0f, 0.0f },
	{ 0.0f, 0.0f,   0.0f },
	{ 0.0f, 0.0f, 559.2f },
	{ 549.6f, 0.0f, 559.2f },
				Material(DIFF, { 1.0f, 1.0f, 1.0f })
			)
			)
	);
	scene.add
	(
		dynamic_cast<Object*>
		(
			new Quad
			(
	{ 213.0f, 548.6f, 227.0f }, { 343.0f, 548.6f, 227.0f }, { 343.0f, 548.6f, 332.0f }, { 213.0f, 548.6f, 332.0f },
				Material(EMIT, { 1.0f, 1.0f, 1.0f }, { 25.0f, 25.0f, 25.0f })
			)
			)
	);
	scene.add
	(
		dynamic_cast<Object*>
		(
			new Quad
			(
	{ 556.0f, 548.8f,   0.0f }, { 556.0f, 548.8f, 559.2f }, { 0.0f, 548.8f, 559.2f }, { 0.0f, 548.8f,   0.0f },
				Material(DIFF, { 1.0f, 1.0f, 1.0f })
			)
			)
	);
	scene.add
	(
		dynamic_cast<Object*>
		(
			new Quad
			(
	{ 549.6f,   0.0f, 559.2f }, { 0.0f,   0.0f, 559.2f }, { 0.0f, 548.8f, 559.2f }, { 556.0f, 548.8f, 559.2f },
				Material(DIFF, { 1.0f, 1.0f, 1.0f })
			)
			)
	);
	scene.add
	(
		dynamic_cast<Object*>
		(
			new Quad(
	{ 0.0f,   0.0f, 559.2f }, { 0.0f,   0.0f,   0.0f }, { 0.0f, 548.8f,   0.0f }, { 0.0f, 548.8f, 559.2f },
				Material(DIFF, { 0.0f, 1.0f, 0.0f })
			)
			)
	);
	scene.add
	(
		dynamic_cast<Object*>
		(
			new Quad
			(
	{ 552.8f,   0.0f,   0.0f }, { 549.6f,   0.0f, 559.2f }, { 556.0f, 548.8f, 559.2f }, { 556.0f, 548.8f,   0.0f },
				Material(DIFF, { 1.0f, 0.0f, 0.0f })
			)
			)
	);
	scene.add(dynamic_cast<Object*>(new Sphere(Vector3d(278.0f, 273.0f, 273.0f),
		90, Material(SPEC, Vector3d(1, 1, 0)))));

	/*scene.add(dynamic_cast<Object*>(new Triangle(Vector3d(278.0f, 173.0f, 273.0f), Vector3d(228.0f, 273.0f, 273.0f), Vector3d(378.0f, 373.0f, 273.0f),
		Material(DIFF, Vector3d(0, 0, 1)))));*/
	scene.add( dynamic_cast<Object*>(new Mesh(Vector3d(), "objFile/dragon2.obj", Material(DIFF, Vector3d(0.9, 0.9, 0.9)))) );

	Renderer renderer = Renderer(&scene, &camera);  // Create renderer with our scene and camera
	renderer.render(samples);                       // Render image to pixel buffer
	renderer.saveImage("render.png");              // Save image

													// Print duration information
	time(&stop);
	double diff = difftime(stop, start);
	int hrs = (int)diff / 3600;
	int mins = ((int)diff / 60) - (hrs * 60);
	int secs = (int)diff - (hrs * 3600) - (mins * 60);
	printf("\rRendering (%i samples): Complete!\nTime Taken: %i hrs, %i mins, %i secs\n\n", samples, hrs, mins, secs);
	return 0;
}