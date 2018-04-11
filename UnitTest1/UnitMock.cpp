#include "stdafx.h"
#include "UnitMock.h"
#include "../ExampleAIModule/Source/BuildingManager.h"
#include "../ExampleAIModule/Source/UnitManager.h"

UnitMock::UnitMock()
{
	
}


UnitMock::~UnitMock()
{
}

int UnitMock::getID() const
{
	return 0;
}

bool UnitMock::exists() const
{
	return false;
}

int UnitMock::getReplayID() const
{
	return 0;
}

BWAPI::Player UnitMock::getPlayer() const
{
	return BWAPI::Player();
}

BWAPI::UnitType UnitMock::getType() const
{
	return BWAPI::UnitType();
}

BWAPI::Position UnitMock::getPosition() const
{
	return BWAPI::Position(1,1);
}

double UnitMock::getAngle() const
{
	return 0.0;
}

double UnitMock::getVelocityX() const
{
	return 0.0;
}

double UnitMock::getVelocityY() const
{
	return 0.0;
}

int UnitMock::getHitPoints() const
{
	return 0;
}

int UnitMock::getShields() const
{
	return 0;
}

int UnitMock::getEnergy() const
{
	return 0;
}

int UnitMock::getResources() const
{
	return 0;
}

int UnitMock::getResourceGroup() const
{
	return 0;
}

int UnitMock::getLastCommandFrame() const
{
	return 0;
}

BWAPI::UnitCommand UnitMock::getLastCommand() const
{
	return BWAPI::UnitCommand();
}

BWAPI::Player UnitMock::getLastAttackingPlayer() const
{
	return BWAPI::Player();
}

BWAPI::UnitType UnitMock::getInitialType() const
{
	return BWAPI::UnitType();
}

BWAPI::Position UnitMock::getInitialPosition() const
{
	return BWAPI::Position();
}

BWAPI::TilePosition UnitMock::getInitialTilePosition() const
{
	return BWAPI::TilePosition();
}

int UnitMock::getInitialHitPoints() const
{
	return 0;
}

int UnitMock::getInitialResources() const
{
	return 0;
}

int UnitMock::getKillCount() const
{
	return 0;
}

int UnitMock::getAcidSporeCount() const
{
	return 0;
}

int UnitMock::getInterceptorCount() const
{
	return 0;
}

int UnitMock::getScarabCount() const
{
	return 0;
}

int UnitMock::getSpiderMineCount() const
{
	return 0;
}

int UnitMock::getGroundWeaponCooldown() const
{
	return 0;
}

int UnitMock::getAirWeaponCooldown() const
{
	return 0;
}

int UnitMock::getSpellCooldown() const
{
	return 0;
}

int UnitMock::getDefenseMatrixPoints() const
{
	return 0;
}

int UnitMock::getDefenseMatrixTimer() const
{
	return 0;
}

int UnitMock::getEnsnareTimer() const
{
	return 0;
}

int UnitMock::getIrradiateTimer() const
{
	return 0;
}

int UnitMock::getLockdownTimer() const
{
	return 0;
}

int UnitMock::getMaelstromTimer() const
{
	return 0;
}

int UnitMock::getOrderTimer() const
{
	return 0;
}

int UnitMock::getPlagueTimer() const
{
	return 0;
}

int UnitMock::getRemoveTimer() const
{
	return 0;
}

int UnitMock::getStasisTimer() const
{
	return 0;
}

int UnitMock::getStimTimer() const
{
	return 0;
}

BWAPI::UnitType UnitMock::getBuildType() const
{
	return BWAPI::UnitType();
}

BWAPI::UnitType::list UnitMock::getTrainingQueue() const
{
	return BWAPI::UnitType::list();
}

BWAPI::TechType UnitMock::getTech() const
{
	return BWAPI::TechType();
}

BWAPI::UpgradeType UnitMock::getUpgrade() const
{
	return BWAPI::UpgradeType();
}

int UnitMock::getRemainingBuildTime() const
{
	return 0;
}

int UnitMock::getRemainingTrainTime() const
{
	return 0;
}

int UnitMock::getRemainingResearchTime() const
{
	return 0;
}

int UnitMock::getRemainingUpgradeTime() const
{
	return 0;
}

