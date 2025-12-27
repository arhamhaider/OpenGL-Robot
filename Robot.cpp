#include "Robot.h"

#include <cmath>

Robot::Robot()
    : leftArmRot(0.0f),
      rightArmRot(0.0f),
      leftElbowRot(0.0f),
      rightElbowRot(0.0f),
      timeSec(0.0f),
      motionShoulderWave(true),
      motionHeadYaw(true),
      motionLegWalk(true),
      shoulderAnimDeg(0.0f),
      headYawDeg(0.0f),
      legSwingDeg(0.0f) {}

void Robot::initMeshes() {
  torso = makeCube();
  headMesh = makeSphere(12, 12, 0.5f);
  armMesh = makeCylinder(16, 0.12f, 1.2f);
  legMesh = makeCylinder(16, 0.15f, 1.4f);
  eyeMesh = makeSolidDisc(32, 0.12f, 0.1f);
  smileMesh = makeHalfDisc(32, 0.2f, 0.03f);
}

void Robot::onKey(unsigned char key) {
  if (key == 'w' || key == 'W') {
    leftArmRot += 5.0f;
    rightArmRot += 5.0f;
  }
  if (key == 's' || key == 'S') {
    leftArmRot -= 5.0f;
    rightArmRot -= 5.0f;
  }
  if (key == 'e' || key == 'E') {
    leftElbowRot += 5.0f;
    rightElbowRot += 5.0f;
  }
  if (key == 'd' || key == 'D') {
    leftElbowRot -= 5.0f;
    rightElbowRot -= 5.0f;
  }
  if (key == '1') {
    motionShoulderWave = !motionShoulderWave;
  }
  if (key == '2') {
    motionHeadYaw = !motionHeadYaw;
  }
  if (key == '3') {
    motionLegWalk = !motionLegWalk;
  }
  if (key == 'r' || key == 'R') {
    leftArmRot = rightArmRot = leftElbowRot = rightElbowRot = 0.0f;
    shoulderAnimDeg = headYawDeg = legSwingDeg = 0.0f;
  }
  const float SHOULDER_MIN = -10.0f, SHOULDER_MAX = 10.0f;
  const float ELBOW_MIN = -20.0f, ELBOW_MAX = 20.0f;
  leftArmRot = glm::clamp(leftArmRot, SHOULDER_MIN, SHOULDER_MAX);
  rightArmRot = glm::clamp(rightArmRot, SHOULDER_MIN, SHOULDER_MAX);
  leftElbowRot = glm::clamp(leftElbowRot, ELBOW_MIN, ELBOW_MAX);
  rightElbowRot = glm::clamp(rightElbowRot, ELBOW_MIN, ELBOW_MAX);
}

void Robot::update(float dt) {
  timeSec += dt;
  if (motionShoulderWave) {
    shoulderAnimDeg = 18.0f * sinf(timeSec * 2.2f);  // wave shoulders
  } else {
    shoulderAnimDeg = 0.0f;
  }
  if (motionHeadYaw) {
    headYawDeg = 25.0f * sinf(timeSec * 1.6f);  // head side-to-side
  } else {
    headYawDeg = 0.0f;
  }
  if (motionLegWalk) {
    legSwingDeg = 25.0f * sinf(timeSec * 2.0f);  // walk cycle
  } else {
    legSwingDeg = 0.0f;
  }
}

