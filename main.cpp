#include <iostream>
#include "GenStack.h"
#include <fstream>

using namespace std;
using namespace hw3;

// main declares game object and runs the game
int main(int argc, char *argv[]){

  bool running = true;
  bool isGood = true;  // syntax innocent until proven guilty
  int lineNum=0;
  char stackchar,filechar; // dump fstream data here
  string line; // used in getline
  string filename = argv[0]; // setting initial filename to first arg
  ifstream FileStream(filename); // begin parsing file
  GenStack<char> TheStack(1); // store opening characters here
  GenStack<int> NumStack(1); // store line numbers here

  while(running){
    // opening and closing chars must be symmetric
    // once closing char is found, compare following to popped stock
    while(getline(FileStream,line)){ // read until there are no more lines
      lineNum++; // keep track of the line number
      for(int x=0;x<line.size();x++){ // for every char in the line
        filechar=line[x];
        if(filechar=='{'||filechar=='('||filechar=='['){
          TheStack.push(filechar); NumStack.push(lineNum); // store opening chars + line num
        }
        if(filechar=='}'||filechar==')'||filechar==']'){ // once closing brace is found
          if(TheStack.size()==0){ // if there's more closing chars than opening
            isGood = false;       // the syntax is bad
          }

          // if closing doesnt match opening then the syntax is big bad
          switch (filechar) {
            case ')':
              stackchar=TheStack.pop();
              NumStack.pop(); // removing elements from line num stack to match char stack
              if(stackchar!='('){isGood=false;}
              break;
            case '}':
              stackchar=TheStack.pop();
              NumStack.pop(); // removing elements from line num stack to match char stack
              if(stackchar!='{'){isGood=false;}
              break;
            case ']':
              stackchar=TheStack.pop();
              NumStack.pop(); // removing elements from line num stack to match char stack
              if(stackchar!='['){isGood=false;}
              break;
          }
        }
        if(!isGood){break;} // once error is found, we can exit program
      }
      if(!isGood){break;} // once error is found, we can exit program
    }
    // check to see if missing opening or closing
    if(TheStack.size()>0){ // no closing char
      cout << "Reached end of file, didn't find a closing char for \""
      << TheStack.pop() << "\"; Line "<<NumStack.pop()<<endl;
      isGood=false;
    }
    else if(!isGood){ // no opening char
      cout<<"No opening char for \""<<filechar<<"\";"<<" Line "<<lineNum<<endl;
    }
    else{ // file is okay
      cout<<"File is good"<<endl;
    }

    // checking if user would like to analyze another file
    string input;
    while(true){
      cout<<"Would you like to read another file (Y/N)? ";
      cin>>input;
      if(input=="N"||input=="n"){running=false;break;} // exit condition
      else if(input=="Y"||input=="y"){ // enter new filename
        cout << "Which file would you like to analyze? ";
        cin >> filename;
        break;
      }
      else{ // prompt for input again
        cout << "Invalid input, try again" << endl;
        cin.clear(); // clearing input buffer
        cin.ignore(55, '\n');
      }
    }
  }
}
