/* Nelani Dlamini
   Assignment 7
   November 2018
   CSC-3310 Theory of Computation
*/

#include <iostream>
#include <fstream>

#define MAX 500000
#define TOTAL 1000000

using namespace std;

//Struct to store the transitions recieved from the transition file
struct transit {
  string currentstate;
  string input;
  string output;
  string action;
  string nextstate;
} transitions[500];
//function to store transitions from transition file
void create_transitions();
void find_states();
void find_accept_states();
void machine();
void findtransition();
void checkaccept();
void execute(int trans);
void accept();
void newlog();
void setTape();
void documentTape();


int transition_num = 0;
string states[500];
int statenum = 0;
string acceptstates[500];
int acceptnum = 0;

string tape[TOTAL];
int top = MAX;
int bottom = MAX;
int head = MAX;
string currstate = "0";

int main()
{
  create_transitions();
  find_states();
  find_accept_states();
  setTape();
  machine();

  return 0;
}
void create_transitions()
{
  string c;
  string line;
  int i = 0;
  ifstream transitionfile ("transition.txt");
  if (transitionfile.is_open()){
    while (getline(transitionfile,line)){
      while(!isspace(line[i])){
        c += line[i];
        i++;
      }
      i++;
      transitions[transition_num].currentstate = c;
      c.clear();
      while(!isspace(line[i])){
        c += line[i];
        i++;
      }
      i++;
      transitions[transition_num].input = c;
      c.clear();
      while(!isspace(line[i])){
        c += line[i];
        i++;
      }
      i++;
      transitions[transition_num].output = c;
      c.clear();
      while(!isspace(line[i])){
        c += line[i];
        i++;
      }
      i++;
      transitions[transition_num].action = c;
      c.clear();
      while(i != line.length()){
        c += line[i];
        i++;
      }
      transitions[transition_num].nextstate = c;
      i = 0;
      c.clear();
      transition_num++;
    }
  }else cout << "Unable to open transition file" << endl;
}
//Function to find accept states by finding states that don't have a transition to follow
void find_states()
{
  for(int i = 0; i < transition_num; i++){
    int j;
    for(j = 0; j < i; j++)
      if(transitions[i].currentstate == states[j])
        break;
      if(i == j){
        states[statenum] = transitions[i].currentstate;
        statenum++;
      }
    }
}
void find_accept_states()
{
  for(int i = 0; i < transition_num; i++){
    int same = 0;
    for(int j = 0; j < statenum; j++){
      if(transitions[i].nextstate == states[j]){
        same = 1;
        break;
      }
    }
      if(same == 0){
        states[statenum] = transitions[i].nextstate;
        acceptstates[acceptnum] = transitions[i].nextstate;
        acceptnum++;
        statenum++;
      }
  }
}
void setTape()
{
  char c;
  ifstream inputfile ("input.txt");
  if (inputfile.is_open()){
    while(inputfile.get(c) && c != ' '){
      tape[top] = c;
      top++;
    }
  }else cout << "Unable to open input file" << endl;
}
void machine()
{
  checkaccept();
  newlog();
  findtransition();
}

void findtransition()
{
  string element;
  element = tape[head];
  int halt = 0;

  for(int i = 0; i < transition_num; i++){
    if(transitions[i].currentstate == currstate){
      for(int j = 0; j < transition_num; j++){
        if(transitions[i].input == element || transitions[i].input == "%"){
          documentTape();
          execute(i);
          documentTape();
        } else halt = 1;
      }
    } else halt = 1;
  }

  if(halt == 1){
    //checkaccept();
  }
}
void documentTape()
{
  ofstream logfile ("log.txt");
  if (logfile.is_open()){
    logfile << "Current Tape: " << endl;
    for(int i = bottom; i < top; i++){
      if(head == i ){
        logfile << tape[i] << "* ";
      }else{
        logfile << tape[i] << " ";
      }
    }
    logfile << endl << endl;
  }else cout << "Unable to open log file" << endl;
}

void execute(int trans)
{
  ofstream logfile ("log.txt");
  if (logfile.is_open()){
    /*
    logfile << "Executing Transition: " << transitions[trans].currentstate << " "
    << transitions[trans].input << " " << transitions[trans].output << " " <<
    transitions[trans].action << " " << transitions[trans].nextstate << endl;

    if(transitions[trans].output != "%"){
      tape[head] = transitions[trans].output;
    }

    if(transitions[trans].action == "L"){
      head--;
      if(head < bottom)
        bottom = head;
    }
    if(transitions[trans].action == "R"){
      head++;
      if(head > top)
        top = head;
    }
    currstate = transitions[trans].nextstate;*/


  }else cout << "Unable to open log file" << endl;
}

void newlog()
{
  ofstream logfile ("log.txt");
  if (logfile.is_open()){
    logfile << "NEW CYCLE STARTING " << endl;
    }
  else cout << "Unable to open log file" << endl;
}

void checkaccept()
{
  for(int i = 0; i < acceptnum; i++)
    if(currstate == acceptstates[i])
      accept();
}

void accept()
{
  ofstream outputfile ("output.txt");
  if (outputfile.is_open()){
    outputfile << "STRING ACCEPTED" << endl;
  }else cout << "Unable to open output file" << endl;
}
