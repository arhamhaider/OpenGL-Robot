#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "IRenderable.h"
#include "IRenderer.h"
#include "IShader.h"
#include "primitive_gen.h"

class Robot : public IRenderable {
  Mesh torso;
  Mesh headMesh;
  Mesh armMesh;
  Mesh legMesh;
  Mesh eyeMesh;
  Mesh smileMesh;
  float leftArmRot;
  float rightArmRot;
  float leftElbowRot;
  float rightElbowRot;
  float timeSec;
  bool motionShoulderWave;
  bool motionHeadYaw;
  bool motionLegWalk;
  float shoulderAnimDeg;
  float headYawDeg;
  float legSwingDeg;

 public:
  Robot();
  void initMeshes();
  void onKey(unsigned char key);
  void update(float dt);
  void draw(const IRenderer& r, IShader& shader) const override;
};
