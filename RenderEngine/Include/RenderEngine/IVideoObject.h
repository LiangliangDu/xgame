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
		virtual ITexture *	getTexture( uint frame) = NULL;
		virtual uint		getFrameCount() = NULL;
		virtual void		release()=NULL;
		virtual float		getFrameInterval()=NULL;
	};
}

#endif