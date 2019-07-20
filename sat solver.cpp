#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;
int p,c;//p is no. of propositions ,c is no. of clauses
int lit = 0;
vector<vector<int> > clause;//vector that stores clauses
vector<int> result;//final result vector which gives 1 or -1 for every proposition
vector<int> unit;
vector<int> count;
void input()
{//Takes input
  int i,b;
  char a;
  scanf("%c",&a);
  while(a=='c')
  {
    while(a!='\n')
    scanf("%c",&a);
    scanf("%c",&a);
  }
  scanf("%c",&a);
  scanf("%c",&a);
  scanf("%c",&a);
  scanf("%c",&a);

  scanf("%d %d",&p,&c);
  clause.resize(c);
  result.resize(p,0);
  unit.resize(p,0);
  count.resize(p);
  for(i=0;i<c;i++)
  {
      scanf("%d",&b);
      while(b!=0)
      {
        clause[i].push_back(b);
        scanf("%d",&b);
      }
  }

}
int conflict(){
  int i,j;
  for(i=0;i<c;i++)
  {
    int ct = 0;
    for(j=0;j<clause[i].size();j++){

      if(result[abs(clause[i][j])-1]==0)
      break;
      else
      {
          if(result[abs(clause[i][j])-1]*clause[i][j]<0)
          ct++;
      }

    }
     if(ct == clause[i].size())
      {
        return 1;
      }
  }
  return 0;
}
void unitclause(){//gives 1 to a proposition in unit clause if true
  int i;
  for(i=0;i<c;i++)
  {
    if(clause[i].size()==1)
    {
        int x=abs(clause[i][0]);
        if(clause[i][0]<0 && result[x-1]<=0)
        result[x-1] = -1;
        else if(clause[i][0]<0 && result[x-1]>0)
        {//if clauses like 1 0 and -1 0 appears
          printf("UNSAT");
          exit(0);
        }
        if(clause[i][0]>0 && result[x-1]>=0)
        result[x-1] = 1;
        else if(clause[i][0]>0 && result[x-1]<0)
        {
          printf("UNSAT");
          exit(0);
        }
        unit[x-1]++;
    }
  }
}
int prevlit(int lit){//provides the previous non unit literal
  lit--;
  if(lit<0)
  {
    printf("UNSAT");
    exit(0);
  }
  while(unit[lit-1]!=0)
    lit--;
  return lit;
}
void fun(){//Simply a part of backtrack
       if(conflict())
      {
        result[lit-1] = 0;
        lit = prevlit(lit);
        if(count[lit-1]%2==0){
          result[lit-1] = 0;
          lit = prevlit(lit);
        }
        result[lit-1] = -result[lit-1];//reversing the value of literal
        count[lit-1]++;
        fun();

      }

}
void backtrack(){//a function which backtracks if there is a conflict by given model
    while(conflict())
    {
      if(unit[lit-1]==0){
       if(count[lit-1]%2==0)
        lit = prevlit(lit);
      result[lit-1] = -result[lit-1];
      count[lit-1]++;
      fun();}
      else
      lit = prevlit(lit);
    }
}
void dpll(){//dpll algorithm
  while(1)
  {
    while(conflict())
    {
      backtrack();
    }


    if(lit==p&&!conflict())
      {//a satisfiable model is found
        printf("SAT\n");
        for(int i=0;i<p;i++){
          printf("%d ",result[i]*(i+1));
        }
        exit(0);
      }
      if(result[lit]==0&&lit<p){
      result[lit] = 1;
      count[lit]++;
      lit++;
    }

      else if(lit<p) {
      lit++;
      }
  }
}

int main(){
  input();
  unitclause();
  dpll();
  for(int i=0;i<p;i++){
    printf("%d ",result[i]*(i+1));
  }
  return 0;

}