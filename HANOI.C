#include<conio.h>
#include<stdio.h>
#include<alloc.h>
# define TT 10
# define BB 50
# define WW 500
/* TT = Max towers + 1 , BB = Max Blocks + 1 , WW = Infinite Weight */

struct block
{
struct block *above;
char type;
char tower;
int weight;
int state;            /* 2 = Base Block of infinite weight , 1 = settled , 0 = unsettled , -1 = settling */
struct block *below;
};

struct TOP          /* For Current state */
{
struct block *top , *temp;
int n , nTemp;             /* No. of blocks in the Tower */
char tower;
struct TOP *next;
}Top,TopF;

struct BASE         /* For Final state */
{
struct block *base;
char tower;
struct BASE *next;
}Base,BaseF;


void Display(struct block *b , char source , char dest , int x);
void CreateTower(int Tower[TT][BB][2] , int x);
void settle();
void moveWeight(int weight , char dest);
int move(char source , char dest);
int TotalBlocks();
char OTHER(char a , char b);
int MIN_weight();
struct block *FindBlockCurrent(char type , int weight , char tower);
struct block *GetBlockFinal();



void main()
{
/*  Base -----> Top    weight of first block = -1 for Empty Tower */
/* {type,weight} types : 1 = A , 2 = B , 3 = C , etc. weights start from 1 */
/* T1 = Initial Tower , T2 = Final Tower */
/*
int T1[TT][BB][2] = { { {,} } ,
		      { {,} } ,
		      { {,} } } ;
*/


/*  Shuffle : */
/*
int T1[TT][BB][2] = { { {1,3},{1,2},{1,1} } ,
		      { {2,3},{2,2},{2,1} } ,
		      { {3,3},{3,2},{3,1} } } ;

int T2[TT][BB][2] = { { {3,3},{3,2},{3,1} } ,
		      { {1,3},{1,2},{1,1} } ,
		      { {2,3},{2,2},{2,1} } } ;

*/

/* Invert Tower: */
/*
int T1[TT][BB][2] = { { {1,5},{2,5},{3,5},{1,3},{2,3},{3,3},{4,3} } ,
		      { {2,-1},{2,2},{2,1} } ,
		      { {3,-1},{3,2},{3,1} } } ;
int T2[TT][BB][2] = { { {3,5},{2,5},{1,5},{4,3},{3,3},{2,3},{1,3} } ,
		      { {2,-1},{2,2},{2,1} } ,
		      { {3,-1},{3,2},{3,1} } } ;
*/

/* Separate Weights */
/*
int T1[TT][BB][2] = { { {1,5},{2,5},{3,4},{2,4},{1,2},{5,2} } ,
		      { {1,5},{4,5},{2,2},{3,2} } ,
		      { {3,4},{5,4},{1,4},{4,2},{5,2} } };

int T2[TT][BB][2] = { { {3,4},{2,4},{1,4},{5,4},{3,4} } ,
		      { {1,5},{4,5},{2,5},{1,5} } ,
		      { {1,2},{5,2},{5,2},{*/

/* Randomized */

int T1[TT][BB][2] = { { {2,7},{3,7},{4,7},{1,3},{1,2},{1,1} } ,
		      { {3,9},{2,9},{1,9},{2,3},{2,2},{2,1} } ,
		      { {3,3},{1,3},{1,2},{1,2},{1,1},{1,1} } } ;

int T2[TT][BB][2] = { { {4,7},{3,7},{2,7},{1,1},{1,1},{2,1},{1,1} } ,
		      { {3,9},{2,9},{1,9},{1,2},{1,2},{2,2},{1,2} } ,
		      { {2,3},{3,3},{1,3},{1,3} } } ;

clrscr();
CreateTower(T1,0);
printf("%d\n",MIN_weight());
Display(NULL,0,0,2); /* x = 2 to print Initial State */
CreateTower(T2,1);
Display(NULL,0,0,1);
settle();
getch();
printf("Transformed");
getch();
}


struct block *GetBlockFinal() /* Generalized : Returns address of heaviest unsettled block from final state  (Requires "Base" object to start from lowest valid block or Base.base = NULL for empty tower) */
{
struct BASE *b1 = &BaseF , *b2 = b1 ;
struct block *t ;

while(b2->base == NULL && b2 != NULL) b2 = b2->next;
if(b2==NULL) return NULL;       /* Returns NULL if all blocks are done */
b1 = b2->next;
while(b1!=NULL)
     {
     while(b1->base == NULL && b1 != NULL) b1 = b1->next;
     if(b1==NULL) break;

     if(b1->base->weight > b2->base->weight)
       b2 = b1;
     b1 = b1->next;
     }
t = b2->base;
b2->base = b2->base->above;

return t;
}


