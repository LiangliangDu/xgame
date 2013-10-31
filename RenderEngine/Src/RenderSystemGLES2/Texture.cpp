#include "StdAfx.h"
#include "Texture.h"
#include "GLPixelFormat.h"



namespace xs
{
	extern GLuint getCombinedMinMipFilter(FilterOptions mMinFilter,FilterOptions mMipFilter);
	extern void getCombinedMinMipFilter(GLuint filter,FilterOptions &mMinFilter,FilterOptions &mMipFilter);

	void  Texture::release()
	{
		m_pTextureManager->releaseTexture(this);
	}

	uint	Texture::width()
	{
		return m_ui32Width;
	}

	uint	Texture::height()
	{
		return m_ui32Height;
	}

	uint	Texture::depth()
	{
		return m_ui32Depth;
	}

	uint	Texture::getNumMipmaps()
	{
		return m_ui32NumMipmaps;
	}
	uint	Texture::getNumFaces()
	{
		return m_i32Flags & IF_CUBEMAP ? 6 : 1;
	}

	bool	Texture::hasAlpha()
	{
		return PixelUtil::getFlags(m_pf) & PFF_HASALPHA;
	}

	PixelFormat	Texture::getPixelFormat()
	{
		return m_pf;
	}

	bool	Texture::isCompressed()
	{
		return m_i32Flags & IF_COMPRESSED ? true : false;
	}

	GLuint		Texture::getGLTextureID()
	{
		return m_gluiTextureID;
	}

	void		Texture::setWidth(uint w)
	{
		m_ui32Width = w;
	}
	void		Texture::setHeight(uint h)
	{
		m_ui32Height = h;
	}
	void		Texture::setDepth(uint d)
	{
		m_ui32Depth = d;
	}
	void		Texture::setGLTextureID(GLuint id)
	{
		m_gluiTextureID = id;
	}
	void		Texture::setNumMipmaps(uint numMipmaps)
	{
		m_ui32NumMipmaps = numMipmaps;
	}
	void		Texture::setFlags(int flags)
	{
		m_i32Flags = flags;
	}
	void		Texture::setPixelFormat(PixelFormat pf)
	{
		m_pf = pf;
	}
	
	const std::string&	Texture::getName()
	{
		return m_strName;
	}

