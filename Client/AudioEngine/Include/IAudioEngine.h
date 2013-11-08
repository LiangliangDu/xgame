/********************************************************************	
*********************************************************************/
/***************************** HISTORY *******************************

*********************************************************************/
#pragma once

/*! \addtogroup AudioEngine
*  ��Ч����
*  @{
*/

/// ����Ĭ�ϵ������ͨ����
#define AUDIOENGINE_DEFAULT_MAXCHANNEL			32

/// ��Ч������������
#define INVALID_CHANNELID						-1

/// ��������
enum
{
	/// �ʺ���Щ��Ҫ��β��ŵ�С������Ƭ�Σ�������Ч��������ʱռ�ú��ٵ�CPU��������ʹ��Ӳ������
	SOUNDRES_TYPE_SOUND = 1,

	/// �ʺ���Щ��Ϊ̫����޷������ڴ�������������ᱻ������װ�뵽һС����FMOD����Ļ��λ����С�
	/// ���ռ������CPU��Ӳ�̴����������ļ���ʽ�������ٸ����ӣ�ʵʱ����MP3��Ȳ���һ��PCM(δ
	/// ѹ��WAV)�ļ�ռ�ø����CPU��һ����ʽ������ֻ�ܲ���һ�Σ���Ϊһ����ֻ��һ���ļ������һ�����λ���
	SOUNDRES_TYPE_STREAM = 2,
};

/// �����飬Ҳ���Ƕ���������һ�����ϣ�����ͬʱ��������С��ֹͣ���ŵ�
/// �˽ӿڲ�Ҫ���أ���Ϊ�������ڻ����ǿ��ת��
struct IChannelGroup
{
	/** �ͷ�
	@param   
	@param   
	@param   
	@return  
	@note     
	@warning 
	@retval buffer 
	*/
	virtual	void			Release(void) = 0;
	
	/** ����������С
	@param   fVolume ��������С(0.0 ~ 1.0)
	@param   
	@param   
	@return  �ɹ���TRUE��ʧ�ܣ�FALSE
	@note     
	@warning 
	@retval buffer 
	*/
	virtual BOOL			SetVolume(float fVolume) = 0;

	/** ȡ��������С
	@param   fVolume ������������С
	@param   
	@param   
	@return  �ɹ���TRUE��ʧ�ܣ�FALSE
	@note     
	@warning 
	@retval buffer 
	*/
	virtual BOOL			GetVolume(float &fVolume) = 0;

	/** ֹͣ������������
	@param   
	@param   
	@param   
	@return  �ɹ���TRUE��ʧ�ܣ�FALSE
	@note     
	@warning 
	@retval buffer 
	*/
	virtual BOOL			Stop(void) = 0;

	/** ���þ������
	@param   nChannel������������
	@param   bMute ��������TRUE,�Ǿ�����FALSE
	@param   
	@return  �ɹ���TRUE��ʧ�ܣ�FALSE
	@note     
	@warning 
	@retval buffer 
	*/
	virtual BOOL			SetMute(bool bMute) = 0;
};


/// ��Ч����ӿ�
struct IAudioEngine
{	
	/** �ͷ���Ч����
	 @param   
	 @param   
	 @param   
	 @return  
	 @note     
	 @warning 
	 @retval buffer 
	 */	
	virtual void			Release(void) = 0;

	/** ����һ��������
	@param   
	@param   
	@param   
	@return  ����һ�������飬����Ҫ�����ͷŴ��ڴ�
	@note     
	@warning 
	@retval buffer 
	*/
	virtual IChannelGroup *	CreateChannelGroup(void) = 0;


	/** ��SID�������ļ���Ӧ����,δ������������ʱ������SIDΪ��ʶ�������������ļ���
	@param   dwSID ��������ID�����ϲ���䣬ȫ��Ψһ
	@param   pstrFileName �������ļ���������·��
	@param   dwSoundType ���������ͣ�������������
	@return  �ɹ���TRUE��ʧ�ܣ�FALSE
	@note     
	@warning ����ͨ���˷�����������Դѹ��pool���ſ��Զ��������Ͻ��в���������
	@retval buffer 
	*/
	virtual BOOL			PutSoundResToPool(DWORD dwSID, LPCSTR pstrFileName, DWORD dwSoundType = SOUNDRES_TYPE_SOUND) = 0;

	
	/** ������Ч
	 @param   dwSID����ЧID
	 @param   nLoop��ѭ��������-1��һֱѭ����0����һ�Σ�1��2....��
	 @param   fVolume ��������С��0.0 ~ 1.0��
	 @param   pChannelGroup �������������θ�������
	 @return  �������������ţ�δ���ر��Ǹ�����ʱ����Ҫ�ṩ���������ţ����أ�1��ʧ��
	 @note     
	 @warning 
	 @retval buffer 
	 */
	virtual int				PlaySound(DWORD dwSID, int nLoop, float fVolume, IChannelGroup * pChannelGroup = NULL) = 0;

	/** �������������ţ�ֹͣ����
	@param   nChannel ������������
	@param   
	@param   
	@return  
	@note     
	@warning 
	@retval buffer 
	*/
	virtual void			StopSound(int nChannel) = 0;

	/** ����SID��ֹͣ����
	@param   nSID����ЧID
	@param   
	@param   
	@return  
	@note     
	@warning 
	@retval buffer 
	*/
	virtual void			StopSoundBySID(DWORD dwSID) = 0;

	/** ����������С
	@param   nChannel������������
	@param   fVolume ��������С(0.0 ~ 1.0)
	@param   
	@return  �ɹ���TRUE��ʧ�ܣ�FALSE
	@note     
	@warning 
	@retval buffer 
	*/
	virtual BOOL			SetVolume(int nChannel, float fVolume) = 0;

	/** ȡ��������С
	@param   nChannel������������
	@param   fVolume ������������С
	@param   
	@return  �ɹ���TRUE��ʧ�ܣ�FALSE
	@note     
	@warning 
	@retval buffer 
	*/
	virtual BOOL            GetVolume(int nChannel, float &fVolume) = 0;

	/** ���þ������
	@param   nChannel������������
	@param   bMute ��������TRUE,�Ǿ�����FALSE
	@param   
	@return  �ɹ���TRUE��ʧ�ܣ�FALSE
	@note     
	@warning 
	@retval buffer 
	*/
	virtual BOOL			SetMute(int nChannel, bool bMute) = 0;


	/** ȡ��������С
	@param   nChannel������������
	@param   bMute ������ ������TRUE,�Ǿ�����FALSE
	@param   
	@return  �ɹ���TRUE��ʧ�ܣ�FALSE
	@note     
	@warning 
	@retval buffer 
	*/
	virtual BOOL            GetMute(int nChannel, bool &bMute) = 0;

};
/** @} */

///////////////////////////////////////////////////////////////////////////////////////////////////////
#if defined(_LIB) || defined(AUDIOENGINE_STATIC_LIB)	/// ��̬��汾
	#	pragma comment(lib, MAKE_LIB_NAME(xs_cae))
	extern "C" IAudioEngine * LoadCAE(int nMaxChannel, int nPoolMaxSize);
	#	define	CreateAudioEngineProc	LoadCAE
#else													/// ��̬��汾
	typedef IAudioEngine * (RKT_CDECL *procCreate)(int nMaxChannel, int nPoolMaxSize);
	#define	CreateAudioEngineProc	DllApi<procCreate>::load(MAKE_DLL_NAME(xs_cae), "LoadCAE")//����@@��
#endif