struct block *FindBlockCurrent(char type , int weight , char tower) /* Generalized : Returns address of first occurrence of unsettled block of given type and weight */
{                                                            /* tower = 0 for all towers , type = 0 for all types */
struct TOP *t = &Top;
struct block *p;

while(tower!=0 && t->next!=NULL && t->tower!=tower)
     t = t->next;

if(type != 0)
  {
  while(t!=NULL)
       {
       p = t->top;
       while( p->state==0 && !(p->type==type && p->weight==weight) )
	    {
	    p = p->below;
	    }
       if(tower!=0)
	 {
	 if(p->state == 0 && p->tower == tower && p->type == type && p->weight == weight)
	   return p;
	 else
	   return NULL;
	 }
       if(p->state == 0 && p->type == type && p->weight == weight)
	 return p;
       else
	 t = t->next;
       }
  }

if(type == 0 && tower != 0)
  {
  p = t->top;
  while(p->state==0 && p->weight!=weight)
       {
       p = p->below;
       }
  if(p->state==0 && p->weight==weight)
    return p;
  else
    return NULL;
  }
}


int MIN_weight() /* Generalized : Returns weight of the least heavy block */
{
struct TOP *t1 = &Top , *t2 = t1 ;

t1 = t1->next;
while(t1!=NULL)
     {
     if(t1->top->weight < t2->top->weight)
       t2 = t1;
     t1 = t1->next;
     }
return t2->top->weight;
}


char OTHER(char a , char b)  /* Returns a char other than the two input char */
{
if( (a=='A' && b=='B') || (b=='A' && a=='B') ) return 'C';
if( (a=='A' && b=='C') || (b=='A' && a=='C') ) return 'B';
if( (a=='B' && b=='C') || (b=='B' && a=='C') ) return 'A';
}


int TotalBlocks()   /* Generalized */
{
struct TOP *t = &Top;
int n=0;

while(t!=NULL)
     {
     n = n + t->n;
     t = t->next;
     }
return n;
}


int move(char source , char dest)   /* Generalized */
{
struct TOP *s = &Top , *d = &Top ;
struct block *t;

while(s->tower!=source)
     s = s->next;
if(s->top->state == -1)     /* Returns -1 if block to be moved is in settling state */
  return -1;
if(s->top->state >= 1)     /* Returns 1 if block to be moved is settled or tower is empty */
  return 1;

while(d->tower!=dest)
     d = d->next;
if(d->top->weight < s->top->weight)     /* Return -2 if block in destination tower is lighter */
  return -2;

t = s->top;
s->top->below->above = NULL;
s->top = s->top->below;
s->n--;

Display(t,source,0,0);       /* Displays Transition */
Display(t,0,dest,0);

t->tower = d->tower;
t->below = d->top;
d->top->above = t;
d->top = t;
d->n++;

getch();
Display(NULL,0,0,0);
return 0;            /* Returns 0 if block is moved successfully */
}


void moveWeight(int weight , char dest)
{
struct TOP *t = &Top , *t1 ;
struct block *b;

if(weight==MIN_weight())
  {
  while(t!=NULL)
       {
       if(t->tower == dest)
	 t = t->next;
       if(t == NULL) break;
       while(t->top->weight == weight && t->top->state == 0)
	    move(t->top->tower,dest);
       t = t->next;
       }
  }

else
  {
  while(t!=NULL)
       {
       if(t->top->tower == dest)
	 t = t->next;
       if(t == NULL) break;

       b = FindBlockCurrent(0,weight,t->tower);
       if(b==NULL)
	 {
	 t = t->next;
	 continue;
	 }

       moveWeight(weight-1,OTHER(t->top->tower,dest));
       while(t->top->weight == weight && t->top->state == 0)
	    move(t->top->tower,dest);
       t = t->next;
       }
  moveWeight(weight-1,dest);
  }
}


