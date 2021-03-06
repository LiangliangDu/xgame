#ifndef __ImageCodecSfp_H__
#define __ImageCodecSfp_H__

#include "ImageCodec.h"

namespace xs
{
	class ImageCodecSfp : public ImageCodec
	{
	protected:
		ImageCodecSfp();
	public:
		static ImageCodec*	Instance();
	public:
		ImageCodecImplement
	private:
		uchar m_defaultPal[512];
	};

}
#endif