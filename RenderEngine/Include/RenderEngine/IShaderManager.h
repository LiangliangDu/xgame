#ifndef __I_ShaderManager_H__
#define __I_ShaderManager_H__
/*

дGLSL��shaderʱ�򣬰󶨲�������Ӧ��
"texture0": 0
"texture1": 1
"texture2": 2
"texture3": 3
"texture4": 4
"texture5": 5
"texture6": 6 
"texture7": 7


дHLSL�� �任�����Ӧ��ֻ��vertex shader ��Ч
"WORLD_MATRIX": world matrix
"VIEW_MATRIX": view matrix
"WORLD_VIEW_MATRIX": world view matrix
"PROJECTION_MATRIX": projection matrix
"VIEW_PROJECTION_MATRIX": view projection matrix
"WORLD_VIEW_PROJECTION_MATRIX": world view projection matrix
"WORLD_NORMAL_MATRIX":transform normal from object  to world space
"VIEW_NORMAL_MATRIX":transform normal from  world space to view space
"WORLD_VIEW_NORMAL_MATRIX":transform normal from object space to view space

*/

namespace xs
{
	/*! addtogroup RenderEngine
	*  ��Ⱦ����
	*  @{
	*/

	enum ShaderType
	{
		ST_VERTEX_PROGRAM,
		ST_FRAGMENT_PROGRAM
	};

	/** ��ɫ���ӿ�,����ӿ���ʱ���ڲ�ʹ�ã��ⲿ��ȡ����
	*/
	struct IShader
	{
		/** �����ɫ�����Ͷ�����ɫ������������ɫ��
		@return ��ɫ������
		@see ShaderType
		*/
		virtual ShaderType		getType() = 0;

		/** ������ɫ��
		@return �Ƿ�ɹ�
		*/
		virtual bool			compile() = 0;

		/** �󶨵�����ɫ��
		@return �Ƿ�󶨳ɹ�
		*/
		virtual bool			bind() = 0;	

		/** ȡ���󶨴���ɫ������bind����ʹ��
		*/
		virtual void 			unbind() = 0;
	};


	/**�任��������
	*/
	enum TransformMatrixType
	{
		// world matrix
		TMT_WORLD = 0x1,
		// view matrix
		TMT_VIEW = 0x2,
		// world view matrix
		TMT_WORLD_VIEW = 0x4,
		// projection matrix
		TMT_PROJECTION = 0x8,
		// view projection matrix
		TMT_VIEW_PROJECTION = 0x10,
		// world view and projection matrix
		TMT_WORLD_VIEW_PROJECTION = 0x20,
		// transform normal from object  to world space
		TMT_WORLD_NORMAL = 0x40,
		// transform normal from  world space to view space
		TMT_VIEW_NORMAL = 0x80,
		// transform normal from object space to view space
		TMT_WORLD_VIEW_NORMAL = 0x100,
	};

	/** ��ɫ����������
	*/
	enum ShaderProgramType
	{
		SPT_LOWLEVEL, //�ͽ�shader����
		SPT_HIGHLEVEL,//�߽�shader����
	};

	/** ��ɫ������ӿ�
	*/
	struct IShaderProgram
	{
		/** ��ȡ��ɫ����������
		*/
		virtual ShaderProgramType getProgramType()=0;

		/** �ͷ���ɫ������
		*/
		virtual void 			release() = 0;

		/** �󶨵�����ɫ������
		@return �Ƿ�ɹ�
		*/
		virtual bool			bind() = 0;	

		/** ȡ���󶨵�����ɫ��
		*/
		virtual void 			unbind() = 0;

		/** ���ļ��������ɫ��
		@param ShaderType ��ɫ������
		@param fn �ļ���
		@return ��ɫ���ӿ�ָ��
		*/
		virtual bool			addShaderFromFile(ShaderType st,const std::string& fn) = 0;	

		/** ���ڴ������������ɫ��
		@param ShaderType ��ɫ������
		@param pBuffer ���ݵ�ַ
		@param len ���ݳ���
		@return ��ɫ���ӿ�ָ��
		@see ShaderType
		*/
		virtual bool		addShaderFromMemory(ShaderType st,const uchar *pBuffer,uint len) = 0;

		/** ���������ɫ������
		@return �Ƿ�ɹ�
		*/
		virtual bool			link() = 0;		
	};

	struct ILowLevelShaderProgram: public IShaderProgram
	{
		/** ����ͳһ������ά����
		@param startRegister	��ʼ�ĸ��㳣���Ĵ������
		@param pData			��������ָ��
		@param countVector4		��ά���������ĸ���
		*/
		virtual	bool		setUniformFloatVector4(uint startRegister, float * pData, uint countVector4)=0;

		/** ����ͳһ������ά����
		@param startRegister	��ʼ�����ͳ����Ĵ������
		@param pData			��������ָ��
		@param countVector4		��ά���������ĸ���
		*/
		virtual	bool		setUniformIntVector4(uint startRegister, int * pData, uint countVector4)=0;

		/** ����ͳһ��������
		@param startRegister	��ʼ�Ĳ��������Ĵ������
		@param pData			��������ָ�룬0��ʾfalse����0��ʾtrue
		@param countBool		�������ݵĸ���
		*/
		virtual	bool		setUniformBool(uint startRegister, int * pData, uint countBool)=0;


