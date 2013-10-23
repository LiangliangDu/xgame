#ifndef __ParticleSystemEmitterPlane_H__
#define __ParticleSystemEmitterPlane_H__

#include "_Particle.h"
#include "_ParticleSystem.h"
#include "_ParticleSystemEmitter.h"

namespace xs
{
	/** Plane����ϵͳ������
	*/
	class ParticleSystemEmitterPlane : public ParticleSystemEmitter
	{
	public:
		ParticleSystemEmitterPlane(MmParticleSystem *pParticleSystem) : ParticleSystemEmitter(pParticleSystem){}
	public:
		virtual void	release();
		virtual MmParticle newParticle(int rangeIndex,AnimationTime *pTime);
	};

	/** Plane����ϵͳ����������
	*/
	class ParticleSystemEmitterFactoryPlane : public ParticleSystemEmitterFactory
	{
	protected:
		ParticleSystemEmitterFactoryPlane(){}
	public:
		static ParticleSystemEmitterFactory* Instance()
		{
			static ParticleSystemEmitterFactoryPlane e;
			return &e;
		}
	public:
		virtual ParticleSystemEmitter*	newEmitter(MmParticleSystem *pParticleSystem);
	};
}

#endif