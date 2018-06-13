#include "stdafx.h"
#include "VultureUnitMock.h"
#include "../ExampleAIModule/Source/BuildingManager.h"
#include "../ExampleAIModule/Source/UnitManager.h"

VultureUnitMock::VultureUnitMock() : BWAPI::UnitInterface()
{
}


VultureUnitMock::~VultureUnitMock()
{
}

int VultureUnitMock::getID() const
{
	return 0;
}

int VultureUnitMock::getDistance(BWAPI::Position target) const
{
	return 0;
}

bool VultureUnitMock::exists() const
{
	return true;
}

int VultureUnitMock::getReplayID() const
{
	return 0;
}

BWAPI::Player VultureUnitMock::getPlayer() const
{
	return BWAPI::Player();
}

BWAPI::UnitType VultureUnitMock::getType() const
{
	return BWAPI::UnitTypes::Terran_Vulture; 
;
}

BWAPI::Position VultureUnitMock::getPosition() const
{
	return Position(564,927); 
}

double VultureUnitMock::getAngle() const
{
	return 0.0;
}

double VultureUnitMock::getVelocityX() const
{
	return 0.0;
}

double VultureUnitMock::getVelocityY() const
{
	return 0.0;
}

int VultureUnitMock::getHitPoints() const
{
	return 0;
}

int VultureUnitMock::getShields() const
{
	return 0;
}

int VultureUnitMock::getEnergy() const
{
	return 0;
}

int VultureUnitMock::getResources() const
{
	return 0;
}

int VultureUnitMock::getResourceGroup() const
{
	return 0;
}

int VultureUnitMock::getLastCommandFrame() const
{
	return 0;
}

BWAPI::UnitCommand VultureUnitMock::getLastCommand() const
{
	return BWAPI::UnitCommand();
}

BWAPI::Player VultureUnitMock::getLastAttackingPlayer() const
{
	return BWAPI::Player();
}

BWAPI::UnitType VultureUnitMock::getInitialType() const
{
	return BWAPI::UnitType();
}

BWAPI::Position VultureUnitMock::getInitialPosition() const
{
	return BWAPI::Position();
}

BWAPI::TilePosition VultureUnitMock::getInitialTilePosition() const
{
	return BWAPI::TilePosition();
}

int VultureUnitMock::getInitialHitPoints() const
{
	return 0;
}

int VultureUnitMock::getInitialResources() const
{
	return 0;
}

int VultureUnitMock::getKillCount() const
{
	return 0;
}

int VultureUnitMock::getAcidSporeCount() const
{
	return 0;
}

int VultureUnitMock::getInterceptorCount() const
{
	return 0;
}

int VultureUnitMock::getScarabCount() const
{
	return 0;
}

int VultureUnitMock::getSpiderMineCount() const
{
	return 0;
}

int VultureUnitMock::getGroundWeaponCooldown() const
{
	return 0;
}

int VultureUnitMock::getAirWeaponCooldown() const
{
	return 0;
}

int VultureUnitMock::getSpellCooldown() const
{
	return 0;
}

int VultureUnitMock::getDefenseMatrixPoints() const
{
	return 0;
}

int VultureUnitMock::getDefenseMatrixTimer() const
{
	return 0;
}

int VultureUnitMock::getEnsnareTimer() const
{
	return 0;
}

int VultureUnitMock::getIrradiateTimer() const
{
	return 0;
}

int VultureUnitMock::getLockdownTimer() const
{
	return 0;
}

int VultureUnitMock::getMaelstromTimer() const
{
	return 0;
}

int VultureUnitMock::getOrderTimer() const
{
	return 0;
}

int VultureUnitMock::getPlagueTimer() const
{
	return 0;
}

int VultureUnitMock::getRemoveTimer() const
{
	return 0;
}

int VultureUnitMock::getStasisTimer() const
{
	return 0;
}

int VultureUnitMock::getStimTimer() const
{
	return 0;
}

BWAPI::UnitType VultureUnitMock::getBuildType() const
{
	return BWAPI::UnitType();
}

BWAPI::UnitType::list VultureUnitMock::getTrainingQueue() const
{
	return BWAPI::UnitType::list();
}

BWAPI::TechType VultureUnitMock::getTech() const
{
	return BWAPI::TechType();
}

BWAPI::UpgradeType VultureUnitMock::getUpgrade() const
{
	return BWAPI::UpgradeType();
}

int VultureUnitMock::getRemainingBuildTime() const
{
	return 0;
}

int VultureUnitMock::getRemainingTrainTime() const
{
	return 0;
}

