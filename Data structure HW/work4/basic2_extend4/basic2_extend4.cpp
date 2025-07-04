#include <iostream>
#include <vector>
#include <string>
#include <map>
#define Datatype int
#define HuffmanCode char**
using namespace std;

typedef struct HTNode
{
    char ch;
    Datatype weight;
    int parent, lchild, rchild;
} *HuffmanTree;

typedef struct Huffman_sheet
{
    map<char, char*> sheet;
} *p_Huffman_sheet;

int create_HTNode_array(string str, vector<Datatype> weight_array, HuffmanTree &HT)
{
    int Length = str.length();
    if (Length != weight_array.size())
    {
        cerr << "Length incompatible, abort from 'create_HTNode_array'." << endl;
        return 0;
    }
    
    try
    {
        HT = new HTNode[2 * Length - 1];
        for (int i = 0; i < Length; i++)
        {
            HT[i].ch = str[i];
            HT[i].weight = weight_array[i];
            HT[i].parent = -1;
            HT[i].lchild = -1;
            HT[i].rchild = -1;
        }
    }
    catch (const bad_alloc &err)
    {
        cerr << "Memory allocation failed: " << err.what() << endl;
        return 0;
    }
    return Length;
}

void Select(HuffmanTree HT, int n, int &s1, int &s2)
{
    vector<int> index_array;
    vector<Datatype> weight_array;
    for (int i = 0; i <= n - 1; i++)
    {
        if (HT[i].parent == -1)
        {
            index_array.push_back(i);
            weight_array.push_back(HT[i].weight);
        }
    }

    for (int i = 0; i < index_array.size() - 1; i++)
    {
        for (int j = 0; j < index_array.size() - 1 - i; j++)
        {
            if (weight_array[j+1] > weight_array[j])
            {
                Datatype temp1 = weight_array[j+1];
                weight_array[j+1] = weight_array[j];
                weight_array[j] = temp1;

                int temp2 = index_array[j+1];
                index_array[j+1] = index_array[j];
                index_array[j] = temp2;
            }
        }
    }

    s1 = index_array.back(); 
    index_array.pop_back();
    s2 = index_array.back();
    index_array.pop_back();
}

void CreateHuffmanTree(HuffmanTree HT, int Length)
{
    int TreeNodes = 2 * Length - 1;
    int s1 = 0, s2 = 0;
    for (int i = Length; i <= TreeNodes - 1; ++i) // 构造Huffman树
    {
        Select(HT, i, s1, s2);
            // 在HT[k](1≤k≤i-1)中选择两个其双亲域为0,
            // 且权值最小的结点,
            // 并返回它们在HT中的序号s1和s2
        HT[s1].parent = i;
        HT[s2].parent = i;

        HT[i].parent = -1;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        // s1,s2分别作为i的左右孩子
        // 此处调换s1，s2可生成镜像Huffman树
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
}

Huffman_sheet CreateHuffmanCode(HuffmanTree HT, int Length)
{
    // 从叶子到根逆向求每个字符的赫夫曼编码，存储在编码表HC中
    HuffmanCode HC = new char *[Length]; // 分配n个字符编码的头指针矢量
    char *cd = new char[Length];       // 分配临时存放编码的动态数组空间
    cd[Length - 1] ='\0';        // 编码结束符
    for (int i = 0; i < Length; ++i)
    { 
        // 逐个字符求赫夫曼编码
        int start = Length - 1;
        int c = i;
        int p = HT[i].parent;
        while (p != -1)
        {            // 从叶子结点开始向上回溯，直到根结点
            --start; // 回溯一次start向前指一个位置
            if (HT[p].lchild == c)
                cd[start] = '0'; // 结点c是f的左孩子，则生成代码0
            else
                cd[start] = '1'; // 结点c是f的右孩子，则生成代码1
            c = p;
            p = HT[p].parent; // 继续向上回溯
        } // 求出第i个字符的编码
        HC[i] = new char[Length - start]; // 为第i个字符编码分配空间
        strcpy(HC[i], &cd[start]); //将求得的编码从临时空间cd复制到HC的当前行中
    }

    Huffman_sheet Latest_sheet;
    for (int i = 0; i < Length; i++)
    {
        Latest_sheet.sheet.insert(pair<char, char*>(HT[i].ch, HC[i]));
    }
    delete[] cd; // 释放临时空间
    return Latest_sheet;
} // CreatHuffanCode

string Huffman_OutputCode(Huffman_sheet New_Sheet, string input_string)
{
    string output_string;
    char *temp;
    for (int i = 0; i < input_string.length(); i++)
    {
        auto it = New_Sheet.sheet.find(char(input_string[i]));
        if (it != New_Sheet.sheet.end())
        {
            temp = it->second;
            for (int j = 0; temp[j] != '\0'; j++)
            {
                cout << temp[j];
                output_string.push_back(temp[j]);
            }
            //output[i] = it->second;
        }
        else
        {
            cerr << "'" << input_string[i] << "' is not found, abort from OutputCode." << endl;
        }
    }
    return output_string;
}

string Huffman_Decode(HuffmanTree HT, string code, int Length)
{
    int i = 0;
    string original_string;
    if ((HT[2 * Length - 2].lchild == -1) || (HT[2 * Length - 2].rchild == -1))
    {
        cerr << "Huffman tree is empty, check whether the tree was assembled and its quantity of Nodes, abort from 'Huffman_Decode'" << endl;
        return "ERROR";
    }

    while (i < code.size())
    {
        HTNode temp = HT[2 * Length - 2];
        for (; (i < code.size()) && (temp.lchild != -1 && temp.rchild != -1); ++i)
        {
            if (code[i] == '0')
            {
                temp = HT[temp.lchild];
            }
            else if (code[i] == '1')
            {
                temp = HT[temp.rchild];
            }
            else
            {
                cerr << "Invalid Huffman code, check the code, abort from 'Huffman_Decode'" << endl;
                return "ERROR";
            }
        }
        if (temp.lchild != -1 && temp.rchild != -1)
        {
            cerr << "Invalid Huffman code, check the code, abort from 'Huffman_Decode'" << endl;
            return "ERROR";
        }
        original_string.push_back(temp.ch);
        cout << temp.ch;
    }
    cout << endl;
    return original_string;
}

int main()
{
    // 测试数据如下
    string Dictionay_str = "abcde";
    vector<Datatype> weight_array = {12, 9, 13, 6, 3};

    // cout << "input the character for code later: ";
    // cin >> Dictionary_str;
    // cout << "input the weight respondently: ";
    // cin >> weight_array;

    HuffmanTree HT;
    int Length= create_HTNode_array(Dictionay_str, weight_array, HT); // 创建森林（单个huffman结点）
    CreateHuffmanTree(HT, Length); // 创建huffman树

    // 创建huffman表
    Huffman_sheet New_Sheet = CreateHuffmanCode(HT, Length);

    string input_string;
    // cout << "input the original string: ";
    // cin >> input_string;

    input_string = "abcde";
    string code = Huffman_OutputCode(New_Sheet, input_string);

    string new_code = "101001011111001001000000";
    string origin = Huffman_Decode(HT, new_code, Length);
}