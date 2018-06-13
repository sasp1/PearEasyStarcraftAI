#include "stdafx.h"
#include "VultureUnitMockFarAway.h"


VultureUnitMockFarAway::VultureUnitMockFarAway() : BWAPI::UnitInterface()
{
}


VultureUnitMockFarAway::~VultureUnitMockFarAway()
{
}

int VultureUnitMockFarAway::getID() const
{
	return 0;
}

int VultureUnitMockFarAway::getDistance(BWAPI::Position target) const
{
	return 0;
}

bool VultureUnitMockFarAway::exists() const
{
	return true;
}

int VultureUnitMockFarAway::getReplayID() const
{
	return 0;
}

BWAPI::Player VultureUnitMockFarAway::getPlayer() const
{
	return BWAPI::Player();
}

BWAPI::UnitType VultureUnitMockFarAway::getType() const
{
	return BWAPI::UnitTypes::Terran_Vulture;
	;
}

BWAPI::Position VultureUnitMockFarAway::getPosition() const
{
	return Position(0, 0);
}

double VultureUnitMockFarAway::getAngle() const
{
	return 0.0;
}

double VultureUnitMockFarAway::getVelocityX() const
{
	return 0.0;
}

double VultureUnitMockFarAway::getVelocityY() const
{
	return 0.0;
}

int VultureUnitMockFarAway::getHitPoints() const
{
	return 0;
}

int VultureUnitMockFarAway::getShields() const
{
	return 0;
}

int VultureUnitMockFarAway::getEnergy() const
{
	return 0;
}

int VultureUnitMockFarAway::getResources() const
{
	return 0;
}

int VultureUnitMockFarAway::getResourceGroup() const
{
	return 0;
}

int VultureUnitMockFarAway::getLastCommandFrame() const
{
	return 0;
}

BWAPI::UnitCommand VultureUnitMockFarAway::getLastCommand() const
{
	return BWAPI::UnitCommand();
}

BWAPI::Player VultureUnitMockFarAway::getLastAttackingPlayer() const
{
	return BWAPI::Player();
}

BWAPI::UnitType VultureUnitMockFarAway::getInitialType() const
{
	return BWAPI::UnitType();
}

BWAPI::Position VultureUnitMockFarAway::getInitialPosition() const
{
	return BWAPI::Position();
}

BWAPI::TilePosition VultureUnitMockFarAway::getInitialTilePosition() const
{
	return BWAPI::TilePosition();
}

int VultureUnitMockFarAway::getInitialHitPoints() const
{
	return 0;
}

int VultureUnitMockFarAway::getInitialResources() const
{
	return 0;
}

int VultureUnitMockFarAway::getKillCount() const
{
	return 0;
}

int VultureUnitMockFarAway::getAcidSporeCount() const
{
	return 0;
}

int VultureUnitMockFarAway::getInterceptorCount() const
{
	return 0;
}

int VultureUnitMockFarAway::getScarabCount() const
{
	return 0;
}

int VultureUnitMockFarAway::getSpiderMineCount() const
{
	return 0;
}

int VultureUnitMockFarAway::getGroundWeaponCooldown() const
{
	return 0;
}

int VultureUnitMockFarAway::getAirWeaponCooldown() const
{
	return 0;
}

int VultureUnitMockFarAway::getSpellCooldown() const
{
	return 0;
}

int VultureUnitMockFarAway::getDefenseMatrixPoints() const
{
	return 0;
}

int VultureUnitMockFarAway::getDefenseMatrixTimer() const
{
	return 0;
}

int VultureUnitMockFarAway::getEnsnareTimer() const
{
	return 0;
}

int VultureUnitMockFarAway::getIrradiateTimer() const
{
	return 0;
}

int VultureUnitMockFarAway::getLockdownTimer() const
{
	return 0;
}

int VultureUnitMockFarAway::getMaelstromTimer() const
{
	return 0;
}

int VultureUnitMockFarAway::getOrderTimer() const
{
	return 0;
}

int VultureUnitMockFarAway::getPlagueTimer() const
{
	return 0;
}

int VultureUnitMockFarAway::getRemoveTimer() const
{
	return 0;
}

int VultureUnitMockFarAway::getStasisTimer() const
{
	return 0;
}

int VultureUnitMockFarAway::getStimTimer() const
{
	return 0;
}

BWAPI::UnitType VultureUnitMockFarAway::getBuildType() const
{
	return BWAPI::UnitType();
}

BWAPI::UnitType::list VultureUnitMockFarAway::getTrainingQueue() const
{
	return BWAPI::UnitType::list();
}

BWAPI::TechType VultureUnitMockFarAway::getTech() const
{
	return BWAPI::TechType();
}

BWAPI::UpgradeType VultureUnitMockFarAway::getUpgrade() const
{
	return BWAPI::UpgradeType();
}

int VultureUnitMockFarAway::getRemainingBuildTime() const
{
	return 0;
}

int VultureUnitMockFarAway::getRemainingTrainTime() const
{
	return 0;
}

