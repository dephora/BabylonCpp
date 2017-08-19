#include <babylon/samples/extensions/noisegeneration/perlin_noise_waves_scene.h>

#include <babylon/cameras/arc_rotate_camera.h>
#include <babylon/engine/engine.h>
#include <babylon/interfaces/icanvas.h>
#include <babylon/lights/hemispheric_light.h>
#include <babylon/materials/standard_material.h>
#include <babylon/mesh/mesh.h>
#include <babylon/mesh/vertex_buffer.h>
#include <babylon/mesh/vertex_data.h>

namespace BABYLON {
namespace Samples {

PerlinNoiseWavesScene::PerlinNoiseWavesScene(ICanvas* iCanvas)
    : IRenderableScene(iCanvas)
    , _ground{nullptr}
    , _ground2{nullptr}
    , _perlineNoise{Extensions::PerlinNoise()}
    , _alpha{0.f}
{
}

PerlinNoiseWavesScene::~PerlinNoiseWavesScene()
{
}

const char* PerlinNoiseWavesScene::getName()
{
  return "Perlin Noise Waves Scene";
}

void PerlinNoiseWavesScene::initializeScene(ICanvas* canvas, Scene* scene)
{
  // Create a camera
  auto camera = ArcRotateCamera::New("Camera", -Math::PI_2, 0.7, 600,
                                     Vector3::Zero(), scene);

  // Attach the camera to the canvas
  camera->attachControl(canvas, true);

  // Create a basic light, aiming 0,1,0 - meaning, to the sky
  auto light = HemisphericLight::New("light1", Vector3(0, 1, 0), scene);

  // Default intensity is 1. Let's dim the light a small amount
  light->intensity = 0.7f;

  // Create ground meshes
  _ground = Mesh::CreateGround("ground", 650, 400, 16, scene, true);
  _ground->setMaterial(StandardMaterial::New("gmat", scene));
  _ground->material()->setDiffuseColor(Color3::FromInts(255, 140, 0));
  _ground->position().y += 50;
  _ground2 = Mesh::CreateGround("ground", 650, 400, 16, scene, true);
  _ground2->setMaterial(StandardMaterial::New("gmat2", scene));
  _ground2->material()->setDiffuseColor(Color3::FromInts(255, 140, 0));
  _ground2->material()->setWireframe(true);
  _ground2->position().y = _ground->position().y;

  // Get positions and indices
  _positions = _ground->getVerticesData(VertexBuffer::PositionKind);
  _indices   = _ground->getIndices();

  // Animations
  _scene->registerBeforeRender([this]() {
    _alpha += 0.016f;
    for (unsigned int i = 0; i < _positions.size(); i += 3) {
      _positions[i + 1]
        = 32.f * static_cast<float>(_perlineNoise.noise(
                   static_cast<double>(_positions[i] / 0.8f),
                   static_cast<double>(_alpha * 0.2f),
                   static_cast<double>(_positions[i + 2] / 0.8f)));
    }
    _ground->updateVerticesData(VertexBuffer::PositionKind, _positions, false,
                                true);
    _ground2->updateVerticesData(VertexBuffer::PositionKind, _positions, false,
                                 true);
    Float32Array normals;
    VertexData::ComputeNormals(_positions, _indices, normals);

    _ground->updateVerticesData(VertexBuffer::NormalKind, normals, false,
                                false);
    _ground2->updateVerticesData(VertexBuffer::NormalKind, normals, false,
                                 false);
  });
}

} // end of namespace Samples
} // end of namespace BABYLON