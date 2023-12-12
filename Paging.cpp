#include <iostream>

#define pageTableLength 64 // 页表长度 64
using namespace std;

class PagingTranslator
{
private:
    int pageTable[pageTableLength] = {0, 42, 29, 15, 45, 31, 44, 43,
                                      41, 28, 1, 30, 12, 24, 6, 32,
                                      14, 27, 13, 46, 7, 33, 10, 22,
                                      40, 2, 51, 11, 39, 23, 49, 50,
                                      26, 16, 25, 4, 47, 17, 3, 48,
                                      52, 36, 58, 35, 57, 34, 21, 63,
                                      5, 37, 18, 8, 62, 56, 20, 54,
                                      60, 19, 38, 9, 61, 55, 59, 53};
    ;             // 系统页号对应块号情况
    int pageSize; // 页面大小

public:
    PagingTranslator(int pagesize);
    int getPhysicalAddress(int logicalAddress);
};

PagingTranslator::PagingTranslator(int pagesize) // 构造函数 初始化成功后输出系统页号对应块号情况
{
    pageSize = pagesize;
    cout << "系统页号对应块号情况（页号—>块号）：" << endl;
    for (size_t t = 0; t < pageTableLength; t++) // 遍历页表
    {
        cout << t << "->" << pageTable[t] << " ";
        if ((t + 1) % 8 == 0) // 输出8个后换行
        {
            cout << endl;
        }
    }
    cout << endl;
}

int PagingTranslator::getPhysicalAddress(int logicalAddress) // 返回转换后的物理地址 若越界返回-1
{
    int page = logicalAddress / pageSize; // 页号 = 逻辑地址 / 页面大小

    if (page > pageTableLength) // 检测是否越界 当页号超出64即为越界
    {
        return -1; // 返回越界信息
    }

    int physicalPage = pageTable[page];         // 物理块号
    int pageOffset = logicalAddress % pageSize; // 偏移量 = 逻辑地址 % 页面大小

    return physicalPage * pageSize + pageOffset; // 物理地址 = 物理块号 * 页大小 + 偏移量
}

int main()
{
    PagingTranslator pt1(1024); // 初始化类 页面大小设置1024
    int logicalAddress;

    cout << "请输入逻辑地址（十进制）：";
    cin >> logicalAddress;

    int physicalAddress = pt1.getPhysicalAddress(logicalAddress); // 获取转换后的逻辑地址

    if (physicalAddress == -1)
    {
        cout << "本次访问的地址已超出进程的地址空间，系统将产生越界中断！" << endl;
    }
    else
    {
        cout << "对应的物理地址为（十进制）：" << physicalAddress << endl;
    }

    return 0;
}