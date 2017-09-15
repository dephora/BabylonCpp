#ifndef BABYLON_MATERIALS_TEXTURES_DYNAMIC_TEXTURE_H
#define BABYLON_MATERIALS_TEXTURES_DYNAMIC_TEXTURE_H

#include <babylon/babylon_global.h>
#include <babylon/engine/engine_constants.h>
#include <babylon/materials/textures/texture.h>

namespace BABYLON {

struct DynamicTextureOptions {
  ICanvas* canvas = nullptr;
  int width;
  int height;
}; // end of struct struct DynamicTexture

class BABYLON_SHARED_EXPORT DynamicTexture : public Texture {

public:
  DynamicTexture(const string_t& name, const DynamicTextureOptions& options,
                 Scene* scene, bool generateMipMaps,
                 unsigned int samplingMode
                 = TextureConstants::TRILINEAR_SAMPLINGMODE,
                 unsigned int format = EngineConstants::TEXTUREFORMAT_RGBA);
  ~DynamicTexture();

  bool canRescale();
  void scale(float ratio) override;
  void scaleTo(int width, int height);
  ICanvasRenderingContext2D* getContext();
  void clear();
  void update(bool invertY = true);
  void drawText(const string_t& text, int x, int y, const string_t& font,
                const string_t& color, const string_t& clearColor,
                bool invertY = true, bool update = true);
  unique_ptr_t<DynamicTexture> clone() const;
  void _rebuild() override;

private:
  void _recreate(const ISize& textureSize);

public:
  unsigned int _samplingMode;

private:
  bool _generateMipMaps;
  ICanvas* _canvas;
  ICanvasRenderingContext2D* _context;

}; // end of class DynamicTexture

} // end of namespace BABYLON

#endif // end of BABYLON_MATERIALS_TEXTURES_DYNAMIC_TEXTURE_H