	bool		Texture::_loadFromImage(const Image& image , Image * pImage)
	{
		//modified by xxh 20091029,��ѹ������ļ��ط����ŵ���Ⱦ�߳�����
		
		//1,���û������ԣ�û���ϴ�����Ҳ����
		setWidth(image.getWidth());
		setHeight(image.getHeight());
		setDepth(image.getDepth());
		//pTexture->setGLTextureID(id);
		setNumMipmaps(image.getNumMipmaps());
		setFlags(image.getFlags());
		setPixelFormat(image.getFormat());

		TextureManager * pTM = static_cast<TextureManager *> (m_pTextureManager);
		ulong ulCurThreadId = static_cast<ulong>(GetCurrentThreadId() );
		if( pTM->getRenderThreadID() != ulCurThreadId) //��ͬ���̣߳�����ʱ����
		{
			if( isCompressed() )
			{
				assert(0);   //��ʱ��֧��ѹ��

				/*
				//��ѹ������ֻ�Ǹ��²����������ϴ�����
				GLenum format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
				PixelFormat pf = getPixelFormat();
				switch(pf)
				{
				case PF_RGB_DXT1:
					format = GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
					break;
				case PF_DXT1:
					format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
					break;
				case PF_DXT3:
					format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
					break;
				case PF_DXT5:
					format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
					break;
				}
				uint dwWidth = this->width();
				uint dwHeight = this->height();
				uint dwDepth = depth();
				uint dwMipMapCount = getNumMipmaps();
				for(uint i = 0;i < dwMipMapCount;i++)
				{
					size_t dwSize = PixelUtil::getMemorySize(dwWidth,dwHeight,dwDepth,pf);//max(1,dwWidth / 4) * max(1,dwHeight / 4) * dwMinSize;

					dwWidth /= 2;
					dwHeight /= 2;
					if(dwWidth == 0)dwWidth = 1;
					if(dwHeight == 0)dwHeight = 1;

					m_memorySize += dwSize;
				}
				//��ͼƬ���ݻ���,�������ñ�־λ
				if( pImage !=0 )
				{
					InterlockedExchangePointer(&m_pImageBuffer, pImage);
				}
				else
				{
					//���ַ�����Ӱ��Ч��
					Image * pTempImg = new Image(image);
					if( 0 == pTempImg) return false;
					InterlockedExchangePointer(&m_pImageBuffer, pTempImg);
					pTempImg = 0;	
				}
				*/
			}
			else
			{
				PixelFormat pf = getPixelFormat();
				GLenum internalFormat = GLPixelUtil::getClosestGLInternalFormat(pf);
				GLenum format = GLPixelUtil::getGLOriginFormat(pf);
				GLenum dataType = GLPixelUtil::getGLOriginDataType(pf);
				uint ui32NumMipmaps = getNumMipmaps();
				const uchar *pData = image.getData();
				uint w = this->width();
				uint h = this->height();
				uint d = depth();

				for(uint i = 0;i < ui32NumMipmaps;i++)
				{
					uint size = PixelUtil::getMemorySize(w,h,d,pf);
					pData += size;
					w /= 2;
					h /= 2;
					if(w == 0)w = 1;
					if(h == 0)h = 1;

					m_memorySize += size;	
				}

				//�ͷ�pImage
				if(!pImage) 
				{
					//���ַ�����Ӱ��Ч��
					Image * pTempImg = new Image(image);
					if( 0 == pTempImg) return false;

#if (TARGET_PLATFORM == PLATFORM_WIN32)
					InterlockedExchangePointer(&m_pImageBuffer, pTempImg);
#elif (TARGET_PLATFORM == PLATFORM_IOS)
                    OSAtomicCompareAndSwapPtr((void*)m_pImageBuffer,(void*)pTempImg,(void * volatile *)&m_pImageBuffer);
#else
                    assert(0); //todo
#endif
                    
					pTempImg = 0;
				}
				else
				{
				
#if (TARGET_PLATFORM == PLATFORM_WIN32)
					InterlockedExchangePointer(&m_pImageBuffer, pImage);
#elif (TARGET_PLATFORM == PLATFORM_IOS)
                    OSAtomicCompareAndSwapPtr((void*)m_pImageBuffer,(void*)pImage,(void * volatile *)&m_pImageBuffer);
#else
                    assert(0); //todo
#endif
				}
			}
		}
		else
		{
			if( isCompressed() )
			{
				assert(0);

				/*
				GLenum format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
				PixelFormat pf = getPixelFormat();
				switch(pf)
				{
				case PF_RGB_DXT1:
					format = GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
					break;
				case PF_DXT1:
					format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
					break;
				case PF_DXT3:
					format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
					break;
				case PF_DXT5:
					format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
					break;
				}
				uint dwWidth = this->width();
				uint dwHeight = this->height();
				uint dwDepth = depth();
				uint dwMipMapCount = getNumMipmaps();

				glBindTexture(GL_TEXTURE_2D,m_gluiTextureID);

				if(m_ui32NumMipmaps <= 1)
				{
					GLint minFilter;
					glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,&minFilter);
					FilterOptions foMin,foMip;
					getCombinedMinMipFilter(minFilter,foMin,foMip);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,getCombinedMinMipFilter(foMin,FO_NONE));
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_LOD,0);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, 0 );
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL,0);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL,0);
				}

				const uchar * pData =image.getData();

				for(uint i = 0;i < dwMipMapCount;i++)
				{
					size_t dwSize = PixelUtil::getMemorySize(dwWidth,dwHeight,dwDepth,pf);
					glCompressedTexImage2D(GL_TEXTURE_2D,i,format,dwWidth,dwHeight,0,dwSize,pData);
					pData += dwSize;
					dwWidth /= 2;
					dwHeight /= 2;
					if(dwWidth == 0)dwWidth = 1;
					if(dwHeight == 0)dwHeight = 1;

					m_memorySize += dwSize;
				}

				//�ͷ�pImage
				if( pImage ) delete pImage;
				pImage = 0;

				//���ü��ر�־
				InterlockedExchange(&m_lUploadFlag, (LONG)1);
				*/
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D,m_gluiTextureID);

				if(m_ui32NumMipmaps <= 1)
				{
					GLint minFilter;
					glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,&minFilter);
					FilterOptions foMin,foMip;
					getCombinedMinMipFilter(minFilter,foMin,foMip);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,getCombinedMinMipFilter(foMin,FO_NONE));
					
					//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_LOD,0);
					//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, 0 );
					//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL,0);
					//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL,0);
				}