int VultureUnitMockFarAway::getRemainingResearchTime() const
{
	return 0;
}

int VultureUnitMockFarAway::getRemainingUpgradeTime() const
{
	return 0;
}

BWAPI::Unit VultureUnitMockFarAway::getBuildUnit() const
{
	return BWAPI::Unit();
}

BWAPI::Unit VultureUnitMockFarAway::getTarget() const
{
	return BWAPI::Unit();
}

BWAPI::Position VultureUnitMockFarAway::getTargetPosition() const
{
	return BWAPI::Position();
}

BWAPI::Order VultureUnitMockFarAway::getOrder() const
{
	return BWAPI::Order();
}

BWAPI::Order VultureUnitMockFarAway::getSecondaryOrder() const
{
	return BWAPI::Order();
}

BWAPI::Unit VultureUnitMockFarAway::getOrderTarget() const
{
	return BWAPI::Unit();
}

BWAPI::Position VultureUnitMockFarAway::getOrderTargetPosition() const
{
	return BWAPI::Position();
}

BWAPI::Position VultureUnitMockFarAway::getRallyPosition() const
{
	return BWAPI::Position();
}

BWAPI::Unit VultureUnitMockFarAway::getRallyUnit() const
{
	return BWAPI::Unit();
}

BWAPI::Unit VultureUnitMockFarAway::getAddon() const
{
	return BWAPI::Unit();
}

BWAPI::Unit VultureUnitMockFarAway::getNydusExit() const
{
	return BWAPI::Unit();
}

BWAPI::Unit VultureUnitMockFarAway::getPowerUp() const
{
	return BWAPI::Unit();
}

BWAPI::Unit VultureUnitMockFarAway::getTransport() const
{
	return BWAPI::Unit();
}

BWAPI::Unitset VultureUnitMockFarAway::getLoadedUnits() const
{
	return BWAPI::Unitset();
}

BWAPI::Unit VultureUnitMockFarAway::getCarrier() const
{
	return BWAPI::Unit();
}

BWAPI::Unitset VultureUnitMockFarAway::getInterceptors() const
{
	return BWAPI::Unitset();
}

BWAPI::Unit VultureUnitMockFarAway::getHatchery() const
{
	return BWAPI::Unit();
}

BWAPI::Unitset VultureUnitMockFarAway::getLarva() const
{
	return BWAPI::Unitset();
}

bool VultureUnitMockFarAway::hasNuke() const
{
	return false;
}

bool VultureUnitMockFarAway::isAccelerating() const
{
	return false;
}

bool VultureUnitMockFarAway::isAttacking() const
{
	return false;
}

bool VultureUnitMockFarAway::isAttackFrame() const
{
	return false;
}

bool VultureUnitMockFarAway::isBeingGathered() const
{
	return false;
}

bool VultureUnitMockFarAway::isBeingHealed() const
{
	return false;
}

bool VultureUnitMockFarAway::isBlind() const
{
	return false;
}

bool VultureUnitMockFarAway::isBraking() const
{
	return false;
}

bool VultureUnitMockFarAway::isBurrowed() const
{
	return false;
}

bool VultureUnitMockFarAway::isCarryingGas() const
{
	return false;
}

bool VultureUnitMockFarAway::isCarryingMinerals() const
{
	return false;
}

bool VultureUnitMockFarAway::isCloaked() const
{
	return false;
}

bool VultureUnitMockFarAway::isCompleted() const
{
	return false;
}

bool VultureUnitMockFarAway::isConstructing() const
{
	return false;
}

bool VultureUnitMockFarAway::isDetected() const
{
	return false;
}

bool VultureUnitMockFarAway::isGatheringGas() const
{
	return false;
}

bool VultureUnitMockFarAway::isGatheringMinerals() const
{
	return false;
}

bool VultureUnitMockFarAway::isHallucination() const
{
	return false;
}

bool VultureUnitMockFarAway::isIdle() const
{
	return false;
}

bool VultureUnitMockFarAway::isInterruptible() const
{
	return false;
}

bool VultureUnitMockFarAway::isInvincible() const
{
	return false;
}

bool VultureUnitMockFarAway::isLifted() const
{
	return false;
}

bool VultureUnitMockFarAway::isMorphing() const
{
	return false;
}

bool VultureUnitMockFarAway::isMoving() const
{
	return false;
}

bool VultureUnitMockFarAway::isParasited() const
{
	return false;
}

bool VultureUnitMockFarAway::isSelected() const
{
	return false;
}

bool VultureUnitMockFarAway::isStartingAttack() const
{
	return false;
}

bool VultureUnitMockFarAway::isStuck() const
{
	return false;
}

bool VultureUnitMockFarAway::isTraining() const
{
	return false;
}

bool VultureUnitMockFarAway::isUnderAttack() const
{
	return false;
}

bool VultureUnitMockFarAway::isUnderDarkSwarm() const
{
	return false;
}

bool VultureUnitMockFarAway::isUnderDisruptionWeb() const
{
	return false;
}

