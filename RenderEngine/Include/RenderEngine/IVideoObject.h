#ifndef __IVIDEOOBJECT_H__
#define __IVIDEOOBJECT_H__

namespace xs
{

	enum  enumVideoObjectType
	{
		EVOT_AVI,	//avi��Ƶ����
		EVOT_Unknown,//δ֪����
	};

	struct IVideoObject
	{
		virtual ITexture *	getTexture( uint frame) = 0;
		virtual uint		getFrameCount() = 0;
		virtual void		release()=0;
		virtual float		getFrameInterval()=0;
	};
}

#endif