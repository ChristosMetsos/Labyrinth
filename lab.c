#include<stdio.h>
#include<stdlib.h>
#include<time.h>


typedef struct s_link
{
  char data;
  struct s_link *up;
  struct s_link *down;
  struct s_link *next;
  struct s_link *prev;
} link;




int HasAvailableMoves(link **path, link **p, int mode);
void PrintLabyrinth1(link ***head);


int main(void)
{
  char fname[100];
  FILE *f;
  char **temp_board;
  int c, i = 1, j = 0;
  int h, w;


  printf("Insert your file's name: ");
  scanf("%s", fname);


  temp_board = (char**)malloc(sizeof(char*));
  temp_board[0] = (char*)malloc(sizeof(char));
  f = fopen(fname,  "r");
  do {
        c = fgetc(f);
        if( feof(f) ) {
           break ;
        }
        if (c == '\n')
        {
          c = fgetc(f);
          if( feof(f) ) {
             break ;
          }
          temp_board = (char**)realloc(temp_board ,(++i) * sizeof(char*));
          temp_board[i-1] = (char*)malloc(sizeof(char));
          w = j;
          j = 0;
        }
        temp_board[i-1] = (char*)realloc(temp_board[i-1], (++j) * sizeof(char));
        temp_board[i-1][j-1] = (char)c;
     } while(1);

     h = i;

     link **head = (link**)malloc(h*sizeof(link*));

     for(i = 0; i < h; i++)
     {
       head[i] = (link*)malloc(sizeof(link));
     }

     link *p, *p2, *p3;

     p = head[0];
     p->data = temp_board[0][0];
     p->prev = NULL;
     for (j = 1; j < w; j++)
     {
       p->next = (link*)malloc(sizeof(link));
       p3 = p->next;
       p3->prev = p;
       p->up = NULL;
       p = p->next;
       p->data = temp_board[0][j];
     }

     for (i = 1; i < h; i++)
     {
       p = head[i];
       p->data = temp_board[i][0];
       p2 = head[i-1];
       p->prev = NULL;
       p->up = p2;
       p2->down = p;
       for (j = 1; j < w; j++)
       {
         p->next = (link*)malloc(sizeof(link));
         p3 = p->next;
         p3->prev = p;
         p = p->next;
         p->data = temp_board[i][j];
         p2 = p2->next;
         p2->down = p;
         p->up = p2;
       }
       p->next = NULL;
     }
     p = head[i-1];
     for (j = 0; j < w - 1; j++)
     {
       p->down = NULL;
     }

     PrintLabyrinth1(&head);


     i = 1;
     link **path = (link**)malloc(sizeof(link*));
     path[0] =head[1];
     path[0]->data = 'w';

     while(1)
     {
       printf("\n\n");
       PrintLabyrinth1(&head);
       printf("\n\n");
       c = HasAvailableMoves(&(path[i-1]), &p, (i-1 == 0) ? 2 : 1);

       if (c == 0)
       {
         if (i-1 == 0) {printf("\nNO WAY OUT\n");break;} // an den exei poy alloy na paei teleiwnei
         path[i-1]->data = 'x';
         while (HasAvailableMoves(&(path[(--i)-1]), &p, (i-1 == 0) ? 2 : 1) == 0)
         {
           if (i-1 == 0) {printf("\nNO WAY OUT\n");break;} // an den exei poy alloy na paei teleiwnei
           path[i]->data = 'x';
           path = (link**)realloc(path, i * sizeof(link*));
         }

         path[i]->data = 'x';
         if (i-1 == 0) {printf("\nNO WAY OUT\n");break;} else continue; // an den exei poy alloy na paei teleiwnei
         path = (link**)realloc(path, i * sizeof(link*));
       }
       else if (c == 2)
       {
         path = (link**)realloc(path, (++i) * sizeof(link*));
         p->data = 'w';
         printf("\nSOLUTION COMPLETE!\n");
         break;
       }
       path = (link**)realloc(path, (++i) * sizeof(link*));
       path[i-1]=p;
       p->data = 'w';
     }
     for(i = 0; i < h; i++)
     {
       p = head[i];
       while (p != NULL)
       {
         p2 = p;
         p = p->next;
         free(p2);
       }
     }
     free(head);
     free(path);
     return 0;
}

int HasAvailableMoves(link **path, link **p, int mode)
{
  int c = 0;
  if (mode == 1)
  {
    if ((*path)->next == NULL || (*path)->prev == NULL || (*path)->up == NULL || (*path)->down == NULL) return 2;

    if ((*path)->next->data == '0')
    {
      *p= (*path)->next;
      return 1;
    }

    if ((*path)->prev->data == '0')
    {
      *p = (*path)->prev;
      return 1;
    }

    if ((*path)->up->data == '0')
    {
      *p = (*path)->up;
      return 1;
    }

    if ((*path)->down->data == '0')
    {
      *p = (*path)->down;
      return 1;
    }
    return 0;
  }
  else if (mode == 2)
  {
    if ((*path)->next != NULL)
    {
      if ((*path)->next->data == '0')
      {
        (*p)= (*path)->next;
        return 1;
      }
    }

    if ((*path)->next != NULL)
    {
      if ((*path)->prev->data == '0')
      {
        (*p) = (*path)->prev;
        return 1;
      }
    }

    if ((*path)->next != NULL)
    {
      if ((*path)->up->data == '0')
      {
        (*p) = (*path)->up;
        return 1;
      }
    }

    if ((*path)->next != NULL)
    {
      if ((*path)->down->data == '0')
      {
        (*p) = (*path)->down;
        return 1;
      }
    }

    return 0;
  }

}

void PrintLabyrinth1(link ***head)
{
  int i = 0;
  link *p = (*head)[0];
  while(p->next != NULL || p->down != NULL)
  {
    printf("%c", p->data);
    if (p->next == NULL)
    {
      p = (*head)[++i];
      printf("\n");
    }
    else
    {
      p = p->next;
    }
  }
  printf("%c\n", p->data);
}