		/** �����磬�������ͶӰ�Ⱦ���󶨵�shader�ĳ���,�ʺϵ�shader��ֻ��ͬʱ��һ������
		@param index	�����Ĵ������
		@param type		��TransformMatrixType��ָʾ�󶨲�ͬ�ľ�������
		@param bindRow	ָ���󶨶�����
		*/
		virtual void			bindTransformMatrix(uint index, uint type, uint bindRow =4)=0;
	};

	struct IHighLevelShaderProgram: public IShaderProgram
	{
		/** ����ͳһ�����ͱ���
		@param	strPara ������
		@param	value   ����ֵ
		@return	�Ƿ����óɹ�
		*/
		virtual bool			setUniformBool(const std::string & strPara,  int value)=0;

		/** ����ͳһ���ͱ���
		@param	strPara ������
		@param	value	����ֵ
		@return	�Ƿ����óɹ�
		*/
		virtual bool			setUniformInt(const std::string & strPara, int value)=0;

		/** ����ͳ�����ͱ���
		@param	strPara ������
		@param	value	����ֵ
		@return	�Ƿ����óɹ�
		*/
		virtual bool			setUniformFloat(const std::string & strPara, float value)=0;

		/** ����ͳһ��������
		@param	strPara ������
		@param	value	����ֵ
		@return	�Ƿ����óɹ�
		*/
		virtual bool			setUniformVector4(const std::string & strPara, const Vector4 & value)=0;

		/** ����һ��ľ���
		@param	strPara ������
		@param	value	����ֵ����������ݣ����������
		@return			�Ƿ����óɹ�
		*/
		virtual bool			setUniformMatrix(const std::string & strPara, const Matrix4 &  value)=0;


		/** ����ͳһ����������
		@param	strPara ������
		@param	count	�����С
		@param	pValue  �����ַ
		@return	�Ƿ����óɹ�
		*/
		virtual bool			setUniformBoolArray(const std::string & strPara, uint count,  int * pValue)=0;

		/** ����ͳһ��������
		@param	strPara ������
		@param	count	�����С
		@param	pValue  �����ַ
		@return	�Ƿ����óɹ�
		*/
		virtual bool			setUniformIntArray(const std::string & strPara, uint count,  int * pValue)=0;

		/** ����ͳһ����������
		@param	strPara ������
		@param	count	�����С
		@param	pValue  �����ַ
		@return	�Ƿ����óɹ�
		*/
		virtual bool			setUniformFloatArray(const std::string & strPara, uint count,  float * pValue)=0;

		/** ����ͳһ����������
		@param	strPara ������
		@param	count	�����С
		@param	pValue  �����ַ
		@return	�Ƿ����óɹ�
		*/
		virtual bool			setUniformVector4Array(const std::string & strPara, uint count,  xs::Vector4 * pValue)=0;

		/** ����ͳһ����������
		@param	strPara ������
		@param	count	�����С
		@param	pValue  �����ַ
		@return	�Ƿ����óɹ�
		*/
		virtual bool			setUniformMatrixArray(const std::string & strPara, uint count,  xs::Matrix4 * pValue)=0;

		/** ���������󶨵�shader�ĳ���
		@param	samplerNum �󶨶��ٸ�������
		*/
		virtual void			bindSampler(uint smaplerNum) = 0;

		/** �����磬�������ͶӰ�Ⱦ���󶨵�shader�ĳ���,�ʺϸ߽�shader����ͬʱ�󶨼�������
		@param flag ��TransformMatrixType�Ļ�ָʾ�󶨲�ͬ�ľ�������
		*/
		virtual void			bindTransformMatrix( uint flag) = 0;
	};

	/** ��ɫ��������ָ�룬����ӿ���ʱ���ڲ�ʹ�ã��ⲿ��ȡ����
	*/
	struct IShaderManager
	{
		/** ���ļ��д�����ɫ������IShaderProgram����
		@param ShaderType ��ɫ������
		@param fn �ļ���
		@return ��ɫ���ӿ�ָ��
		*/
		virtual IShader*		createShaderFromFile(ShaderType st,const std::string& fn) = 0;	

		/** ���ڴ������д�����ɫ������IShaderProgram����
		@param ShaderType ��ɫ������
		@param pBuffer ���ݵ�ַ
		@param len ���ݳ���
		@return ��ɫ���ӿ�ָ��
		@see ShaderType
		*/
		virtual IShader*		createShaderFromMemory(ShaderType st,const uchar *pBuffer,uint len) = 0;	

		/** ����һ����ɫ������IShaderProgram����
		@param IShader* ��ɫ��ָ��
		*/
		virtual void 			releaseShader(IShader*) = 0;				

		/** �������е���ɫ��
		*/
		virtual void 			releaseAllShader() = 0;

		/** �ͷ��Լ�
		*/
		virtual void			release() = 0;
	};


	/** ��ɫ�����������
	*/
	struct IShaderProgramManager
	{
		/** ������ɫ������
		@return ��ɫ������ӿ�ָ��
		*/
		virtual IShaderProgram*		createShaderProgram(ShaderProgramType type) = 0;

		/**	 ��ȡ����������Ⱦ����ɫ������
		@return ��ɫ������ӿ�ָ��
		*/
		virtual IShaderProgram*		getCurrentShaderProgam() = 0;

		/** �ͷ��Լ�
		*/
		virtual void			release() = 0;
	};

	/** @} */
}

#endif