				PixelFormat pf = getPixelFormat();
				GLenum internalFormat = GLPixelUtil::getClosestGLInternalFormat(pf);
				GLenum format = GLPixelUtil::getGLOriginFormat(pf);
				GLenum dataType = GLPixelUtil::getGLOriginDataType(pf);
				uint ui32NumMipmaps = getNumMipmaps();
				const uchar *pData = image.getData();
				uint w = this->width();
				uint h = this->height();
				uint d = depth();

				for(uint i = 0;i < ui32NumMipmaps;i++)
				{
					uint size = PixelUtil::getMemorySize(w,h,d,pf);

					glTexImage2D(
						GL_TEXTURE_2D,
						i,
						internalFormat,
						w,
						h,
						0,
						format,
						dataType,
						pData);

					pData += size;
					w /= 2;
					h /= 2;
					if(w == 0)w = 1;
					if(h == 0)h = 1;

					m_memorySize += size;	
				}

				//�ͷ�pImage
				if(pImage) delete pImage;
				pImage = 0;
				//���������ϴ���־λ
				
                long ltemp = 1;
#if (TARGET_PLATFORM == PLATFORM_WIN32)
                InterlockedExchange(&m_lUploadFlag, (LONG)1);
#elif (TARGET_PLATFORM == PLATFORM_IOS)
                OSAtomicCompareAndSwapPtr((void*)m_lUploadFlag,(void*)ltemp,(void * volatile *)&m_lUploadFlag);
#else
                assert(0); //todo
#endif
			}
		}
		return true;

