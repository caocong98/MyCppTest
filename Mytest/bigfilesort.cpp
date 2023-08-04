#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

const int BLOCK_SIZE = 2000000;

//版本1 存储排序好的分块文件

//版本2 不将排序好的分块文件存储到磁盘，直接内存内合并至一个文件中   
//32位vector存多个block报异常 : Microsoft C++ 异常: std::bad_alloc
//64位正常运行

//版本3 版本2基础多线程排序  待添加

//#define VERSION1
#define VERSION2
// #define VERSION3


#ifdef VERSION1

void bigFileSort(const string& inputFile, const string& outputFile)
{
    ifstream fin(inputFile);
    int totalLines = 0;
    while (fin.peek() != EOF)
    {
        string line;
        getline(fin, line);
        totalLines++;
    }
    fin.close();

    vector<string> block;
    block.reserve(BLOCK_SIZE);
    int blockNums = (totalLines + BLOCK_SIZE - 1) / BLOCK_SIZE;

    fin.open(inputFile);

    for (int blockId = 0; blockId < blockNums; ++blockId)
    {
        block.clear();
        block.reserve(BLOCK_SIZE);

        ofstream fout("D:/data/result/block" + to_string(blockId) + ".txt");

        for (int i = 0; i < BLOCK_SIZE; ++i)
        {
            string line;
            if (getline(fin, line))
                block.emplace_back(line);
            else
                break;
        }
        sort(block.begin(), block.end());
        cout << "Block " << blockId << " become sorted." << endl;
        for (const auto& line : block)
        {
            fout << line << endl;
        }
        fout.close();
    }
    fin.close();

    vector<ifstream> blockFins;
    blockFins.reserve(blockNums);
    for (int blockId = 0; blockId < blockNums; ++blockId)
    {
        blockFins.emplace_back("D:/data/result/block" + to_string(blockId) + ".txt");
    }

    ofstream fout(outputFile);
    vector<string> lines;
    lines.reserve(blockNums);

    for (int i = 0; i < blockNums; ++i)
    {
        string line;
        if (getline(blockFins[i], line))
            lines.emplace_back(line);
    }
    int count = 0; //记录进度
    while (!lines.empty())
    {
        auto minItem = min_element(lines.begin(), lines.end());
        fout << *minItem << endl;

        int minIdx = minItem - lines.begin();
        if (!getline(blockFins[minIdx], lines[minIdx])) //当前组元素取完
        {
            blockFins[minIdx].close();
            blockFins.erase(blockFins.begin() + minIdx);
            lines.erase(minItem);
        }
        ++count;
        if (count % BLOCK_SIZE == 0)
            cout << "Current sorting progress: " << double(count) / double(totalLines) * 100 << "%" << endl;
    }
    fout.close();
    cout << "Total: " << totalLines << " records.\n";
    // for (int blockId = 0; blockId < blockNums; ++blockId) 
    // {
    //     remove(("block" + to_string(blockId) + ".txt").c_str());
    // }
}

#elifdefine

#else
    
void bigFileSort(const string& inputFile, const string& outputFile)
{
    ifstream fin(inputFile);
    int totalLines = 0;
    while (fin.peek() != EOF)
    {
        string line;
        getline(fin, line);
        totalLines++;
    }
    fin.close();

    vector<string> block;
    block.reserve(BLOCK_SIZE);
    
    int blockNums = (totalLines + BLOCK_SIZE - 1) / BLOCK_SIZE;
    vector<vector<string>> blocks;  //存放每组排序好的数据
    blocks.reserve(blockNums);

    fin.open(inputFile);

    for (int blockId = 0; blockId < blockNums; ++blockId)
    {
        block.clear();
        block.reserve(BLOCK_SIZE);

        for (int i = 0; i < BLOCK_SIZE; ++i)
        {
            string line;
            if (getline(fin, line))
                block.emplace_back(line);
            else
                break;
        }
        sort(block.begin(), block.end());
        blocks.emplace_back(block);
        cout << "Block " << blockId << " become sorted." << endl;
    }
    fin.close();

    ofstream fout(outputFile);
    vector<vector<string>::iterator> lines;  //存放各组数据迭代器
    lines.reserve(blockNums);

    for (int i = 0; i < blockNums; ++i)
    {
        lines.emplace_back(blocks[i].begin());
    }

    int count = 0; //记录进度
    while (!lines.empty())  //多路归并
    {
        int minIdx = 0;
        string minItem = *lines[minIdx];
        for (size_t i = 0; i < lines.size(); ++i)
        {
            if (minItem > *lines[i])
            {
                minItem = *lines[i];
                minIdx = i;
            }
        }

        fout << minItem << endl;

        if (++lines[minIdx] == blocks[minIdx].end()) //当前组元素取完
        {
            blocks.erase(blocks.begin() + minIdx);
            lines.erase(lines.begin() + minIdx);
        }
        ++count;
        if (count % BLOCK_SIZE == 0)
            cout << "Current sorting progress: " << double(count) / double(totalLines) * 100 << "%" << endl;
    }
    fout.close();
    cout << "Total: " << totalLines << " records.\n";
}

#endif

// 排序结果验证
bool verifySort(const string& resultRoute)
{
    string pre, now;
    ifstream fin(resultRoute);
    if (!getline(fin, pre))
        return true;
    int totalLines = 1;
    while (fin.peek() != EOF)
    {
        getline(fin, now);
        if (pre > now)
            return false;
        pre = now;
        ++totalLines;
    }
    fin.close();
    cout << "Verify total: " << totalLines << " records.\n";
    return true;
}

int main() {
    bigFileSort("D:/data/users_id.txt", "D:/data/result/result.txt");
    if (verifySort("D:/data/result/result.txt"))
        cout << "sort right\n";
    else
        cout << "sort wrong\n";
    return 0;
}