#version 440

struct Material
{
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  sampler2D diffuseTex;
  sampler2D specularTex;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

uniform Material material;
uniform vec3 lightPos0;
uniform vec3 cameraPos;

vec4 calculateAmbient(Material material)
{
  return vec4(material.ambient, 1.f);
}

vec4 calculateDiffuse(Material material)
{
  vec3 posToLightDirVec = normalize(lightPos0 - vs_position);
  float diffuse = clamp(dot(posToLightDirVec, vs_normal), 0, 1);
  return vec4(material.diffuse * diffuse, 1.f);
}

vec4 calculateSpecular(Material material)
{
  vec3 lightToPosDirVec = normalize(vs_position - lightPos0);
  vec3 reflectDirVec = normalize(reflect(lightToPosDirVec, normalize(vs_normal)));
  vec3 posToViewDirVec = normalize(cameraPos - vs_position);
  float specularConstant = pow(max(dot(posToViewDirVec, reflectDirVec), 0), 30);
  return vec4(material.specular * specularConstant * texture(material.specularTex, vs_texcoord).rgb, 1.f);
}

void main()
{
  vec4 ambientLight = calculateAmbient(material);
  vec4 diffuseLight = calculateDiffuse(material);
  vec4 specularLight = calculateSpecular(material);

  // attenuation

  // final
  fs_color =
    texture(material.diffuseTex, vs_texcoord)
    * (ambientLight + diffuseLight + specularLight);
}