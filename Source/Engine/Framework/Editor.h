#pragma once

#include "Core/StringUtils.h"

namespace nc
{
	class Editor
	{
	public:
		void Update();

		void ProcessGui(class Scene* scene);

	private:
		bool active = true;
		class Object* m_selected = nullptr;
		class Object* m_rename = nullptr;
	};
}