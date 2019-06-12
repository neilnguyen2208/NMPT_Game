#pragma once
#include "PlayScene.h"


class SceneManager {
public:
	static SceneManager *GetInstance();
	void CreateScene(PlayScene *scene);
//	void CreateSceneWithTransition(Scene *scenedest, TransitionEffect *effect);
//	void UpdateWithEffect(double dt);
	bool isSceneTransitioning() {
		return isTransitioning;
	}
//	void OnFinishTransition();

	PlayScene* GetCurrentScene();
	PlayScene* GetNextScene();
private:
	static SceneManager *instance;
	PlayScene *curScene;
	PlayScene *desScene;
	static bool isTransitioning;
};