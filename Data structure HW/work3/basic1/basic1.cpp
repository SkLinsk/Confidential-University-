#include<iostream>
using namespace std;
#define Maxsize 100
#define TRUE 1
#define OK 1
#define FALSE 0
#define NULL 0
#define ERROR -1
typedef int status;
typedef char Selemtype;
typedef struct
{
    Selemtype *base;
    Selemtype *top;
    int stacksize;
}Sqstack;

status InitStack( Sqstack &s );
status Push( Sqstack &s, Selemtype e );
status Pop( Sqstack &s, Selemtype &e );
Selemtype GetTop( Sqstack s );

status InitStack( Sqstack &s )
{
	s.base = new Selemtype[ Maxsize ];
	s.top = s.base;
	s.stacksize = Maxsize;
    return OK;
}
status Push( Sqstack &s, Selemtype e )
{
	if ( s.top - s.base >= s.stacksize ) 
    {
        return ERROR;
    }
	else 
    {
        *s.top++ = e;
    }
	return OK;
}

status Pop( Sqstack &s, Selemtype &e )
{
	if( s.top == s.base )
    {
        return ERROR;
    }
	else 
    {
        e = *( --s.top );
    }
	return OK;
}

Selemtype GetTop( Sqstack s )
{
	return *( s.top - 1 );
}

int empty( Sqstack s )
{
    if( s.top == s.base )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}



int judge( Sqstack &s )
{                        
    Selemtype symb, ch, store;
    Push( s, '#' );
    cin >> symb;
    while( symb != '#' )
    {
        switch( symb )
        {
            case '(':
            case '[':
            case '{':
            {
                Push( s, symb );
                break;
            }
            case ')':
            {
                Pop( s, ch );
                if( ch != '(' ) 
                {
                    return FALSE;
                }
                break;
            }
            case ']':
            {
                Pop( s, ch );
                if( ch != '[' ) 
                {
                    return FALSE;
                }
                break;
            }
            case '}':
            {
                Pop( s, ch );
                if( ch != '{' ) return FALSE;
                break;
            }
            default:
            {
                break;
            }
        }
        cin >> symb; 
    }
    Pop( s, ch );

    if( ch == '#' )
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

 int main()
 {
    Sqstack q;
    InitStack( q );
    cout << "please input an express end with symbol '#':" << endl;
    if( judge( q ) )
    {
        cout << "yes " << endl;
    }
    else
    {
        cout << "no " << endl;
    }
    
    return 1;
 }
