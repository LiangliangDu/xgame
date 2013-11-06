//==========================================================================
/**
* @file	  : SkillViewDef.h
* @author : 
* created : 2008-3-13   17:35
* purpose : ���ܹ�Ч���Զ���
*/
//==========================================================================

#ifndef __SKILLVIEWDEF_H__
#define __SKILLVIEWDEF_H__

enum
{ 
	MAX_SUBSKILLVIEW_COUNT	= 1000, 
	MAX_SKILLVIEW_COUNT		= 100,
};

enum ESkillViewProperty
{
	SkillViewProperty_Depth,                                         // �ű����    
	SkillViewProperty_Name,                                          // ����
	SkillViewProperty_Id,                                            // ���
	SkillViewProperty_EffectType,                                    // ��Ч����
	SkillViewProperty_NotAdjustDir,                                  // ��Ч�����Ƿ������ʩ��������һֱ
	SkillViewProperty_AttackReadyActId,                              // ��������
	SkillViewProperty_AttackReadyActSpeed,                           // ���������ٶ�
	SkillViewProperty_AttackReadyMagicId,                            // ������Ч
    SkillViewProperty_AttackReadyMagicIdOnTarget,                    // ������Ч��Ŀ�꣩
    SkillViewProperty_AttackReadyMagicOnTargetAttachToTarget,        // ������Ч��Ŀ�꣩�Ƿ����Ŀ����      
	SkillViewProperty_RapidOrChannel,                                // ˲������ͨ��
	SkillViewProperty_AttackActId,                                   // ��������
	SkillViewProperty_AttackActSpeed,                                // ���������ٶ�
	SkillViewProperty_AttackMagicId,                                 // ʩ����Ч
	SkillViewProperty_AttackMagicAttachToSource,                     // ʩ����Ч�Ƿ����Դ��
	SkillViewProperty_BeHitMagicId,                                  // Ŀ���ܻ���Ч
	SkillViewProperty_BeHitFlyMagicId,                               // Ŀ���ܻ����й�Ч
	SkillViewProperty_WoundMagicId,                                  // �����˺���Ч
	SkillViewProperty_TrackMagicId,                                  // ���ٹ�Ч
    SkillViewProperty_ExplodeMagicType,                              // ��ը��Ч����
	SkillViewProperty_ExplodeMagicID,                                // ��ը��Ч
    SkillViewProperty_ExplodeMagicAttachToTarget,                    // ��ը��Ч�Ƿ����Ŀ����
	SkillViewProperty_Dummy,                                         // ��Ч�Ƿ��ܹ���������
	SkillViewProperty_FlySpeed,                                      // �����ٶ�
	SkillViewProperty_AttackRange,                                   // ���
	SkillViewProperty_Delay,                                         // ���
	SkillViewProperty_Times,                                         // ����
	SkillViewProperty_LifeTime,                                      // ѭ��ʱ��
	SkillViewProperty_Vibrate,                                       // ��������

    SkillViewProperty_MagicID,                                       // ���������õ�
	SkillViewProperty_SoundIDPreAttack,                              // �����׶ε���ЧID
	SkillViewProperty_bSoundLoopPreAttack,                           // �����׶ε���Ч�Ƿ�ѭ��
	SkillViewProperty_SoundIDAttack,                                 // �����׶ε���Ч
	SkillViewProperty_bSoundLoopeAttack,                             // �����׶ε���Ч�Ƿ�ѭ��
	SkillViewProperty_SoundIDBeHit,                                  // ��������Ч
	SkillViewProperty_bSoundLoopeBeHit,                              // �������Ƿ�ѭ��

	MaxSkillViewPropertyCount,                                       // Max
};

#endif // __SKILLVIEWDEF_H__