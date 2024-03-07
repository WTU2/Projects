// WILLIAM TU
// W2 Lab - Reading Writing Files
// Goal: Successfully open, read, and write to a file containing integers. Write sum to file.

#include <fstream> // including <fstream> for
// reading and writing files
#include <iostream>
// IO operations
#include <string> // including <string> for
// string operations
#include <vector> // including <vector> for
// array operations

void functionWriteFile(std::vector<int> intText, std::string textFile) 
{
  std::ofstream outFile;
  outFile.open(textFile);

  // ERROR if unable to write in file
  if (!outFile.is_open())
  {
    std::cerr << "Error writing to file. Please try again." << std::endl;
  }

  else
  {
    std::cout << "Writing to file..." << std::endl;
    int sum = 0;

    // adding up integers in text file for the sum
    for (int i = 0; i < intText.size(); i++)
      {
        sum += intText[i];
      }

    // keeping original values from text file
    for (int j = 0; j < intText.size(); j++)
      {
        outFile << intText[j] << std::endl;
      }

    // writing sum to file
    outFile << "Sum: " << sum << std::endl;
    std::cout << "Writing to file succeeded." << std::endl;
    std::cout << "Terminating program...";

    outFile.close();
  }

}

void functionOpenFile(std::string textFile) 
{
  // opening file to be able to read or write to file

  std::ifstream inFile;
  inFile.open(textFile); // opens for reading

  // creating vector to store integers
  std::vector<int> intText;
  int num;

  // ERROR if file is not found or does not exist.
  if (!inFile.is_open())
  {
    std::cerr << "Error opening file. Please try again." << std::endl;
  }

  else 
  {
    // reading each integer in the file and storing them into num
    while (inFile >> num) 
    {
      // storing integers from num into intText vector
      intText.push_back(num);
    }

    // checking if correct file is open
    std::cout << "Are these the correct values? (y/n): " << std::endl;

    for (int i = 0; i < intText.size(); i++) 
    {
      std::cout << intText[i] << " ";
    }
    std::cout << std::endl;

    // allow user input choice
    std::string choice;
    std::cin >> choice;
    if (choice == "y") 
    {
      // if user choice is yes, call functionWriteFile
      functionWriteFile(intText, textFile);
    }

    if (choice == "n") 
    {
      // recursion if user choice is no
      std::cout << "Please enter the correct file name: ";
      std::cin >> textFile;
      functionOpenFile(textFile);
    }

    // close file
    inFile.close();
  }
}

int main() 
{
  // user input text file name
  std::cout << "Enter Text File: ";
  std::string textFile;
  std::cin >> textFile;

  //calling function
  functionOpenFile(textFile);
    
  return 0;
}
