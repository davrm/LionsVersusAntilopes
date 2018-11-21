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
}


void LionsVersusAntilopes::Antilope::InitBehaviourTree()
{
	m_tree = new BehaviourTree();
	Root * root = new Root();
	m_tree->setRootChild(root);

	///////////////////////////////////
	Selector *s1 = new Selector(), *s2 = new Selector();
	Sequence *sq1 = new Sequence(), *sq2 = new Sequence(), 
		*sq3 = new Sequence(), *sq4 = new Sequence(), 
		*sq5 = new Sequence(), *sq6 = new Sequence();
	Inverter *i1 = new Inverter(), *i2 = new Inverter();
	///////////////////////////////////
	
	Conditional *cFarFromOtherAnimalsOfMyTeam = new Conditional(std::bind(&GameObjectAnimal::IsFarFromOtherAnimalsOfMyTeam, this));
	Conditional *cOurTeamHaveTheFlag = new Conditional(std::bind(&GameObjectAnimal::IsOurTeamHavingTheFlag, this));
	Conditional *cEnemyTeamHaveTheFlag = new Conditional(std::bind(&GameObjectAnimal::IsEnemyTeamHavingTheFlag, this));
	Conditional *cIHaveTheFlag = new Conditional(std::bind(&GameObjectAnimal::IsThisAnimalHavinfTheFlag, this));
	///////////////////////////////////
	Action *aGoTotheNearestTeammate = new Action(std::bind(&GameObjectAnimal::GoTotheNearestTeammate, this));
	Action *aGotoTheEnemyFlag = new Action(std::bind(&GameObjectAnimal::GotoTheEnemyFlag, this));
	Action *aCaptureEnemyFlag = new Action(std::bind(&GameObjectAnimal::CaptureEnemyFlag, this));
	Action *aGoToOurFlag = new Action(std::bind(&GameObjectAnimal::GoToOurFlag, this));
	Action *aAttackEnemy = new Action(std::bind(&GameObjectAnimal::AttackEnemy, this));
	///////////////////////////////////
	s1->setName("s1");
	s2->setName("s2");
	sq1->setName("sq1");
	sq2->setName("sq2");
	sq3->setName("sq3");
	sq4->setName("sq4");
	sq5->setName("sq5");
	sq6->setName("sq6");

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
	s1->AddChildren({sq1,sq2,sq3,sq4});
	//---------------------------------
	sq1->AddChildren({ cFarFromOtherAnimalsOfMyTeam,aGoTotheNearestTeammate });
	//---------------------------------
	sq2->AddChildren({i1,s2,sq5});
	//---------------------------------
	i1->setChild(cOurTeamHaveTheFlag);
	//---------------------------------
	s2->AddChildren({i2,cIHaveTheFlag});
	//---------------------------------
	i2->setChild(cEnemyTeamHaveTheFlag);
	//---------------------------------
	sq5->AddChildren({aGotoTheEnemyFlag,aCaptureEnemyFlag});
	//---------------------------------
	sq3->AddChildren({cEnemyTeamHaveTheFlag,sq6});
	//---------------------------------
	sq6->AddChildren({aGoToOurFlag,aAttackEnemy});
	//---------------------------------


}