BWAPI::Unit UnitMock::getBuildUnit() const
{
	return BWAPI::Unit();
}

BWAPI::Unit UnitMock::getTarget() const
{
	return BWAPI::Unit();
}

BWAPI::Position UnitMock::getTargetPosition() const
{
	return BWAPI::Position();
}

BWAPI::Order UnitMock::getOrder() const
{
	return BWAPI::Order();
}

BWAPI::Order UnitMock::getSecondaryOrder() const
{
	return BWAPI::Order();
}

BWAPI::Unit UnitMock::getOrderTarget() const
{
	return BWAPI::Unit();
}

BWAPI::Position UnitMock::getOrderTargetPosition() const
{
	return BWAPI::Position();
}

BWAPI::Position UnitMock::getRallyPosition() const
{
	return BWAPI::Position();
}

BWAPI::Unit UnitMock::getRallyUnit() const
{
	return BWAPI::Unit();
}

BWAPI::Unit UnitMock::getAddon() const
{
	return BWAPI::Unit();
}

BWAPI::Unit UnitMock::getNydusExit() const
{
	return BWAPI::Unit();
}

BWAPI::Unit UnitMock::getPowerUp() const
{
	return BWAPI::Unit();
}

BWAPI::Unit UnitMock::getTransport() const
{
	return BWAPI::Unit();
}

BWAPI::Unitset UnitMock::getLoadedUnits() const
{
	return BWAPI::Unitset();
}

BWAPI::Unit UnitMock::getCarrier() const
{
	return BWAPI::Unit();
}

BWAPI::Unitset UnitMock::getInterceptors() const
{
	return BWAPI::Unitset();
}

BWAPI::Unit UnitMock::getHatchery() const
{
	return BWAPI::Unit();
}

BWAPI::Unitset UnitMock::getLarva() const
{
	return BWAPI::Unitset();
}

bool UnitMock::hasNuke() const
{
	return false;
}

bool UnitMock::isAccelerating() const
{
	return false;
}

bool UnitMock::isAttacking() const
{
	return false;
}

bool UnitMock::isAttackFrame() const
{
	return false;
}

bool UnitMock::isBeingGathered() const
{
	return false;
}

bool UnitMock::isBeingHealed() const
{
	return false;
}

bool UnitMock::isBlind() const
{
	return false;
}

bool UnitMock::isBraking() const
{
	return false;
}

bool UnitMock::isBurrowed() const
{
	return false;
}

bool UnitMock::isCarryingGas() const
{
	return false;
}

bool UnitMock::isCarryingMinerals() const
{
	return false;
}

bool UnitMock::isCloaked() const
{
	return false;
}

bool UnitMock::isCompleted() const
{
	return false;
}

bool UnitMock::isConstructing() const
{
	return false;
}

bool UnitMock::isDetected() const
{
	return false;
}

bool UnitMock::isGatheringGas() const
{
	return false;
}

bool UnitMock::isGatheringMinerals() const
{
	return false;
}

bool UnitMock::isHallucination() const
{
	return false;
}

bool UnitMock::isIdle() const
{
	return false;
}

bool UnitMock::isInterruptible() const
{
	return false;
}

bool UnitMock::isInvincible() const
{
	return false;
}

bool UnitMock::isLifted() const
{
	return false;
}

bool UnitMock::isMorphing() const
{
	return false;
}

bool UnitMock::isMoving() const
{
	return false;
}

bool UnitMock::isParasited() const
{
	return false;
}

bool UnitMock::isSelected() const
{
	return false;
}

bool UnitMock::isStartingAttack() const
{
	return false;
}

bool UnitMock::isStuck() const
{
	return false;
}

bool UnitMock::isTraining() const
{
	return false;
}

bool UnitMock::isUnderAttack() const
{
	return false;
}

bool UnitMock::isUnderDarkSwarm() const
{
	return false;
}

bool UnitMock::isUnderDisruptionWeb() const
{
	return false;
}

bool UnitMock::isUnderStorm() const
{
	return false;
}

bool UnitMock::isPowered() const
{
	return false;
}

bool UnitMock::isVisible(BWAPI::Player player) const
{
	return false;
}

bool UnitMock::isTargetable() const
{
	return false;
}

bool UnitMock::issueCommand(BWAPI::UnitCommand command)
{
	return false;
}

