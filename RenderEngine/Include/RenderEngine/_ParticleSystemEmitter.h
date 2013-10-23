#ifndef __ParticleSystemEmitter_H__
#define __ParticleSystemEmitter_H__

#include "_Particle.h"
#include "_ParticleSystem.h"

namespace xs
{
	enum ParticleSystemEmitterType
	{
		PSET_PLANE		=	1,
		PSET_SPHERE		=	2,
		PSET_REAL_SPHERE	= 3,
	};

	class ParticleSystemEmitter;
	/** ����ϵͳ���������󹤳�����
	*/
	class _RenderEngineExport ParticleSystemEmitterFactory
	{
	private:
		typedef std::map<uint,ParticleSystemEmitterFactory*> ParticleSystemEmitterFactoryList;
		static ParticleSystemEmitterFactoryList	m_Factories;
	public:
		static void registerEmitterFactory(uint type,ParticleSystemEmitterFactory *pFactory);
		static void unregisterEmitterFactory(uint type);
		static ParticleSystemEmitter * newEmitter(uint type,MmParticleSystem *pParticleSystem);
	public:
		virtual ParticleSystemEmitter*	newEmitter(MmParticleSystem *pParticleSystem) = 0;
	};
	/** ����ϵͳ����������
	*/
	class _RenderEngineExport ParticleSystemEmitter
	{
	protected:
		MmParticleSystem *m_pParticleSystem;
	public:
		ParticleSystemEmitter(MmParticleSystem* pParticleSystem) : m_pParticleSystem(pParticleSystem){}
	public:
		virtual void	release() = 0;
		virtual MmParticle newParticle(int rangeIndex,AnimationTime *pTime) = 0;
	};
}

#endif