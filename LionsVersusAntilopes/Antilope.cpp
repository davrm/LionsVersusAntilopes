#include "pch.h"
#include "Antilope.h"


using namespace LionsVersusAntilopes;

Antilope::~Antilope()
{

}

void Antilope::Update(DX::StepTimer const & timer)
{
	UpdateMovement(timer);
	m_tree->Update();
	m_timeNextAttack -= timer.GetElapsedSeconds();
}


void LionsVersusAntilopes::Antilope::InitBehaviourTree()
{
	m_tree = new BehaviourTree();
	Root * root = new Root();
	m_tree->setRootChild(root);

	///////////////////////////////////
	Selector *s1 = new Selector(), *selector_con_capture_flag = new Selector();
	Sequence *sequence_go_together = new Sequence(), *sequence_capture_flag = new Sequence(), 
		*sequence_defend_flag = new Sequence(), *sequence_attack_nearby_enemies = new Sequence(), 
		*sequence_go_or_capture_flag = new Sequence(), *sequence_recover_flag = new Sequence(), 
		*sequence_defend_transporter = new Sequence();
	Inverter *i1 = new Inverter(), *i2 = new Inverter(), *i3 = new Inverter(), * i4 = new Inverter();
	///////////////////////////////////
	Conditional *cFarFromOtherAnimalsOfMyTeam = new Conditional(std::bind(&GameObjectAnimal::IsFarFromOtherAnimalsOfMyTeam, this));
	Conditional *cOurTeamHaveTheFlag = new Conditional(std::bind(&GameObjectAnimal::IsOurTeamHavingTheFlag, this));
	Conditional *cOurTeamHaveTheFlag2 = new Conditional(std::bind(&GameObjectAnimal::IsOurTeamHavingTheFlag, this));
	Conditional *cEnemyTeamHaveTheFlag = new Conditional(std::bind(&GameObjectAnimal::IsEnemyTeamHavingTheFlag, this));
	Conditional *cIHaveTheFlag = new Conditional(std::bind(&GameObjectAnimal::IsThisAnimalHavinfTheFlag, this));
	Conditional *cIHaveTheFlag2 = new Conditional(std::bind(&GameObjectAnimal::IsThisAnimalHavinfTheFlag, this));
	Conditional *cEnemiesNearby = new Conditional(std::bind(&GameObjectAnimal::IsNearFromEnemies, this));
	///////////////////////////////////
	Action *aGoTotheNearestTeammate = new Action(std::bind(&GameObjectAnimal::GoTotheNearestTeammate, this));
	Action *aGotoTheEnemyFlag = new Action(std::bind(&GameObjectAnimal::GotoTheEnemyFlag, this));
	Action *aCaptureEnemyFlag = new Action(std::bind(&GameObjectAnimal::CaptureEnemyFlag, this));
	Action *aGoToOurFlag = new Action(std::bind(&GameObjectAnimal::GoToOurFlag, this));
	Action *aAttackEnemy = new Action(std::bind(&GameObjectAnimal::AttackEnemy, this));
	Action *aDefendTransporter = new Action(std::bind(&GameObjectAnimal::DefendTheTransporter, this));
	///////////////////////////////////
	s1->setName("s1");
	selector_con_capture_flag->setName("selector_con_capture_flag");
	sequence_go_together->setName("sequence_go_together");
	sequence_capture_flag->setName("sequence_capture_flag");
	sequence_defend_flag->setName("sequence_defend_flag");
	sequence_attack_nearby_enemies->setName("sequence_attack_nearby_enemies");
	sequence_go_or_capture_flag->setName("sequence_go_or_capture_flag");
	sequence_recover_flag->setName("sequence_recover_flag");

	cFarFromOtherAnimalsOfMyTeam->setName("cFarFromOtherAnimalsOfMyTeam");
	cOurTeamHaveTheFlag->setName("cOurTeamHaveTheFlag");
	cEnemyTeamHaveTheFlag->setName("cEnemyTeamHaveTheFlag");
	cIHaveTheFlag->setName("cIHaveTheFlag");

	aGoTotheNearestTeammate->setName("aGoTotheNearestTeammate");
	aGotoTheEnemyFlag->setName("aGotoTheEnemyFlag");
	aCaptureEnemyFlag->setName("aCaptureEnemyFlag");
	aGoToOurFlag->setName("aGoToOurFlag");
	aAttackEnemy->setName("aAttackEnemy");
	///////////////////////////////////
	//---------------------------------
	root->setChild(s1);
	//---------------------------------
	s1->AddChildren({sequence_go_together,sequence_capture_flag,sequence_defend_flag,sequence_defend_transporter,sequence_attack_nearby_enemies});
	//---------------------------------
	sequence_go_together->AddChildren({ i3,cFarFromOtherAnimalsOfMyTeam,aGoTotheNearestTeammate });
	//---------------------------------
	i3->setChild(cIHaveTheFlag2);
	//---------------------------------
	sequence_capture_flag->AddChildren({i1,selector_con_capture_flag,sequence_go_or_capture_flag});
	//---------------------------------
	i1->setChild(cOurTeamHaveTheFlag);
	//---------------------------------
	selector_con_capture_flag->AddChildren({i2,cIHaveTheFlag});
	//---------------------------------
	i2->setChild(cEnemyTeamHaveTheFlag);
	//---------------------------------
	sequence_go_or_capture_flag->AddChildren({aGotoTheEnemyFlag,aCaptureEnemyFlag});
	//---------------------------------
	sequence_defend_flag->AddChildren({cEnemyTeamHaveTheFlag,sequence_recover_flag});
	//---------------------------------
	sequence_recover_flag->AddChildren({aGoToOurFlag,aAttackEnemy});
	//---------------------------------
	sequence_defend_transporter->AddChildren({ cOurTeamHaveTheFlag2, i4,aDefendTransporter });
	//---------------------------------
	i4->setChild(cEnemiesNearby);
	//---------------------------------
	sequence_attack_nearby_enemies->AddChildren({ aAttackEnemy});
}
