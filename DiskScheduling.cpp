#include <iostream>
#include <vector>
#include <algorithm>

class DiskScheduling
{
private:
    std::vector<int> trackAccessOrder; // 磁道访问顺序
    int startTrack;                    // 起始磁道

public:
    DiskScheduling(std::vector<int> TrackAccessOrder, int StartTrack)
        : trackAccessOrder(TrackAccessOrder), startTrack(StartTrack) {}

    void FCFS_Run() const // 先来先服务算法 FCFS
    {
        int currentAccessTrack = startTrack; // 当前磁道位置
        int currentMove = 0;                 // 当前移动距离
        float totalMove = 0;                 // 总移动距离
        std::cout << "先来先服务算法" << std::endl;
        std::cout << "被访问的下一个磁道\t移动距离<磁道数>" << std::endl;

        for (size_t i = 0; i < trackAccessOrder.size(); i++)
        {
            currentMove = abs(currentAccessTrack - trackAccessOrder[i]);                      // 移动距离=求当前磁道位置 - 目的位置的绝对值
            currentAccessTrack = trackAccessOrder[i];                                         // 更新当前磁头位置
            std::cout << "\t" << trackAccessOrder[i] << "\t\t\t" << currentMove << std::endl; // 输出信息
            totalMove = totalMove + currentMove;
        }
        std::cout << "\t平均磁道移动距离: " << totalMove / trackAccessOrder.size() << std::endl;
    }

    void SSTF_Run() const // 最短寻道优先算法
    {
        int currentAccessTrack = startTrack;                 // 当前磁道位置
        int currentMove = 0;                                 // 当前移动距离
        float totalMove = 0;                                 // 总移动距离
                                                             // 移动距离
        std::vector<int> SSTFAccessOrder = trackAccessOrder; // 复制磁道访问顺序避免修改
        std::cout << "最短寻道优先算法" << std::endl;
        std::cout << "被访问的下一个磁道\t移动距离<磁道数>" << std::endl;

        while (SSTFAccessOrder.size() != 0)
        {
            std::vector<int> accessMove; // 用于保存最小值下标
            // 查找最小值下标
            for (size_t i = 0; i < SSTFAccessOrder.size(); i++) // 计算移动距离
            {
                accessMove.push_back(abs(currentAccessTrack - SSTFAccessOrder[i]));
            }
            int minIndex = std::distance(accessMove.begin(),
                                         std::min_element(accessMove.begin(), accessMove.end()));
            currentMove = abs(currentAccessTrack - SSTFAccessOrder[minIndex]);                      // 移动距离=求当前磁道位置 - 目的位置的绝对值
            currentAccessTrack = SSTFAccessOrder[minIndex];                                         // 更新当前磁头位置
            std::cout << "\t" << SSTFAccessOrder[minIndex] << "\t\t\t" << currentMove << std::endl; // 输出信息
            totalMove = totalMove + currentMove;
            SSTFAccessOrder.erase(SSTFAccessOrder.begin() + minIndex); // 把已完成的磁道移除
        }
        std::cout << "\t平均磁道移动距离: " << totalMove / trackAccessOrder.size() << std::endl
                  << std::endl;
    }

    void SCAN_Run(bool direction) // Direction -> True 朝外移动，-> False 朝内移动
    {
        int currentAccessTrack = startTrack;                       // 当前磁道位置
        int currentMove = 0;                                       // 当前移动距离
        float totalMove = 0;                                       // 总移动距离
        std::vector<int> SCANAccessOrder = trackAccessOrder;       // 复制磁道访问顺序避免修改
        std::sort(SCANAccessOrder.begin(), SCANAccessOrder.end()); // 排序
        std::cout << "SCAN算法" << std::endl;
        std::cout << "被访问的下一个磁道\t移动距离<磁道数>" << std::endl;
        if (direction) // 朝外扫描
        {
            for (size_t i = 0; i < SCANAccessOrder.size(); i++)
            {
                if (SCANAccessOrder[i] >= 100)
                {
                    currentMove = abs(currentAccessTrack - SCANAccessOrder[i]);                      // 移动距离=求当前磁道位置 - 目的位置的绝对值
                    currentAccessTrack = SCANAccessOrder[i];                                         // 更新当前磁头位置
                    std::cout << "\t" << SCANAccessOrder[i] << "\t\t\t" << currentMove << std::endl; // 输出信息
                    totalMove = totalMove + currentMove;
                }
            }

            // 到达尽头调转方向开始扫描
            for (int i = SCANAccessOrder.size() - 1; i >= 0; i--)
            {
                if (SCANAccessOrder[i] < 100)
                {
                    currentMove = abs(currentAccessTrack - SCANAccessOrder[i]);                      // 移动距离=求当前磁道位置 - 目的位置的绝对值
                    currentAccessTrack = SCANAccessOrder[i];                                         // 更新当前磁头位置
                    std::cout << "\t" << SCANAccessOrder[i] << "\t\t\t" << currentMove << std::endl; // 输出信息
                    totalMove = totalMove + currentMove;
                }
            }
            std::cout << "\t平均磁道移动距离: " << totalMove / trackAccessOrder.size() << std::endl
                      << std::endl;
        }
        else // 朝内扫描
        {
            for (int i = SCANAccessOrder.size() - 1; i >= 0; i--)
            {
                if (SCANAccessOrder[i] <= 100)
                {
                    currentMove = abs(currentAccessTrack - SCANAccessOrder[i]);                      // 移动距离=求当前磁道位置 - 目的位置的绝对值
                    currentAccessTrack = SCANAccessOrder[i];                                         // 更新当前磁头位置
                    std::cout << "\t" << SCANAccessOrder[i] << "\t\t\t" << currentMove << std::endl; // 输出信息
                    totalMove = totalMove + currentMove;
                }
            }
            for (size_t i = 0; i < SCANAccessOrder.size(); i++)
            {
                if (SCANAccessOrder[i] > 100)
                {
                    currentMove = abs(currentAccessTrack - SCANAccessOrder[i]);                      // 移动距离=求当前磁道位置 - 目的位置的绝对值
                    currentAccessTrack = SCANAccessOrder[i];                                         // 更新当前磁头位置
                    std::cout << "\t" << SCANAccessOrder[i] << "\t\t\t" << currentMove << std::endl; // 输出信息
                    totalMove = totalMove + currentMove;
                }
            }
            std::cout << "\t平均磁道移动距离: " << totalMove / trackAccessOrder.size() << std::endl
                      << std::endl;
        }
    }