#if 0

		//2,��ѹ���ͷ�ѹ������Ĳ�ͬ�������
		
		if( isCompressed())//ѹ������
		{

			//��ѹ������ֻ�Ǹ��²����������ϴ�����
			GLenum format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			PixelFormat pf = getPixelFormat();
			switch(pf)
			{
			case PF_RGB_DXT1:
				format = GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
				break;
			case PF_DXT1:
				format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
				break;
			case PF_DXT3:
				format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
				break;
			case PF_DXT5:
				format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
				break;
			}
			uint dwWidth = this->width();
			uint dwHeight = this->height();
			uint dwDepth = depth();
			uint dwMipMapCount = getNumMipmaps();

			TextureManager * pTM = static_cast<TextureManager *> (m_pTextureManager);
			ulong ulCurThreadId = static_cast<ulong>(GetCurrentThreadId() );
			if( pTM->getRenderThreadID() != ulCurThreadId) //��ͬ���̣߳�����ʱ����
			{
				for(uint i = 0;i < dwMipMapCount;i++)
				{
					size_t dwSize = PixelUtil::getMemorySize(dwWidth,dwHeight,dwDepth,pf);//max(1,dwWidth / 4) * max(1,dwHeight / 4) * dwMinSize;

					dwWidth /= 2;
					dwHeight /= 2;
					if(dwWidth == 0)dwWidth = 1;
					if(dwHeight == 0)dwHeight = 1;

					m_memorySize += dwSize;
				}
				//��ͼƬ���ݻ���,�������ñ�־λ
				if( pImage !=0 )
				{
					InterlockedExchangePointer(&m_pImageBuffer, pImage);
				}
				else
				{
					//���ַ�����Ӱ��Ч��
					Image * pTempImg = new Image(image);
					if( 0 == pTempImg) return false;
					InterlockedExchangePointer(&m_pImageBuffer, pTempImg);
					pTempImg = 0;	
				}
						
			}
			else//ͬһ���̣߳���ֱ�Ӽ���
			{
				glBindTexture(GL_TEXTURE_2D,m_gluiTextureID);

				if(m_ui32NumMipmaps <= 1)
				{
					GLint minFilter;
					glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,&minFilter);
					FilterOptions foMin,foMip;
					getCombinedMinMipFilter(minFilter,foMin,foMip);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,getCombinedMinMipFilter(foMin,FO_NONE));
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_LOD,0);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, 0 );
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL,0);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL,0);
				}

				const uchar * pData =image.getData();

				for(uint i = 0;i < dwMipMapCount;i++)
				{
					size_t dwSize = PixelUtil::getMemorySize(dwWidth,dwHeight,dwDepth,pf);
					glCompressedTexImage2D(GL_TEXTURE_2D,i,format,dwWidth,dwHeight,0,dwSize,pData);
					pData += dwSize;
					dwWidth /= 2;
					dwHeight /= 2;
					if(dwWidth == 0)dwWidth = 1;
					if(dwHeight == 0)dwHeight = 1;

					m_memorySize += dwSize;
				}

				//�ͷ�pImage
				if( pImage ) delete pImage;
				pImage = 0;

				//���ü��ر�־
				InterlockedExchange(&m_lUploadFlag, (LONG)1);
				
			}
		
		}
		else//��ѹ��������첽����
		{
			glBindTexture(GL_TEXTURE_2D,m_gluiTextureID);

			if(m_ui32NumMipmaps <= 1)
			{
				GLint minFilter;
				glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,&minFilter);
				FilterOptions foMin,foMip;
				getCombinedMinMipFilter(minFilter,foMin,foMip);
				glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,getCombinedMinMipFilter(foMin,FO_NONE));
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_LOD,0);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, 0 );
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL,0);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL,0);
			}

			PixelFormat pf = getPixelFormat();
			GLenum internalFormat = GLPixelUtil::getClosestGLInternalFormat(pf);
			GLenum format = GLPixelUtil::getGLOriginFormat(pf);
			GLenum dataType = GLPixelUtil::getGLOriginDataType(pf);
			uint ui32NumMipmaps = getNumMipmaps();
			const uchar *pData = image.getData();
			uint w = this->width();
			uint h = this->height();
			uint d = depth();

			for(uint i = 0;i < ui32NumMipmaps;i++)
			{
				uint size = PixelUtil::getMemorySize(w,h,d,pf);

				glTexImage2D(
					GL_TEXTURE_2D,
					i,
					internalFormat,
					w,
					h,
					0,
					format,
					dataType,
					pData);

				pData += size;
				w /= 2;
				h /= 2;
				if(w == 0)w = 1;
				if(h == 0)h = 1;

				m_memorySize += size;	
			}

			//�ͷ�pImage
			if(pImage) delete pImage;
			pImage = 0;
			//���������ϴ���־λ
			InterlockedExchange(&m_lUploadFlag, (LONG)1);
		}

		return true;
