#include "PluginSDK.h"

PluginSetup("Quinn")

// Menus
IMenu* MainMenu;

IMenu* ComboSettings;
IMenu* ComboQSettings;
IMenuOption* ComboQ;
//IMenu* ComboWSettings;
//IMenuOption* ComboW;
IMenu* ComboESettings;
IMenuOption* ComboE;
/*IMenu ComboRSettings;
IMenuOption* ComboR;*/

IMenuOption* AutoW;

//IMenu* MixedSettings;
//IMenu* MixedQSettings;
//IMenuOption* MixedQ;
//IMenu* MixedWSettings;
//IMenuOption* MixedW;
//IMenu* MixedESettings;
//IMenuOption* MixedE;
//IMenu* MixedRSettings;
//IMenuOption* MixedR;

IMenu* LaneClearSettings;
IMenu* LaneClearQSettings;
IMenuOption* LaneClearQ;
IMenuOption* LaneClearQMinionsRequired;
//IMenu* LaneClearWSettings;
//IMenuOption* LaneClearW;
//IMenuOption* LaneClearWMinionsRequired;
IMenu* LaneClearESettings;
IMenuOption* LaneClearE;
IMenuOption* LaneClearEMinionsRequired;
//IMenu* LaneClearRSettings;
//IMenuOption* LaneClearR;
//IMenuOption* LaneClearRMinionsRequired;
IMenuOption* FarmEnergy;

IMenu* DrawSettings;
IMenuOption* DrawQRange;
//IMenuOption* DrawWRange;
IMenuOption* DrawERange;
//IMenuOption* DrawRRange;

ISpell2* Q;
ISpell2* W;
ISpell2* E;
ISpell2* R;
ISpell2* Ignite;

// Useful units
IUnit* Player;
std::vector<IUnit*> minions;
std::vector<IUnit*> myTeam;
std::vector<IUnit*> enemyTeam;

// Useful pointers
IGame* game;

IInventoryItem* cutlass;
IInventoryItem* botrk;
IInventoryItem* youmuus;

bool useR;

void Menu()
{
	//Main Menu Setup
	MainMenu = GPluginSDK->AddMenu("Quinn");
	ComboSettings = MainMenu->AddMenu("Combo Settings");
	//MixedSettings = MainMenu->AddMenu("Mixed Settings");
	LaneClearSettings = MainMenu->AddMenu("Lane Clear Settings");
	DrawSettings = MainMenu->AddMenu("Drawings");
	AutoW = MainMenu->CheckBox("Auto W", true);

	//Combo Menu Setup
	ComboQSettings = ComboSettings->AddMenu("Combo Q");
	//ComboWSettings = ComboSettings->AddMenu("Combo W");
	ComboESettings = ComboSettings->AddMenu("Combo E");
	//ComboRSettings = ComboSettings->AddMenu("Combo R");
	//Combo Q Option Setup
	ComboQ = ComboQSettings->CheckBox("Enabled", true);
	//Combo W Option Setup
	//ComboW = ComboWSettings->CheckBox("Enabled", true);
	//Combo E Option Setup
	ComboE = ComboESettings->CheckBox("Enabled", true);
	//Combo R Option Setup
	//ComboR = ComboRSettings->CheckBox("Enabled", true);
	
	//Mixed Menu Setup
	/*MixedQSettings = MixedSettings->AddMenu("Mixed Q");
	MixedWSettings = MixedSettings->AddMenu("Mixed W");
	MixedESettings = MixedSettings->AddMenu("Mixed E");
	MixedRSettings = MixedSettings->AddMenu("Mixed R");
	//Mixed Q Option Setup
	MixedQ = MixedQSettings->CheckBox("Enabled", true);
	//Mixed W Option Setup
	MixedW = MixedWSettings->CheckBox("Enabled", true);
	//Mixed E Option Setup
	MixedE = MixedESettings->CheckBox("Enabled", true);
	//Mixed R Option Setup
	MixedR = MixedRSettings->CheckBox("Enabled", true);*/

	//Lane Clear Menu Setup
	LaneClearQSettings = LaneClearSettings->AddMenu("Lane Clear Q");
	//LaneClearWSettings = LaneClearSettings->AddMenu("Lane Clear W");
	LaneClearESettings = LaneClearSettings->AddMenu("Lane Clear E");
	//LaneClearRSettings = LaneClearSettings->AddMenu("Lane Clear R");
	FarmEnergy = LaneClearSettings->AddInteger("Mana %", 10, 100, 35);
	//Lane Clear Q Option Setup
	LaneClearQ = LaneClearQSettings->CheckBox("Use Q", true);
	LaneClearQMinionsRequired = LaneClearQSettings->AddInteger("Min # of Minions", 1, 6, 3);
	//Lane Clear W Option Setup
	/*LaneClearW = LaneClearWSettings->CheckBox("Use W", false);
	LaneClearWMinionsRequired = LaneClearWSettings->AddInteger("Min # of Minions", 1, 6, 3);*/
	//Lane Clear E Option Setup
	LaneClearE = LaneClearESettings->CheckBox("Use E", false);
	LaneClearEMinionsRequired = LaneClearESettings->AddInteger("Min # of Minions", 1, 6, 3);
	//Lane Clear R Option Setup
	/*LaneClearR = LaneClearRSettings->CheckBox("Use R", false);
	LaneClearRMinionsRequired = LaneClearRSettings->AddInteger("Min # of Minions", 1, 6, 3);*/

	//Draw Menu Setup
	DrawQRange = DrawSettings->CheckBox("Draw Q Range", true);
	//DrawWRange = DrawSettings->CheckBox("Draw W Range", true);
	DrawERange = DrawSettings->CheckBox("Draw E Range", true);
	//DrawRRange = DrawSettings->CheckBox("Draw R Range", true);
}

