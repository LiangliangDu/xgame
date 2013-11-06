//==========================================================================
/**
* @file	  : StateDef.h
* @author : pk <pk163@163.com>
* created : 2008-3-5   15:01
* purpose : ״̬����(��Ҫ���ģ�Ͷ������)
*/
//==========================================================================

#ifndef __STATEDEF_H__
#define __STATEDEF_H__

/**
	���ǵ����ǵĶ���û��wow��ô��û������������˶���
	����ȥ����ǰ�Ĳ���״̬�������м򻯴���
*/

enum
{
	stateStand,
	stateMove,
	stateSitdown,
	stateDeath,
	stateFallow,
	stateWound,
	stateStun,
	stateAttackReady,
	stateAttack,
	//stateSpellReady,
	//stateSpell,
	MaxStateCount,
	// ����޸ĸ�ö�٣����޸�StateComponentMZ::setState�е�loopFlag
};


/*
��ɫ����(֧��1������)��
վ�� Stand
���� Walk
����׼�� AttackReady
������ Attack
ʩ��׼�� SpellReady
ʩ�� Spell
ͨ��ʩ�� SpellChannel
���� Hit / Wound
���� Death
ʬ�� DecayFlesh

��ѡ:
���� Fallow / Emote
��� Ride
���� Rise / SitGroundUp
���� Sitting  / SitGroundDown
���� SitGround
���� Lie
ѣ�� Stun / Dizzy
��� Parry


���︽�ӣ�
ʬ�� DecayBone
���� Birth
*/

#endif // __STATEDEF_H__