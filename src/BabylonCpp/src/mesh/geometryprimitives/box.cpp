#include <babylon/mesh/geometryprimitives/box.h>

#include <babylon/engine/scene.h>
#include <babylon/mesh/vertex_data.h>
#include <babylon/mesh/vertex_data_options.h>
#include <babylon/tools/tools.h>

namespace BABYLON {
namespace GeometryPrimitives {

Box::Box(const string_t& _id, Scene* scene, float _size, bool canBeRegenerated,
         Mesh* mesh, unsigned int _side)
    : _Primitive{_id, scene, canBeRegenerated, mesh}, size{_size}, side{_side}
{
}

Box::~Box()
{
}

unique_ptr_t<VertexData> Box::_regenerateVertexData()
{
  BoxOptions options(size);
  options.sideOrientation = side;

  return VertexData::CreateBox(options);
}

Geometry* Box::copy(const string_t& _id)
{
  return Box::New(_id, getScene(), size, canBeRegenerated(), nullptr, side);
}

Box* Box::Parse(const Json::value& parsedBox, Scene* scene)
{
  const auto parsedBoxId = Json::GetString(parsedBox, "id");
  if (parsedBoxId.empty() || scene->getGeometryByID(parsedBoxId)) {
    return nullptr; // null since geometry could be something else than a box...
  }

  return Box::New(parsedBoxId, scene, Json::GetNumber(parsedBox, "size", 1.f),
                  Json::GetBool(parsedBox, "canBeRegenerated", true), nullptr);
}

} // end of namespace GeometryPrimitives
} // end of namespace BABYLON