int VultureUnitMock::getRemainingResearchTime() const
{
	return 0;
}

int VultureUnitMock::getRemainingUpgradeTime() const
{
	return 0;
}

BWAPI::Unit VultureUnitMock::getBuildUnit() const
{
	return BWAPI::Unit();
}

BWAPI::Unit VultureUnitMock::getTarget() const
{
	return BWAPI::Unit();
}

BWAPI::Position VultureUnitMock::getTargetPosition() const
{
	return BWAPI::Position();
}

BWAPI::Order VultureUnitMock::getOrder() const
{
	return BWAPI::Order();
}

BWAPI::Order VultureUnitMock::getSecondaryOrder() const
{
	return BWAPI::Order();
}

BWAPI::Unit VultureUnitMock::getOrderTarget() const
{
	return BWAPI::Unit();
}

BWAPI::Position VultureUnitMock::getOrderTargetPosition() const
{
	return BWAPI::Position();
}

BWAPI::Position VultureUnitMock::getRallyPosition() const
{
	return BWAPI::Position();
}

BWAPI::Unit VultureUnitMock::getRallyUnit() const
{
	return BWAPI::Unit();
}

BWAPI::Unit VultureUnitMock::getAddon() const
{
	return BWAPI::Unit();
}

BWAPI::Unit VultureUnitMock::getNydusExit() const
{
	return BWAPI::Unit();
}

BWAPI::Unit VultureUnitMock::getPowerUp() const
{
	return BWAPI::Unit();
}

BWAPI::Unit VultureUnitMock::getTransport() const
{
	return BWAPI::Unit();
}

BWAPI::Unitset VultureUnitMock::getLoadedUnits() const
{
	return BWAPI::Unitset();
}

BWAPI::Unit VultureUnitMock::getCarrier() const
{
	return BWAPI::Unit();
}

BWAPI::Unitset VultureUnitMock::getInterceptors() const
{
	return BWAPI::Unitset();
}

BWAPI::Unit VultureUnitMock::getHatchery() const
{
	return BWAPI::Unit();
}

BWAPI::Unitset VultureUnitMock::getLarva() const
{
	return BWAPI::Unitset();
}

bool VultureUnitMock::hasNuke() const
{
	return false;
}

bool VultureUnitMock::isAccelerating() const
{
	return false;
}

bool VultureUnitMock::isAttacking() const
{
	return false;
}

bool VultureUnitMock::isAttackFrame() const
{
	return false;
}

bool VultureUnitMock::isBeingGathered() const
{
	return false;
}

bool VultureUnitMock::isBeingHealed() const
{
	return false;
}

bool VultureUnitMock::isBlind() const
{
	return false;
}

bool VultureUnitMock::isBraking() const
{
	return false;
}

bool VultureUnitMock::isBurrowed() const
{
	return false;
}

bool VultureUnitMock::isCarryingGas() const
{
	return false;
}

bool VultureUnitMock::isCarryingMinerals() const
{
	return false;
}

bool VultureUnitMock::isCloaked() const
{
	return false;
}

bool VultureUnitMock::isCompleted() const
{
	return false;
}

bool VultureUnitMock::isConstructing() const
{
	return false;
}

bool VultureUnitMock::isDetected() const
{
	return false;
}

bool VultureUnitMock::isGatheringGas() const
{
	return false;
}

bool VultureUnitMock::isGatheringMinerals() const
{
	return false;
}

bool VultureUnitMock::isHallucination() const
{
	return false;
}

bool VultureUnitMock::isIdle() const
{
	return false;
}

bool VultureUnitMock::isInterruptible() const
{
	return false;
}

bool VultureUnitMock::isInvincible() const
{
	return false;
}

bool VultureUnitMock::isLifted() const
{
	return false;
}

bool VultureUnitMock::isMorphing() const
{
	return false;
}

bool VultureUnitMock::isMoving() const
{
	return false;
}

bool VultureUnitMock::isParasited() const
{
	return false;
}

bool VultureUnitMock::isSelected() const
{
	return false;
}

bool VultureUnitMock::isStartingAttack() const
{
	return false;
}

bool VultureUnitMock::isStuck() const
{
	return false;
}

bool VultureUnitMock::isTraining() const
{
	return false;
}

bool VultureUnitMock::isUnderAttack() const
{
	return false;
}

bool VultureUnitMock::isUnderDarkSwarm() const
{
	return false;
}

bool VultureUnitMock::isUnderDisruptionWeb() const
{
	return false;
}

bool VultureUnitMock::isUnderStorm() const
{
	return false;
}

