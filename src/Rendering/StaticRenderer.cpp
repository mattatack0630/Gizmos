//
// Created by mathew on 6/2/18.
//

#include <Rendering/Fbo.h>
#include <Rendering/StaticRenderer.h>
#include <Rendering/ModelLoader.h>
#include <Rendering/StaticMesh.h>

static std::string file_to_string(std::string name)
{
	std::ifstream infile{name};
	std::string file_contents{std::istreambuf_iterator<char>(infile), std::istreambuf_iterator<char>()};
	return file_contents;
}

static float map(float x, float in_min, float in_max, float out_min, float out_max)
{
	return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void render_textured_quad(float x, float y, Vao vert_array_quad, GLuint texture_id, Shader& shader)
{
	vert_array_quad.bind();

	Matrix4f MVP = Matrix4f();
	MVP.set_identity();

	WorldTransform quad_transform = WorldTransform(x, y, 0, 0, 0, 0, 0.45, 0.45, 0.45);

	linear::dot(MVP, quad_transform.get_matrix(), MVP);

	shader.upload_uniform<Matrix4fUniform>("vMVP", MVP);
	shader.upload_uniform<TextureUniform>("texture1", texture_id, 0);

	GLCall(glDrawElements(vert_array_quad.get_topology(), vert_array_quad.get_vertex_count(), GL_UNSIGNED_INT, (void*) 0));
}

float CalcPointLightBSphere(const PointLight& Light)
{
	float MaxChannel = fmax(fmax(Light.color.get_element(0), Light.color.get_element(1)), Light.color.get_element(2));
	float constant = Light.attenuation.get_element(0);
	float linear = Light.attenuation.get_element(1);
	float exp = Light.attenuation.get_element(2);

	float ret = (-linear + sqrtf(linear * linear - 4 * exp * (constant - 256 * MaxChannel * 0.1)))
				/ (2 * exp);
	return ret;
}

Vector3f toCartisian(float radius, float theta1, float theta2)
{
	float x = radius * sin(theta1) * cos(theta2);
	float y = radius * sin(theta1) * sin(theta2);
	float z = radius * cos(theta1);

	return Vector3f({x, y, z});
}

Vector3f toPolar(float x, float y, float z)
{
	float radius = sqrt(x * x + y * y + z * z);
	float theta1 = acos(z / radius);
	float theta2 = atan(y / x);

	return Vector3f({radius, theta1, theta2});
}

StaticMesh calc_sphere()
{

	const int total = 10;
	Vector3f points[(total + 1) * (total + 1)] = {};

	for (int j = 0; j <= total; j++) {
		float lon = map(j, 0, total, 0, M_PI);
		for (int i = 0; i <= total; i++) {
			float lat = map(i, 0, total, 0, M_PI * 2);
			float r = 1;
			Vector3f cart1 = toCartisian(r, lon, lat);
			points[j * total + i] = cart1;
		}
	}

	StaticMesh mesh = StaticMesh(total * total, GL_TRIANGLES);

	mesh.start();
	for (int j = 0; j <= total - 1; j++) {
		for (int i = 0; i <= total - 1; i++) {
			Vector3f cart1 = points[(j % (total + 1)) * total + (i % total)];
			Vector3f cart2 = points[(j % (total + 1)) * total + ((i + 1) % total)];
			Vector3f cart3 = points[((j + 1) % (total + 1)) * total + ((i + 1) % total)];
			Vector3f cart4 = points[((j + 1) % (total + 1)) * total + (i % total)];

			mesh.vertex(cart1.get_element(0), cart1.get_element(1), cart1.get_element(2), 1, 0, 0, 0, 0);
			mesh.vertex(cart2.get_element(0), cart2.get_element(1), cart2.get_element(2), 1, 0, 0, 0, 0);
			mesh.vertex(cart3.get_element(0), cart3.get_element(1), cart3.get_element(2), 1, 0, 0, 0, 0);

			mesh.vertex(cart4.get_element(0), cart4.get_element(1), cart4.get_element(2), 1, 0, 0, 0, 0);
			mesh.vertex(cart1.get_element(0), cart1.get_element(1), cart1.get_element(2), 1, 0, 0, 0, 0);
			mesh.vertex(cart3.get_element(0), cart3.get_element(1), cart3.get_element(2), 1, 0, 0, 0, 0);
		}
	}
	mesh.finish();

	return mesh; //  Too many objects know about VAOs, maybe decouple these
}


StaticRenderer::StaticRenderer() : RendererBase()
{

}

void StaticRenderer::generate()
{
	RendererBase::generate();

	screen_quad = ModelLoader::load_OBJ("/home/mathew/CLionProjects/Gizmos/tests/quad.obj");

	StaticMesh sphere = calc_sphere();
	sphere_vao = sphere.to_vao();

	shader_g_buffer = std::make_unique<Shader>(
			file_to_string("/home/mathew/CLionProjects/Gizmos/shaders/shader.fs"),
			file_to_string("/home/mathew/CLionProjects/Gizmos/shaders/shader.vs")
	);

	shader_lighting = std::make_unique<Shader>(
			file_to_string("/home/mathew/CLionProjects/Gizmos/shaders/shader1.fs"),
			file_to_string("/home/mathew/CLionProjects/Gizmos/shaders/shader1.vs")
	);

	fbo_g_buffer = std::make_unique<Fbo>(640, 640);
	fbo_g_buffer->attach_render_texture(0, GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE); //  Colors
	fbo_g_buffer->attach_render_texture(1, GL_RGB16F, GL_RGB, GL_FLOAT); // Normals
	fbo_g_buffer->attach_render_texture(2, GL_RGB16F, GL_RGB, GL_FLOAT); // Positions
	fbo_g_buffer->attach_depth_buffer();

	fbo_lighting = std::make_unique<Fbo>(640, 640); // placeholder for screen
	fbo_lighting->attach_render_texture(0, GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE); //  Colors
	fbo_lighting->attach_depth_buffer();

	shader_g_buffer->generate();
	shader_lighting->generate();

	fbo_g_buffer->generate();
	fbo_lighting->generate();

	// Temp
}

void StaticRenderer::pre_render()
{
	RendererBase::pre_render();

	GLCall(glDisable(GL_BLEND));
	GLCall(glEnable(GL_CULL_FACE));
	GLCall(glCullFace(GL_BACK));
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glDepthFunc(GL_LESS));
}

