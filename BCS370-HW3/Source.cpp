#include <iostream>
#include <fstream>
#include <random>
#include "farmingdaleDynamicContiguousMemoryQueue.h"

using namespace std;

void randomStream(std::string filename, int iterations)
{
    //set randoms for letters
    std::random_device rd1;
    std::mt19937 gen1(rd1());
    std::uniform_int_distribution<> dis1(0, 5);

    //set randoms for numbers that follow 'A'
    std::random_device rd2;
    std::mt19937 gen2(rd2());
    std::uniform_int_distribution<> dis2(INT_MIN, INT_MAX);

    //declare variables
    int temp;
    string letters[6] = { "A","D","P","E","C","S" }; //string to hold letters, use rand for i to get rand letter
    ofstream outputFile(filename); //open file

    for (int i = 0; i < iterations; ++i)
    {
        temp = dis1(gen1); //temp int to hold rand num
        if (temp == 0) //if rand num produces 'A', use rand gen2 to add more rand nums
        {
            outputFile << letters[temp] << " " << dis2(gen2);//output to file
        }
        else //if rand != A, the just add the letter
        {
            outputFile << letters[temp];
        }
        if (i != iterations - 1) //num of lines must be EXACTLY same as iterations...if not last line, add new line
        {
            outputFile << "\n";
        }
    }
    outputFile.close(); //close file
}

void testStream(std::string filename)
{
    //create four instances of the farmingdale::queue ADT holding std::strings. 
    farmingdale::queue<std::string> queue1;
    farmingdale::queue<std::string> queue2;
    farmingdale::queue<std::string> queue3;
    farmingdale::queue<std::string> queue4;

    //initialize statusCode variables to compare cases
    farmingdale::statusCode statusCodeQueue1;
    farmingdale::statusCode statusCodeQueue2;
    farmingdale::statusCode statusCodeQueue3;
    farmingdale::statusCode statusCodeQueue4;

    //initalize peekValue variables to compare cases
    std::string peekValue1;
    std::string peekValue2;
    std::string peekValue3;
    std::string peekValue4;

    //initalize dequeueValue variables to compare cases
    std::string dequeueValue1;
    std::string dequeueValue2;
    std::string dequeueValue3;
    std::string dequeueValue4;

    //initialize isEmpty bools to compare cases
    bool queueIsEmpty1;
    bool queueIsEmpty2;
    bool queueIsEmpty3;
    bool queueIsEmpty4;

    //open file
    fstream myFile;
    myFile.open(filename, ios::in);

    //read each line of the file
    int iterator = 1;
    if (myFile.is_open())
    {
        string fileLine;
        while (getline(myFile, fileLine))
        {
            //process each line as if it was a set of instructions
            switch (fileLine[0])
            {
            case 'A':
            {
                //get the number from the remainder of the line as a string
                fileLine.erase(0, 2);

                //enqueue() number into all of the queues and return status codes
                statusCodeQueue1 = queue1.enqueue(fileLine);
                statusCodeQueue2 = queue2.enqueue(fileLine);
                statusCodeQueue3 = queue3.enqueue(fileLine);
                statusCodeQueue4 = queue4.enqueue(fileLine);

                /*
                It must check the return value of the enqueue() operations.
                If any of the enqueues return FAILURE because they are full,
                all must return that same return code.
                (since these are dynamic, this really is not expected)
                If only some of the queues return FAILURE, that is an error,
                and it should terminate and print the line number from the instruction file
                (not the program line number)
                */
                if (statusCodeQueue1 != statusCodeQueue2 ||
                    statusCodeQueue1 != statusCodeQueue3 ||
                    statusCodeQueue1 != statusCodeQueue4)
                {
                    std::cout << "testStream() FAILURE" << std::endl;
                    std::cout << "Enqueue statusCode ERROR on instruction file line " << iterator << "!" << std::endl;
                    std::cout << "Terminating program!" << std::endl;
                    exit(0);
                }

                break;
            }
            case 'P':
            {
                //peek() the queues
                statusCodeQueue1 = queue1.peek(peekValue1);
                statusCodeQueue2 = queue2.peek(peekValue2);
                statusCodeQueue3 = queue3.peek(peekValue3);
                statusCodeQueue4 = queue4.peek(peekValue4);

                /*
                It must check the return value of the peek()operations.
                If any of the queues return FAILURE because they are empty,
                all must return that same return code.
                If only some of the queues return FAILURE, that is an error,
                and it should terminate and print the line number from the instruction file.
                */
                if (statusCodeQueue1 != statusCodeQueue2 ||
                    statusCodeQueue1 != statusCodeQueue3 ||
                    statusCodeQueue1 != statusCodeQueue4)
                {
                    std::cout << "testStream() FAILURE" << std::endl;
                    std::cout << "Peek statusCode ERROR on instruction file line " << iterator << "!" << std::endl;
                    std::cout << "Terminating program!" << std::endl;
                    exit(0);
                }

                /*
                If the peek()did not return FAILURE,
                your code should make sure all peek()s “returned” the same top string element
                (we use “return” loosely here to include data returned to the caller as a reference parameter)
                */
                if (peekValue1 != peekValue2 ||
                    peekValue1 != peekValue3 ||
                    peekValue1 != peekValue4)
                {
                    std::cout << "testStream() FAILURE" << std::endl;
                    std::cout << "PeekValue ERROR on instruction file line " << iterator << "!" << std::endl;
                    std::cout << "Terminating program!" << std::endl;
                    exit(0);
                }

                break;
            }
            case 'D':
            {
                //dequeue() all the queues
                statusCodeQueue1 = queue1.dequeue(dequeueValue1);
                statusCodeQueue2 = queue2.dequeue(dequeueValue2);
                statusCodeQueue3 = queue3.dequeue(dequeueValue3);
                statusCodeQueue4 = queue4.dequeue(dequeueValue4);

                /*
                It must check the return value of the dequeue()operations.
                If any of the queues return FAILURE because they are empty,
                all must return that same return code.
                If only some of the queues return FAILURE, that is an error,
                and it should terminate and print the line number from the instruction file.
                */
                if (statusCodeQueue1 != statusCodeQueue2 ||
                    statusCodeQueue1 != statusCodeQueue3 ||
                    statusCodeQueue1 != statusCodeQueue4)
                {
                    std::cout << "testStream() FAILURE" << std::endl;
                    std::cout << "Dequeue statusCode ERROR on instruction file line " << iterator << "!" << std::endl;
                    std::cout << "Terminating program!" << std::endl;
                    exit(0);
                }

                /*
                If the queues were not empty (that is, if it did not return FAILURE),
                it must check all elements removed from each queue were the same
                */
                if (dequeueValue1 != dequeueValue2 ||
                    dequeueValue1 != dequeueValue3 ||
                    dequeueValue1 != dequeueValue4)
                {
                    std::cout << "testStream() FAILURE" << std::endl;
                    std::cout << "DequeueValue ERROR on instruction file line " << iterator << "!" << std::endl;
                    std::cout << "Terminating program!" << std::endl;
                    exit(0);
                }

                break;
            }
            case 'E':
            {
                //should check if the queues are empty
                queueIsEmpty1 = queue1.isEmpty();
                queueIsEmpty2 = queue2.isEmpty();
                queueIsEmpty3 = queue3.isEmpty();
                queueIsEmpty4 = queue4.isEmpty();

                /*
                It should run isEmpty() on all queues
                It should check the return values of isEmpty().
                True or false is fine, but all must agree.
                If they don’t agree, then it’s an error.
                */
                if (queueIsEmpty1 != queueIsEmpty2 ||
                    queueIsEmpty1 != queueIsEmpty3 ||
                    queueIsEmpty1 != queueIsEmpty4)
                {
                    std::cout << "testStream() FAILURE" << std::endl;
                    std::cout << "IsEmpty ERROR on instruction file line " << iterator << "!" << std::endl;
                    std::cout << "Terminating program!" << std::endl;
                    exit(0);
                }

                break;
            }
            default:
            {
                //If the line is anything other than D, E, P or A, ignore the line.

                break;
            }
            }
            iterator++;
        }
        myFile.close();
        std::cout << "\ntestStream() SUCCESS" << std::endl;
    }
}

