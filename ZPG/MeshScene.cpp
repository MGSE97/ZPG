#include "MeshScene.h"
#include "BaseEngine.h"
#include "Assets.h"
#include "StandartMaterial.h"

void Application::Scenes::MeshScene::Load(Engine::BaseEngine* engine)
{
	Engine::Components::Graphics::Shader* shader = engine->Shaders->First();

	auto sunconfig = new Engine::Components::Graphics::LightConfiguration;
	sunconfig->AmbientColor = glm::vec3(1.f, .8f, .3f);
	sunconfig->DiffuseColor = glm::vec3(1.f, .8f, .3f);
	sunconfig->SpecularColor = glm::vec3(1.f, 1.f, 1.f);;
	sunconfig->SpecularSize = 8;
	sunconfig->GlobalStrength = 10.f;
	Lights->Add("Sun", new Engine::Components::Light(shader, glm::vec3(0, 2, 20), glm::vec4(1.f, 0.8f, 0.3f, 1.f), sunconfig));

	/*auto cube = new Engine::Components::Objects::Mesh();
	cube->Load(Assets::Meshes, "test.obj");
	for (auto& object : *cube->Components)
	{
		object->Material->SetShader(shader);
		object->Transform->Rotation(30, 90, 0);
	}*/

	auto earth = (new Engine::Components::Objects::Mesh())
		->Load(Assets::Earth2Model, "Earth.obj");
	//earth->Load(Assets::EarthModel, "koule.obj", aiProcess_Triangulate|aiProcess_CalcTangentSpace|aiProcess_OptimizeMeshes);
	for (auto& object : *earth->Components)
	{
		//object->Material->Color = glm::vec4(1, 0, 0, 1);
		object->Material->SetShader(shader);
		object->Transform->Scale(0.2f, 0.2f, 0.2f, true)
						 ->Position(20, 0, 20)
						 ->Rotation(-30, -130, 0);
	}

	auto skydome = (new Engine::Components::Objects::Mesh())
		->Load(Assets::SkyModel, "fullskydome.obj");
	for (auto& object : *skydome->Components)
	{
		object->Material->SetShader(shader);
		object->Material->Color = glm::vec4(0.1f, 0.1f, 0.1f, 0.1f);
		object->Material->Light.UseLighting = false;
		object->Transform->Scale(10, 10, 10, true);
	}

	auto ship = (new Engine::Components::Objects::Mesh())
		->Load(Assets::ShipModel, "Sample_Ship.obj", aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_OptimizeMeshes | aiProcess_GenSmoothNormals | aiProcess_FixInfacingNormals );
	for (auto& object : *ship->Components)
	{
		object->Material->SetShader(shader);
		object->Transform->Position(1, 1, 1, true);
	}


	/*auto house = new Engine::Components::Objects::Mesh();
	house->Load(Assets::HouseModel, "house.obj");
	for (auto& object : *house->Components)
	{
		object->Material->SetShader(shader);
		//object->Transform->Scale(0.1, 0.1, 0.1, true);
		//object->Transform->Position(-10, 0, -10);
	}*/

	Meshes->Add("sky", skydome);
	//Meshes->Add("cube", cube);
	Meshes->Add("earth", earth);
	//Meshes->Add("house", house);
	Meshes->Add("ship", ship);


	// Besier
	n = 2;
	P.push_back(glm::vec3(0, 0, 10));
	P.push_back(glm::vec3(0, 5, 15));
	P.push_back(glm::vec3(0, 0, 20));
	P.push_back(glm::vec3(0, -5, 15));
	P.push_back(glm::vec3(0, 0, 10));


	auto asteroid = (new Engine::Components::Objects::Mesh());

	for(auto p : P)
	{
		asteroid->Load(Assets::AsteroidModel, "A2.obj");
		auto object = asteroid->Components->back();
		object->Material->SetShader(shader);
		object->Transform->Position(p, true)
						 ->Scale(0.1f, 0.1f, 0.1f,true);
	}

	Meshes->Add("asteroid", asteroid);
}

void Application::Scenes::MeshScene::Unload(Engine::BaseEngine* engine)
{
}

int Application::Scenes::MeshScene::nChoosek(unsigned n, unsigned k)
{
	if (k > n) return 0;
	if (k * 2 > n) k = n - k;
	if (k == 0) return 1;

	int result = n;
	for (int i = 2; i <= k; ++i) {
		result *= (n - i + 1);
		result /= i;
	}
	return result;
}

void Application::Scenes::MeshScene::FrameUpdate(Engine::BaseEngine* engine)
{
	Scene::FrameUpdate(engine);

	glm::vec3 p = glm::vec3(0);
	for(int i = 0; i < P.size(); i++)
	{
		auto B = nChoosek(n, i) * pow(t, i)*pow(1 - t, n - i);
		p += P[i] * B;
	}

	Lights->Get("Sun")->Transform->Position(p, true);

	t += 0.01f*direction;
	if (t >= 1 || t <= 0)
		direction *= -1;
}