void settle()
{
struct TOP *t , *t1;
struct block *f , *c , *c1 ;
char temp;
while(1)
     {
     f = GetBlockFinal();
     if(f==NULL) break;                    /* End Point */
     c = FindBlockCurrent(f->type,f->weight,0);

     if(c->tower != f->tower)
       {
       for( t = &Top ; t->tower==c->tower || t->tower==f->tower ; t = t->next )
          {
          }
       c->state = -1;
       moveWeight(c->weight,t->tower); /* or moveWeight(c->weight,OTHER(c->tower,f->tower)) */
       c->state = 0;
       move(c->tower,f->tower);
       c->state = 1;
       }

     else
       {
       c1 = c;
       while(c1->state == 0 && c1->weight == c->weight)
            {
            if(c1->type == c->type)
	      c = c1;
            c1 = c1->below;
            }

       if(c->below->state > 0)
         {
         c->state = 1;
	 continue;
         }

       for( t = &Top ; t->tower == c->tower ; t = t->next )
          {
          }
       for( t1 = t->next ; t1->tower == c->tower ; t1 = t1->next )
          {
          }
       c->state = -1;
       moveWeight(c->weight,t->tower);
       temp = c->tower;

       c->state = 0;
       move(c->tower,t1->tower);
       c->state = -1;

       moveWeight(c->weight,t->tower);

       c->state = 0;
       move(t1->tower,temp);
       c->state = 1;
       }
     }
}


void CreateTower(int Tower[TT][BB][2] , int x)   /* Generalized : x = 0 for initial state , x = 1 for final state */
{
struct TOP *t = &Top ;
struct BASE *b = &Base ;
struct block *b1;
int i=0 , j ;

if(x==1)
  t = &TopF;

while(Tower[i][0][0]!=0)
     {
     if(i!=0)
       {
       t->next = (struct TOP*) malloc(sizeof(struct TOP));
       t = t->next;
       }
     t->next = NULL;
     t->n = 0;
     t->tower = i+'A';           /* Towers are named A , B , C , etc. */

     t->top = (struct block*) malloc(sizeof(struct block));
     t->top->state = 2;         /* Block of infinite weight ie. state = 2 is made as lowest block of each tower */
     t->top->tower = i+'A';
     t->top->type = i+'A';
     t->top->weight = WW;
     t->top->above = NULL;
     t->top->below = NULL;

     if(Tower[i][0][1]==-1)      /* weight of first block = -1 for Empty Tower */
       {
       i++;
       continue;
       }
     j = 0;
     while(Tower[i][j][0]!=0)
	  {
	  b1 = (struct block*) malloc(sizeof(struct block));
	  b1->tower = t->tower;
	  b1->type = Tower[i][j][0]+'A'-1;     /* Block types are A , B , C , etc. */
	  b1->weight = Tower[i][j][1];
	  b1->state = 0;
	  b1->above = NULL;
	  b1->below = t->top;
	  t->top->above = b1;
	  t->top = b1;
	  t->n++;
	  j++;
	  }
     i++;
     }

if(x==1)
  {
  t = &TopF;
  b = &BaseF;
  }
while(t!=NULL)
     {
     t->temp = t->top;
     b->tower = t->tower;
     if(t->top->state == 2)
       b->base = NULL;
     else
       {
       while(t->temp->below->state!=2)
	    t->temp = t->temp->below;
       b->base = t->temp;
       }
     if(t->next!=NULL)
       b->next = (struct BASE*) malloc(sizeof(struct BASE));
     else
       b->next = NULL;

     t = t->next;
     b = b->next;
     }
}


void Display(struct block *b , char source , char dest , int x)    /* Generalized : x = 1 for Final Tower , Displays towers for (NULL,0,0) and lifting transition for (b,source,0) and dropping transition for (b,0,dest) */
{
int n = TotalBlocks();
struct TOP *t;
getch();
clrscr();

if(b!=NULL)
  n++;

t = &Top;
if(x==1)
  t = &TopF;
while(t!=NULL)
     {
     if(t->tower == source && b!=NULL)
       printf("%c%d\t",b->type,b->weight);
     else
       printf("\t");
     t = t->next;
     }
printf("\n");

t = &Top;
if(x==1)
  t = &TopF;
while(t!=NULL)
     {
     if(t->tower == dest && b!=NULL)
       printf("%c%d\t",b->type,b->weight);
     else
       printf("\t");
     t = t->next;
     }
printf("\n");

t = &Top;
if(x==1)
  t = &TopF;
while(t!=NULL)
     {
     t->temp = t->top;
     t->nTemp = n - t->n;
     t = t->next;
     }

while(n!=0)
     {
     t = &Top;
     if(x==1)
       t = &TopF;
     while(t!=NULL)
	  {
	  if(t->nTemp == 0)
	    {
	    printf("%c%d\t",t->temp->type,t->temp->weight);
	    t->temp = t->temp->below;
	    }
	  else
	    {
	    printf("\t");
	    t->nTemp--;
	    }
	  t = t->next;
	  }
     printf("\n");
     n--;
     }
if(x==1) printf("Final State");
if(x==2) printf("Initial State");
}
