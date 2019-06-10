#pragma once
#include "Scene.h"


class SceneManager {
public:
	static SceneManager *GetInstance();
	void CreateScene(Scene *scene);
	//void CreateSceneWithTransition();
	//void CreateSceneWithRandomTransition();
	//void UpdateWithEffect();
	/*bool isSceneTransitioning() {
		return isTransitioning;
	}*/
	Scene* GetCurrentScene();
private:
	static SceneManager *instance;
	Scene *CurrentScene;
	Scene *DestScene;
	bool isTransitioning;

};