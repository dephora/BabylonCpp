#include <babylon/materials/pbr/pbr_base_simple_material.h>

#include <babylon/materials/pbr/pbr_material.h>
#include <babylon/materials/textures/base_texture.h>

namespace BABYLON {
namespace Internals {

PBRBaseSimpleMaterial::PBRBaseSimpleMaterial(const std::string& iName,
                                             Scene* scene)
    : PBRBaseMaterial{iName, scene}
    , maxSimultaneousLights{4}
    , disableLighting{false}
    , environmentTexture{nullptr}
    , invertNormalMapX{false}
    , invertNormalMapY{false}
    , normalTexture{nullptr}
    , emissiveColor{Color3(0, 0, 0)}
    , emissiveTexture{nullptr}
    , occlusionStrength{1.f}
    , occlusionTexture{nullptr}
    , alphaCutOff{0.f}
    , _transparencyMode{PBRMaterial::PBRMATERIAL_OPAQUE}
{
  _useAmbientInGrayScale = true;
}

PBRBaseSimpleMaterial::~PBRBaseSimpleMaterial()
{
}

const char* PBRBaseSimpleMaterial::getClassName() const
{
  return "PBRBaseSimpleMaterial";
}

unsigned int PBRBaseSimpleMaterial::transparencyMode() const
{
  return _transparencyMode;
}

void PBRBaseSimpleMaterial::setTransparencyMode(unsigned int value)
{
  if (_transparencyMode == value) {
    return;
  }
  _transparencyMode = value;
  if (value == PBRMaterial::PBRMATERIAL_ALPHATESTANDBLEND) {
    _forceAlphaTest = true;
  }
  else {
    _forceAlphaTest = false;
  }

  _markAllSubMeshesAsTexturesDirty();
}

bool PBRBaseSimpleMaterial::doubleSided() const
{
  return _twoSidedLighting;
}

void PBRBaseSimpleMaterial::setDoubleSided(bool value)
{
  if (_twoSidedLighting == value) {
    return;
  }
  _twoSidedLighting = value;
  setBackFaceCulling(!value);
  _markAllSubMeshesAsTexturesDirty();
}

bool PBRBaseSimpleMaterial::_shouldUseAlphaFromAlbedoTexture() const
{
  return _albedoTexture && _albedoTexture->hasAlpha()
         && _transparencyMode != PBRMaterial::PBRMATERIAL_OPAQUE;
}

bool PBRBaseSimpleMaterial::needAlphaBlending()
{
  if (_linkRefractionWithTransparency) {
    return false;
  }

  return (alpha < 1.f)
         || (_shouldUseAlphaFromAlbedoTexture()
             && (_transparencyMode == PBRMaterial::PBRMATERIAL_ALPHABLEND
                 || _transparencyMode
                      == PBRMaterial::PBRMATERIAL_ALPHATESTANDBLEND));
}

bool PBRBaseSimpleMaterial::needAlphaTesting()
{
  if (_linkRefractionWithTransparency) {
    return false;
  }

  return _shouldUseAlphaFromAlbedoTexture()
         && _transparencyMode == PBRMaterial::PBRMATERIAL_ALPHATEST;
}

std::vector<BaseTexture*> PBRBaseSimpleMaterial::getActiveTextures() const
{
  auto activeTextures = PBRBaseMaterial::getActiveTextures();

  if (environmentTexture) {
    activeTextures.emplace_back(environmentTexture);
  }

  if (normalTexture) {
    activeTextures.emplace_back(normalTexture);
  }

  if (emissiveTexture) {
    activeTextures.emplace_back(emissiveTexture);
  }

  if (occlusionTexture) {
    activeTextures.emplace_back(occlusionTexture);
  }

  return activeTextures;
}

} // end of namespace Internals
} // end of namespace BABYLON