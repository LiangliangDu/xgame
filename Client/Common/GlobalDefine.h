//////////////////////////////////////////////////////////////////////////
//  ���ļ������˿ͻ���ʹ�õ�һЩȫ�����ݽṹ��

#pragma once

//////////////////////////////////////////////////////////////////////////
//  ProgressBar�ĳ�ʼ��������
struct CProgressBarInitArgs
{
    //  ����ʱ�䣻
    ulong m_ulDuration;
    //  �Ƿ�ת��ʾ��
    bool m_bInverse;

    CProgressBarInitArgs() :
    m_ulDuration(0),
        m_bInverse(false)
    {
    };
};

//  ��������
struct CTaskPrize
{
    //  ���飻
    int m_nExperience;
    //  ��Ǯ��
    int m_nMoney;
    //  �ɵ���Ʒ�����ý���ѡ�񣩣�
    std::string m_strGoodsInfo;
    //  ��ѡ��Ʒ����ѡһ����
    std::string m_strSelectingGoodsInfo;
};
