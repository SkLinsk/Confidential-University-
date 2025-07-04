#include <iostream>
using namespace std;
#define ERROR 0
#define OK 1
#define OVERFLOW -1

typedef int status;
typedef int elemtype;
typedef struct LNode
{
    elemtype data;
    struct LNode* next;
}LNode, * Linklist;

status Init_Linklist(Linklist& L)
{
    L = new LNode;
    L->next = NULL;
    return OK;
}

status creat_Linklist(Linklist head)
/*头插法构造单链表*/
{
    LNode* p = head, * s;
    elemtype e;
    cout << "Type in the elements of the linklist, -1 means end." << endl;
    cin >> e;
    while (e != -1)
    {
        s = new LNode;
        s->data = e;
        s->next = p->next;
        p->next = s;
        cin >> e;
    }
    return OK;
}

status creat_Linklist(Linklist head, int* arr, int size)
// non-output, created by array. 尾插法
{
    Linklist p = head;
    Linklist s;
    for (int i = 0; i < size; i++)
    {
        s = new LNode;
        s->data = arr[i];
        p->next = s;
        p = s;
        p->next = NULL;
    }
    return OK;
}

LNode* LocateElem_Linklist(Linklist head, elemtype k, int flag)
{
    Linklist s;
    int index = 1;
    s = head->next;
    while (s != NULL && s->data != k)
    {
        s = s->next;
        index++;
    }

    switch (flag)
    {
    case 0:
    {
        if (s != NULL)
        {
            return s;
        }
        else
        {
            return NULL;
        }
    }
    case 1:
    {
        if (s != NULL)
        {
            switch (index)
            {
            case 1:
            {
                cout << k << " is found at the 1st position of the LinkList." << endl;
                return s;
            }
            case 2:
            {
                cout << k << " is found at the 2nd position of the LinkList." << endl;
                return s;
            }
            case 3:
            {
                cout << k << " is found at the 3rd position of the LinkList." << endl;
                return s;
            }
            default:
            {
                cout << k << " is found at the " << index << "th position of the LinkList." << endl;
                return s;
            }
            }
        }
        else
        {
            cerr << k << " is not found." << endl;
            return NULL;
        }
    }
    default:
    {
        return NULL;
    }
    }
}

status Insert_Linklist(Linklist head, int index, elemtype x)
{
    int j = 0;
    LNode* p = head;
    while (p->next && j < index - 1)
    {
        p = p->next;
        j++;
    }

    if ((p->next == NULL) && (j < index - 1))
    {
        cerr << "Index exceeds the length of LinkList, the element will be inserted as the last." << endl;
    }

    if (!p || j > index - 1)
    {
        cerr << "Invalid index for ListList, insertion failed";
        return ERROR;
    }

    Linklist s = new LNode;
    if (!s)
    {
        return OVERFLOW;
    }
    s->data = x;
    s->next = p->next;
    p->next = s;

    return OK;
}

void Delete_Linklist_index(Linklist head, int index) /*删除链表的第i个结点*/
{
    if (head->next == NULL)
    {
        cerr << "Linklist is empty." << endl;
        return;
    }

    int j = 0;
    Linklist current = head, advance, previous = head;
    while ((current->next != NULL) && (j < index - 1))
    {
        previous = current;
        current = current->next;
        j++;
    }
    // 对于两个条件的判断、链表末尾指针为NULL
    if ((current->next != NULL) && (j == index - 1))
    {
        advance = current->next;
        current->next = advance->next;
        free(advance);
    } // think twice
    else
    {
        cerr << "Invalid index, deletion failed at index " << index << endl;
    }
}

void Delete_Linklist_data(Linklist head, elemtype data)
{
    if (head->next == NULL)
    {
        cerr << "Linklist is empty." << endl;
        return;
    }

    int flag = 0;
    Linklist current = head->next, previous = head, temp;
    while (current != NULL) // here!!!!!!!!!!
    {
        if (current->data == data)
        {
            if (current->next != NULL)
            {
                temp = current;
                previous->next = current->next;
                current = current->next;
                free(temp);
                flag = 1;
            }
            else
            {
                free(current);
                previous->next = NULL;
                flag = 1;
                break;
            }
        }
        else
        {
            previous = current, current = current->next;
        }
    }
    if (!flag)
    {
        cerr << "No " << data << " was found in the Linklist, Deletion abort." << endl;
    }
}

void Print_Linklist(Linklist head)  /*打印出链表head中各个结点的值*/
{
    Linklist p;
    p = head->next;
    while (p != NULL)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

int Menu()
{
    int flag = 0;
    cout << "Type in 0 for a non-input demo, and 1 for an input demo." << endl;
    return flag;
}

int main()
{
    Linklist head;
    int flag = Menu();

    switch (flag)
    {
        case 0:
        {
            int arr[6] = { 2, 8, 6, 4, 10, 9 };
            int size = sizeof(arr) / sizeof(arr[0]);

            Init_Linklist(head);
            creat_Linklist(head, arr, size);
            Print_Linklist(head);

            LocateElem_Linklist(head, 1, 1);
            LocateElem_Linklist(head, 8, 1);

            Insert_Linklist(head, 1, 101);
            Insert_Linklist(head, 6, 106);
            Insert_Linklist(head, 999, 10999);
            Print_Linklist(head);

            Delete_Linklist_index(head, 1);
            Delete_Linklist_index(head, 2);
            Delete_Linklist_index(head, 7);
            Delete_Linklist_index(head, 999);
            Print_Linklist(head);

            Insert_Linklist(head, 2, 2);
            Print_Linklist(head);
            
            Delete_Linklist_data(head, 9);
            Delete_Linklist_data(head, 4);
            Delete_Linklist_data(head, 2);
            Delete_Linklist_data(head, 1000);
            Print_Linklist(head);

            return 1;
        }
        case 1:
        {
            int x;
            int i, j;

            Init_Linklist(head);
            creat_Linklist(head);
            cout << "we have created a linklist as follow:\n";
            Print_Linklist(head);

            cout << "now start search, please input the search value:";
            cin >> x;
            LocateElem_Linklist(head, x, 1);

            cout << "start insert operation, please input insert position and the elemtype:" << endl;
            cin >> i >> x;
            Insert_Linklist(head, i, x);
            cout << "after insertion:\n";
            Print_Linklist(head);

            cout << "now start delete operation, input the delete position please:" << endl;
            cin >> j;
            Delete_Linklist_index(head, j);
            cout << "after deletion:\n";
            Print_Linklist(head);

            return 1;
        }
    }
}
