#include <iostream>
#include <cmath>
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

void PrintList( Sqlist &L )
{
    for( int i = 0; i < L.length; ++i )
    {
        cout << L.data[ i ] << " ";
    }
    cout << endl;
}

void InitList( Sqlist &L, int *arr, int size ) // 传入时数组退化为指针，不携带其大小信息
{
    if( size > MAXSIZE )
    {
        cerr << "Array size exceeds MAXSIZE." << endl << endl;
        L.length = 0;
    }

    L.length = size;
    for( int i = 0; i < L.length; i++ )
    {
        L.data[ i ] = arr[ i ];
    }
    cout << "Original: ";
    PrintList( L );
    cout << "Length: " << L.length << endl << endl;
}

void DeleteItem( Sqlist &L, ElemType item, int choice )
{
    int ind = 0;
    bool flag = false;

    for( int i = 0; i < L.length; ++i )
    {
        if( L.data[ i ] != item )
        {
            L.data[ ind++ ] = L.data[ i ];
        }
        else
        {
            flag = true;
        }
    }
    L.length = ind;

    switch ( choice )
    {
        case 0:
        {
            break;
        }
        case 1:
        {
            if( flag == true )
            {
                cout << "Modified( delete " << item << " ): ";
                PrintList( L );
                cout << "Length: " << L.length << endl << endl;
            }
            else
            {
                cout << "Item not found." << endl;
            }
            break;
        }
    }
}

int InsertList( Sqlist &L, int pos, ElemType elem, int choice )
{
    if( pos < 1 || pos > L.length + 1)
    {
        cerr << "Error position" << endl << endl;
        return ERROR;
    }
    else if( L.length >= MAXSIZE )
    {
        cerr << "List is full" << endl << endl;
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

    switch ( choice )
    {
        case 0:
        {
            return OK;
            break;
        }
        case 1:
        {
            cout << "Modified( Insert " << elem << " at position "<<  pos << " ): ";
            PrintList( L );
            cout << "Length: " << L.length << endl << endl;
            return OK;
            break;
        }
    }
}

int LocateElem( Sqlist &L, ElemType key )
{
    for( int i = 0; i < L.length; i++ )
    {
        if( key == L.data[ i ] )
        {
            cout << "Find " << key << " at position " << i << endl << endl;
            return i;
        }
    }
    
    cout << key << " not found." << endl << endl;
    return ERROR;
}

void inverse( Sqlist &L )
{
    for( int i = 0; i < ceil( ( L.length - 1 ) / 2.0 ) ; i++ )
    {
        int temp = L.data[ i ];
        L.data[ i ] = L.data[ L.length - 1 - i ];
        L.data[ L.length - 1 - i ] = temp;
    }
    cout << "Modified( inverse ): ";
    PrintList( L );
    cout << "Length: " << L.length << endl << endl;
}

void delsame( Sqlist &L )
{
    for( int i = 0; i < L.length; i++ )
    {
        for( int j = i + 1; j < L.length; j++ )
        {
            if( L.data[ i ] == L.data[ j ] )
            {
                int temp = L.data[ i ];
                DeleteItem( L, L.data[ i ], 0 );
                InsertList( L, i + 1, temp, 0 );
            }
        }
    }
    cout << "Modified( delsame ): ";
    PrintList( L );
    cout << "Length: " << L.length << endl;
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
        cout << "DiffSet is empty." << endl << endl;
    }
    else
    {
        cout << "DiffSet is: ";
        PrintList( diffset );
        cout << "Length: " << diffset.length << endl << endl;
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

    DeleteItem( L, 4, 1 );

    InsertList( L, 6, 99, 1 );

    LocateElem( L, 100 );

    Sqlist L0;
    int arr[] = { 1, 2, 3, 4 };
    int arr_size = sizeof( arr ) / sizeof( arr[ 0 ] );
    InitList( L0, arr, arr_size );

    Sqlist diffset;
    DiffSet( L, L0, diffset );
    
    inverse( diffset );

    Sqlist L1;
    int arr1[] = { 2, 3, 2, 4, 3, 6 };
    int arr1_size = sizeof( arr1 ) / sizeof( arr1[ 0 ] );
    InitList( L1, arr1, arr1_size );
    delsame( L1 );

    return 0;
}