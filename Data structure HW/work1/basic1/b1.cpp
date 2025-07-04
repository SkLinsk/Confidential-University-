#include <iostream>
using namespace std;

#define MAXSIZE 100
#define OK 1
#define ERROR -1
#define ElemType int
  
typedef struct
{
    ElemType data[ MAXSIZE ];
    int length;
} Sqlist;

void InitList( Sqlist &L )
{
    L.length = 0;
}

void InitList( Sqlist &L, int *arr, int size ) // 传入时数组退化为指针，不携带其大小信息
{
    if( size > MAXSIZE )
    {
        cerr << "Array size exceeds MAXSIZE." << endl;
        L.length = 0;
    }

    L.length = size;
    for( int i = 0; i < L.length; i++ )
    {
        L.data[ i ] = arr[ i ];
    }
}

void PrintList( Sqlist &L )
{
    for( int i = 0; i < L.length; ++i )
    {
        cout << L.data[ i ] << " ";
    }
    cout << endl;
}

void DeleteItem( Sqlist &L, ElemType item )
{
    int ind = 0;

    for( int i = 0; i < L.length; ++i )
    {
        if( L.data[ i ] != item )
        {
            L.data[ ind++ ] = L.data[ i ];
        }
    }

    L.length = ind;
}

int InsertList( Sqlist &L, int pos, ElemType elem )
{
    if( pos < 1 || pos > L.length + 1)
    {
        cout << "Error position" << endl;
        return ERROR;
    }
    else if( L.length >= MAXSIZE )
    {
        cout << "List is full" << endl;
        return ERROR;
    }
    else
    {
        for( int i = L.length; i >= pos; i-- )
        {
            L.data[ i ] = L.data[ i - 1 ];
        }
        L.data[ pos - 1 ] = elem;
        L.length++;
    }
    return OK;
}

int LocateList( Sqlist &L, ElemType key )
{
    for( int i = 0; i < L.length; i++ )
    {
        if( key == L.data[ i ] )
        {
            return i;
        }
    }
    
    cout << key << " not found." << endl;
    return ERROR;
}

void DiffSet( Sqlist &L1, Sqlist &L2, Sqlist &diffset )
{
    int ind = 0;
    bool flag;
    for( int i = 0; i < L1.length; i++ )
    {
        flag = false;
        for( int j = 0; j < L2.length; j++ )
        {
            if( L1.data[ i ] == L2.data[ j ] )
            {
                flag = true;
                break;
            }
        }
        if( !flag )
        {
            diffset.data[ ind++ ] = L1.data[ i ];
        }
        else
        {
            flag = 0;
        }
    }
    diffset.length = ind;

    if ( diffset.length == 0 )
    {
        cout << "DiffSet is empty." << endl;
    }
    else
    {
        cout << "DiffSet is: ";
        PrintList( diffset );
    }

}

int main()
{
    Sqlist L;
    InitList( L );

    for( int i = 1; i <= 6; i++ )  
    {  
        if( L.length < MAXSIZE )
        {
            L.data[ L.length++ ] = i;
        }
    }  

    cout << "Original: ";
    PrintList( L );

    DeleteItem( L, 4 );
    cout << "Modified( delete 4 ): ";
    PrintList(L);

    InsertList( L, 6, 99 );
    cout << "Modified( Insert 99 at pos 6 ): ";
    PrintList( L );

    LocateList( L, 100 );

    Sqlist L0;
    int arr[] = { 1, 2, 3, 4 };
    int arr_size = sizeof( arr ) / sizeof( arr[ 0 ] );

    InitList( L0, arr, arr_size );
    cout << "Original: ";
    PrintList( L0 );

    Sqlist diffset;
    DiffSet( L, L0, diffset);

    return 0;
}