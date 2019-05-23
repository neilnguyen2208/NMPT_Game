#include "SceneManager.h"

SceneManager *SceneManager::instance = NULL;

SceneManager * SceneManager::GetInstance() {
	if (instance == NULL)
		instance = new SceneManager();
	return instance;
}

void SceneManager::CreateScene(Scene * scene) {
	if (scene) {
		if (CurrentScene)
			delete CurrentScene;
		CurrentScene = scene;
	}
}

Scene * SceneManager::GetCurrentScene() {
	return CurrentScene;
}
