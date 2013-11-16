//==========================================================================
/**
* @file	  : Radial.h
* @author : pk <pk163@163.com>
* created : 2008-4-11   21:25
* purpose : ����ö���࣬�������н��ķ���,���η���·�ϵĸ�����
*/
//==========================================================================

#ifndef __RADIAL_H__
#define __RADIAL_H__

class Radial
{
	int mStepX,mStepY;	/// ������ʸ��
	int x,y;			/// ��ǰ��ʼ��
	int mDistX,mDistY;	/// ���룬����
	int pk,c,d;
	int mLength;		/// ��ǰ����

public:
	Radial(int x1, int y1, int x2, int y2)
	{
		x = x1;
		y = y1;
		int dx = x2 - x1;
		int dy = y2 - y1;

		if (dx > 0)
			mStepX = 1;
		else if (dx < 0)
			mStepX = -1;

		if (dy > 0)
			mStepY = 1;
		else if (dy < 0)
			mStepY = -1;

		mDistX = dx * mStepX;
		mDistY = dy * mStepY;
		int twoDistX = 2 * mDistX;
		int twoDistY = 2 * mDistY;
		
		// б�߿���x��
		if (mDistX >= mDistY)
		{
			c = twoDistY;
			d = twoDistY - twoDistX;
			pk = twoDistY - mDistX;
		}
		else // б�߿���y��
		{
			c = twoDistX;
			d = twoDistX - twoDistY;
			pk = twoDistX - mDistY;
		}

		mLength = 0;
	}

	void move(long& lNowX, long& lNowY, int length)
	{
		while (length--)
			move(lNowX, lNowY);
	}

	void move(xs::Point& pt)
	{
		move(pt.x, pt.y);
	}

	void move(long& lNowX, long& lNowY)
	{
		mLength ++;

		// ��ֱ��
		if (mDistX == 0) 
		{
			y += mStepY;
			lNowX = x;
			lNowY = y;
			return;
		}
		
		// ˮƽ��
		if (mDistY == 0) 
		{
			x += mStepX;
			lNowX = x;
			lNowY = y;
			return;
		}

		// б��(����x��)
		if (mDistX >= mDistY)
		{
				x += mStepX;
				if (pk < 0)
				{
					pk += c;

					lNowX = x;
					lNowY = y;
					return;
				}
				else
				{
					pk += d;
					y += mStepY;

					lNowX = x;
					lNowY = y;
					return;
				}
		}
		else // ����y���б��
		{

				y += mStepY;
				if (pk < 0)
				{
					pk += c;

					lNowX = x;
					lNowY = y;
					return;
				}
				else
				{
					pk += d;
					x += mStepX;

					lNowX = x;
					lNowY = y;
					return;
				}
		}
	}

	//  �����߹��ĳ���
	int getLength() const			{ return mLength; }
	void setCurPos(int x_, int y_)	{ x = x_; y = y_; }
};

#endif // __RADIAL_H__