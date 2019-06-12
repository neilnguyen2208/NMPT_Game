#include "SceneManager.h"

SceneManager *SceneManager::instance = NULL;
bool SceneManager::isTransitioning = false;

SceneManager * SceneManager::GetInstance() {
	if (instance == NULL)
		instance = new SceneManager();
	return instance;
}

void SceneManager::CreateScene(PlayScene * scene) {
	if (scene) {
		if (curScene)
			delete curScene;
		curScene = scene;
	}
}

PlayScene * SceneManager::GetCurrentScene() {
	return curScene;
}

PlayScene * SceneManager::GetNextScene()
{
	return desScene;
}
