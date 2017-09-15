#ifndef BABYLON_POSTPROCESS_RENDERPIPELINE_POST_PROCESS_RENDER_PIPELINE_H
#define BABYLON_POSTPROCESS_RENDERPIPELINE_POST_PROCESS_RENDER_PIPELINE_H

#include <babylon/babylon_global.h>
#include <babylon/interfaces/idisposable.h>

namespace BABYLON {

/**
 * @brief
 */
class BABYLON_SHARED_EXPORT PostProcessRenderPipeline : public IDisposable {

public:
  static constexpr const char* PASS_EFFECT_NAME  = "passEffect";
  static constexpr const char* PASS_SAMPLER_NAME = "passSampler";

public:
  PostProcessRenderPipeline(Engine* engine, const string_t& name);
  virtual ~PostProcessRenderPipeline();

  /**
   * Returns the string "PostProcessRenderPipeline"
   */
  const char* getClassName() const;

  vector_t<Camera*> getCameras() const;
  bool isSupported() const;
  void addEffect(PostProcessRenderEffect* renderEffect);
  void _enableEffect(const string_t& renderEffectName,
                     const vector_t<Camera*>& cameras);
  void _disableEffect(const string_t& renderEffectName,
                      const vector_t<Camera*>& cameras);
  void _attachCameras(const vector_t<Camera*>& cameras, bool unique);
  void _detachCameras(const vector_t<Camera*>& cameras);
  void _enableDisplayOnlyPass(const string_t& passName,
                              const vector_t<Camera*>& cameras);
  void _disableDisplayOnlyPass(const string_t& passName,
                               const vector_t<Camera*>& cameras);
  void _update();
  void _reset();
  virtual void dispose(bool doNotRecurse = false) override;

public:
  string_t _name;
  Engine* _engine;

protected:
  unordered_map_t<string_t, Camera*> _cameras;

private:
  unordered_map_t<string_t, PostProcessRenderEffect*> _renderEffects;
  unordered_map_t<string_t, PostProcessRenderEffect*>
    _renderEffectsForIsolatedPass;

}; // end of class PostProcessRenderPipeline

} // end of namespace BABYLON

#endif // end of
       // BABYLON_POSTPROCESS_RENDERPIPELINE_POST_PROCESS_RENDER_PIPELINE_H