int main() {
    std::cout << "WELCOME TO THE EXTRA-MODULE INDIVIDUAL ASSIGNMENT" << std::endl;
    std::cout << "........now complete with part two functionality!" << std::endl;

    bool programRunning = true;
    int choice;
    string filename;
    int iterations;

    //MAIN MENU
    while (programRunning)
    {
        std::cout << "_________________________________________________";
        std::cout << "\nMENU\n----" << std::endl;
        std::cout << "1) Exit Program!" << std::endl;
        std::cout << "2) Run randomStream   : Produce a file filled with random letters. " << std::endl;
        std::cout << "3) Run testStream     : Read a file to test and compare queues." << std::endl;
        std::cout << "4) Run both functions : First run randomStream, then run testStream with the same file." << std::endl;

        std::cout << "\nPlease enter a number to select an option...";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
        {
            std::cout << "\nEnding program ... Goodbye!" << std::endl;
            programRunning = false;

            break;
        }
        case 2:
        {
            std::cout << "\nUser selected option 2: randomStream!" << std::endl;

            //ask for filename
            std::cout << "\nPlease input a filename. (remember to add an extension, ie '.txt')...";
            std::cin >> filename;

            //ask for iterations
            std::cout << "\nPlease input the iterations...";
            std::cin >> iterations;

            //call method
            randomStream(filename, iterations);

            break;
        }
        case 3:
        {
            std::cout << "\nUser selected option 3: testStream!" << std::endl;

            //ask for filename
            std::cout << "\nPlease input a filename. (remember to add an extension, ie '.txt')...";
            std::cin >> filename;

            //call method
            testStream(filename);

            break;
        }
        case 4:
        {
            std::cout << "\nUser selected option 4: randomStream AND testStream!" << std::endl;
            std::cout << "Starting randomStream..." << std::endl;

            //ask for filename
            std::cout << "\nPlease input a filename. (remember to add an extension, ie '.txt')...";
            std::cin >> filename;

            //ask for iterations
            std::cout << "\nPlease input the iterations...";
            std::cin >> iterations;

            //call randomStream method
            randomStream(filename, iterations);

            //call testStream method
            std::cout << "\nStarting testStream..." << std::endl;
            std::cout << "Using the previous filename: " << filename << std::endl;
            testStream(filename);

            break;
        }
        default:
        {
            std::cout << "\nPlease try again." << std::endl;

            break;
        }
        }
    }
    exit(0);
}