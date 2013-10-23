#ifndef __SubModel_H__
#define __SubModel_H__

namespace xs
{
	struct IRenderSystem;
	class Model;

	class SubModel : public ISubModel
	{
	public:
		/** �����ģ�͵�����
		@return ��ģ�͵�����
		*/
		virtual const char* getName();

		virtual ushort getIndexStart();

		virtual ushort getIndexCount();

		virtual ushort getVertexStart();

		virtual ushort getVertexEnd();

		virtual const  Material&	getMaterial();

		virtual GeosetAnimation*	getGeosetAnimation();

		virtual bool	isAnimated();

		//��Ӳ����Ƥ��֧��

		virtual uchar *	 getBindedBonesIndices(uint & validIndicesNum);

	public:
		void  setMaterial(const Material& mtl);
	private:
		Material	m_mtl;

	public:
		SubModel();

	public:
		std::string	m_name;
		int		m_matIndex;
		ushort indexStart,indexCount,vertexStart,vertexEnd;
		bool	m_bAnimated;
		GeosetAnimation	m_GeosetAnimation;
		uchar	m_ValidIndices;//��Ч�Ĺ���������
		uchar   m_BindedBonesIndices[VERTEX_BLEND_MATRICES_NUM];//�µĹ�������
		uchar	m_BonesMappings[VERTEX_BLEND_MAPPINGS_NUM];//��������ӳ���
	};
}

#endif