/*
Author:  Eric Milliser
Date written: 03/25/24
Assignment:   Module1 exercise1 part2 
Short Desc:  Prompt a user to input variables for a stero then give a menu of options
			for the user to do within the program such as changing the volume
			power and vand including another attribute of the music playing.
*/




//include statements
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include "headerMethods.h"




int main() //main program
{
	//declaration
	std::string manufacturer, model, serialNum; //input variables for class
	float wattage; //input variables for class
	int numChannels; //input variables for class



	//prompt and enter all the input variables for the class
	std::cout << "Enter the manufacturer: ";
	std::getline(std::cin, manufacturer);
	std::cout << "Enter the model: ";
	std::getline(std::cin, model);
	std::cout << "Enter the serialNum: ";
	std::getline(std::cin, serialNum);
	std::cout << "Enter the wattage (0.1 - 5.0): ";
	std::cin >> wattage;
	wattage = inputValid(wattage, 0.1, 5.0);
	std::cout << "Enter the number of channels (1-100): ";
	std::cin >> numChannels;
	numChannels = inputValid(numChannels, 1.0, 100.0);


	int input = 0; //integer for input choices

	char yesNo = 'n'; //setting a sentinal variable
	std::string inputString; //input string varaiable

	
	do //do while yesNo == 'n"
	{

		//display input details
		std::cout << "Details of the Radio" << std::endl;
		std::cout << "Manufacturer: " << manufacturer << std::endl;
		std::cout << "Model: " << model << std::endl;
		std::cout << "Serial Number: " << serialNum << std::endl;
		std::cout << "Wattage: " << wattage << std::endl;
		std::cout << "Number of Channels: " << numChannels << std::endl;


		//validate input
		std::cout << "Is this information correct? {Y}es or [N]o (make changes): ";
		std::getline(std::cin, inputString);
		yesNo = validYesNo(inputString);

		if (yesNo == 'y') //break if yes
		{
			break;
		}
		else
		{
			//prompt for details to change
			std::cout << "Please choose next the number next to the thing you wish to change. " << std::endl;
			std::cout << "1. Manufacturer" << std::endl;
			std::cout << "2. Model" << std::endl;
			std::cout << "3. Serial Number" << std::endl;
			std::cout << "4. Wattage" << std::endl;
			std::cout << "5. Number of channels" << std::endl;
			std::cin >> input;
			input = inputValid(input, 1, 5);
			switch (input)
			{
			case 1: //change manufacturer
				std::cout << "Enter the manufacturer: ";
				std::cin.ignore(100, '\n');
				std::getline(std::cin, manufacturer);
				break;
			case 2: //change model
				std::cout << "Enter the model: ";
				std::cin.ignore(100, '\n');
				std::getline(std::cin, model);
				break;
			case 3: //change serialNum
				std::cout << "Enter the serialNum: ";
				std::cin.ignore(100, '\n');
				std::getline(std::cin, serialNum);
				break;
			case 4: //change wattage
				std::cout << "Enter the wattage (0.1 - 5.0): ";
				std::cin >> wattage;
				wattage = inputValid(wattage, 0.1, 5.0);
				break;
			case 5: //change channels
				std::cout << "Enter the number of channels (1-100): ";
				std::cin >> numChannels;
				numChannels = inputValid(numChannels, 1.0, 100.0);
				break;

			}
		}


	} while (yesNo == 'n'); //while sentinal is not 'y'


	//constructor and setting everything
	StereoReceiver newStereo = StereoReceiver(manufacturer, model, serialNum, wattage, numChannels);
	newStereo.setFrequencies(); //creating the frequencies by the number of channels
	newStereo.setFrequency(1); //set the frequency to the first value inb the lise


	input = 0; //declare before while loop

	while (input < 6 || input == 9) //while the inputs are not the sentinel control;ers
	{
		//declare variables for what to display
		bool isOn = newStereo.getPower();
		bool alarmSet = newStereo.getAlarm();


		//display information
		std::cout << "Stereo Receiver" << std::endl;
		std::cout << newStereo.getManufacturer() << ": " << newStereo.getModel() << std::endl;
		std::cout << "Serial Number: " << newStereo.getSerialNum() << std::endl;
		std::cout << newStereo.getWattage() << " Watts" << std::endl;
		std::cout << "Number of Channels: " << newStereo.getNumChannels() << std::endl;
		std::cout << "Band: " << newStereo.getBand() << std::endl;
		std::cout << "Frequency: " << newStereo.getfrequency() << std::endl;
		std::cout << "Volume: " << newStereo.getVolume() << std::endl;


		//block to determine to show what displayed
		if (isOn == false)
		{
			//if the reciever is off, don't display the other information
			std::cout << "The reciever is " << newStereo.getPowerString() << std::endl;
		}
		else
		{
			//if the reciever is on, display song and alarm
			newStereo.setSong();

			std::cout << newStereo.getSong() << std::endl;


			if (alarmSet == true)
			{
				std::cout << "Alarm is " << newStereo.getAlarmString() << " and set for " << newStereo.getAlarmTime() << std::endl;
			}
			else
			{
				std::cout << "Alarm is " << newStereo.getAlarmString() << std::endl;
			}
		}


		///prompt choices based on the isOn varriable
		std::cout << "What would you like to do?" << std::endl;
		if (isOn == false)
		{
			std::cout << "1. Power on" << std::endl;
		}
		else if (isOn == true)
		{
			std::cout << "1. Power off" << std::endl;
		}

		std::cout << "2. Change band" << std::endl;
		std::cout << "3. Change Volume" << std::endl;
		std::cout << "4. Change Frequency" << std::endl;
		std::cout << "5. Set Alarm" << std::endl;
		std::cout << "6. Leave" << std::endl;
		if (isOn == true)
		{
			std::cout << "9. Complain about the music" << std::endl;
		}
		std::cin >> input; //input


		if (input == 9 && isOn == true) //validatation of input if it is 9 and it is on
		{
			//This is the lengthy part of the program where it takes a look at the song
			//variables and plays on the fact the songs are all "overplayed" or annoying
			srand(time(0));
			int random = rand() % 11;

			//output
			std::cout << "You call the radio station to complain about the music..." << std::endl;
			std::cout << "Someone picks up.." << std::endl << std::endl;
			std::cout << "\'This is the automated call center for... " << newStereo.getfrequency() << "\"" << std::endl;
			std::cout << "\"We understand you may not like our music... Too bad!\"" << std::endl;
			std::cout << "\"Please wait while we reach out to the host...\"" << std::endl;


			int counter = 0;
			yesNo = 'y';

			//put on hold scenario, and loops while the user waits or until the counter hits 20 and the "phone hangs up"
			while (counter < 20 && yesNo == 'y')
			{
				newStereo.setSong();
				std::cout << "You hear the automated message after a brief hold..." << std::endl;
				std::cout << "\"" << newStereo.getSong() << "\"" << std::endl;
				std::cout << "The song starts to play over the phone." << std::endl;

				std::cout << "Do you wish to wait? [Y]es or [N]o? ";
				std::cin.ignore(100, '\n');
				std::cin >> inputString;
				yesNo = validYesNo(inputString);


				if (counter == 10 && alarmSet == true)
				{
					std::cout << std::endl;
					std::cout << "The radio starts blaring this current song. You check to find the alarm is going off." << std::endl;
					std::cout << "You have been waiting a long time." << std::endl;
					std::cout << std::endl;
				}



				if (counter >= 19)
				{
					newStereo.setComplain();
					newStereo.setSong();
					
					std::cout << std::endl;
					std::cout << "You hear the automated message once more." << std::endl;
					std::cout << newStereo.getSong() << std::endl;

					newStereo.setComplain();

					std::cout << "The phone hangs up." << std::endl << std::endl;
				}

				counter++;

			}


		}

		//any other choice goes here
		if (input != 9 || (input == 9 && isOn == false))
		{
			input = inputValid(input, 1, 6);


			switch (input)
			{
			case 1: //flip power
				newStereo.setPower(); //flips power
				std::cout << std::endl;
				break;
			case 2: //flip band
				std::cout << "You change the band. " << std::endl; //flips band
				newStereo.setBand();
				std::cout << std::endl;
				break;
			case 3: //change volume
				std::cout << "Change the volume dial (Enter a number 0-10) ";
				std::cin >> input;
				input = inputValid(input, 0, 10);
				newStereo.setVolume(input); //changes volume to input
				input = 0;
				std::cout << std::endl;
				break;
			case 4: //display channels
				std::cout << "Here are your aviable channesls" << std::endl;
				newStereo.displayFrequencies();
				std::cout << "Please choose one of these options: ";
				std::cin >> input;
				input = inputValid(input, 1, newStereo.getNumChannels());
				newStereo.setFrequency(input);
				input = 0;
				std::cout << std::endl;
				break;
			case 5: //set alarm
				std::cout << "Set a time for the alarm: ";
				std::cin.ignore(100, '\n');
				std::getline(std::cin, inputString);
				newStereo.setAlarmTime(inputString);
				newStereo.setAlarm();
				std::cout << std::endl;
			default:
				break;
			}



		}

	}
}