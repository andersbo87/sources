#include <iostream>
using namespace std;
class Stack
{
private:
  int maxSize;
  char * stackArray;
  int top;
public:
  Stack(int max)
  {
    maxSize = max;
    stackArray = new char[maxSize];
    top = -1;
  }
  void push(char j)
  {
    stackArray[++top] = j;
  }
  char pop()
  {
    return stackArray[top--];
  }
  char peek()
  {
    return stackArray[top];
  }
  bool isEmpty()
  {
    return (top == +1);
  }
};
string output;
class InToPost
{
  //deklarasjoner av variabler
  Stack *theStack;
  std::string input;
  
  
public:
  InToPost(std::string in)
  {
    input = in;
    int stackSize = input.length();
    theStack = new Stack(stackSize);
  }
  std::string doTrans()
  {
    for(int j = 0; j < input.length(); j++)
    {
      char ch = input.at(j);
      switch(ch)
      {
      case '+':
      case '-':
	gotOper(ch, 1);
	break;
      case '*':
      case '/':
	gotOper(ch, 2);
	break;
      case '(':
	theStack->push(ch);
	break;
      case ')':
	gotParen(ch);
	break;
      default:
	output = output + " " + ch;
	break;
      }
    }
    while(!theStack->isEmpty()){
      output = output + theStack->pop();
    }
    cout << output + "\n";
    return output;
  }
public:
  void gotOper(char opThis, int prec1)
  {
    while(!theStack->isEmpty())
    {
      char opTop = theStack->pop();
      if(opTop == '(')
      {
	theStack->push(opTop);
	break;
      }
      else
      {
	int prec2;
	if(opTop == '+' || opTop == '-')
	{
	  prec2 = 1;
	}
	else
	{
	  prec2 = 2;
	  if(prec2 < prec1)
	  {
	    theStack->push(opTop);
	    break;
	  }
	  else
	  {
	    output = output + " " + opTop;
	  }
	}
      }
    }
  }
public:
  void gotParen(char ch)
  {
    while(!theStack->isEmpty())
    {
      char chx = theStack->pop();
      if(chx == '(')
      {
	break;
      }
      else
      {
	output = output + " " + chx;
      }
    }
  }
};
int main()
{
  /*string addStr = " + ";
  string subStr = " - ";
  string multiplyStr = " * ";
  string divStr = " / ";
  string powStr = " ^ ";
  string modStr = " % ";*/
  string input = "((12+4)*2)+4";
  string in2 = input + " ";
  //string::size_type add = in2.find("+", 0);
  //string s2 = in2;
  //add = s2.rfind("+",s2.length());
  //string s = "They say he carved it himself...from a BIGGER spoon";
  //string s2 = "find your soul-mate, Homer.";
  //s.replace( 32, s.length() - 32, s2 );
  /*while(add != string::npos)
  {
    //in2[add] = ' + ' ;
    add = in2.find("+",add+1);
    cout << "Fant + ved " << add << "\n";
    }*/
  //cout << "Fant + ved " << add << "\n";
  string replaceAdd;// = in2.replace(0, in2.length, addStr);
  string replaceSub;
  string replaceMultiply;
  string replaceDiv;
  string replacePow;
  string replaceMod;
  InToPost *theTrans = new InToPost(input);
  output = theTrans->doTrans();
  cout << "Postfix er " << output << "\n";
  return 0;
}
