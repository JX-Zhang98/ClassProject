#pragma once

//系统空间大小
const int SYSTEM = (1 << 30);

//分块空间大小
const int BLOCK = (1 << 12);

//最大分块个数(实际要少)
const int MAXBLOCKNUMBER = SYSTEM / BLOCK;

//索引大小
const int INDEX = sizeof(int);

//索引空间大小
const int INDEXSIZE = INDEX * MAXBLOCKNUMBER;

//索引起始块位置
const int INDEXLOCATION = 0;

//目录大小
const int DIRECTORY = (1 << 5);

//目录空间大小
const int DIRECTORYSIZE = DIRECTORY * MAXBLOCKNUMBER;

//目录起始块位置
const int DIRECTORYLOCTION = INDEXSIZE;

//数据块起始位置
const int BLOCKLOCATION = INDEXSIZE + DIRECTORYSIZE;

//实际分块个数
const int BLOCKNUMBER = MAXBLOCKNUMBER - INDEXSIZE / BLOCK - DIRECTORYSIZE / BLOCK;

//默认总文件名称
const char DEFAULTNAME[] = "Data/mydisk.minifs";

//最大缓冲区大小
const int MAXBUFFERSIZE = 1 << 24;