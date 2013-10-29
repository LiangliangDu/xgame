/******************************************************************
** ��  ��:	1.0
** ��  ��:	Mpw�ļ�������			
** Ӧ  ��:  
******************************************************************/

#include "Stdafx.h"

#include "MpwFormat.h"
#include "MpwDecoder.h"
namespace xs
{
	MpwDecoder::MpwDecoder()
	{
		m_frames = 0;
		m_listFrame.clear();
	}

	MpwDecoder::~MpwDecoder()
	{
		close();
	}

	void MpwDecoder::close()
	{
		// �ͷ�
		TLIST_FRAME::iterator itF = m_listFrame.begin();
		for( ; itF != m_listFrame.end(); ++itF)
		{
			FrameInfoHeader * pHeader = &(*itF);
			// �ͷ��ڴ�
			pHeader->Close();
		}
		m_listFrame.clear();
	}

	bool MpwDecoder::load(const char* pszMpwFileName)
	{
		//Info("mpw:"<<pszMpwFileName<<endl);
		m_strMpwFileName = pszMpwFileName;
		return load(m_strMpwFileName);
	}

	bool MpwDecoder::load(const std::string & strMpwFileName)
	{
		m_strMpwFileName = strMpwFileName;
		if(m_strMpwFileName.empty())
		{
			Error("RenderEngine::MpwDecoder::loader,strMpwFileName is empty,"<<strMpwFileName.c_str()<<endl);
			return false;
		}
		//���
		close();

		// �õ�mwd·��
		string stringTempMpwFileName = strMpwFileName;
		// ��mpw�ļ����Ƿ����
		CStreamHelper pStreamMpw = xs::getFileSystem()->open(stringTempMpwFileName.c_str());
		if(pStreamMpw == NULL)
		{
			Error("RenderEngine::MpwLoader::loader open mpw fail."<<stringTempMpwFileName.c_str()<<" not exist."<<endl);
			return false;
		}

		/////////////////////////////// ����ͷ�ļ���Ȼ�����ж��Ƿ���ܻ�ѹ��
		if(!m_packFileHeader.Open(pStreamMpw))
		{	
			pStreamMpw->close();
			Error("RenderEngine::MpwLoader::loader Invalid Pack File Header."<<strMpwFileName.c_str()<<endl);
			return false;
		}

		// ���Ƿ���ܻ���ѹ����
		bool  bCompressFlag = m_packFileHeader.GetCompressFlag() != 0 ? true : false;
		DWORD dwZipLen = m_packFileHeader.GetZipLen();
		if(bCompressFlag && dwZipLen <= 0)
		{
			pStreamMpw->close();
			Error("RenderEngine::MpwLoader::loader Invalid Zip code.\n");
			return false;
		}

		// �Ż���ȡ����֡
		m_listFrame.clear();
		for(DWORD i = 0; i < m_packFileHeader.GetTotalFrame(); i++)
		{
			FrameInfoHeader frameinfo;
			if(!frameinfo.Open(pStreamMpw))
			{
				pStreamMpw->close();
				Error("RenderEngine::MpwLoader::loader open frame error.");
				return false;
			}
			m_listFrame.push_back(frameinfo);
		}
		pStreamMpw->close();

		m_frames = m_listFrame.size();
		return true;
	}

	/** �õ���֡��
	*/
	ulong MpwDecoder::getTotalFrame()
	{
		if(m_frames)
			return m_packFileHeader.GetTotalFrame();
		return 0;
	}

	/** ȡ���ļ���ʽ
	*/
	const char* MpwDecoder::getFileFormat(void)
	{
		if(m_frames)
			return m_packFileHeader.GetFileFormat();
		return 0;
	}

	/** ȡ��Delay
	*/
	ulong MpwDecoder::getPlayDelay()
	{
		if(m_frames)
			return m_packFileHeader.GetPlayDelay();
		return 0;
	}

	void MpwDecoder::getImageOffset(int nFrame,int &nX,int &nY)
	{
		if(nFrame >= (int)(m_frames))
		{
			nX = 0;
			nY = 0;
			return;
		}
		
		m_listFrame[nFrame].GetImageOffset(nX,nY);
	}

	/** ȡ����֡��
	@param nFrame ֡��
	@return NULL to fail.
	*/
	Stream * MpwDecoder::getFrameData(int nFrame)
	{
		if(nFrame >= (int)(m_frames))
			return NULL;
		int nImageSize = 0;
		return m_listFrame[nFrame].GetImageData(nImageSize);
	}

	void MpwDecoder::release() 
	{
		close();
		delete this;
	}
}