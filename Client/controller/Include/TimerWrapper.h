/******************************************************************************
** �ļ���:	TimerWrapper.h
** ��  Ȩ:	(C)  
** 
** ��  ��:	2008/5/26   15:57
** ��  ��:	1.0
** ��  ��:	geb			
** Ӧ  ��:  
******************************************************************/
#pragma once


unsigned long setTimer(const std::string& subscriber_name, ulong timerId, ulong interval);
void killTimer(ulong handle1);