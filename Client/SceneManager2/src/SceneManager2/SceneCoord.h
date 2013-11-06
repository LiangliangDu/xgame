#ifndef __SceneCoord_H__
#define __SceneCoord_H__

class SceneCoord
{
public:
	//added by xxh
	// ����tile�����pixel���꣨��������)�ļ�����
	// tile�������£�
	// /(y)	
	// \(x)
	// pixel����(��������)���£�
	// -(x)
	// |(y)

	// tile����ĵ�(0,183)��Ӧpixel�����(0��0)�㡣������ptTile.xÿ��1��ptWorld.x��ptWorld.y��1��Ӧ��λ
	// ptTile.yÿ��1��ptWorld.x��1��λ��ptWorld.y��1��λ����pixel���꣬x����ĵ�λΪ32���أ�y����ĵ�λΪ16���أ�
	// �Ӷ��õ�tile������pixel����ת����ʽ��
	// pWorld.x = [ ( pTile.x-0) + (pTile.y - 183) ] * 32 + 0 => (pTile.x +pTile.y -m_yOff)<< 5 ;
	// pWorld.y = [ (pTile.x-0) - (pTile.y -183) ] * 16 + 0  => (pTile.x - pTile.y + m_yOff)<< 4;

	// ���ڽ�world����ӳ��Ϊtile���꣬��΢��Щ���ӡ����ȿ϶���pWorld.x/32��pWorld.y/16���õ����Ƶ������(0,183)��������꣬
	// ��ʱҪ�õ����Ƶ�tile���ֻ꣬Ҫ��������Ϳ����ˣ�
	// pTile.x = (pWorld.x/64 +pWorld.y/32) /2 + 0 => pWorld.x>>6 + pWorld.y >>5;
	// pTile.y = ( (pWorld.x/32 - pWorld.y/16 ) + 2* 183 ) / 2  => pWorld.x>>6 - pWorld.y>>5 + m_myOff
	// ���ǲ�һ�������������µ����������tileֵ����ͬ����������ֵ��ͬ���������ֵ��m_TilePoint�Ķ��壬����Ҳ���ñ���������ͼ��5����ͬ���򣬵���ֵ��һ��
	// ����OffsetX��OffsetY��5����ͬ�Ķ�Ӧֵ
	// ________
	// |  /\  |
	// | /  \ |
	// |/    \|
	// |\    /|
	// | \  / |
	// |__\/__|
	//
	// ���Եõ���ʽ��
	// pTile.x = pWorld.x>>6 + pWorld.y>>5 + OffSetX[off]
	// pTile.y = pWorld.x>>6 - pWorld.y>>5 + OffSetY[off] + m_myOff


	void tile2Pixel(IN const POINT& ptTile, OUT POINT& ptTileCenter) const
	{
		ptTileCenter.x = (ptTile.x + ptTile.y - m_yOff) << 5; // * 64 / 2;
		ptTileCenter.y = (ptTile.x - ptTile.y + m_yOff) << 4; // * 32 / 2;
	}
	void pixel2Tile(IN const POINT& ptWorld, OUT POINT& ptTile) const
	{
		const static int OffsetX[5] = { 0, 1, 1, 1, 2};
		const static int OffsetY[5] = { 0, 1, 0,-1, 0};

		int kx = ptWorld.x >> 6;
		int ky = ptWorld.y >> 5;
		int off = m_TilePoint[ptWorld.y & 0x1F][ptWorld.x & 0x3F];
		ptTile.x = kx + ky + OffsetX[off];
		ptTile.y = kx - ky + OffsetY[off] + m_yOff;
	}