void Robot::draw(const IRenderer& r, IShader& shader) const {
    shader.use();

    glm::vec3 bodyColor(0.1f, 0.8f, 0.1f);


    // Torso
    shader.setObjColor(glm::vec3 (0.5f, 0.0f, 0.5f));
    glm::mat4 torsoM(1.0f);
    torsoM = glm::translate(torsoM, glm::vec3(0.0f, 1.0f, 0.0f));
    torsoM = glm::scale(torsoM, glm::vec3(1.0f, 1.4f, 0.5f));
    r.draw(torso, torsoM);

    // Head
    shader.setObjColor(glm::vec3 (0.3f, 0.5f, 1.0f));
    glm::mat4 headM = glm::translate(glm::mat4(1.0f),
                        glm::vec3(0.0f, 0.9f + 1.4f * 0.5f + 0.55f, 0.0f));
    headM = glm::rotate(headM, glm::radians(headYawDeg), glm::vec3(0, 1, 0));
    r.draw(headMesh, headM);

    float torsoWidth = 1.0f;
    float armAttachX = torsoWidth * 0.5f + 0.12f;
    float armY = 1.0f;
    float fullArmLen = 1.2f;
    float upperLen = fullArmLen * 0.5f;
    float lowerLen = fullArmLen * 0.5f;

    // Arms
    shader.setObjColor(bodyColor);
    {
        glm::mat4 ls(1.0f);
        ls = glm::translate(ls, glm::vec3(-armAttachX + 0.12f, armY, 0.0f));
        ls = glm::scale(ls, glm::vec3(0.25f, 0.25f, 0.25f));
        r.draw(armMesh, ls);

        glm::mat4 rs(1.0f);
        rs = glm::translate(rs, glm::vec3(armAttachX - 0.12f, armY, 0.0f));
        rs = glm::scale(rs, glm::vec3(0.25f, 0.25f, 0.25f));
        r.draw(armMesh, rs);
    }

    // Upper left arm
    shader.setObjColor(glm::vec3 (0.75f, 1.0f, 0.75f));
    float leftUpperLen = upperLen * 0.7f;
    glm::mat4 lUpper(1.0f);
    lUpper = glm::translate(lUpper, glm::vec3(-armAttachX, armY, 0.0f));
    lUpper = glm::rotate(lUpper, glm::radians(-5.0f), glm::vec3(0, 0, 1));
    lUpper = glm::rotate(lUpper, glm::radians(leftArmRot + shoulderAnimDeg), glm::vec3(1, 0, 0));
    r.draw(armMesh, lUpper);

    glm::mat4 lUpperScaled = glm::scale(lUpper, glm::vec3(1.0f, -0.7f, 1.0f));
    glm::mat4 lLower = lUpper;
    lLower = glm::translate(lLower, glm::vec3(0.0f, -leftUpperLen, 0.0f));
    lLower = glm::rotate(lLower, glm::radians(leftElbowRot), glm::vec3(1, 0, 0));
    r.draw(armMesh, lUpperScaled);

    // Upper right arm
    shader.setObjColor(glm::vec3 (0.75f, 1.0f, 0.75f));
    float rightUpperLen = upperLen * 0.7f;
    glm::mat4 rUpper(1.0f);
    rUpper = glm::translate(rUpper, glm::vec3(armAttachX, armY, 0.0f));
    rUpper = glm::rotate(rUpper, glm::radians(5.0f), glm::vec3(0, 0, 1));
    rUpper = glm::rotate(rUpper, glm::radians(rightArmRot - shoulderAnimDeg), glm::vec3(1, 0, 0));
    r.draw(armMesh, rUpper);

    glm::mat4 rUpperScaled = glm::scale(rUpper, glm::vec3(1.0f, 0.7f, 1.0f));
    glm::mat4 rLower = rUpper;
    rLower = glm::translate(rLower, glm::vec3(0.0f, -rightUpperLen, 0.0f));
    rLower = glm::rotate(rLower, glm::radians(rightElbowRot), glm::vec3(1, 0, 0));
    r.draw(armMesh, rUpperScaled);

    // Hands
    shader.setObjColor(glm::vec3 (1.0f, 1.0f, 1.0));
    {
        glm::mat4 lc = lLower;
        lc = glm::translate(lc, glm::vec3(0.0f, lowerLen * -0.5f + 0.15f * 0.5f, 0.0f));

        glm::mat4 palm = lc;
        palm = glm::rotate(palm, glm::radians(90.0f), glm::vec3(0, 0, 1));
        palm = glm::scale(palm, glm::vec3(0.25f, 0.15f, 0.25f));
        r.draw(torso, palm);

        glm::mat4 f1 = lc;
        f1 = glm::translate(f1, glm::vec3(-0.25f * 0.5f, 0.0f, 0.07f));
        f1 = glm::rotate(f1, glm::radians(90.0f), glm::vec3(0, 0, 1));
        f1 = glm::scale(f1, glm::vec3(0.25f, 0.05f, 0.05f));
        r.draw(torso, f1);

        glm::mat4 f2 = lc;
        f2 = glm::translate(f2, glm::vec3(-0.25f * 0.5f, 0.0f, -0.07f));
        f2 = glm::rotate(f2, glm::radians(90.0f), glm::vec3(0, 0, 1));
        f2 = glm::scale(f2, glm::vec3(0.25f, 0.05f, 0.05f));
        r.draw(torso, f2);
    }

    {   // right hand
    glm::mat4 rc = rLower;
    rc = glm::translate(rc, glm::vec3(0.0f, lowerLen * -0.5f + 0.15f * 0.5f, 0.0f));

    glm::mat4 palm = rc;
    palm = glm::rotate(palm, glm::radians(-90.0f), glm::vec3(0, 0, 1));  // MIRROR ROTATION
    palm = glm::scale(palm, glm::vec3(0.25f, 0.15f, 0.25f));
    r.draw(torso, palm);

    glm::mat4 f1 = rc;
    f1 = glm::translate(f1, glm::vec3(+0.25f * 0.5f, 0.0f, 0.07f));
    f1 = glm::rotate(f1, glm::radians(-90.0f), glm::vec3(0, 0, 1));     // MIRROR ROTATION
    f1 = glm::scale(f1, glm::vec3(0.25f, 0.05f, 0.05f));
    r.draw(torso, f1);

    glm::mat4 f2 = rc;
    f2 = glm::translate(f2, glm::vec3(+0.25f * 0.5f, 0.0f, -0.07f));
    f2 = glm::rotate(f2, glm::radians(-90.0f), glm::vec3(0, 0, 1));     // MIRROR ROTATION
    f2 = glm::scale(f2, glm::vec3(0.25f, 0.05f, 0.05f));
    r.draw(torso, f2);
}


    // legs
    shader.setObjColor(glm::vec3 (1.0f, 0.95f, 0.5f));
    float legHeight = 1.4f;
    float hipY = 0.1f + legHeight * 0.5f;

    glm::mat4 lLeg(1.0f);
    lLeg = glm::translate(lLeg, glm::vec3(-0.35f, hipY, 0.0f));
    lLeg = glm::rotate(lLeg, glm::radians(legSwingDeg), glm::vec3(1, 0, 0));
    lLeg = glm::translate(lLeg, glm::vec3(0.0f, -legHeight * 0.5f, 0.0f));
    r.draw(legMesh, lLeg);

    glm::mat4 rLeg(1.0f);
    rLeg = glm::translate(rLeg, glm::vec3(0.35f, hipY, 0.0f));
    rLeg = glm::rotate(rLeg, glm::radians(-legSwingDeg), glm::vec3(1, 0, 0));
    rLeg = glm::translate(rLeg, glm::vec3(0.0f, -legHeight * 0.5f, 0.0f));
    r.draw(legMesh, rLeg);

    // Feet
    shader.setObjColor(glm::vec3 (1.0f, 1.0f, 1.0f));
    {
        float footH = 0.1f;
        float footW = 0.4f;
        float footD = 0.5f;

        glm::mat4 lf = lLeg;
        lf = glm::translate(lf, glm::vec3(0.0f, -legHeight * 0.5f - 0.05f, 0.0f));
        lf = glm::scale(lf, glm::vec3(footW, footH, footD));
        r.draw(torso, lf);

        glm::mat4 rf = rLeg;
        rf = glm::translate(rf, glm::vec3(0.0f, -legHeight * 0.5f - 0.05f, 0.0f));
        rf = glm::scale(rf, glm::vec3(footW, footH, footD));
        r.draw(torso, rf);
    }

    // Eyes
    shader.setObjColor(glm::vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 leftEye = headM;
    leftEye = glm::translate(leftEye, glm::vec3(-0.19f, 0.08f, 0.45f));
    r.draw(eyeMesh, leftEye);

    glm::mat4 rightEye = headM;
    rightEye = glm::translate(rightEye, glm::vec3(0.19f, 0.08f, 0.45f));
    r.draw(eyeMesh, rightEye);

    // Mouth/smile
    shader.setObjColor(glm::vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 smile = headM;
    smile = glm::translate(smile, glm::vec3(0.0f, -0.12f, 0.47f));
    smile = glm::rotate(smile, glm::radians(180.0f), glm::vec3(0, 0, 1));
    r.draw(smileMesh, smile);
}

