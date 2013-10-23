/******************************************************************
** ��  ��:	Mpw�ļ��������ӿ�			
** Ӧ  ��:  
******************************************************************/
#pragma once
namespace xs
{
	struct IMpwDecoder
	{
		/** ����mpw�ļ�
		@param strMpwFileName
		@return true -- load success false -- load fail.
		*/
		virtual bool load(const std::string & strMpwFileName) = 0;

		/** ����mpw�ļ�
		@param pszMpwFileName
		@return true -- load success false -- load fail.
		*/
		virtual bool load(const char* pszMpwFileName) = 0;

		/** �õ���֡��
		*/
		virtual ulong getTotalFrame() = 0;

		/** ȡ���ļ���ʽ
		*/
		virtual const char* getFileFormat(void) = 0;

		/** ȡ��Delay
		*/
		virtual ulong getPlayDelay() = 0;

		virtual void getImageOffset(int nFrame,int &nX,int &nY) = 0;

		/** ȡ����֡��
		@param nFrame ֡��
		@return NULL to fail.
		*/
		virtual Stream * getFrameData(int nFrame) = 0;

		virtual void close() = 0;
		/** �ͷŶ���
		*/
		virtual void release() = 0;
	};
}