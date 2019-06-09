#include "RunnerFollowState.h"
#include "Enemy.h"
#include"Grid.h"
RunnerFollowState::RunnerFollowState(EnemyData *data) : EnemyState(data) {
	auto textures = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 texture = textures->Get(TEX_RUNNER);
	m_Animation = new Animation();
	m_Animation->AddFrames(texture, 1, 2, RUNNER_FRAME * (1/60.0f));
	m_AnimationJumping = new Animation();
	m_AnimationJumping->AddFramesA(texture, 1, 1,1,1,2, RUNNER_FRAME * (1 / 60.0f));
	isJump = false;
}

RunnerFollowState::~RunnerFollowState() {
}

void RunnerFollowState::ResetState() {

	auto enemy = enemyData->enemy;
	auto enemyX = enemy->GetPosition().x;
	auto playerX = Player::GetInstance()->GetPosition().x;

	if (playerX > enemyX)
		enemy->SetVx(RUNNER_SPEED);
	else
		enemy->SetVx(-RUNNER_SPEED);

	enemy->SetColliderTop(16);
	enemy->SetColliderBottom(-16);
	enemy->SetColliderLeft(-8);
	enemy->SetColliderRight(8);

	enemy->offsetScaleX = enemy->GetBigWidth() - enemy->GetWidth();

	EnemyState::ResetState();
}

void RunnerFollowState::Update(double dt) {

	vector<Entity*> staticObjects = Grid::GetInstance(BoxCollider(224,0,0,2048))->staticObject;
	auto side = Entity::SideCollision::NotKnow;
	
	for (int i = 0; i < staticObjects.size(); i++)
	{
		bool onGround = false;
		float collisionTime = CollisionDetector::SweptAABB(enemyData->enemy, staticObjects[i], side, dt);
		if (collisionTime == 2)
			continue;
		enemyData->enemy->OnCollision(staticObjects[i], side, collisionTime);
		if (side == Entity::Bottom) {
				onGround = true;
		}
		if (onGround)
		{
			if ((enemyData->enemy->GetMoveDirection() == Entity::LeftToRight&&enemyData->enemy->GetRect().right > staticObjects[i]->GetRect().right - 10*ENEMY_OFFSET_BORDER)
				|| (enemyData->enemy->GetMoveDirection() == Entity::RightToLeft&&enemyData->enemy->GetRect().left < staticObjects[i]->GetRect().left + 10*ENEMY_OFFSET_BORDER))
			{
				enemyData->enemy->SetVy(RUNNER_JUMP_SPEED);
				isJump = true;
				break;
			}
			isJump = false;
		}
	}
	
	m_Animation->Update(dt);
}

void RunnerFollowState::Render()
{
	if (isJump)
	{
		m_AnimationJumping->Render(enemyData->enemy->GetPosition(), BoxCollider(), D3DCOLOR_XRGB(255, 255, 255), enemyData->enemy->GetMoveDirection() == Entity::EntityDirection::RightToLeft);
	}
	else
	{
		EnemyState::Render();
	}
}