#endif

		/*

		setWidth(image.getWidth());
		setHeight(image.getHeight());
		setDepth(image.getDepth());
		//pTexture->setGLTextureID(id);
		setNumMipmaps(image.getNumMipmaps());
		setFlags(image.getFlags());
		setPixelFormat(image.getFormat());

		glBindTexture(GL_TEXTURE_2D,m_gluiTextureID);

		if(m_ui32NumMipmaps <= 1)
		{
			GLint minFilter;
			glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,&minFilter);
			FilterOptions foMin,foMip;
			getCombinedMinMipFilter(minFilter,foMin,foMip);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,getCombinedMinMipFilter(foMin,FO_NONE));
		}

		if(isCompressed())
		{
			GLenum format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
			uint dwMinSize = 8;
			PixelFormat pf = getPixelFormat();
			switch(pf)
			{
			case PF_RGB_DXT1:
				format = GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
				dwMinSize = 8;
				break;
			case PF_DXT1:
				format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
				dwMinSize = 8;
				break;
			case PF_DXT3:
				format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
				dwMinSize = 16;
				break;
			case PF_DXT5:
				format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
				dwMinSize = 16;
				break;
			}
			uint dwWidth = this->width();
			uint dwHeight = this->height();
			uint dwDepth = depth();
			uint dwMipMapCount = getNumMipmaps();
			const uchar *pData = image.getData();
			for(uint i = 0;i < dwMipMapCount;i++)
			{
				size_t dwSize = PixelUtil::getMemorySize(dwWidth,dwHeight,dwDepth,pf);//max(1,dwWidth / 4) * max(1,dwHeight / 4) * dwMinSize;

				//modified by xxh 20091029, ���ַ�����Ӧnvidia�����ֲ�ͬ�汾����������ûʲô�õĽ���취�����ڰ������ϴ��ŵ���Ⱦ�߳�����
				//modified by xxh 20091019, ���ֻ�ú���glCompressedTexImage2D���ڸ����̼߳���ʱ�����������
				//���ڲ��õķ�ʽ������glCompressedTexImage2D���������Կ��ڴ棬�����Ӻ���glCompressedTexSubImage2D�ϴ��������ݡ�
				//glCompressedTexImage2D(GL_TEXTURE_2D,i,format,dwWidth,dwHeight,0,dwSize,pData);
				//glCompressedTexImage2D(GL_TEXTURE_2D,i,format,dwWidth,dwHeight,0,dwSize,0);
				//glCompressedTexSubImage2D(GL_TEXTURE_2D, i, 0, 0, dwWidth, dwHeight,format, dwSize , pData);

				pData += dwSize;
				dwWidth /= 2;
				dwHeight /= 2;
				if(dwWidth == 0)dwWidth = 1;
				if(dwHeight == 0)dwHeight = 1;

				m_memorySize += dwSize;
			}
		}
		else
		{
			PixelFormat pf = getPixelFormat();
			GLenum internalFormat = GLPixelUtil::getClosestGLInternalFormat(pf);
			GLenum format = GLPixelUtil::getGLOriginFormat(pf);
			GLenum dataType = GLPixelUtil::getGLOriginDataType(pf);
			uint ui32NumMipmaps = getNumMipmaps();
			const uchar *pData = image.getData();
			uint w = this->width();
			uint h = this->height();
			uint d = depth();

			for(uint i = 0;i < ui32NumMipmaps;i++)
			{
				uint size = PixelUtil::getMemorySize(w,h,d,pf);

				glTexImage2D(
					GL_TEXTURE_2D,
					i,
					internalFormat,
					w,
					h,
					0,
					format,
					dataType,
					pData);

				pData += size;
				w /= 2;
				h /= 2;
				if(w == 0)w = 1;
				if(h == 0)h = 1;

				m_memorySize += size;
			}
		}

		return true;
		*/
	}

	bool			Texture::loadFromFile(const std::string& name)
	{
		//commeted by xxh
		//Image image;
		//if(!image.load(name))return false;
		//return _loadFromImage(image);

		//added by xxh
		Image * pImage = new Image();
		if( !pImage ) return false;
		if( !pImage->load(name) ) return false;
		return _loadFromImage(*pImage, pImage);	//˵�����pImage���Դ洢����Ȼ�����ĺ���Ҫ�����ͷ�
	}

	bool			Texture::loadFromImage(const Image& image,const Rect* pRect)
	{
		uint width = image.getWidth();
		uint height = image.getHeight();
		assert(width > 0 && height > 0 && "Texture::loadFromImage not support zero-width texture!\n");

		Rect rcImage(0,0,width - 1,height - 1);
		if(!pRect || rcImage == *pRect)return _loadFromImage(image);

		Image sub;
		if(sub.subImage(image,*pRect))
		{
			return _loadFromImage(sub);
		}

		return false;

		/*bool bWholeImage = true;
		if(pRect && rcImage != *pRect)bWholeImage = false;

		if(bWholeImage)
		{
			rect = rcImage;
		}
		else
		{
			if(image.hasFlag(IF_COMPRESSED))
			{
				Error("Texture::loadFromImage sub-texture not support compressed textures!\n");
				return false;
			}
			rect = *pRect;
			if(rect.left > rect.right){int t = rect.left;rect.left = rect.right;rect.right = t;}
			if(rect.top > rect.bottom){int t = rect.top;rect.top = rect.bottom;rect.bottom = t;}
			if(rect.left < 0)rect.left = 0;
			if(rect.top < 0)rect.top = 0;
			if(rect.right > (int)width - 1)rect.right = width - 1;
			if(rect.bottom > (int)height - 1)rect.bottom = height - 1;
		}*/

		return true;
	}

	bool			Texture::loadFromRawData(uchar *pBuffer,uint width,uint height,PixelFormat pf)
	{	
		setWidth(width);
		setHeight(height);
		setDepth(1);
		//pTexture->setGLTextureID(id);
		setNumMipmaps(1);
		setFlags(0);
		setPixelFormat(pf);

		TextureManager * pTM = static_cast<TextureManager *> (m_pTextureManager);
		ulong ulCurThreadId = static_cast<ulong>(GetCurrentThreadId() );
		if( pTM->getRenderThreadID() != ulCurThreadId) 
		{
			PixelFormat pf = getPixelFormat();
			GLenum internalFormat = GLPixelUtil::getClosestGLInternalFormat(pf);
			GLenum format = GLPixelUtil::getGLOriginFormat(pf);
			GLenum dataType = GLPixelUtil::getGLOriginDataType(pf);
			uint ui32NumMipmaps = getNumMipmaps();
			xs::Image * pTempImg = new xs::Image();
			uint memsize = PixelUtil::getMemorySize(width,height,1, pf) ;
			uchar * buffer = new uchar[memsize];
			memcpy(buffer, pBuffer, memsize);
			pTempImg->loadDynamicImage( buffer, width, height, 1, pf,true,1,1);
#ifdef RKT_WIN32
			InterlockedExchangePointer(&m_pImageBuffer, pTempImg);
#else
			m_pImageBuffer = pTempImg;
#endif
			const uchar *pData = m_pImageBuffer->getData();
			uint w = this->width();
			uint h = this->height();
			uint d = depth();

			for(uint i = 0;i < ui32NumMipmaps;i++)
			{
				uint size = PixelUtil::getMemorySize(w,h,d,pf);
				pData += size;
				w /= 2;
				h /= 2;
				if(w == 0)w = 1;
				if(h == 0)h = 1;

				m_memorySize += size;	
			}
		}
		else
		{
			glBindTexture(GL_TEXTURE_2D,m_gluiTextureID);
			glTexImage2D(GL_TEXTURE_2D,0,GLPixelUtil::getClosestGLInternalFormat(pf),width,height,0,GLPixelUtil::getGLOriginFormat(pf),GLPixelUtil::getGLOriginDataType(pf),pBuffer);

			//modified by xxh 20091029, ���ǵ�ѹ�������ͬ���ϴ�
			//���ñ�־λ
			
            long ltemp = 1;
#if (TARGET_PLATFORM == PLATFORM_WIN32)
            InterlockedExchange(&m_lUploadFlag,(LONG)1);
#elif (TARGET_PLATFORM == PLATFORM_IOS)
            OSAtomicCompareAndSwapPtr((void*)m_lUploadFlag,(void*)ltemp,(void * volatile *)&m_lUploadFlag);
#else
            assert(0); //todo
#endif

		}



		return true;
	}

	bool			Texture::setSubData(uint level,uint left,uint top,uint width,uint height,void  *pData)
	{
		//modified by xxh 20091029 ����ͬ���ϴ�ѹ������
		if( m_lUploadFlag != 1) return false;

		if(width == 0 || height == 0 || !pData)return false;
		if(m_gluiTextureID == 0)return false;

		//GLint unpackAlignmentSave;
		//glGetIntegerv(GL_UNPACK_ALIGNMENT,&unpackAlignmentSave);
		//glPixelStorei( GL_UNPACK_ALIGNMENT, 1);

		glBindTexture( GL_TEXTURE_2D, m_gluiTextureID);
		if(isCompressed())
		{
			glCompressedTexSubImage2D( GL_TEXTURE_2D, level, left, top, width, height, GLPixelUtil::getGLOriginFormat(m_pf), GLPixelUtil::getGLOriginDataType(m_pf), pData);
		}
		else
		{
			glTexSubImage2D( GL_TEXTURE_2D, level, left, top, width, height, GLPixelUtil::getGLOriginFormat(m_pf), GLPixelUtil::getGLOriginDataType(m_pf), pData);
		}
		//4 is the default value
		//glPixelStorei( GL_UNPACK_ALIGNMENT, unpackAlignmentSave);

		//GLint gmm;
		//glGetTexParameteriv(GL_TEXTURE_2D,GL_GENERATE_MIPMAP,&gmm);
/*
		uchar *pPixels = new uchar[256 * 256];
		glGetTexImage(GL_TEXTURE_2D,0,GL_ALPHA,GL_UNSIGNED_BYTE,pPixels);
		FILE *fp = fopen("1.raw","wb+");
		if(fp)
		{
			fwrite(pPixels,256 * 256,1,fp);
			fclose(fp);
		}
		delete[] pPixels;
*/

		return true;
	}

	bool			Texture::setSubData(uint level,const Image& image,const Rect* pRect)
	{
		//modified by xxh 20091029 ����ͬ���ϴ�ѹ������
		if( m_lUploadFlag != 1) return false;

		if(m_gluiTextureID == 0)return false;
		if(m_pf != image.getFormat())return false;

		if(isCompressed())return false;

		uint imageWidth = image.getWidth();
		uint imageHeight = image.getHeight();
		Rect rcImage = Rect(0,0,imageWidth - 1,imageHeight - 1);
		Rect rcIntersect;
		if(pRect)
		{
			if(!rcImage.intersect(*pRect,rcIntersect))
			{
				Error("Texture::setSubData pRect is not within image");
				return false;
			}
		}
		else
		{
			rcIntersect = rcImage;
		}
		if((uint)rcIntersect.width() > m_ui32Width)
		{
			rcIntersect.right = rcIntersect.left + m_ui32Width;
		}
		if((uint)rcIntersect.height() > m_ui32Height)
		{
			rcIntersect.bottom = rcIntersect.top + m_ui32Height;
		}

		Image sub;
		if(sub.subImage(image,rcIntersect))
		{
			if(isCompressed())
			{
				glCompressedTexSubImage2D( GL_TEXTURE_2D, level, 0, 0, sub.getWidth(), sub.getHeight(), GLPixelUtil::getGLOriginFormat(m_pf), GLPixelUtil::getGLOriginDataType(m_pf), sub.getData());
			}
			else
			{
				glTexSubImage2D( GL_TEXTURE_2D, level, 0, 0, sub.getWidth(), sub.getHeight(), GLPixelUtil::getGLOriginFormat(m_pf), GLPixelUtil::getGLOriginDataType(m_pf), sub.getData());
			}

			return true;
		}

		return false;
		/*glBindTexture( GL_TEXTURE_2D, m_gluiTextureID);
		uint h = rcIntersect.height();
		uint w = rcIntersect.width();
		uchar *pData = (uchar*)image.getData() + (rcIntersect.top * image.getWidth() + rcIntersect.left) * image.getPixelSize();
		for(uint i = 0;i < h;i++)
		{
			glTexSubImage2D(
				GL_TEXTURE_2D,
				level,
				rcIntersect.left,rcIntersect.top + i,
				w,
				1,
				GLPixelUtil::getGLOriginFormat(m_pf),
				GLPixelUtil::getGLOriginDataType(m_pf),
				pData);
			pData += image.getLineSize();
		}*/

		return true;
	}

	size_t Texture::getMemorySize()
	{
		return m_memorySize;
	}


	void Texture::setCustomInfo(const std::string & key, const std::string & val)
	{
		m_customInfo[key] = val;
	}


	bool Texture::getCustomInfo(const std::string & key, std::string & val)
	{
		CustomInfoMap::iterator it = m_customInfo.find(key);
		if( it == m_customInfo.end() )
			return false;

		val = it->second;
		return true;
	}

	bool Texture::realUpLoadTextureToGraphicMemory()
	{
		if( m_lUploadFlag == 1 ) return true;
		else if ( m_pImageBuffer) //�ϴ�����
		{
			if( isCompressed() )
			{
				assert(0);

				/*
				glBindTexture(GL_TEXTURE_2D,m_gluiTextureID);

				if(m_ui32NumMipmaps <= 1)
				{
					GLint minFilter;
					glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,&minFilter);
					FilterOptions foMin,foMip;
					getCombinedMinMipFilter(minFilter,foMin,foMip);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,getCombinedMinMipFilter(foMin,FO_NONE));
					
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_LOD,0);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, 0 );
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL,0);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL,0);
				}

				GLenum format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
				PixelFormat pf = getPixelFormat();
				switch(pf)
				{
				case PF_RGB_DXT1:
					format = GL_COMPRESSED_RGB_S3TC_DXT1_EXT;
					break;
				case PF_DXT1:
					format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
					break;
				case PF_DXT3:
					format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
					break;
				case PF_DXT5:
					format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
					break;
				}
				uint dwWidth = this->width();
				uint dwHeight = this->height();
				uint dwDepth = depth();
				uint dwMipMapCount = getNumMipmaps();
				const uchar * pData = m_pImageBuffer->getData();
				for(uint i = 0;i < dwMipMapCount;i++)
				{
					size_t dwSize = PixelUtil::getMemorySize(dwWidth,dwHeight,dwDepth,pf);
					glCompressedTexImage2D(GL_TEXTURE_2D,i,format,dwWidth,dwHeight,0,dwSize,pData);

					pData += dwSize;
					dwWidth /= 2;
					dwHeight /= 2;
					if(dwWidth == 0)dwWidth = 1;
					if(dwHeight == 0)dwHeight = 1;
				}

				//���ñ�־λ������ɾ��ͼ�񻺴�
				InterlockedExchange(&m_lUploadFlag, (LONG)1);
				delete m_pImageBuffer;
				m_pImageBuffer = 0;
				return true;
				*/
				return false;
			}
			else//��ѹ���������Ѿ���load��ʱ���ϴ���
			{
				
				glBindTexture(GL_TEXTURE_2D,m_gluiTextureID);

				if(m_ui32NumMipmaps <= 1)
				{
					GLint minFilter;
					glGetTexParameteriv(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,&minFilter);
					FilterOptions foMin,foMip;
					getCombinedMinMipFilter(minFilter,foMin,foMip);
					glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,getCombinedMinMipFilter(foMin,FO_NONE));
					
					/*
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_LOD,0);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LOD, 0 );
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL,0);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL,0);
					*/
				}

				PixelFormat pf = getPixelFormat();
				GLenum internalFormat = GLPixelUtil::getClosestGLInternalFormat(pf);
				GLenum format = GLPixelUtil::getGLOriginFormat(pf);
				GLenum dataType = GLPixelUtil::getGLOriginDataType(pf);
				uint ui32NumMipmaps = getNumMipmaps();
				const uchar *pData = m_pImageBuffer->getData();
				uint w = this->width();
				uint h = this->height();
				uint d = depth();

				for(uint i = 0;i < ui32NumMipmaps;i++)
				{
					uint size = PixelUtil::getMemorySize(w,h,d,pf);

					glTexImage2D(
						GL_TEXTURE_2D,
						i,
						internalFormat,
						w,
						h,
						0,
						format,
						dataType,
						pData);

					pData += size;
					w /= 2;
					h /= 2;
					if(w == 0)w = 1;
					if(h == 0)h = 1;
				}

				//���ñ�־λ������ɾ��ͼ�񻺴�
                
                long ltemp = 1;
#if (TARGET_PLATFORM == PLATFORM_WIN32)
                InterlockedExchange(&m_lUploadFlag,(LONG)1);
#elif (TARGET_PLATFORM == PLATFORM_IOS)
                OSAtomicCompareAndSwapPtr((void*)m_lUploadFlag,(void*)ltemp,(void * volatile *)&m_lUploadFlag);
#else
                assert(0); //todo
#endif
                
                
				delete m_pImageBuffer;
				m_pImageBuffer = 0;
				return true;
			}
			
		}
		else//����û�дӴ��̼��ص��ڴ�
		{
			return false;
		}
	}
}