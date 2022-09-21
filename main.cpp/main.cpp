
#include<iostream>
#include<iomanip>
#define READ 01         //Read a word into a specific memory location.
#define WRITE 02        //Print a word from a specific memory location.
#define STORE 11        //Store the word in the accumulator into a spe$
#define LOAD 12         //Load a word from a specific memory location $
#define ADD 21          //Add a word in a specific memory location to $
#define SUBTRACT 22     //Subtract a word in a specific memory locatio$
#define MULTIPLY 23     //Multiply a word in a specific memory locatio$
#define DIVIDE 24       //Divide a word in a specific memory location $
#define BRANCH 31       //Branch to a specific memory location.
#define BRANCHZERO 32   //Branch to a specific memory location if the $
#define BRANCHNEG 33    //Branch to a specific memory location if the $
#define HALT 34

using namespace std;

//#include"simplesim.h"
//#include"sml.h"
class simplesim
{
        public:
                simplesim();
                bool load_program();
                void execute_program();
                void dump_program() const;
        private:
                int memory[100];
                int accumulator = 0;
                int instruction_counter=0;
                int instruction_register=0;
                int operation_code=0;
                int operand=0;
};


int main()
{
    simplesim s;

    if (s.load_program())
        s.execute_program();

    s.dump_program();

    return 0;
}


simplesim::simplesim()
{

         for(int i = 0; i < 100; ++i)
         {
             memory[i] = 4444; // initializing all memory locations to 4444
         }
        accumulator = 0;
        instruction_counter=0;
        instruction_register=0;
        operation_code=0;
        operand=0;
   
    

}


bool validWord(int word)
{
 return word >= -9999 && word <= 9999;
}

bool simplesim::load_program()
{
    int i =0 ;
    int array[100];
    int storage = 0;
    
        while (cin >> array[i])
        {
        
            if  (!validWord(i))
            {
                cout << "*** ABEND: pgm load: invalid word ***" << endl;
                return false;
            }
        else
        {

            if( array[i] >100)
            {
                cout <<"*** ABEND: pgm load: pgm too large ***" << endl;
                return false; // might have to chnage the return type
            }
            memory[storage++]= i;
            return true ;
        }
        
        }
       //memory[storage]= words;
       //storage++;
return false;
}

bool validstorage(int storage)
{
    return storage > 0 && storage < 99 ;
}

void simplesim::execute_program()
{
     bool done = false;
     int temp = 0;

     while (!done)
     {
      if (!validstorage(instruction_counter))
          {
              cout <<"*** ABEND: addressability error ***" << endl;
          }
         
          instruction_register = memory[instruction_counter];
          operation_code = instruction_register / 100;
          operand = instruction_register % 100;
        
         
      switch (operation_code)
      {
      case READ:
            while( cin >> temp)
              if (!validWord(temp))
                {
                  cout << "*** ABEND: illegal input ***";
                    done = true;
                }
              memory[operand] = temp;
              instruction_counter++;
              cout <<"Read:"<< memory << endl ; //  might memory or operand
       break;
     
      case WRITE:
                cout <<operand << ": " << memory[operand] << endl; // might have to adjust between which one gets printed
                instruction_counter++;
       break;
     
      case LOAD:
              accumulator = memory[operand];
              instruction_counter++;
       break;
              
      case STORE:
              memory[operand] = accumulator;
              instruction_counter++;
       break;
              
      case ADD:
       temp = accumulator + memory[operand];
             if (temp < -9999)
                {
                    cout <<"*** ABEND: underflow ***";
                    done = true;
                }
            else if(temp > 9999)
                {
                    cout << "*** ABEND: overflow ***";
                    done = true;
                }
                accumulator = temp;
                instruction_counter++;
     
                
       break;
     
      case SUBTRACT:
              temp = accumulator - memory[operand];
              if (temp < -9999)
                   {
                       cout <<"*** ABEND: underflow ***";
                       done = true;       // might have to chnage to return 0;
                   }
              else if(temp > 9999)
                {
                  cout << "*** ABEND: overflow ***";
                  done = true;
                }
                accumulator = temp;
                instruction_counter++;

       break;
              
      case DIVIDE:
              temp = accumulator / memory[operand];
           if (memory[operand] == 0)
               {
                    cout << "*** ABEND: attempted division by 0 ***";
                    done = true;
               }
        else if (temp < -9999)
               {
                   cout <<"*** ABEND: underflow ***";
                   done = true;
               }
       else if(temp > 9999)
               {
                   cout << "*** ABEND: overflow ***";
                   done = true;
               }
      
                accumulator = temp;
                instruction_counter++;
       break;
              
      case MULTIPLY:
       temp = accumulator * memory[operand];
              if (temp < -9999)
              {
                  cout <<"*** ABEND: underflow ***";
                  done = true;
              }
          else if(temp > 9999)
              {
                  cout << "*** ABEND: overflow ***";
                  done = true;
              }
                accumulator = temp;
                instruction_counter++;
           
       break;
              
      case BRANCH:
       instruction_counter = operand;
       break;
              
      case BRANCHNEG:
       
              if (accumulator < 0)
              {
                  instruction_counter = operand;
              }
                   instruction_counter++;
       break;
              
      case BRANCHZERO:
              if (accumulator == 0 )
              {
                  instruction_counter = operand;
              }
              instruction_counter++;
       break;
              
      case HALT:
       cout << "****************** Simplesim execution terminated ***************\n";
       break;
              
      default:
       cout << "*** ABEND: invalid opcode ***";
       done = true;
       break;
     
      }
         if (operation_code != BRANCH && !done)
         {
             instruction_counter++;
         }
     }
}

