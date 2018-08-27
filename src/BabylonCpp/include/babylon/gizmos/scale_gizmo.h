#ifndef BABYLON_GIZMOS_SCALE_GIZMO_H
#define BABYLON_GIZMOS_SCALE_GIZMO_H

#include <babylon/babylon_global.h>
#include <babylon/gizmos/gizmo.h>
#include <babylon/rendering/utility_layer_renderer.h>

namespace BABYLON {

/**
 * @brief Gizmo that enables scaling a mesh along 3 axis.
 */
class BABYLON_SHARED_EXPORT ScaleGizmo : public Gizmo {

public:
  /**
   * @brief Creates a ScaleGizmo
   * @param gizmoLayer The utility layer the gizmo will be added to
   */
  ScaleGizmo(const shared_ptr_t<UtilityLayerRenderer>& gizmoLayer
             = UtilityLayerRenderer::DefaultUtilityLayer());
  ~ScaleGizmo() override;

  /**
   * @brief Disposes of the gizmo.
   */
  void dispose(bool doNotRecurse               = false,
               bool disposeMaterialAndTextures = false) override;

protected:
  void set_attachedMesh(const AbstractMeshPtr& mesh) override;
  void set_updateGizmoRotationToMatchAttachedMesh(bool value);
  bool get_updateGizmoRotationToMatchAttachedMesh() const;
  void set_snapDistance(float value);
  float get_snapDistance() const;
  void set_scaleRatio(float value);
  float get_scaleRatio() const;

public:
  /**
   * Internal gizmo used for interactions on the x axis
   */
  unique_ptr_t<AxisScaleGizmo> xGizmo;

  /**
   * Internal gizmo used for interactions on the y axis
   */
  unique_ptr_t<AxisScaleGizmo> yGizmo;

  /**
   * Internal gizmo used for interactions on the z axis
   */
  unique_ptr_t<AxisScaleGizmo> zGizmo;

  /**
   * Internal gizmo used to scale all axis equally
   */
  unique_ptr_t<AxisScaleGizmo> _uniformGizmo;

  /**
   * Drag distance in babylon units that the gizmo will snap to when dragged
   * (Default: 0)
   */
  Property<ScaleGizmo, float> snapDistance;

  /**
   * Ratio for the scale of the gizmo (Default: 1)
   */
  Property<ScaleGizmo, float> scaleRatio;

  Property<ScaleGizmo, bool> updateGizmoRotationToMatchAttachedMesh;

}; // end of class ScaleGizmo

} // end of namespace BABYLON

#endif // end of BABYLON_GIZMOS_SCALE_GIZMO_H