bool VultureUnitMockFarAway::isUnderStorm() const
{
	return false;
}

bool VultureUnitMockFarAway::isPowered() const
{
	return false;
}

bool VultureUnitMockFarAway::isVisible(BWAPI::Player player) const
{
	return false;
}

bool VultureUnitMockFarAway::isTargetable() const
{
	return false;
}

bool VultureUnitMockFarAway::issueCommand(BWAPI::UnitCommand command)
{
	return false;
}

bool VultureUnitMockFarAway::canIssueCommand(BWAPI::UnitCommand command, bool checkCanUseTechPositionOnPositions, bool checkCanUseTechUnitOnUnits, bool checkCanBuildUnitType, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canIssueCommandGrouped(BWAPI::UnitCommand command, bool checkCanUseTechPositionOnPositions, bool checkCanUseTechUnitOnUnits, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canCommand() const
{
	return false;
}

bool VultureUnitMockFarAway::canCommandGrouped(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canIssueCommandType(BWAPI::UnitCommandType ct, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canIssueCommandTypeGrouped(BWAPI::UnitCommandType ct, bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canTargetUnit(BWAPI::Unit targetUnit, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canAttack(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canAttack(BWAPI::Position target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canAttack(BWAPI::Unit target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canAttackGrouped(bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canAttackGrouped(BWAPI::Position target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canAttackGrouped(BWAPI::Unit target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canAttackMove(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canAttackMoveGrouped(bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canAttackUnit(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canAttackUnit(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canAttackUnitGrouped(bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canAttackUnitGrouped(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canBuild(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canBuild(BWAPI::UnitType uType, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canBuild(BWAPI::UnitType uType, BWAPI::TilePosition tilePos, bool checkTargetUnitType, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canBuildAddon(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canBuildAddon(BWAPI::UnitType uType, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canTrain(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canTrain(BWAPI::UnitType uType, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canMorph(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canMorph(BWAPI::UnitType uType, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canResearch(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canResearch(BWAPI::TechType type, bool checkCanIssueCommandType) const
{
	return false;
}

bool VultureUnitMockFarAway::canUpgrade(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canUpgrade(BWAPI::UpgradeType type, bool checkCanIssueCommandType) const
{
	return false;
}

bool VultureUnitMockFarAway::canSetRallyPoint(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canSetRallyPoint(BWAPI::Position target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canSetRallyPoint(BWAPI::Unit target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canSetRallyPosition(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canSetRallyUnit(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canSetRallyUnit(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canMove(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canMoveGrouped(bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canPatrol(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canPatrolGrouped(bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canFollow(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canFollow(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canGather(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canGather(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canReturnCargo(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canHoldPosition(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canStop(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canRepair(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canRepair(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canBurrow(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canUnburrow(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canCloak(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canDecloak(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canSiege(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canUnsiege(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canLift(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canLand(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canLand(BWAPI::TilePosition target, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canLoad(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canLoad(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canUnloadWithOrWithoutTarget(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canUnloadAtPosition(BWAPI::Position targDropPos, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canUnload(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canUnload(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkPosition, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canUnloadAll(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canUnloadAllPosition(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canUnloadAllPosition(BWAPI::Position targDropPos, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canRightClick(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canRightClick(BWAPI::Position target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canRightClick(BWAPI::Unit target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canRightClickGrouped(bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canRightClickGrouped(BWAPI::Position target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canRightClickGrouped(BWAPI::Unit target, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canRightClickPosition(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canRightClickPositionGrouped(bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canRightClickUnit(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canRightClickUnit(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canRightClickUnitGrouped(bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canRightClickUnitGrouped(BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkCanIssueCommandType, bool checkCommandibilityGrouped, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canHaltConstruction(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canCancelConstruction(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canCancelAddon(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canCancelTrain(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canCancelTrainSlot(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canCancelTrainSlot(int slot, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canCancelMorph(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canCancelResearch(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canCancelUpgrade(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canUseTechWithOrWithoutTarget(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canUseTechWithOrWithoutTarget(BWAPI::TechType tech, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return true;
}

bool VultureUnitMockFarAway::canUseTech(BWAPI::TechType tech, BWAPI::Position target, bool checkCanTargetUnit, bool checkTargetsType, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canUseTech(BWAPI::TechType tech, BWAPI::Unit target, bool checkCanTargetUnit, bool checkTargetsType, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canUseTechWithoutTarget(BWAPI::TechType tech, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canUseTechUnit(BWAPI::TechType tech, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canUseTechUnit(BWAPI::TechType tech, BWAPI::Unit targetUnit, bool checkCanTargetUnit, bool checkTargetsUnits, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canUseTechPosition(BWAPI::TechType tech, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canUseTechPosition(BWAPI::TechType tech, BWAPI::Position target, bool checkTargetsPositions, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canPlaceCOP(bool checkCommandibility) const
{
	return false;
}

bool VultureUnitMockFarAway::canPlaceCOP(BWAPI::TilePosition target, bool checkCanIssueCommandType, bool checkCommandibility) const
{
	return false;
}