void simplesim::dump_program() const
{
    void dump_check( const char [] , int, int, bool);
    
    cout << "REGISTERS:"<< endl;
    dump_check("accumulator: ",5,accumulator,true);
    dump_check("instruction_counter:", 2, instruction_counter, false);
    dump_check("instruction_register:", 5, instruction_register, true);
    dump_check("operation_code", 2, operation_code, false);
    dump_check("operand:", 2, operand, false);
    
    cout << "MEMORY:"<<endl;

       int i = 0;
        //alligns the header values to the last value in the columns fills in with spaces
        cout << setfill(' ')<< setw(3)<< ' ' ;
    
       //print header values from 0 to 9
       for (i= 0; i <= 9; ++i)
       {
        cout << setw(5) << i << " ";
       }
       
        //print out memory and left most column from 0 to 10
       for (i = 0; i < 100; ++i)
       {
           if (i % 10 == 0)         //printing out the left most column of table until
           {                        //reaching 100 displaying by 10
               cout << endl << setw(2) << i << " ";
           }
                    // will display all the memory from the array including signs
                cout << internal <<showpos
                << setw(5) << memory[i] << " "
                << internal<< noshowpos ;
       }
       cout << endl;
    
}

void dump_check( const char registers[] , int width, int data_member, bool sign)
{
 
 cout << setfill(' ') << left << setw(20) << registers << ' ';
 cout << left << setfill('0'); // will ensure that accumulator

// will add postivive or negative sign if needed
 if (sign == true)
    {
        cout << showpos <<internal;
    }
 else if (sign == false )
    {
        cout << noshowpos <<internal;
    }
 
 //determine the field width and dispay value
 if (width == 5)
  cout << setw(width) << data_member << endl;
 else //width is 2
  cout << setfill(' ') << setw(4) << ' ' << setw(width) << setfill('0') << data_member
        << endl;
 

}



// simplesim.cpp
// csci241 Assignment 4
// Created by Vanessa Aguilar (z1846838)

#include<iostream>
#include<iomanip>

#include"simplesim.h"
#include"sml.h"

using namespace std;

/*
* The default constructor performs initialization process for a simplesim objec
*
* @param: None
* @return: Nothing
*
* @note: None
*/

simplesim::simplesim()
{

         for(int i = 0; i < 100; ++i)
         {
             memory[i] = 4444; // initializing all memory locations to 4444
         }
        accumulator = 0;
        instruction_counter=0;
        instruction_register=0;
        operation_code=0;
        operand=0;
}
/*
* This function will check if the word brought in from load_program is "valid"
* between the parameters
*
* @param: int word: this word is brought in from loading in from cin
* @return: true if the word lies between those parameters
*
* @note: None
*/

bool validWord(int word)
{
 return word >= -9999 && word <= 9999;
}

/*
* This member function reads an sml program from standard input and attempts
* to load it into the simplesim memory.
*
* @param: None
* @return: Nothing
*
* @note: boolean value indicating whether or not the program was successfully loaded
*/

bool simplesim::load_program()
{
  int i =0 ;
    int array[100];
    int storage = 0;
    
        while (cin >> array[i])
        {
        
            if  (!validWord(i))
            {
                cout << "*** ABEND: pgm load: invalid word ***" << endl;
                return false;
            }
        else
        {

            if( array[i] >100)
            {
                cout <<"*** ABEND: pgm load: pgm too large ***" << endl;
                return false; // might have to chnage the return type
            }
            memory[storage++]= i;
            return true ;
        }
        
        }
       //memory[storage]= words;
       //storage++;
return false;
}

/*
* This function will check if the word broughn from l  "valid"
*
*
* @param: int storage: if it contains a memory location from (0-99)
* @return: true if the word lies between those parameters
*
* @note: None
*/

bool validstorage(int storage)
{
    return storage > 0 && storage < 99 ;
}

