#include <babylon/materials/pbr/pbr_material_defines.h>

namespace BABYLON {

PBRMaterialDefines::PBRMaterialDefines() : MaterialDefines{}
{
  _keys = {
    "PBR",
    "MAINUV1",
    "MAINUV2",
    "UV1",
    "UV2",
    "ALBEDO",
    "VERTEXCOLOR",
    "AMBIENT",
    "AMBIENTINGRAYSCALE",
    "OPACITY",
    "VERTEXALPHA",
    "OPACITYRGB",
    "ALPHATEST",
    "DEPTHPREPASS"
    "ALPHABLEND",
    "ALPHAFROMALBEDO",
    "SPECULAROVERALPHA",
    "RADIANCEOVERALPHA",
    "ALPHAFRESNEL",
    "PREMULTIPLYALPHA",
    "EMISSIVE",
    "REFLECTIVITY",
    "SPECULARTERM",
    "MICROSURFACEFROMREFLECTIVITYMAP",
    "MICROSURFACEAUTOMATIC",
    "LODBASEDMICROSFURACE",
    "MICROSURFACEMAP",
    "METALLICWORKFLOW",
    "ROUGHNESSSTOREINMETALMAPALPHA",
    "ROUGHNESSSTOREINMETALMAPGREEN",
    "METALLNESSSTOREINMETALMAPBLUE",
    "AOSTOREINMETALMAPRED",
    "ENVIRONMENTBRDF",
    "NORMAL",
    "TANGENT",
    "BUMP",
    "PARALLAX",
    "PARALLAXOCCLUSION",
    "NORMALXYSCALE",
    "LIGHTMAP",
    "USELIGHTMAPASSHADOWMAP",
    "REFLECTION",
    "REFLECTIONMAP_3D",
    "REFLECTIONMAP_SPHERICAL",
    "REFLECTIONMAP_PLANAR",
    "REFLECTIONMAP_CUBIC",
    "REFLECTIONMAP_PROJECTION",
    "REFLECTIONMAP_SKYBOX",
    "REFLECTIONMAP_EXPLICIT",
    "REFLECTIONMAP_EQUIRECTANGULAR",
    "REFLECTIONMAP_EQUIRECTANGULAR_FIXED",
    "REFLECTIONMAP_MIRROREDEQUIRECTANGULAR_FIXED",
    "INVERTCUBICMAP",
    "USESPHERICALFROMREFLECTIONMAP",
    "USESPHERICALINFRAGMENT",
    "REFLECTIONMAP_OPPOSITEZ",
    "LODINREFLECTIONALPHA",
    "GAMMAREFLECTION",
    "REFRACTION",
    "REFRACTIONMAP_3D",
    "REFRACTIONMAP_OPPOSITEZ",
    "LODINREFRACTIONALPHA",
    "GAMMAREFRACTION",
    "LINKREFRACTIONTOTRANSPARENCY",
    "INSTANCES",
    "MORPHTARGETS",
    "MORPHTARGETS_NORMAL",
    "MORPHTARGETS_TANGENT",
    "IMAGEPROCESSING",
    "VIGNETTE",
    "VIGNETTEBLENDMODEMULTIPLY",
    "VIGNETTEBLENDMODEOPAQUE",
    "TONEMAPPING",
    "CONTRAST",
    "COLORCURVES",
    "COLORGRADING",
    "SAMPLER3DGREENDEPTH",
    "SAMPLER3DBGRMAP",
    "IMAGEPROCESSINGPOSTPROCESS",
    "EXPOSURE",
    "USEPHYSICALLIGHTFALLOFF",
    "TWOSIDEDLIGHTING",
    "SHADOWFLOAT",
    "USERIGHTHANDEDSYSTEM",
    "CLIPPLANE",
    "POINTSIZE",
    "FOG",
    "LOGARITHMICDEPTH",
    "FORCENORMALFORWARD",
  };
  rebuild();
}

PBRMaterialDefines::~PBRMaterialDefines()
{
}

void PBRMaterialDefines::reset()
{
  MaterialDefines::reset();
  ALPHATESTVALUE = 0.5f;
  defines[PBR]   = true;
}

} // end of namespace BABYLON
