/******************************************************************
** �ļ���:	MpwDecoder.h
** ��  ��:	1.0
** ��  ��:	Mpw�ļ�������
** Ӧ  ��:  
******************************************************************/
#pragma once
#include "MpwFormat.h"
#include "IMpwDecoder.h"
#include <string>

using namespace std;

namespace xs
{
	class _RenderEngineExport  MpwDecoder : public IMpwDecoder
	{

		typedef vector< FrameInfoHeader > TLIST_FRAME;	
		// ֡������Ϣ
		TLIST_FRAME					m_listFrame;

		PackFileHeader	m_packFileHeader;

		std::string		m_strMpwFileName;

		uint			m_frames;

		/************************************************************************/
		/* constructor and deconstructor                                        */
		/************************************************************************/
	public:
		MpwDecoder();
		~MpwDecoder();

		/************************************************************************/
		/* �ⲿ���ú�������                                                     */
		/************************************************************************/
	public:
		/** ����mpw�ļ�
		@param strMpwFileName
		@return true -- load success false -- load fail.
		*/
		virtual bool load(const std::string & strMpwFileName);

		/** ����mpw�ļ�
		@param pszMpwFileName
		@return true -- load success false -- load fail.
		*/
		virtual bool load(const char* pszMpwFileName);

		/** �õ���֡��
		*/
		virtual ulong getTotalFrame();

		/** ȡ���ļ���ʽ
		*/
		virtual const char* getFileFormat(void);

		/** ȡ��Delay
		*/
		virtual ulong getPlayDelay();

		virtual void getImageOffset(int nFrame,int &nX,int &nY);
	
		/** ȡ����֡��
		@param nFrame ֡��
		@return NULL to fail.
		*/
		virtual Stream * getFrameData(int nFrame);

		/** �������
		*/
		void close();

		/** �ͷŶ���
		*/
		virtual void release() ;
	};
}