/*
* This member function executes an sml program
*
* @param: None
* @return: Nothing
*
* @note:
*/
void simplesim::execute_program()
{
     bool done = false;
     int temp = 0;

     while (!done)
     {
    // if it does not contain a memory location print error
      if (!validstorage(instruction_counter))
          {
              cout <<"*** ABEND: addressability error ***" << endl;
          }

          instruction_register = memory[instruction_counter];
          operation_code = instruction_register / 100;
          operand = instruction_register % 100;

  switch (operation_code)
      {
      case READ:
        while( cin >> temp)
        {
              if (!validWord(temp))
                {
                  cout << "*** ABEND: illegal input ***";
                    done = true;
                }
               memory[operand] = temp;
                  instruction_counter++;
                  cout <<"Read:"<< temp << endl;
        } //  might memory or operand
    
       break;
     
      case WRITE:
                cout <<memory[operand] << endl; // might have to adjust between which one gets printed
                instruction_counter++;
       break;
     
      case LOAD:
              accumulator = memory[operand];
              instruction_counter++;
       break;
              
      case STORE:
              memory[operand] = accumulator;
              instruction_counter++;
       break;
              
      case ADD:
       temp = accumulator + memory[operand];
             if (temp < -9999)
                {
                    cout <<"*** ABEND: underflow ***";
                    done = true;
                }
            else if(temp > 9999)
                {
                    cout << "*** ABEND: overflow ***";
                    done = true;
                }
                accumulator = temp;
                instruction_counter++;
     
                
       break;
     
      case SUBTRACT:
              temp = accumulator - memory[operand];
              if (temp < -9999)
                   {
                       cout <<"*** ABEND: underflow ***";
                       done = true;       // might have to chnage to return 0;
                   }
              else if(temp > 9999)
                {
                  cout << "*** ABEND: overflow ***";
                  done = true;
                }
                accumulator = temp;
                instruction_counter++;

       break;
              
      case DIVIDE:
              temp = accumulator / memory[operand];
           if (memory[operand] == 0)
               {
                    cout << "*** ABEND: attempted division by 0 ***";
                    done = true;
               }
        else if (temp < -9999)
               {
                   cout <<"*** ABEND: underflow ***";
                   done = true;
               }
       else if(temp > 9999)
               {
                   cout << "*** ABEND: overflow ***";
                   done = true;
               }
      
                accumulator = temp;
                instruction_counter++;
       break;
              
      case MULTIPLY:
       temp = accumulator * memory[operand];
              if (temp < -9999)
              {
                  cout <<"*** ABEND: underflow ***";
                  done = true;
              }
          else if(temp > 9999)
              {
                  cout << "*** ABEND: overflow ***";
                  done = true;
              }
                accumulator = temp;
                instruction_counter++;
           
       break;
              
      case BRANCH:
       instruction_counter = operand;
       break;
              
      case BRANCHNEG:
       
              if (accumulator < 0)
              {
                  instruction_counter = operand;
              }
                   instruction_counter++;
       break;
              
      case BRANCHZERO:
              if (accumulator == 0 )
              {
                  instruction_counter = operand;
              }
              instruction_counter++;
       break;
              
      case HALT:
       cout << "****************** Simplesim execution terminated ***************\n";
       break;
              
      default:
       cout << "*** ABEND: invalid opcode ***";
       done = true;
       break;
     
      }
         if (operation_code != BRANCH && !done)
         {
             instruction_counter++;
         }
     }
}
/*
* This member function dumps the contents of the simplesims registers and memory
*
* @param: None
* @return: Nothing
*
* @note:
*/
void simplesim::dump() const
{
    void dump_check( const char [] , int, int, bool);
    
    cout << "REGISTERS:"<< endl;
    dump_check("accumulator: ",5,accumulator,true);
    dump_check("instruction_counter:", 2, instruction_counter, false);
    dump_check("instruction_register:", 5, instruction_register, true);
    dump_check("operation_code", 2, operation_code, false);
    dump_check("operand:", 2, operand, false);
    
    cout << "MEMORY:"<<endl;

       int i = 0;
        //alligns the header values to the last value in the columns fills in with spaces
        cout << setfill(' ')<< setw(3)<< ' ' ;
    
       //print header values from 0 to 9
       for (i= 0; i <= 9; ++i)
       {
        cout << setw(5) << i << " ";
       }
       
        //print out memory and left most column from 0 to 10
       for (i = 0; i < 100; ++i)
       {
           if (i % 10 == 0)         //printing out the left most column of table until
           {                        //reaching 100 displaying by 10
               cout << endl << setw(2) << i << " ";
           }
                    // will display all the memory from the array including signs
                cout << internal <<showpos
                << setw(5) << memory[i] << " "
                << internal<< noshowpos ;
       }
       cout << endl;
    
}
/*
* This function will ensure that the display of the table will be modified and set to
* the desired display
*
* @param const char  registers[]: bring in each register name to display
* @param int width: set fill to fix display
* @param int data_member:  data member content will be displayed
* @param bool sign : will add a positive sign or not
*
* @return: Nothing
*/
void dump_check( const char registers[] , int width, int data_member, bool sign)
{
 
 cout << setfill(' ') << left << setw(20) << registers << ' ';
 cout << left << setfill('0'); // will ensure that accumulator

// will add postivive or negative sign if needed
 if (sign == true)
    {
        cout << showpos <<internal;
    }
 else if (sign == false )
    {
        cout << noshowpos <<internal;
    }
 
 //determine the field width and dispay value
 if (width == 5)
  cout << setw(width) << data_member << endl;
 else //width is 4
  cout << setfill(' ') << setw(4) << ' ' << setw(width) << setfill('0') << data_member
        << endl;
 

}