float GetDistance(IUnit* source, IUnit* target)
{
	auto x1 = source->GetPosition().x;
	auto x2 = target->GetPosition().x;
	auto y1 = source->GetPosition().y;
	auto y2 = target->GetPosition().y;
	auto z1 = source->GetPosition().z;
	auto z2 = target->GetPosition().z;
	return static_cast<float>(sqrt(pow((x2 - x1), 2.0) + pow((y2 - y1), 2.0) + pow((z2 - z1), 2.0)));
}

void Combo()
{
	auto bestTarget = GTargetSelector->FindTarget(QuickestKill, PhysicalDamage, 1300);
	auto focusTarget = GTargetSelector->GetFocusedTarget();

	IUnit* target = nullptr;

	if (focusTarget != nullptr)
	{
		target = focusTarget;
	} else {
		target = bestTarget;
	}

	if (target != nullptr && target->IsValidTarget() && !target->IsDead()) {

		// Is Combo Q Enabled?
		if (ComboQ->Enabled() && Q->IsReady())
		{
			Q->CastOnTarget(target);
		}

		// Is Combo W Enabled?
		/*if (ComboW->Enabled())
		{

		}*/

		// Is Combo E Enabled?
		if (ComboE->Enabled() && E->IsReady() && Player->IsFacing(target))
		{
			E->CastOnTarget(target);
		}

		// Is Combo R Enabled?
		/*if (ComboR->Enabled())
		{

		}*/

		if (cutlass->IsOwned() && cutlass->IsReady() && GetDistance(Player, target) < 550)
		{
			cutlass->CastOnTarget(target);
		}

		if (botrk->IsOwned() && botrk->IsReady() && GetDistance(Player, target) < 550)
		{
			botrk->CastOnTarget(target);
		}

		if (youmuus->IsOwned() && youmuus->IsReady() && GetDistance(Player, target) < 900)
		{
			youmuus->CastOnPlayer();
		}

		if (Ignite != nullptr&& Ignite->IsReady())
		{
			if (target->GetHealth() < (GDamage->GetSpellDamage(Player, target, kSlotQ) * 3) 
				+ GDamage->GetSpellDamage(Player, target, kSlotE)
				+ GDamage->GetSummonerSpellDamage(Player, target, kSummonerSpellIgnite)) {
				Ignite->CastOnTarget(target);
			}
		}
	}
}

//void Mixed()
//{
//	if (MixedQ->Enabled())
//	{
//
//	}
//	if (MixedW->Enabled())
//	{
//
//	}
//	if (MixedE->Enabled())
//	{
//
//	}
//	if (MixedR->Enabled())
//	{
//
//	}
//}

void LaneClear()
{
	if (Player->ManaPercent() < FarmEnergy->GetInteger())
		return;

	if (LaneClearQ->Enabled() && Q->IsReady())
	{
		minions = GEntityList->GetAllMinions(false, true, true);
		for (auto minion : minions)
		{
			if (minion != nullptr && !minion->IsDead())
			{
				if (GEntityList->Player()->IsValidTarget(minion, Q->Range()))
				{
					Q->CastOnTarget(minion, kHitChanceHigh);
				}
			}
		}
	}
	/*if (LaneClearW->Enabled())
	{

	}*/
	if (LaneClearE->Enabled() && E->IsReady())
	{
		minions = GEntityList->GetAllMinions(false, true, true);
		for (auto minion : minions)
		{
			if (minion != nullptr && !minion->IsDead())
			{
				if (!minion->IsDead() && minion->GetHealth() <= GDamage->GetSpellDamage(Player, minion, kSlotE))
				{
					E->CastOnUnit(minion);
				}
			}
		}
	}
	/*if (LaneClearR->Enabled())
	{

	}*/
}

