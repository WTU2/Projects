//
//	Name:	Tu, William
//	Due:	1 November 2024
//	Course:	cs-1400-05-f24
//
//	Description:
//			This program reads information from a data file containing details regarding elements in the periodic table, and searches for the user's element.
//

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

record Element(int atomicNumber, String symbol, double mass, String name) {}

public class PeriodicTable
{
	public static void main(String[] args) 
	{
		// creating new Element array
		final int MAX_ELEMENTS = 200;
		Element[] periodicTable = new Element[MAX_ELEMENTS];
		int actualSize = readPeriodicTable(periodicTable);
		selectionSort(periodicTable, actualSize);

		// menu for user
		Scanner keyboard = new Scanner(System.in);
		String userInput;
		do
		{
			System.out.println("Periodic Table by W. Tu");
			System.out.println();
			System.out.println("Periodic table loaded with " + actualSize);
			System.out.println();

			System.out.println("N Search  by atomic number");
			System.out.println("S Search by symbol");
			System.out.println("P Print table to a file");
			System.out.println("Q Quit");
			System.out.println();

			System.out.print("Select? ");
			userInput = keyboard.nextLine();

			switch (userInput)
			{
				case "N" ->
				{
					System.out.print("Enter atomic number? ");
					int userAtomicNumber = keyboard.nextInt();
					keyboard.nextLine();

					int index = linearSearch(periodicTable, actualSize, userAtomicNumber);
					if (index != -1)
					{
						Element element = periodicTable[index];
						System.out.printf("%3d %2s    %s   %19.2f %n", element.atomicNumber(), element.symbol(), element.name(), element.mass());
					}
					else
					{
						System.out.println(userAtomicNumber + " not found");
					}
				}

				case "S" ->
				{
					System.out.print("Enter symbol? ");
					String userSymbol = keyboard.nextLine();

					int index = linearSearch(periodicTable, actualSize, userSymbol);
					if (index != -1)
					{
						Element element = periodicTable[index];
						System.out.printf("%3d %2s    %s   %19.2f %n", element.atomicNumber(), element.symbol(), element.name(), element.mass());
					}
					else
					{
						System.out.println(userSymbol + " not found");
					}
				}

				case "P" ->
				{
					System.out.print("Enter file name? ");
					String fileName = keyboard.nextLine();
					String saveDirectory = System.getProperty("user.dir");
					printTable(periodicTable, actualSize, fileName);
					System.out.println("Table saved in " + saveDirectory);
				}
			}
		} while (!"Q".equals(userInput));
	}

    public static int readPeriodicTable(Element[] table) {
		// creating new file object, reading from periodictable.dat
		int index = 0;
		try (Scanner newFile = new Scanner(new File("periodictable.dat")))
		{
			while (newFile.hasNext() && index < table.length)
			{
				int atomicNumber = newFile.nextInt();
				String symbol = newFile.next();
				double atomicMass = newFile.nextDouble();
				String elementName = newFile.next();
				table[index] = new Element(atomicNumber, symbol, atomicMass, elementName);
				index++;
			}
			newFile.close();
		}
		catch (IOException e)
		{
			System.out.println("Error reading from file.");
		}
	return index;
    }

	// search by atomic number
	static int linearSearch(Element[] table, int actualSize, int number)
	{
		for (int i = 0; i < actualSize; i++)
		{
			if (table[i].atomicNumber() == number)
			{
				return i;
			}
		}
		return -1;
	}

	// search by element symbol
	static int linearSearch(Element[] table, int actualSize, String symbol)
	{
		for (int i = 0; i < actualSize; i++)
		{
			String userSymbol = symbol.toUpperCase();
			if (table[i].symbol().toUpperCase().contains(userSymbol))
			{
				return i;
			}
		}
		return -1;
	}
	
	static void printTable(Element[] table, int actualSize, String fileName)
	{
		File newFile = new File(fileName + ".txt");
		try
		{
			if (newFile.createNewFile())
			{
				try
					{
						PrintWriter writer = new PrintWriter(new FileWriter(newFile));
						writer.println("Periodic Table by W. Tu");
						writer.println ();
						writer.println(actualSize + " elements");
						writer.println();

						writer.printf("ANo %4s %5s %25s", "Sym", "Name", "Mass");
						writer.println();
						writer.printf("--- %4s  %5s  %5s", "---", "--------------------", "--------");
						writer.println();

						for (int i = 0; i < actualSize; i++)
						{
							writer.printf("%3d  %-4s %-25s%5.2f%n", table[i].atomicNumber(), table[i].symbol(), table[i].name(), table[i].mass());
						}
						writer.close();
					}catch (IOException e)
					{
						System.out.println("Error writing into file.");
					}
			}
		} catch (IOException e)
		{
			System.out.println("Error occured creating file.");
		}
		

	}

	static void selectionSort(Element[] table, int actualSize)
	{
		int startScan, index, minIndex;
		Element minValue;
		for (startScan = 0; startScan < actualSize - 1; startScan++)
		{
			minIndex = startScan;
			minValue = table[startScan];

			for (index = startScan + 1; index < actualSize; index++)
			{
				if (table[index].atomicNumber() < minValue.atomicNumber())
				{
					minValue = table[index];
					minIndex = index;
				}
			}
			table[minIndex] = table[startScan];
			table[startScan] = minValue;
		}
	}
}