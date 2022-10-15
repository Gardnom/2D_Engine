#pragma once
#include "glm/glm.hpp"
#include "CoreTypes.h"
#include "Settings.h"

class EngineCore {
public:
	FAILABLE_PROCEDURE Init();
	glm::vec3 ApplyTranslation(const glm::vec3& original, glm::vec3& translation);
	glm::vec3 ApplyPerspective(const glm::vec3& original);
	glm::vec3 CenterScreen(const glm::vec3 original);
private:
	f32 m_Z0;
};