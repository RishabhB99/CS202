#include <stdio.h>
#include <stdlib.h>
int main(void) {
  int i,j,k,l,m,n;
  FILE*fp=fopen("input.txt","w");   //input file to store propositions
  int prop[9][9][9];    //3 d array to store propositions
  char input[9][9];
  for(i=0;i<9;i++)
  {   //loop for storing propositions of the given entries
    for(j=0;j<9;j++)
      {
        scanf("%c ",&input[i][j]);
        if(input[i][j]!=46)
        {
          int a = 100*(i+1)+10*(j+1)+(int)input[i][j]-48;
          fprintf(fp,"%d %d\n",a,0);
        }
      }
  }
  for(i=0;i<9;i++)
  { ////loop for at least element in a cell
    for(j=0;j<9;j++)
    {
      for(k=0;k<9;k++)
      prop[i][j][k] = (100*(i+1))+(10*(j+1))+k+1;
    }
  }
  for(i=0;i<9;i++)
  {
    for(j=0;j<9;j++)
    {
      for(k=0;k<9;k++)
      fprintf(fp,"%d ",prop[i][j][k]);
      fprintf(fp,"%d\n",0);
    }
  }
  for(i=0;i<9;i++)
  {   //loop for at most element in a cell
    for(j=0;j<9;j++)
    {
      for(k=0;k<9;k++)
        for(l=k+1;l<9;l++)
        fprintf(fp,"%d %d %d\n",-prop[i][j][k],-prop[i][j][l],0);
    }
  }
  for(i=0;i<9;i++)
  {   //loop for all elements in each row
    for(k=0;k<9;k++)
    {
      for(j=0;j<9;j++)
      fprintf(fp,"%d ",prop[i][j][k]);
      fprintf(fp,"%d\n",0);
    }
  }
  for(i=0;i<9;i++)
  {   //loop for all elements in each column
    for(k=0;k<9;k++)
    {
      for(j=0;j<9;j++)
      fprintf(fp,"%d ",prop[j][i][k]);
      fprintf(fp,"%d\n",0);
    }
  }
  for(m=0;m<3;m++)
  {   //loop for all elements in each block
    for(n=0;n<3;n++)
    {
      for(k=0;k<9;k++)
      {
        for(j=3*m;j<3+3*m;j++)
        {
        for(i=3*n;i<3+3*n;i++)
        fprintf(fp,"%d ",prop[j][i][k]);
        }
      fprintf(fp,"%d\n",0);
      }
    }
  }
  for(i=0;i<9;i++)
  {   //loop for all elements in 1st main diagonal
    for(k=0;k<9;k++)
    fprintf(fp,"%d ",prop[k][k][i]);
    fprintf(fp,"%d\n",0);
  }
  for(i=0;i<9;i++)
  {   //loop for all elements in 2nd main diagonal
    for(k=0;k<9;k++)
    fprintf(fp,"%d ",prop[k][8-k][i]);
    fprintf(fp,"%d\n",0);
  }
  fclose(fp);
  system("minisat input.txt output.txt");   //calling sat function
FILE*ab=fopen("output.txt","r");    //reading output of minisat
int sudoku[9][9];   //array for printing solution
char string[10];
fscanf(ab,"%s",string);
if(string[0]!='S'){
  printf("No solution exists");   //if no sol exist
  fclose(ab);
  return 0;
}
else
{
  for(int k=0;k<2;k++)
    fscanf(ab,"%s",string);
}
while(!feof(ab))
{   
  fscanf(ab,"%d",&i);
  if(i>0)
  sudoku[i/100 - 1][i/10 - 10*(i/100) - 1] = i%10;    //assigining values to sudoku solution
}
for(i=0;i<9;i++)
{
  for(int j=0;j<9;j++)
  printf("%d ",sudoku[i][j]);   //printing sudoku
  printf("\n");
}
fclose(ab);
  return 0;
}