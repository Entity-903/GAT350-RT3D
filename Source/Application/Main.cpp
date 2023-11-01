#include "World05.h"
#include "Core/Core.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

using namespace std;

int main(int argc, char* argv[])
{

	cout << nc::StringUtils::ToUpper("beam me up") << "\n";
	cout << nc::StringUtils::ToLower("SEND ME DOWN") << "\n";
	cout << nc::StringUtils::IsEqualIgnoreCase("DiGiTaL hAlLuCiNaTiOnS", "dIgItAl HaLlUcInAtIoNs") << "\n";
	cout << nc::StringUtils::CreateUnique("Entity") << "\n";
	cout << nc::StringUtils::CreateUnique("Entity") << "\n";
	cout << nc::StringUtils::CreateUnique("Entity") << "\n";

	INFO_LOG("Initialize Engine...")

	//nc::MemoryTracker::Initialize();
	nc::seedRandom((unsigned int)time(nullptr));
	nc::setFilePath("assets");

	ENGINE.Initialize();

	auto world = make_unique<nc::World05>();
	world->Initialize();

	

	// main loop
	bool quit = false;
	while (!quit)
	{
		// update
		ENGINE.Update();
		quit = ENGINE.IsQuit();

		world->Update(ENGINE.GetTime().GetDeltaTime());

		// draw
		world->Draw(*ENGINE.GetSystem<nc::Renderer>());
	}

	world->Shutdown();
	ENGINE.Shutdown();

	return 0;
}
