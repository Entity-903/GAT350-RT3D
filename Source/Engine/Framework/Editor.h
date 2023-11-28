#pragma once

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
	};
}