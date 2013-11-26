#ifndef __BeginEndPrimitiveProxy_H__
#define __BeginEndPrimitiveProxy_H__

/** ˵��:
1,֧�ֵ�ͼԪ����:
	PT_POINTS, 
	PT_LINES, PT_LINE_STRIP, PT_LINE_LOOP(��PT_LINE_STRIPʵ��),
	PT_TRIANGLES,PT_TRIANGLE_STRIP,PT_TRIANGLE_FAN
	PT_QUADS(��TPT_TRIANGLESʵ��)

2,֧�ֵĶ�������:
	λ�ã����ߣ���ɫ���������֧꣨�ֶ�����������)


*/


namespace xs
{
	class BeginEndPrimitiveProxy;
	class RenderSystemD3D9;
	class VertexBufferD3D9;
	class IndexBufferD3D9;

	class BeginEndPrimitiveProxyCreater
	{
	public:
		static BeginEndPrimitiveProxy * create( RenderSystemD3D9 * pRenderSystem);
	};

	class BeginEndPrimitiveProxy
	{
		//��Ⱦ����ӿ�
	public:
		/**	��ʼ����ָ����ͼԪ
		*/
		void	beginPrimitive(PrimitiveType pt);

		/** ��������ָ����ͼԪ(�����ش���ͼԪ����)
		*/
		void	endPrimitive();

		/** ���Ͷ���λ������
		*/
		void	sendVertex(const Vector2& vertex);
		void	sendVertex(const Vector3& vertex);
		void	sendVertex(const Vector4& vertex);

		/** ���Ͷ��㷨������
		*/
		void	setNormal(const Vector3& normal);

		/** ���Ͷ�����ɫ����
		*/
		void	setColor(const ColorValue& color);

		/** ���Ͷ���0������Ԫ��������������
		*/
		void	setTexcoord(const Vector2& texcoord);

		/** ���Ͷ�������Ԫ��������������
		*/
		void 	setMultiTexcoord(ushort unit,const Vector2& texcoord);

		/** ���ñ߽��־
		*/
		void setEdgeFlag(bool bEdgeFlag);

		/** �ͷź���
		*/
		void release();

	private:
		///** ��λ����
		//*/
		//void reset();

		/** �ص�δ��ʼ״̬
		*/
		void toUnBeginPrimitive();

		/** ȷ��FVF
		*/
		void determineFVF();

	private:
		friend class BeginEndPrimitiveProxyCreater;
		bool	create(RenderSystemD3D9 * pRenderSystem);//��������
		BeginEndPrimitiveProxy();
		~BeginEndPrimitiveProxy();

	private:
		bool	m_bSetNormal;//�Ƿ������˷���
		xs::Vector3 m_vCurrentNormal;//��ǰ�ķ���

		bool	m_bSetDiffuse;//�Ƿ������˵�ǰ��ɢ���
		DWORD	m_dwCurrentDiffuse;//��ǰ��ɢ���

		uint	m_TexcoordCount;//���õ���������ļ���
		const	static uint cs_MaxTexcoordCount = 8;//��������������
		xs::Vector2	m_vCurrentTexcoord[cs_MaxTexcoordCount];//��ǰ��������

		bool	m_bBetweenBeginEnd;//�Ƿ���beginPrimitive �� endPrimitive��	
		PrimitiveType	m_CurrentPrimitiveType;//��ǰ��ͼԪ
		RenderSystemD3D9 * m_pRenderSystem;//��Ⱦϵͳָ��

		bool	m_bIsFVFdetermined;//�����ʽ�Ƿ��Ѿ�ȷ��
		DWORD	m_dwFVF;//�����ʽ	
		uint	m_uiCurrentVertexSize;//��ǰ����Ĵ�С
		uint	m_uiVertexCount;//�ύ�Ķ�����

		const static uint	cs_uiStackSize = 48*2048;//�����ջ��С
		uint	m_uiCurrentStackPointer;//��ǰ��ջ����
		uchar	m_VertexStack[cs_uiStackSize];//�����ջ
		ushort	m_IndexBufferForDrawQuads[((cs_uiStackSize/12)/4)*6];//�����ı����õ�index buffer
	};
}

#endif