void Auto()
{
	if (Player->IsRecalling())
	{
		useR = true;
	}

	//in home is auto R
	if (useR && GUtility->IsPositionInFountain(Player->GetPosition()) && R->IsReady() && R->ManaCost() != 0.0f
		&& GOrbwalking->GetOrbwalkingMode() != kModeLaneClear
		&& GOrbwalking->GetOrbwalkingMode() != kModeCombo
		&& GOrbwalking->GetOrbwalkingMode() != kModeMixed)
	{
		R->CastOnPlayer();
		useR = false;
	}

	//auto W
	if (AutoW->Enabled() && W->IsReady() && !Player->IsRecalling() && !GUtility->IsPositionInFountain(Player->GetPosition()))
	{
		W->CastOnPlayer();
	}
}

PLUGIN_EVENT(void) OnGameUpdate()
{
	Player = GEntityList->Player();

	if (Player->IsDead())
	{
		return;
	}

	if (GOrbwalking->GetOrbwalkingMode() == kModeCombo) {
		Combo();
	}
	else if (GOrbwalking->GetOrbwalkingMode() == kModeMixed)
	{
		//Mixed();
	}
	else if (GOrbwalking->GetOrbwalkingMode() == kModeLaneClear)
	{
		LaneClear();
	}
	Auto();
}

void DrawRanges()
{
	if (Player->IsDead())
	{
		return;
	}

	if (DrawQRange->Enabled())
	{
		GPluginSDK->GetRenderer()->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), Q->Range());
	}
	if (DrawERange->Enabled())
	{
		GPluginSDK->GetRenderer()->DrawOutlinedCircle(GEntityList->Player()->GetPosition(), Vec4(255, 255, 0, 255), E->Range());
	}
}

PLUGIN_EVENT(void) OnRender()
{
	DrawRanges();
}

void InitSpells()
{
	//Q
	Q = GPluginSDK->CreateSpell2(kSlotQ, kLineCast, true, true, kCollidesWithYasuoWall | kCollidesWithMinions);
	Q->SetSkillshot(0.25f, 50, 1700, 1025);

	//W
	W = GPluginSDK->CreateSpell2(kSlotW, kCircleCast, false, true, kCollidesWithNothing);
	W->SetOverrideRange(2100);

	//E
	E = GPluginSDK->CreateSpell2(kSlotE, kTargetCast, false, false, kCollidesWithNothing);
	E->SetOverrideRange(675);

	//R
	R = GPluginSDK->CreateSpell2(kSlotR, kCircleCast, false, false, kCollidesWithNothing);
	R->SetOverrideRange(700);

	if (strcmp(GEntityList->Player()->GetSpellName(kSummonerSlot1), "SummonerDot") == 0)
	{
		Ignite = GPluginSDK->CreateSpell2(kSummonerSlot1, kTargetCast, false, false, kCollidesWithNothing);
		Ignite->SetOverrideRange(600);
	}
	if (strcmp(GEntityList->Player()->GetSpellName(kSummonerSlot2), "SummonerDot") == 0)
	{
		Ignite = GPluginSDK->CreateSpell2(kSummonerSlot2, kTargetCast, false, false, kCollidesWithNothing);
		Ignite->SetOverrideRange(600);
	}

	cutlass = GPluginSDK->CreateItemForId(3144, 550);
	botrk = GPluginSDK->CreateItemForId(3153, 550);
	youmuus = GPluginSDK->CreateItemForId(3142, 0);
}

PLUGIN_API void OnLoad(IPluginSDK* PluginSDK)
{
	PluginSDKSetup(PluginSDK);
	Menu();
	InitSpells();
	GEventManager->AddEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->AddEventHandler(kEventOnRender, OnRender);
}

PLUGIN_API void OnUnload()
{
	MainMenu->Remove();
	GEventManager->RemoveEventHandler(kEventOnGameUpdate, OnGameUpdate);
	GEventManager->RemoveEventHandler(kEventOnRender, OnRender);
}