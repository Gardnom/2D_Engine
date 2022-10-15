#include "EngineCore.h"

FAILABLE_PROCEDURE EngineCore::Init() {
	m_Z0 = (RESOLUTION_X / 2.0) / glm::tan((FIELD_OF_VIEW / 2.0) * PI / 180.0);
	return { true, "" };
}

glm::vec3 EngineCore::ApplyTranslation(const glm::vec3& original, glm::vec3& translation) {
	return original + translation;
}
glm::vec3 EngineCore::ApplyPerspective(const glm::vec3& original) {
	glm::vec3 result;
	result.x = original.x * m_Z0 / (m_Z0 + original.z);
	result.y = original.y * m_Z0 / (m_Z0 + original.z);
	result.z = original.z;

	return result;
}

glm::vec3 EngineCore::CenterScreen(const glm::vec3 original) {
	return glm::vec3(original.x + RESOLUTION_X / 2, original.y + RESOLUTION_Y / 2, original.z);
}
