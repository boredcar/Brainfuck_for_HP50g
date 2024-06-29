#include <hpstdio.h>
#include <hpconio.h>
#include <hpstring.h>
#include <hpkeyb49.h>
#include <hpstring.h>
int  p , r , q,i;
char a [ 5000 ], f [ 5000 ],lastf[200], b , o , *s = f;
char temp,name[50],*pn=name;
unsigned short int looptime=0;
char whetherloop='\n';


int snapshot(int offset)
{
	int snappos;
	char k;
	char lk;
	char status;
	char string[10]={0};
	k=0;
	lk=0;
	itoa(p+offset,string,10);
	puts(string);
	//putchar('|');
	for(snappos=0;snappos<=39 && p+1<4999;snappos++)
	{
		if(k==4)
		{
			if(lk==1)
			{
			//putchar('\n');
			//putchar('|');
			lk=0;
			}
			else
			{
			putchar(' ');
			lk=1;
			}
			k=0;
		}
		//putchar(a[p+snappos+offset]);
		strcpy(string, "");
		itoa((int)a[p+snappos+offset],string,10);
		//puts(string);
		putchar(string[0]);
		putchar(string[1]);
		putchar(string[2]);
		putchar('|');
		k++;
	}
	putchar('\n');
	status=getchar();
	if(status=='\n')
	{
		return 0;
	}
	else if(status=='4')
	{
		if(p-4+offset>=0){
		snapshot(-4+offset);}
		else{puts("OUTs!\n");snapshot(-p);}
	}
	else if(status=='6')
	{
		snapshot(4+offset);
	}
	else if(status=='C')
	{
		return 1;
	}
	else{return 0;}
	return 0;
}

char translate(char a)
{
	switch(a)
	{
	case '1': return '>';
	case '2': return '<';
	case '3': return '+';
	case '4': return '-';
	case '5': return '.';
	case '6': return ',';
	case '7': return '[';
	case '8': return ']';
	case 'c': return 'c';
	case 'C': return 'C';
	case 'B': return 'B';
	case 'A': return 'A';
	case '-': return '-';
	case '+': return '+';
	case '\n': return '\n';
	case '\b': return '\b';
	case ' ': return ' ';
	default : return '\0';
	}
	return ' ';
}

int interpret( char * c)
{
        char * d;
        r ++;
        while( * c ) {
                //if(strchr("<>;+-,.[]/n",*c))printf("%c",*c);
                switch( o = 1 , * c ++) {
				case 'C' : if(snapshot(0)){return -1;} else{break;}
				//case 'B' : return 3;break;
				case 'A' : strcpy(a, "");p=0;puts("RESET a CLEAR p=0");break;
                case '<' : p --;        break;
                case '>' : p ++;        break;
                case '+' : a [p ] ++;     break;
                case '-' : a [p ] --;     break;
                case '.' : putchar( a [p ]); break;
                case ',' : a [p ] = getchar();putchar(a[p]); break;
                case '[' :
                        for( b = 1 , d = c; b && * c; c ++ )
                                b +=* c == '[' , b -=* c == ']';
                        if( !b) {
                                c [ - 1 ] = 0;
                                while( a [p ] )
								{		
										if(looptime==50000)
										{
											puts("WHETHER?");
											whetherloop=getchar();
											if(whetherloop!='\n')
											{
											return -1;
											}
											else{looptime=0;}
										}
										
										looptime++;
                                        interpret( d);
								}
                                c [ - 1 ] = ']';
                                break;
                        }
                case ']' :
                        puts( "UNBALANCED BRACKETS" );return 1;
                case '#' :
                        if( q > 2)
                                printf( "%2d %2d %2d %2d %2d %2d %2d %2d %2d %2d /n %*s /n " ,
                                       * a , a [ 1 ], a [ 2 ], a [ 3 ], a [ 4 ], a [ 5 ], a [ 6 ], a [ 7 ], a [ 8 ], a [ 9 ], 3 *p + 2 , "^");
                        break;
                default : o = 0;
                }
                if( p < 0 || p > 4999)
                {
					puts( "RANGE ERROR" );
					return 1;
				}
        }
        r --;
		return 0;
//        chkabort();
}

int doit()
{

		//gets(f);
		while(1)
		{
			//putchar('\b');
			temp=translate(getchar());
			//putchar(temp);
			//putchar('|');
			if(temp=='\n')
			{
				putchar(temp);
				break;
			}
			else if(temp=='\0')
			{
				putchar(temp);
				puts("delete");
				memset(f,0,sizeof(f));
				return 1;
			}
			else if(temp=='\b'  && (s-1)>=f)
			{
				putchar(temp);
				s--;
				*s='\0';
			}
			/*else if(temp=='C')
			{
				snapshot();
			}*/
			else if(temp=='B')
			{
				FILE *bfTEMP;
				bfTEMP=fopen("bfTEMP","r");
				fseek(bfTEMP, 0, SEEK_SET);
				while(!feof(bfTEMP))
				{
					b=fgetc(bfTEMP);
					putchar(b);
					*s ++=b;
				}
				fclose(bfTEMP);
			}
			else if(temp=='c')                   //bftemp write
			{
				puts("\nthis will overwrite bftemp, sure? Y/n");
				if(getchar()=='Y')
				{
					FILE *bfTEMP;
					bfTEMP=fopen("bfTEMP","w");
					fseek(bfTEMP, 0, SEEK_SET);
					int i=0;
					for(i=0;i<4999&&f[i]!='\0';i++)
					{
						fputc(f[i],bfTEMP);
					}
					fclose(bfTEMP);
					return 0;
				}
			}
			else
			{
				putchar(temp);
				*s=temp;
				s++;
			}
		}
	return 0;
}


int main( int argc , char * argv [])
{
FILE * z;
q = argc;
clear_screen();
puts("name:");
gets(name);
z = fopen( name, "r");
if( z!=NULL)                  //start read file
{
	while(!feof(z) )
	{
		b = fgetc( z);
		*s ++=b;
	}
	*s = 0;
	interpret( f);
}
else                          //input from keyb
{
	f[0]=0;
	while(f[0]!=99)
	{
		s=f;
		//putchar('|');
		doit();
		
		/*if(interpret(f)==3){puts(lastf);}
		else if(interpret(f)){break;}
		else{strcpy(lastf,f);}*/
		if(interpret(f)){break;}
		memset(f,0,sizeof(f));
		putchar('{');
		//putchar('\n');
		//interpret(".");
	}
	/*while(f[0]!=99)
	{	
		loop_start:
		s=f;
		interpret(f);
		putchar('{');
		putchar('\n');
		interpret(".");
		//gets(f);
		while(1)
		{
			temp=translate(getchar());
			putchar(temp);
			if(temp=='\n')
				break;
			if(temp==' '){
				puts("delete");
				goto loop_start;}

			else
			{
				*s=temp;
				s++;
			}
		}*/
	}

	keyb_waitKeyPressed();
	keyb_waitKeyPressed();	
	return 0;
}