bool VultureUnitMock::isPowered() const
{
	return false;
}

bool VultureUnitMock::isVisible(BWAPI::Player player) const
{
	return false;
}

bool VultureUnitMock::isTargetable() const
{
	return false;
}

bool VultureUnitMock::issueCommand(BWAPI::UnitCommand command)
{
	return false;
}

bool VultureUnitMock::canIssueCommand(BWAPI::UnitCommand command, bool checkCanUseTechPositionOnPositions, bool checkCanUseTechUnitOnUnits, bool checkCanBuildUnitType, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canIssueCommandGrouped(BWAPI::UnitCommand command, bool checkCanUseTechPositionOnPositions, bool checkCanUseTechUnitOnUnits, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canCommand() const
{
	return false;
}

bool VultureUnitMock::canCommandGrouped(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canIssueCommandType(BWAPI::UnitCommandType ct, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canIssueCommandTypeGrouped(BWAPI::UnitCommandType ct, bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canTargetUnit(BWAPI::Unit targetUnit, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canAttack(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canAttack(BWAPI::Position target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canAttack(BWAPI::Unit target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canAttackGrouped(bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canAttackGrouped(BWAPI::Position target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canAttackGrouped(BWAPI::Unit target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canAttackMove(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canAttackMoveGrouped(bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canAttackUnit(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canAttackUnit(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canAttackUnitGrouped(bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canAttackUnitGrouped(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canBuild(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canBuild(BWAPI::UnitType uType, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canBuild(BWAPI::UnitType uType, BWAPI::TilePosition tilePos, bool checkTargetUnitType, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canBuildAddon(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canBuildAddon(BWAPI::UnitType uType, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canTrain(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canTrain(BWAPI::UnitType uType, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canMorph(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canMorph(BWAPI::UnitType uType, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canResearch(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canResearch(BWAPI::TechType type, bool checkCanIssueCommandType) const
{
	return false;
}

bool VultureUnitMock::canUpgrade(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canUpgrade(BWAPI::UpgradeType type, bool checkCanIssueCommandType) const
{
	return false;
}

bool VultureUnitMock::canSetRallyPoint(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canSetRallyPoint(BWAPI::Position target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canSetRallyPoint(BWAPI::Unit target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canSetRallyPosition(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canSetRallyUnit(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canSetRallyUnit(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canMove(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canMoveGrouped(bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canPatrol(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canPatrolGrouped(bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canFollow(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canFollow(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canGather(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canGather(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canReturnCargo(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canHoldPosition(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canStop(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canRepair(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canRepair(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canBurrow(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canUnburrow(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canCloak(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canDecloak(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canSiege(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canUnsiege(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canLift(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canLand(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canLand(BWAPI::TilePosition target, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canLoad(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canLoad(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canUnloadWithOrWithoutTarget(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canUnloadAtPosition(BWAPI::Position targDropPos, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canUnload(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canUnload(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkPosition, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canUnloadAll(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canUnloadAllPosition(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canUnloadAllPosition(BWAPI::Position targDropPos, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canRightClick(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canRightClick(BWAPI::Position target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canRightClick(BWAPI::Unit target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canRightClickGrouped(bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canRightClickGrouped(BWAPI::Position target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canRightClickGrouped(BWAPI::Unit target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canRightClickPosition(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canRightClickPositionGrouped(bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canRightClickUnit(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canRightClickUnit(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canRightClickUnitGrouped(bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canRightClickUnitGrouped(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canHaltConstruction(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canCancelConstruction(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canCancelAddon(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canCancelTrain(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canCancelTrainSlot(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canCancelTrainSlot(int slot, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canCancelMorph(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canCancelResearch(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canCancelUpgrade(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canUseTechWithOrWithoutTarget(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canUseTechWithOrWithoutTarget(BWAPI::TechType tech, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return true;
}

bool VultureUnitMock::canUseTech(BWAPI::TechType tech, BWAPI::Position target, bool checkCanTargetUnit, bool checkTargetsType, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canUseTech(BWAPI::TechType tech, BWAPI::Unit target, bool checkCanTargetUnit, bool checkTargetsType, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canUseTechWithoutTarget(BWAPI::TechType tech, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canUseTechUnit(BWAPI::TechType tech, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canUseTechUnit(BWAPI::TechType tech, BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkTargetsUnits, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canUseTechPosition(BWAPI::TechType tech, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canUseTechPosition(BWAPI::TechType tech, BWAPI::Position target, bool checkTargetsPositions, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canPlaceCOP(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMock::canPlaceCOP(BWAPI::TilePosition target, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}