	RECT pixelRectToAreaTileRect(RECT rc) const
	{
		IntersectRect(&rc, &m_rcMap, &rc);
#if 0
		rc.left = (Ceil(rc.left, 64)) * 64;
		rc.top = (Ceil(rc.top, 32)) * 32;
		rc.right &= ~63;
		rc.bottom &= ~31;
#else
		rc.left = (Ceil(rc.left, 64)) * 64;
		rc.top = (Ceil(rc.top, 32)) * 32;
		rc.right  = Ceil(rc.right,64) * 64;
		rc.bottom = Ceil(rc.bottom,32) * 32;
#endif
		RECT rcTileArea;
		pixel2Tile((const POINT&)rc, (POINT&)rcTileArea);
		rcTileArea.right = Ceil(rc.right - rc.left, 64);
		rcTileArea.bottom = Ceil(rc.bottom - rc.top, 32);
        //  ��ȷ�ϵ�ʵ�ִ��룺
		//	�˴���ʱ�����ΪʲôҪʹ��m_nMatrixHeight�������жϣ�����˵���޸ĵ���rcTileArea.right������Ϊ������
		//	��ʹ�õģ��˴��ƺ�Ӧ��ʹ��m_nMatrixWidth��
		//	���⣬ʹ��m_nMatrixHeight�������жϣ��ᵼ�µ�ͼ��������е�tile�ں�̵�EnumRect::EnumTileArea()�����
		//	����û�б��������ڣ��޸�Ϊʹ��m_nMatrixWidth��������ʱû���ٳ��֣�
		//	���ڶ�tile�����ת������ش��뻹�ڽ�һ��ѧϰ�У���˴˴����޸�����ɵ�Ӱ����Ҫ���н�һ���Ĺ۲죻

		//added by xxh
		// rcTileArea.top��tile��x���꣬rcTileArea.right��tile��x�������Գ��ȣ�������ƽ���ľ��ȳ��ȡ�
		//������m_nMatrixHeight�������жϣ�����Ϊ( m_nMatrixHeight =nRows + nCols)��������tile������x������������ֵ���������е�֣�
		//��Ϊtile������б��,������ֽ�ϻ������ԡ�
		//�Ҳ����׵��ǣ���һ����ʲô��˼��rcTileArea.bottom = rcTileArea.top + 1;ΪʲôҪ�޸ġ�������һ��һ�㲻��ִ��
		//������ܻ��bug
#if 0
		if (rcTileArea.top + rcTileArea.right >= m_nMatrixHeight)
			rcTileArea.right = m_nMatrixHeight - rcTileArea.top - 1;
#endif
		if (rcTileArea.top + rcTileArea.right >= m_nMatrixWidth)
		{
			rcTileArea.right = m_nMatrixWidth - rcTileArea.top - 1;
		}

		if (rcTileArea.top < rcTileArea.bottom - 1)
			rcTileArea.bottom = rcTileArea.top + 1;

		return rcTileArea;
	}

	RECT _pixelRectToAreaTileRect(RECT rc) const
	{
		RECT rcTileArea;
		pixel2Tile((const POINT&)rc, (POINT&)rcTileArea);
		rcTileArea.right = Ceil(rc.right - rc.left, 64);
		rcTileArea.bottom = Ceil(rc.bottom - rc.top, 32);

		return rcTileArea;	
	}

	bool create(int nWidth, int nHeight)
	{
		int w = nWidth, h = nHeight;
		w &= ~63;
		h &= ~31;

		int nRows = Ceil(nHeight, 32);
		int nCols = Ceil(nWidth, 64);

		m_rcMap.right = nWidth;
		m_rcMap.bottom = nHeight;

		// note by zjp��
		m_yOff = nRows - 1;// ���������˼��˵��ͼ����������(0,0)��Ӧ��tile����Ϊ(0,m_yOff)��������Ϊ�ڱ༭����������ô�趨�ģ���ÿһ�ŵ�ͼ�����ϽǶ�����(0,nRows - 1)���tile���괦��
		// ������������ʽ����˼����tile����ϵ�У�45����������ϵ������ͼ��tile����ϵ����������tileֵ�Ƿֱ���١�������ֵ����ô�ó������أ����Բο������༭������һ����ͼ�Լ����£�������֤���ȷʵ��ˡ�
		// �������Ǿ�֪��һ����ͼ��Ӧ����Чtile��Χ��:
		// 0<=tile.X<=m_nMatrixWidth
		// 0<=tile.Y<=m_nMatrixHeight
		// ע�⣬����������������Ч��Χ�ڵ�tile������ܶ�Ӧ����Ч�ĵ�ͼ���꣬����tile���꣨0��0�����Ҳ�����Ӧ�ĵ�ͼ���꣬����������һ��m_nMatrixWidth*m_nMatrixHeight��С��tile���飬��������һ����tile��û���õ��ģ��ⲿ��tile��Ѱ·��
		// ������;��ʱ�������Ϊ���赲�Ļ���Ч��tile��
		m_nMatrixWidth = nRows + nCols;
		m_nMatrixHeight = m_nMatrixWidth - 1;
		return true;
	}
	int getMatrixWidth()
	{
		return m_nMatrixWidth;
	}
	int getMatrixHeight()
	{
		return m_nMatrixHeight;
	}
	RECT& getMapRect()
	{
		return m_rcMap;
	}
	SceneCoord()
	{
		m_yOff = 0;
		m_nMatrixWidth = m_nMatrixHeight = 0;
		memset(&m_rcMap, 0, sizeof(m_rcMap));
	}
	~SceneCoord()
	{
		
	}
	const static char m_TilePoint[32][64];
private:
	int		m_yOff;
	RECT	m_rcMap; // ������ͼ�ľ�����Ϣ
	int		m_nMatrixWidth;
	int		m_nMatrixHeight;
};

#endif
