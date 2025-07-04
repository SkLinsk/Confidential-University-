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
    struct LNode *next;
}LNode , *Linklist;

void Print_Linklist( Linklist head );
int List_length( Linklist head );

status Init_Linklist ( Linklist &L )
{
    L = new LNode;
    L->next = NULL;
    return OK;
}

status Create_Linklist( Linklist head )
/*头插法构造单链表*/
{
    Linklist p = head, s;
    elemtype e;
    cout << "Type in the elements of the linklist, -1 means end." << endl;
    cin >> e;
    while( e != -1 )
    {
        s = new LNode;
        s->data = e;
        s->next = p->next;
        p->next = s;
        cin >> e;
    }
    return OK;
}

status Create_Linklist( Linklist head, int *arr, int size )
// non-output, Createed by array. 尾插法
{
    Linklist p = head;
    Linklist s = NULL;
    for( int i = 0; i < size; i++ )
    {
        s = new LNode;
        s->data = arr[ i ];
        p->next = s;
        s->next = NULL;
        p = s;
    }
    return OK;
}

Linklist LocateElem_Linklist_data( Linklist head, elemtype k, int flag )
{
    Linklist s;
    int index = 1;
    s = head->next;
    while( s != NULL && s->data != k )
    {
        s = s->next;
        index++;
    }

    switch ( flag )
    {
        case 0:
        {
            if( s != NULL )
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
            if( s != NULL )
            {
                switch ( index )
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

Linklist LocateElem_Linklist_index( Linklist head, int index, int flag )
{
    Linklist s;
    int k = 1;
    s = head->next;
    while( s != NULL && k++ != index )
    {
        s = s->next;
    }

    switch ( flag )
    {
        case 0:
        {
            if( s != NULL )
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
            if( s != NULL )
            {
                switch ( index )
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

status Insert_Linklist( Linklist head, int index, elemtype x )
{
    int i = 0;
    Linklist p = head;
    while( p->next && i < index - 1 )
    {
        p = p->next;
        i++;
    }

    if( ( p->next == NULL ) && ( i < index - 1 ) )
    {
        cerr << "Index exceeds the length of LinkList, the element will be inserted as the last." << endl;
    }

    if( !p || i > index - 1 ) 
    {
        cerr << "Invalid index for ListList, insertion failed";
        return ERROR;
    }
    
    Linklist s = new LNode;
    if( !s ) 
    {
        return OVERFLOW;
    }
    s->data = x;
    s->next = p->next;
    p->next = s;
    
    return OK;
}

status Insert_Linklist( Linklist head, int index, int *arr, int size )
{
    int i = 0;
    Linklist p = head;
    while( p->next && i < index - 1 )
    {
        p = p->next;
        i++;
    }

    if( ( p->next == NULL ) && ( i < index - 1 ) )
    {
        cerr << "Index exceeds the length of LinkList, the element will be inserted as the last." << endl;
    }

    if( !p || i > index - 1 ) 
    {
        cerr << "Invalid index for ListList, insertion failed";
        return ERROR;
    }

    Linklist segment;
    Init_Linklist( segment );
    Create_Linklist( segment, arr, size );

    if( !segment ) 
    {
        return OVERFLOW;
    }
    while( segment->next != NULL )
    {
        Insert_Linklist( head, i + 1, segment->next->data );
        i++;
        segment = segment->next;
    }
    return OK;
}

status Insert_Linklist( Linklist head, int index, Linklist segment )
{
    int i = 0;
    Linklist p = head;
    while( p->next && i < index - 1 )
    {
        p = p->next;
        i++;
    }

    if( ( p->next == NULL ) && ( i < index - 1 ) )
    {
        cerr << "Index exceeds the length of LinkList, the element will be inserted as the last." << endl;
    }

    if( !p || i > index - 1 ) 
    {
        cerr << "Invalid index for ListList, insertion failed";
        return ERROR;
    }

    while( segment->next != NULL )
    {
        Insert_Linklist( head, i + 1, segment->next->data );
        i++;
        segment = segment->next;
    }
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

void Reverse_Linklist( Linklist &head )
{
    Linklist current = head->next;
    Linklist advance, previous = NULL;
    while ( current->next != NULL )
    {
        advance = current->next;
        current->next = previous;
        previous = current;
        current = advance;
    }
    current->next = previous;
    head->next = current;
}

Linklist duplicate_Linklist( Linklist head )
{
    Linklist copy;
    Init_Linklist( copy );
    if( head->next == NULL )
    {
        return copy;
    }
    else
    {
        Linklist p = head->next;
        Linklist q = copy;
        Linklist s = NULL;
        do
        {
            s = new LNode;
            s->data = p->data;
            p = p->next;
            q->next = s;
            q = q->next;
        }while( p != NULL );
        q->next = NULL;
        return copy;
    }
}

int List2Ring( Linklist head )
{
    if( head->next == NULL )
    {
        cerr << "Linklist is empty." << endl;
        return ERROR;
    }

    Linklist current = head->next;
    while( current->next != NULL )
    {
        current = current->next;
    }
    current->next = head->next;
    return OK;
}

void Print_Linklist( Linklist head )
{
    if( head->next == NULL )
    {
        cerr << "Linklist is empty." << endl;
    }

    Linklist p = head->next;
    do
    {
        cout << p->data << " ";
        p = p->next;
    }while( ( p != NULL ) && ( p != head->next ) );

    if( p == head->next )
    {
        cout << "circle" << endl;
    }
    else
    {
        cout << "list" << endl;
    }
    cout << endl;
}

int List_length( Linklist head )
{   
    int length = 0;
    Linklist p = head->next;
    do
    {
        p = p->next;
        length++;
    }while( ( p != NULL ) && ( p != head->next ) );
    return length;
}

void Josephus_ring( Linklist ring, int out_index )
{
    while( List_length( ring ) != 1 )
    {
        if( ring->next == NULL )
        {
            cerr << "Linklist is empty." << endl;
            return;
        }

        int j = 0;
        Linklist current, advance;
        current = ring;
        while( j < out_index - 1 )
        {
            current = current->next;
            j++;
        }
        advance = current->next;
        current->next = advance->next;
        ring->next = current->next;
        free( advance );
    }
    cout << ring->next->data << " is the number which is left in the Josephus_ring with the out index " << out_index << endl;
}

void Delsame_Linklist( Linklist head, elemtype data )
{
    Linklist s;
    Init_Linklist( s );

    Linklist p, c = head->next;
    while( c != NULL && c->data != data )
    {
        p = c;
        c = c->next;
    }

    if( c == NULL )
    {
        cerr << data << " not found in the linklist, deletion abort." << endl;
    }
    else
    {
        s->next = c->next;
        Delete_Linklist_data( s, data );
    }
}

Linklist Polynomial_addition( Linklist ahead, Linklist bhead )
{
    int a = List_length( ahead );
    int b = List_length( bhead );
    int quotient = 0;
    if( a > b )
    {
        quotient = a - b;
        for( int i = 0; i < quotient; i++ )
        {
            Insert_Linklist( bhead, 1, 0 );
        }
    }
    else if( a < b )
    {
        quotient = b - a;
        for( int i = 0; i < quotient; i++ )
        {
            Insert_Linklist( ahead, 1, 0 );
        }
    }

    Linklist p, q, s, sum, c;
    Init_Linklist( sum );
    p = ahead->next;
    q = bhead->next;
    c = sum;
    while( p != NULL )
    {
        s = new LNode;
        s->data = p->data + q->data;
        c->next = s;
        c = s;
        p = p->next;
        q = q->next;
    }
    c = NULL;

    return sum;
}

int main()
{
    Linklist head;
    
    int arr[ 6 ] = { 2, 8, 6, 4, 10, 9 };
    int size = sizeof( arr ) / sizeof( arr[ 0 ] );

    Init_Linklist( head );
    Create_Linklist( head, arr, size );
    Print_Linklist( head );

    LocateElem_Linklist_data( head, 1, 1 );
    LocateElem_Linklist_data( head, 8, 1 );

    Insert_Linklist( head, 1, 101 );
    Insert_Linklist( head, 6, 106 );
    Insert_Linklist( head, 999, 10999 );
    Print_Linklist( head );

    Delete_Linklist_index( head, 1 );
    Delete_Linklist_index( head, 2 );
    Delete_Linklist_index( head, 7 );
    Delete_Linklist_index( head, 999 );
    Print_Linklist( head );

    Insert_Linklist( head, 2, 2 );
    Print_Linklist( head );

    Delete_Linklist_data( head, 0 );
    Delete_Linklist_data( head, 9 );
    Delete_Linklist_data( head, 4 );
    Delete_Linklist_data( head, 2 );
    Delete_Linklist_data( head, 100 );
    Print_Linklist( head );

    Reverse_Linklist( head );
    Print_Linklist( head );

    Insert_Linklist( head, 3, arr, size );
    Print_Linklist( head );

    cout << "head2 starts here." << endl;
    Linklist head2 = duplicate_Linklist( head );
    List2Ring( head2 );
    Print_Linklist( head2 );

    Josephus_ring( head2, 6 );

    Delsame_Linklist( head, 6 );
    Delsame_Linklist( head, 10 );
    Print_Linklist( head );


    Linklist head4, head5;
    Init_Linklist( head4 );
    Init_Linklist( head5 );
    int arr4[ 6 ] = { 1, 2, 3 }, arr5[ 4 ] = { 1, 2, 3, 4 };
    int size4 = sizeof( arr4 ) / sizeof( arr4[ 0 ] ), size5 = sizeof( arr5 ) / sizeof( arr5[ 0 ] );
    Create_Linklist( head4, arr4, size4 );
    Create_Linklist( head5, arr5, size5 );

    Linklist head3 = Polynomial_addition( head4, head5 );
    Print_Linklist( head3 );

    return OK;
}