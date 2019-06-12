#include "Player.h"
#include "PlayerRunningState.h"
#include "PlayerIdleState.h"
#include "PlayerSlashState.h"
#include "PlayerCrouchState.h"
#include "PlayerCrouchSlashState.h"
#include "PlayerJumpingState.h"
#include "PlayerClimbState.h"
#include "PlayerUseSkillState.h"
#include "PlayerBeatenState.h"


Player* Player::instance = NULL;

Player * Player::GetInstance() {
	if (instance == NULL)
		instance = new Player();
	return instance;
}

Player::Player() : Entity() {
	instance = this;
	Textures *textures = Textures::GetInstance();
	textures->Add(TEX_PLAYER, "Resources/Sprites/SpriteNinja.png", D3DCOLOR_XRGB(254, 163, 176));

	playerData = new PlayerData();
	playerData->player = this;

	idleState = new PlayerIdleState(playerData);
	runningState = new PlayerRunningState(playerData);
	slashState = new PlayerSlashState(playerData);
	crouchState = new PlayerCrouchState(playerData);
	crouchSlashState = new PlayerCrouchSlashState(playerData);
	jumpState = new PlayerJumpingState(playerData);
	climbState = new PlayerClimbState(playerData);
	useSkillState = new PlayerUseSkillState(playerData);
	beatenState = new PlayerBeatenState(playerData);

	SetState(PlayerState::Idle);
	SetTag(Entity::EntityTag::Player);
	SetType(Entity::EntityType::PlayerType);
	SetAliveState(Entity::EntityAliveState::Alive);

	D3DSURFACE_DESC desc;
	textures->Get(TEX_PLAYER)->GetLevelDesc(0, &desc);
	width = desc.Width / 4;
	height = desc.Height / 10;

	isActive = true;
	isRenderLastFrame = true;
	isHurting = false;

	skill = Skill::NoneSkill;

	useitemtimeFreeze = false;
	score = 0;
	power = 0;
	blood = 16;
	fate = 2;
	skillnumer= 0;

	enemyAttack = Entity::EntityTag::None;
}

Player::~Player() {
}

void Player::Update(double dt) {
	auto vely = velocity;

	if (playerData->state)
		playerData->state->Update(dt);

	if ((position.x + collider.left) + velocity.x * dt >= 16)
		Entity::Update(dt);

	BoxCollider exPlayer = BoxCollider(GetPosition(), GetWidth(), GetBigHeight());


	if (!isHurting)
	{
		if ((side == Left && velocity.x < 0) || (side == Right && velocity.x > 0))
			velocity.x = 0;
		if ((side == Bottom && velocity.y < 0))
			velocity.y = 0;
	}
	side = NotKnow;


	if (isHurting)
	{
		HurtingTime += dt;
		AddVy(-10);
		isRenderLastFrame = false;
		aliveState = Entity::Beaten;
	}
	if (HurtingTime >= PLAYER_MAX_HURTING_TIME)
	{
		playerData->player->SetState(PlayerState::Idle);
		isHurting = false;
		onAir = false;
		HurtingTime = 0;
		isHurtingAnimation = true;
		aliveState = Entity::Alive;
		AddBlood(enemyAttack);
		enemyAttack = Entity::EntityTag::None;
		/*if (blood <= 0)
			(ExternalDataCollector::GetInstance()->SetPlayerDead(true));*/
	}
}

void Player::Render() {
	if (isHurtingAnimation &&  timeHurtingAnimation <= PLAYER_HURTING_TIME_ANIMATION)
	{
		if (!isRenderLastFrame)
		{
			isRenderLastFrame = true;
		}
		else
		{
			playerData->state->Render();
			isRenderLastFrame = false;
		}
		timeHurtingAnimation++;
	}
	else
	{
		playerData->state->Render();
		timeHurtingAnimation = 0;
		isHurtingAnimation = false;
	}

}

void Player::SetState(PlayerState::State name, int dummy) {
	bool falling = false;

	switch (name) {
	case PlayerState::Running:
		playerData->state = runningState;
		break;
	case PlayerState::Idle:
		playerData->state = idleState;
		break;
	case PlayerState::Slash:
		CSoundChoose::GetInstance()->PlaySoundChoose(7); //âm thanh khi ninja chém 
		playerData->state = slashState;
		break;
	case PlayerState::Crouch:
		playerData->state = crouchState;
		break;
	case PlayerState::CrouchSlash:
		CSoundChoose::GetInstance()->PlaySoundChoose(7); //âm thanh khi ninja chém 
		playerData->state = crouchSlashState;
		break;
	case PlayerState::Climb:
		playerData->state = climbState;
		break;
	case PlayerState::UseSkill:
		playerData->state = useSkillState;
		break;
	case PlayerState::Jumping:
		CSoundChoose::GetInstance()->PlaySoundChoose(8); //âm thanh khi ninja nhảy 
		playerData->state = jumpState;
		break;
	case PlayerState::Falling:
		playerData->state = jumpState;
		falling = true;
		break;
	case PlayerState::Beaten:
		CSoundChoose::GetInstance()->PlaySoundChoose(6); //âm thanh khi ninja bị thương 
		playerData->state = beatenState;
		break;
	}
	currentState = playerData->state->GetState();

	playerData->state->ResetState(dummy);

}

