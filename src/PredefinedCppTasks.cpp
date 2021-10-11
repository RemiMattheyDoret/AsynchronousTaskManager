#include "PredefinedCppTasks.h"
#include <iostream>
#include <fstream>
#include <sstream>


unsigned long long PredefinedCppTasks::factorial(int n)
{
	unsigned long long fact = 1;
	for (int i=1 ; i <= n ; i++ )
		fact = fact * i;
	return fact;
}

void PredefinedCppTasks::doThis(CppProcessController&& controller)
{
	/*
		Not a very interesting function. It is just an example of a process
	*/

	std::ofstream myfile;
	myfile.open ("/Users/remi/test/doThis.txt");
	myfile << "Starting\n";
	

	for ( int n=0 ; n <= 20 ; ++n )
	{
		for ( int i = 0 ; i < 100; ++i)
		{
			//while (controller.shouldPause()) std::this_thread::sleep_for(std::chrono::seconds(1));
			if (controller.pause_and_shouldStop())
			{
				myfile.close();
				return;
			}

			(void) factorial(i);
		}
	}

	myfile << "Finishing\n";

	myfile.close();
}

void PredefinedCppTasks::doThat(CppProcessController&& controller)
{
	/*
		Not a very interesting function. It is just an example of a process
	*/

	std::ofstream myfile;
	myfile.open ("/Users/remi/test/doThat.txt");
	myfile << "Starting\n";

	for (int i = 0 ; i < 1000 ; ++i)
	{
		//while (controller.shouldPause()) std::this_thread::sleep_for(std::chrono::seconds(1));
		if (controller.pause_and_shouldStop())
		{
			myfile.close();
			return;
		}
		std::this_thread::sleep_for (std::chrono::seconds(1));
		myfile << i << std::endl;
	}

	myfile << "Finishing\n";
	myfile.close();
}


void PredefinedCppTasks::i_am_a_ghost(CppProcessController&& controller)
{
	std::ofstream myfile;
	myfile.open ("/Users/remi/test/i_am_a_ghost.txt");

	int i,j; 
	for(j=26;j>=-52;j--){ 
		for(i=-39;i<=39;i++){
			if (controller.pause_and_shouldStop())
			{
				myfile.close();
				return;
			} 
			if ((((abs(i)<22)&&(abs(j-4)<2||abs(j+2)<2||abs(j+8)<2))||(abs(i)==22&&(j==4||j==-2||j==-8)))||(!((676*i*i+1521*j*j<=822557)||(abs(i)<35&&j<0)))) 
				myfile<<" "; 
			else 
				myfile<<"*";
		} 
		std::cout<<std::endl;
	}

	myfile.close();
}


void PredefinedCppTasks::isSoftwareDeveloperAGoodJob(CppProcessController&& controller)
{
	std::ofstream myfile;
	myfile.open ("/Users/remi/test/Otis.txt");


	std::string s = "Vous savez, moi je ne crois pas qu’il y ait de bonne ou de mauvaise situation. Moi, si je devais résumer ma vie aujourd’hui avec vous, je dirais que c’est d’abord des rencontres. Des gens qui m’ont tendu la main, peut-être à un moment où je ne pouvais pas, où j’étais seul chez moi. Et c’est assez curieux de se dire que les hasards, les rencontres forgent une destinée... Parce que quand on a le goût de la chose, quand on a le goût de la chose bien faite, le beau geste, parfois on ne trouve pas l’interlocuteur en face je dirais, le miroir qui vous aide à avancer. Alors ça n’est pas mon cas, comme je disais là, puisque moi au contraire, j’ai pu : et je dis merci à la vie, je lui dis merci, je chante la vie, je danse la vie... je ne suis qu’amour ! Et finalement, quand beaucoup de gens aujourd’hui me disent « Mais comment fais-tu pour avoir cette humanité ? », et bien je leur réponds très simplement, je leur dis que c’est ce goût de l’amour ce goût donc qui m’a poussé aujourd’hui à entreprendre une construction mécanique, mais demain qui sait ? Peut-être simplement à me mettre au service de la communauté, à faire le don, le don de soi...";
	std::istringstream Otis(s);
	
	std::string word;
	while (Otis >> word)
	{
		myfile << word;
		if (controller.pause_and_shouldStop())
		{
			myfile.close();
			return;
		} 
		std::this_thread::sleep_for (std::chrono::seconds(1));
	}

	myfile.close();
}


void PredefinedCppTasks::duration_xs(CppProcessController&& controller, unsigned x)
{
	std::ofstream myfile;
	myfile.open(std::string("/Users/remi/test/duration_") + std::to_string(x) + std::string("s.txt"), std::ofstream::out | std::ofstream::trunc);
	for (unsigned i = 0 ; i < x ; ++i)
	{
		if (controller.pause_and_shouldStop())
		{
			myfile.close();
			return;
		} 
		std::this_thread::sleep_for(std::chrono::seconds(1));
		myfile << i << "s" << std::endl;
	}
	myfile.close();
}

void PredefinedCppTasks::duration_5s(CppProcessController&& controller)
{
	duration_xs(std::move(controller), 5);
}

void PredefinedCppTasks::duration_50s(CppProcessController&& controller)
{
	duration_xs(std::move(controller), 50);
}

void PredefinedCppTasks::duration_500s(CppProcessController&& controller)
{
	duration_xs(std::move(controller), 500);
}




const function_t PredefinedCppTasks::get_fct_from_fctName(const std::string& functionName)
{
	if (functionName == "doThis")
	{
		return PredefinedCppTasks::doThis;
	} else if (functionName == "doThat")
	{
		return PredefinedCppTasks::doThat;
	} else if (functionName == "duration_5s")
	{
		return PredefinedCppTasks::duration_5s;
	} else if (functionName == "duration_50s")
	{
		return PredefinedCppTasks::duration_50s;
	} else if (functionName == "duration_500s")
	{
		return PredefinedCppTasks::duration_500s;
	} else if (functionName == "i_am_a_ghost")
	{
		return PredefinedCppTasks::i_am_a_ghost;
	} else
	{
		throw std::string("Unknown CPP function name ") + functionName + std::string("\n");
	}
}