    void CSCAN_Run(bool direction)
    {
        int currentAccessTrack = startTrack;                         // 当前磁道位置
        int currentMove = 0;                                         // 当前移动距离
        float totalMove = 0;                                         // 总移动距离
        std::vector<int> CSCANAccessOrder = trackAccessOrder;        // 复制磁道访问顺序避免修改
        std::sort(CSCANAccessOrder.begin(), CSCANAccessOrder.end()); // 排序
        std::cout << "CSCAN算法" << std::endl;
        std::cout << "被访问的下一个磁道\t移动距离<磁道数>" << std::endl;

        if (direction) // 朝外扫描
        {
            for (size_t i = 0; i < CSCANAccessOrder.size(); i++)
            {
                if (CSCANAccessOrder[i] >= startTrack)
                {
                    currentMove = abs(currentAccessTrack - CSCANAccessOrder[i]);                      // 移动距离=求当前磁道位置 - 目的位置的绝对值
                    currentAccessTrack = CSCANAccessOrder[i];                                         // 更新当前磁头位置
                    std::cout << "\t" << CSCANAccessOrder[i] << "\t\t\t" << currentMove << std::endl; // 输出信息
                    totalMove = totalMove + currentMove;
                }
            }
            for (size_t i = 0; i < CSCANAccessOrder.size(); i++) // 回到起始方向开始扫描
            {
                if (CSCANAccessOrder[i] < startTrack)
                {
                    currentMove = abs(currentAccessTrack - CSCANAccessOrder[i]);                      // 移动距离=求当前磁道位置 - 目的位置的绝对值
                    currentAccessTrack = CSCANAccessOrder[i];                                         // 更新当前磁头位置
                    std::cout << "\t" << CSCANAccessOrder[i] << "\t\t\t" << currentMove << std::endl; // 输出信息
                    totalMove = totalMove + currentMove;
                }
            }
        }
        else // 朝内扫描
        {
            for (size_t i = 0; i < CSCANAccessOrder.size(); i++) // 回到起始方向开始扫描
            {
                if (CSCANAccessOrder[i] < startTrack)
                {
                    currentMove = abs(currentAccessTrack - CSCANAccessOrder[i]);                      // 移动距离=求当前磁道位置 - 目的位置的绝对值
                    currentAccessTrack = CSCANAccessOrder[i];                                         // 更新当前磁头位置
                    std::cout << "\t" << CSCANAccessOrder[i] << "\t\t\t" << currentMove << std::endl; // 输出信息
                    totalMove = totalMove + currentMove;
                }
            }

            for (size_t i = 0; i < CSCANAccessOrder.size(); i++)
            {
                if (CSCANAccessOrder[i] >= startTrack)
                {
                    currentMove = abs(currentAccessTrack - CSCANAccessOrder[i]);                      // 移动距离=求当前磁道位置 - 目的位置的绝对值
                    currentAccessTrack = CSCANAccessOrder[i];                                         // 更新当前磁头位置
                    std::cout << "\t" << CSCANAccessOrder[i] << "\t\t\t" << currentMove << std::endl; // 输出信息
                    totalMove = totalMove + currentMove;
                }
            }
        }
        std::cout << "\t平均磁道移动距离: " << totalMove / trackAccessOrder.size() << std::endl
                  << std::endl;
    }
};
int main()
{
    std::vector<int> trackAccessOrder;
    int trackSize; // 进程数量
    int cinTemp;
    int startTrack; // 起始磁道
    int op;         // 选项
    int n = 1;
    bool direction;

    std::cout << "请输入提出磁盘I/O申请的进程数量: ";
    std::cin >> trackSize;
    std::cout << "请依此输入要访问的磁道号: ";
    for (size_t i = 0; i < trackSize; i++)
    {
        std::cin >> cinTemp;
        trackAccessOrder.push_back(cinTemp);
    }
    std::cout << "请输入开始磁盘号: ";
    std::cin >> startTrack;

    DiskScheduling ds(trackAccessOrder, startTrack);

    while (n != 0)
    {
        std::cout << "请选择寻道方式 1.FCFS 2.SSTF 3.SCAN 4.CSCSN: ";
        std::cin >> op;

        switch (op)
        {
        case 1:
            std::cout << std::endl;
            ds.FCFS_Run();
            break;

        case 2:
            std::cout << std::endl;
            ds.SSTF_Run();
            break;

        case 3:
            std::cout << "请选择开始方向 1-向外 0-向里: ";
            std::cin >> direction;
            std::cout << std::endl;
            ds.SCAN_Run(direction);
            break;

        case 4:
            std::cout << "请选择开始方向 1-向外 0-向里: ";
            std::cin >> direction;
            std::cout << std::endl;
            ds.CSCAN_Run(direction);
            break;

        default:
            std::cout << "选项无效 " << std::endl;
            break;
        }

        std::cout << "是否继续选择寻道算法？1-是 0-否: ";
        std::cin >> n;
    }

    return 0;
}