void Player::OnCollision(Entity * impactor, Entity::SideCollision side, float collisionTime) {
	if (impactor->GetTag() == CamRect)
		return;	
	playerData->state->OnCollision(impactor, side);
	if (!isHurting)
	{
		if (side == Bottom && velocity.y < 0) {
			velocity.y *= collisionTime;
		}
		else if ((side == Right && velocity.x > 0) || (side == Left && velocity.x < 0))
			velocity.x *= collisionTime;
	};
	enemyAttack = impactor->GetTag();
	this->collisionTime = collisionTime;
	this->side = side;
}


void Player::AddItem(Entity::EntityTag tag)
{
	switch (tag)
	{
	case Entity::SpiritPoints5:
		power += 5;
		break;
	case Entity::SpiritPoints10:
		power += 10;
		break;
	case Entity::Scores500:
		score += 500;
		break;
	case Entity::TimeFreeze:
		TimeFreezeSkill(true);
		break;
	case Entity::Scores1000:
		score += 1000;
		break;
	case Entity::Health:
		blood += 5;
		break;
	case Entity::ThrowingStar:
		SetSkill(Player::Skill::BlueShurikenSkill);
		skillnumer = 1;
		break;
	case Entity::WindmillStar:
		SetSkill(Player::Skill::RedShurikenSkill);
		skillnumer = 2;
		break;
	case Entity::Flames:
		SetSkill(Player::Skill::FlameWheelSkill);
		skillnumer = 3;
		break;
	}
}

BoxCollider Player::GetRect() {
	BoxCollider r;
	r.top = position.y + collider.top;
	r.left = position.x + collider.left;
	r.right = position.x + collider.right;
	r.bottom = position.y + collider.bottom;
	return r;
}

BoxCollider Player::GetBigBound() {
	BoxCollider r;
	r.top = position.y + height / 2;
	r.left = position.x - width / 2;
	r.bottom = position.y - height / 2;
	r.right = position.x + width / 2;
	return r;
}

PlayerState::State Player::GetState() {
	return playerData->state->GetState();
}

int Player::GetBigWidth() {
	return Entity::GetWidth();
}

int Player::GetBigHeight() {
	return Entity::GetHeight();
}

float Player::GetWidth() {
	return collider.right - collider.left;
}

float Player::GetHeight() {
	return collider.top - collider.bottom;
}

void Player::OnFalling() {
	onAir = true;
	SetState(PlayerState::Falling);
}

void Player::SetColliderTop(int top) {
	collider.top = top;
}

void Player::SetColliderLeft(int left) {
	collider.left = left;
	collider.right = -left;
}

void Player::SetColliderBottom(int bottom) {
	collider.bottom = bottom;
}

void Player::SetColliderRight(int right) {
	collider.right = right;
}

BoxCollider Player::GetCollider() {
	return collider;
}

void Player::HandleInput() {
	if (this->playerData->state)
		playerData->state->HandleInput();
}

void Player::SetSkill(Skill skill)
{
	this->skill = skill;
}

Player::Skill Player::GetSkill()
{
	return skill;
}

void Player::AddScore(Entity::EntityTag tag)
{
	switch (tag)
	{
	case Entity::Sparta:
		score += 100;
		break;
	case Entity::Cat:
		score += 200;
		break;
	case Entity::Soldier:
		score += 200;
		break;
	case Entity::Cannoner:
		score += 200;
		break;
	case Entity::Eagle:
		score += 300;
		break;
	case Entity::Thrower:
		score += 300;
		break;
	case Entity::Runner:
		score += 300;
		break;
	}
}

void Player::AddBlood(Entity::EntityTag tag)
{
	switch (tag)
	{
	case Entity::Sparta:
		blood--;
		break;
	case Entity::Cat:
		blood--;
		break;
	case Entity::Soldier:
		blood--;
		break;
	case Entity::SoldierBullet:
		blood--;
		break;
	case Entity::Eagle:
		blood -= 3;
		break;
	case Entity::Thrower:
		blood--;
		break;
	case Entity::ThrowerBullet:
		blood--;
		break;
	case Entity::Runner:
		blood--;
		break;
	case Entity::Cannoner:
		blood--;
		break;
	case Entity::CannonerBullet:
		blood -= 2;
		break;
	}
}

void Player::TimeFreezeSkill(bool skill)
{
	if (skill)
	{
		useitemtimeFreeze = true;
	}
	else {
		timeFreeze = 0;
		useitemtimeFreeze = false;
	}
}

void Player::checkTimeFreezeSkill()
{
	if (timeFreeze < ANIMATION_ITEM_TIMEFREEZE && useitemtimeFreeze == true)
	{
		timeFreeze++;
		if (timeFreeze % 50 == 0)
			CSoundChoose::GetInstance()->PlaySoundChoose(11); //âm thanh sử dụng SkillTimeFreeze 
	}
	else TimeFreezeSkill(false);
}

void Player::Reset()
{
	delete instance;
	instance = NULL;
}