void StaticRenderer::render(Fbo& fbo_result)
{
	RendererBase::render(fbo_result);

	// G-Buffer Pass
	{
		shader_g_buffer->bind();
		fbo_g_buffer->bind();

		GLCall(glClearColor(0.0, 0.0, 0.0, 1.0));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		Vao* last_vao = nullptr;

		for (Renderable renderable : renderables) {
			Vao* vao = &renderable.vao;

			if ((last_vao == nullptr) || (last_vao->get_id() != vao->get_id()))
				vao->bind();

			shader_g_buffer->upload_uniforms(renderable.uniforms);

			GLCall(glDrawElements(vao->get_topology(), vao->get_vertex_count(), GL_UNSIGNED_INT, (void*) 0));

			last_vao = vao;
		}
	}


	// Lighting Pass
	{
		shader_lighting->bind();
		screen_quad.bind();
		fbo_result.bind();

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_ONE, GL_ONE));
		GLCall(glDisable(GL_DEPTH_TEST));
		GLCall(glDisable(GL_CULL_FACE));
		GLCall(glClearColor(0.0, 0.0, 0.0, 1.0));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		shader_lighting->upload_uniform<TextureUniform>("Colors_Texture", fbo_g_buffer->get_attachment(0), 0);
		shader_lighting->upload_uniform<TextureUniform>("Normals_Texture", fbo_g_buffer->get_attachment(1), 1);
		shader_lighting->upload_uniform<TextureUniform>("Depth_Texture", fbo_g_buffer->get_attachment(2), 2);

		Matrix4f MVP = Matrix4f();
		MVP.set_identity();
		shader_lighting->upload_uniform<Matrix4fUniform>("vMVP", MVP);

		GLCall(glDrawElements(screen_quad.get_topology(), screen_quad.get_vertex_count(), GL_UNSIGNED_INT, (void*) 0));

		/*
		for (PointLight light : point_lights) {
				float scale = CalcPointLightBSphere(light);

				std::cout << scale << std::endl;
				Matrix4f MVP = Matrix4f();
				WorldTransform view = WorldTransform(0, 0, -100, 0, 0, 0, 1, 1, 1);
				WorldTransform model = WorldTransform(0, 0, 0, 0, M_PI, 0, 1, 1, 1);
				PerspectiveTransform projection = PerspectiveTransform(1, 0.1, 600, M_PI / 3);

				model.set_translation(light.position.get_element(0), light.position.get_element(1), light.position.get_element(2));
				model.set_scale(scale, scale, scale);

				MVP.set_identity();
				linear::dot(MVP, projection.get_matrix(), MVP);
				linear::dot(MVP, view.get_matrix(), MVP);
				linear::dot(MVP, model.get_matrix(), MVP);

				shader_lighting->upload_uniform<Vector3fUniform>("pointLight.pos", light.position);
				shader_lighting->upload_uniform<Vector3fUniform>("pointLight.att", light.attenuation);
				shader_lighting->upload_uniform<Vector3fUniform>("pointLight.col", light.color);

				shader_lighting->upload_uniform<Matrix4fUniform>("vMVP", MVP);

				GLCall(glDrawElements(sphere_vao.get_topology(), sphere_vao.get_vertex_count(), GL_UNSIGNED_INT, (void*) 0));
			}
			*/
	}


/*
	// Render Quads to Screen
	{
		shader_g_buffer->bind();
		fbo_result.bind();

		GLCall(glDisable(GL_BLEND));
		GLCall(glClearColor(0.7, 0.7, 0.7, 1));
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		render_textured_quad(0.5, 0.5, screen_quad, fbo_g_buffer->get_attachment(0), *shader_g_buffer);
		render_textured_quad(-1.0 + 0.5, 0.5, screen_quad, fbo_g_buffer->get_attachment(2), *shader_g_buffer);
		render_textured_quad(0.5, -1.0 + 0.5, screen_quad, fbo_lighting->get_attachment(0), *shader_g_buffer);
		render_textured_quad(-1.0 + 0.5, -1.0 + 0.5, screen_quad, fbo_g_buffer->get_attachment(1), *shader_g_buffer);
	}
 */
}

void StaticRenderer::post_render()
{
	RendererBase::post_render();

	spot_lights.clear();
	point_lights.clear();
	direction_lights.clear();
}

void StaticRenderer::destroy()
{
	RendererBase::destroy();

	shader_g_buffer->destroy();
	shader_lighting->destroy();
	fbo_g_buffer->destroy();
	fbo_lighting->destroy();
}

void StaticRenderer::add_spot_light(SpotLight l)
{
	spot_lights.push_back(l);
}

void StaticRenderer::add_point_light(PointLight l)
{
	point_lights.push_back(l);
}

void StaticRenderer::add_direction_light(DirectionLight l)
{
	direction_lights.push_back(l);
}
