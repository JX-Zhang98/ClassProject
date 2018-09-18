#pragma once

//ϵͳ�ռ��С
const int SYSTEM = (1 << 30);

//�ֿ�ռ��С
const int BLOCK = (1 << 12);

//���ֿ����(ʵ��Ҫ��)
const int MAXBLOCKNUMBER = SYSTEM / BLOCK;

//������С
const int INDEX = sizeof(int);

//�����ռ��С
const int INDEXSIZE = INDEX * MAXBLOCKNUMBER;

//������ʼ��λ��
const int INDEXLOCATION = 0;

//Ŀ¼��С
const int DIRECTORY = (1 << 5);

//Ŀ¼�ռ��С
const int DIRECTORYSIZE = DIRECTORY * MAXBLOCKNUMBER;

//Ŀ¼��ʼ��λ��
const int DIRECTORYLOCTION = INDEXSIZE;

//���ݿ���ʼλ��
const int BLOCKLOCATION = INDEXSIZE + DIRECTORYSIZE;

//ʵ�ʷֿ����
const int BLOCKNUMBER = MAXBLOCKNUMBER - INDEXSIZE / BLOCK - DIRECTORYSIZE / BLOCK;

//Ĭ�����ļ�����
const char DEFAULTNAME[] = "Data/mydisk.minifs";

//��󻺳�����С
const int MAXBUFFERSIZE = 1 << 24;