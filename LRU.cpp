#include <iostream>
#include <vector>

class Node // 双向链表节点
{
public:
    int key;
    int data;
    Node *prev;
    Node *next;

    Node(int value, int Key)
    {
        data = value;
        key = Key;
        prev = nullptr;
        next = nullptr;
    }
};

class LinkedList // 双向链表类
{
public:
    Node *head;    // 头部节点
    Node *tail;    // 尾部节点
    int maxLength; // 物理块数

    // 链表初始化
    LinkedList(int page)
    {
        head = nullptr;
        tail = nullptr;
        maxLength = page;
    }

    // 获取链表长度 返回int
    int getLength()
    {
        int length = 0;
        Node *current = head;
        while (current)
        {
            length++;
            current = current->next;
        }
        return length;
    }

    // 移除尾部节点（页面）
    int removeTail()
    {

        int key;
        Node *prevNode = tail->prev;
        key = tail->key;
        // std::cout << "Log: prevNode->data and key:" << prevNode->data << " " << prevNode->key << std::endl;
        delete tail;
        tail = prevNode;
        prevNode->next = nullptr;

        return key;
    }
    // 修改：每次新增节点都正确更新一次尾节点
    void updateTail()
    {
        Node *current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        tail = current;
    }

    // 发生缺页 新增页到头部
    int addPageAtHead(int value, int Key)
    {
        Node *newNode = new Node(value, Key);
        int returnKey;
        if (!head) // 如果没有头部节点则新节点成为头尾节点
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            // 如果节点数量超过物理块数则把最久未使用的tail尾部节点移除
            if (getLength() >= maxLength)
            {
                returnKey = removeTail();
            }
            // std::cout << "Log: newNode->data:" << newNode->data
            //           << " newNode->key:" << newNode->key << std::endl;
            newNode->next = head; // 新节点next为旧头部
            head->prev = newNode; // 旧头部的prev为新节点
            head = newNode;       // 把新节点修改为新head
            updateTail();
        }
        return returnKey;
    }

    void show()
    {
        Node *current = head;
        while (current)
        {
            if (head == current)
            {
                std::cout << "#Head ";
            }
            else if (tail == current)
            {
                std::cout << "#Tail ";
            }
            else
            {
                std::cout << "#Node ";
            }

            std::cout << "data -> " << current->data
                      << " key -> " << current->key
                      << " address -> " << current
                      << " prev -> " << current->prev
                      << " next -> " << current->next
                      << std::endl;
            current = current->next;
        }
    }

    // 查找页面 如果查找成功则将其移动到头节点处并返回true 失败则返回false
    bool find(int value)
    {
        Node *current = head;
        while (current != nullptr)
        {
            if (current->data == value)
            {
                if (current == head) // 如果如果找到的节点就是头节点，直接返回true
                {
                    return true;
                }
                else // 如果不是头节点
                {
                    // 将当前节点的前一个节点（current->prev）的next指针更新为当前节点的下一个节点
                    current->prev->next = current->next;

                    if (current->next)
                    {
                        current->next->prev = current->prev;
                    }

                    current->prev = nullptr;
                    current->next = head;
                    head->prev = current;
                    head = current;
                    updateTail();
                    return true;
                }
            }
            current = current->next;
        }
        // std::cout << "Log: 没有找到" << std::endl;
        return false;
    }
};

class LRU
{
private:
    int pageAccesses = 0; // 页面访问次数
    int pageFaults = 0;   // 缺页次数
    double pageFaultRate; // 缺页率
    int pageSize;
    std::vector<int> page;

public:
    LRU(int PageSize, std::vector<int> Page)
    {
        pageSize = PageSize;
        page = Page; // 初始化页面走向
    }

    void Run()
    {
        int key;
        LinkedList LL(pageSize); // 初始化物理块大小
        // std::cout << "Log: vector size->" << page.size() << std::endl;

        std::cout << "物理块数: " << pageSize << " 置换情况如下:" << std::endl;
        for (size_t i = 0; i < page.size(); i++)
        {
            // std::cout << "Log: " << (i + 1) << "号page正在find data为" << page[i] << std::endl;

            if (LL.find(page[i])) // 查找页面号是否在链表中
            {
                std::cout << "内存中有"
                          << i + 1
                          << "号页面，无须缺页中断！"
                          << std::endl;
            }
            else
            {
                if (LL.getLength() < pageSize)
                {
                    // std::cout << "Log: LL.getLength()已运行 准备addPageAtHead" << std::endl;
                    LL.addPageAtHead(page[i], i + 1); // 将页面写入链表
                    // std::cout << "Log: LL.addPageAtHead()已运行 准备输出信息" << std::endl;
                    std::cout << "发生缺页中断，但内存中有空闲区，"
                              << i + 1 << "号页面直接调入！"
                              << std::endl;
                }
                else
                {
                    // std::cout << "Log: LL.getLength()已运行 准备addPageAtHead page[i]=" << page[i] << " key=" << (i + 1) << std::endl;

                    key = LL.addPageAtHead(page[i], (i + 1));

                    // std::cout << "Log: LL.addPageAtHead()已运行 准备输出信息" << std::endl;

                    std::cout << "发生缺页中断，将"
                              << key
                              << "号页面调出，"
                              << i + 1
                              << "号装入！"
                              << std::endl;
                }

                pageFaults++; // 没有找到 缺页次数++
            }
            // 详细展示链表数据
            LL.show();
            std::cout << std::endl;

            pageAccesses++; // 页面访问次数++
        }

        std::cout << "页号->" << pageAccesses;
        std::cout << " 缺页中断->" << pageFaults;
        std::cout << " 缺页率->" << (double(pageFaults) / double(pageAccesses) * 100) << "%" << std::endl;
    }
};

int main()
{
    // 作业的页面序号走向
    std::vector<int> page = {4, 3, 2, 4, 2,
                             3, 1, 4, 5, 1,
                             4, 3, 5, 4, 3,
                             2, 1, 5, 3, 1,
                             2, 4};

    LRU lru3(3, page); // 物理块数目 M 为3
    LRU lru4(4, page); // 物理块数目 M 为4

    lru3.Run();
    std::cout << std::endl
              << std::endl;
    lru4.Run();

    return 0;
}