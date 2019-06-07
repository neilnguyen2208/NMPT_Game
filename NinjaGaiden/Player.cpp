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

	skill = Skill::BlueShuriken;

	useitemtimeFreeze = false;
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
		playerData->state = slashState;
		break;
	case PlayerState::Crouch:
		playerData->state = crouchState;
		break;
	case PlayerState::CrouchSlash:
		playerData->state = crouchSlashState;
		break;
	case PlayerState::Climb:
		playerData->state = climbState;
		break;
	case PlayerState::UseSkill:
		playerData->state = useSkillState;
		break;
	case PlayerState::Jumping:
		playerData->state = jumpState;
		break;
	case PlayerState::Falling:
		playerData->state = jumpState;
		falling = true;
		break;
	case PlayerState::Beaten:
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
	}
	this->collisionTime = collisionTime;
	this->side = side;
}


void Player::AddItem(Entity::EntityTag tag)
{
	switch (tag)
	{
	case Entity::SpiritPoints5:

		break;
	case Entity::SpiritPoints10:

		break;
	case Entity::Scores500:

		break;
	case Entity::TimeFreeze:
		TimeFreezeSkill(true);
		break;
	case Entity::Scores1000:

		break;
	case Entity::Health:

		break;
	case Entity::ThrowingStar:
		SetSkill(Player::Skill::BlueShuriken);
		break;
	case Entity::WindmillStar:
		SetSkill(Player::Skill::RedShuriken);
		break;
	case Entity::Flames:
		SetSkill(Player::Skill::FlameRound);
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
	}
	else TimeFreezeSkill(false);
}