bool UnitMock::canIssueCommand(BWAPI::UnitCommand command, bool checkCanUseTechPositionOnPositions, bool checkCanUseTechUnitOnUnits, bool checkCanBuildUnitType, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canIssueCommandGrouped(BWAPI::UnitCommand command, bool checkCanUseTechPositionOnPositions, bool checkCanUseTechUnitOnUnits, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canCommand() const
{
	return false;
}

bool UnitMock::canCommandGrouped(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canIssueCommandType(BWAPI::UnitCommandType ct, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canIssueCommandTypeGrouped(BWAPI::UnitCommandType ct, bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canTargetUnit(BWAPI::Unit targetUnit, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canAttack(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canAttack(BWAPI::Position target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canAttack(BWAPI::Unit target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canAttackGrouped(bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canAttackGrouped(BWAPI::Position target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canAttackGrouped(BWAPI::Unit target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canAttackMove(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canAttackMoveGrouped(bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canAttackUnit(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canAttackUnit(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canAttackUnitGrouped(bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canAttackUnitGrouped(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canBuild(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canBuild(BWAPI::UnitType uType, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canBuild(BWAPI::UnitType uType, BWAPI::TilePosition tilePos, bool checkTargetUnitType, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canBuildAddon(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canBuildAddon(BWAPI::UnitType uType, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canTrain(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canTrain(BWAPI::UnitType uType, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canMorph(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canMorph(BWAPI::UnitType uType, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canResearch(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canResearch(BWAPI::TechType type, bool checkCanIssueCommandType) const
{
	return false;
}

bool UnitMock::canUpgrade(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canUpgrade(BWAPI::UpgradeType type, bool checkCanIssueCommandType) const
{
	return false;
}

bool UnitMock::canSetRallyPoint(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canSetRallyPoint(BWAPI::Position target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canSetRallyPoint(BWAPI::Unit target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canSetRallyPosition(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canSetRallyUnit(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canSetRallyUnit(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canMove(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canMoveGrouped(bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canPatrol(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canPatrolGrouped(bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canFollow(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canFollow(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canGather(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canGather(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canReturnCargo(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canHoldPosition(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canStop(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canRepair(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canRepair(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canBurrow(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canUnburrow(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canCloak(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canDecloak(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canSiege(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canUnsiege(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canLift(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canLand(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canLand(BWAPI::TilePosition target, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canLoad(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canLoad(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canUnloadWithOrWithoutTarget(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canUnloadAtPosition(BWAPI::Position targDropPos, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canUnload(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canUnload(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkPosition, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canUnloadAll(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canUnloadAllPosition(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canUnloadAllPosition(BWAPI::Position targDropPos, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canRightClick(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canRightClick(BWAPI::Position target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canRightClick(BWAPI::Unit target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canRightClickGrouped(bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canRightClickGrouped(BWAPI::Position target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canRightClickGrouped(BWAPI::Unit target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canRightClickPosition(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canRightClickPositionGrouped(bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canRightClickUnit(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canRightClickUnit(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canRightClickUnitGrouped(bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canRightClickUnitGrouped(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canHaltConstruction(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canCancelConstruction(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canCancelAddon(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canCancelTrain(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canCancelTrainSlot(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canCancelTrainSlot(int slot, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canCancelMorph(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canCancelResearch(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canCancelUpgrade(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canUseTechWithOrWithoutTarget(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canUseTechWithOrWithoutTarget(BWAPI::TechType tech, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canUseTech(BWAPI::TechType tech, BWAPI::Position target, bool checkCanTargetUnit, bool checkTargetsType, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canUseTech(BWAPI::TechType tech, BWAPI::Unit target, bool checkCanTargetUnit, bool checkTargetsType, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canUseTechWithoutTarget(BWAPI::TechType tech, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canUseTechUnit(BWAPI::TechType tech, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canUseTechUnit(BWAPI::TechType tech, BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkTargetsUnits, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canUseTechPosition(BWAPI::TechType tech, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canUseTechPosition(BWAPI::TechType tech, BWAPI::Position target, bool checkTargetsPositions, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canPlaceCOP(bool checkCommandibility) const
{
	return false;
}

bool UnitMock::canPlaceCOP(BWAPI::TilePosition target, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}


