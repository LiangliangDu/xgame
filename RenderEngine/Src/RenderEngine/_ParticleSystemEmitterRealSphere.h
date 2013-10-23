#ifndef __ParticleSystemEmitterRealSphere_H__
#define __ParticleSystemEmitterRealSphere_H__


#include "_Particle.h"
#include "_ParticleSystem.h"
#include "_ParticleSystemEmitter.h"

namespace xs
{
	/** RealSphere����ϵͳ������
	*/
	class ParticleSystemEmitterRealSphere : public ParticleSystemEmitter
	{
	public:
		ParticleSystemEmitterRealSphere(MmParticleSystem *pParticleSystem) : ParticleSystemEmitter(pParticleSystem){}
	public:
		virtual void	release();
		virtual MmParticle newParticle(int rangeIndex,AnimationTime *pTime);
	};

	/** RealSphere����ϵͳ����������
	*/
	class ParticleSystemEmitterFactoryRealSphere : public ParticleSystemEmitterFactory
	{
	protected:
		ParticleSystemEmitterFactoryRealSphere(){}
	public:
		static ParticleSystemEmitterFactory* Instance()
		{
			static ParticleSystemEmitterFactoryRealSphere e;
			return &e;
		}
	public:
		virtual ParticleSystemEmitter*	newEmitter(MmParticleSystem *pParticleSystem);
	};
}


#endif