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

void PredefinedCppTasks::factorials(CppProcessController&& controller, const std::string& filePath)
{
	/*
		Not a very interesting function. It is just an example of a process
	*/

	std::ofstream outFile;
	outFile.open (filePath);
	outFile << "Factorials:\n";
	

	for ( int n=0 ; n <= 20 ; ++n )
	{
		for ( int i = 0 ; i < 100; ++i)
		{
			//while (controller.shouldPause()) std::this_thread::sleep_for(std::chrono::seconds(1));
			if (controller.pause_and_shouldStop())
			{
				outFile.close();
				return;
			}

			outFile << i << ": " << factorial(i) << std::endl;
		}
	}

	outFile.close();
}

void PredefinedCppTasks::doThat(CppProcessController&& controller, const std::string& filePath)
{
	/*
		Not a very interesting function. It is just an example of a process
	*/

	std::ofstream outFile;
	outFile.open (filePath);
	outFile << "Starting doing 'that'...";

	for (int i = 0 ; i < 1000 ; ++i)
	{
		//while (controller.shouldPause()) std::this_thread::sleep_for(std::chrono::seconds(1));
		if (controller.pause_and_shouldStop())
		{
			outFile.close();
			return;
		}
		std::this_thread::sleep_for (std::chrono::seconds(1));
		outFile << i << std::endl;
	}

	outFile << "... 'that' is done. Thank you!\n";
	outFile.close();
}

/*
void PredefinedCppTasks::i_am_a_ghost(CppProcessController&& controller, const std::string& filePath)
{
	std::ofstream outFile;
	outFile.open (filePath);

	int i,j; 
	for(j=26;j>=-52;j--){ 
		for(i=-39;i<=39;i++){
			if (controller.pause_and_shouldStop())
			{
				outFile.close();
				return;
			} 
			if ((((abs(i)<22)&&(abs(j-4)<2||abs(j+2)<2||abs(j+8)<2))||(abs(i)==22&&(j==4||j==-2||j==-8)))||(!((676*i*i+1521*j*j<=822557)||(abs(i)<35&&j<0)))) 
				outFile<<" "; 
			else 
				outFile<<"*";
		} 
		std::cout<<std::endl;
	}

	outFile.close();
}
*/


void PredefinedCppTasks::isSoftwareDeveloperAGoodJob(CppProcessController&& controller, const std::string& filePath)
{
	std::ofstream outFile;
	outFile.open (filePath);


	std::string s = "Vous savez, moi je ne crois pas qu’il y ait de bonne ou de mauvaise situation. Moi, si je devais résumer ma vie aujourd’hui avec vous, je dirais que c’est d’abord des rencontres. Des gens qui m’ont tendu la main, peut-être à un moment où je ne pouvais pas, où j’étais seul chez moi. Et c’est assez curieux de se dire que les hasards, les rencontres forgent une destinée... Parce que quand on a le goût de la chose, quand on a le goût de la chose bien faite, le beau geste, parfois on ne trouve pas l’interlocuteur en face je dirais, le miroir qui vous aide à avancer. Alors ça n’est pas mon cas, comme je disais là, puisque moi au contraire, j’ai pu : et je dis merci à la vie, je lui dis merci, je chante la vie, je danse la vie... je ne suis qu’amour ! Et finalement, quand beaucoup de gens aujourd’hui me disent « Mais comment fais-tu pour avoir cette humanité ? », et bien je leur réponds très simplement, je leur dis que c’est ce goût de l’amour ce goût donc qui m’a poussé aujourd’hui à entreprendre une construction mécanique, mais demain qui sait ? Peut-être simplement à me mettre au service de la communauté, à faire le don, le don de soi...";
	std::istringstream Otis(s);
	
	std::string word;
	while (Otis >> word)
	{
		outFile << word << " " << std::flush;
		if (controller.pause_and_shouldStop())
		{
			outFile.close();
			return;
		} 
		std::this_thread::sleep_for (std::chrono::milliseconds(100));
	}

	outFile.close();
}


void PredefinedCppTasks::duration_xs(CppProcessController&& controller, unsigned x, const std::string& filePath)
{
	std::ofstream outFile;
	outFile.open(filePath, std::ofstream::out | std::ofstream::trunc);
	for (unsigned i = 0 ; i < x ; ++i)
	{
		if (controller.pause_and_shouldStop())
		{
			outFile.close();
			return;
		} 
		std::this_thread::sleep_for(std::chrono::seconds(1));
		outFile << i << "s" << std::endl;
	}
	outFile.close();
}

void PredefinedCppTasks::duration_5s(CppProcessController&& controller, const std::string& filePath)
{
	duration_xs(std::move(controller), 5, filePath);
}

void PredefinedCppTasks::duration_50s(CppProcessController&& controller, const std::string& filePath)
{
	duration_xs(std::move(controller), 50, filePath);
}

void PredefinedCppTasks::duration_500s(CppProcessController&& controller, const std::string& filePath)
{
	duration_xs(std::move(controller), 500, filePath);
}





void PredefinedCppTasks::pikachu(CppProcessController&& controller, const std::string& filePath)
{
	std::ofstream outFile;
	outFile.open(filePath, std::ofstream::out | std::ofstream::trunc);

/*
	std::cout << "\n";
	std::cout << "	       \\:.             .:/" << std::endl;
	std::cout << "        \\``._________.''/ " << std::endl;
	std::cout << "         \\             / " << std::endl;
	std::cout << " .--.--, / .':.   .':. \\" << std::endl;
	std::cout << "/__:  /  | '::' . '::' |" << std::endl;
	std::cout << "   / /   |`.   ._.   .'|" << std::endl;
	std::cout << "  / /    |.'         '.|" << std::endl;
	std::cout << " /___-_-,|.\\  \\   /  /.|" << std::endl;
	std::cout << "      // |''\\.;   ;,/ '|" << std::endl;
	std::cout << "      `==|:=         =:|" << std::endl;
	std::cout << "         `.          .'" << std::endl;
	std::cout << "           :-._____.-:" << std::endl;
	std::cout << "          `''       `''" << std::endl;
*/

	outFile << "       \\:.             .:/" << std::endl;
	outFile << "        \\``._________.''/ " << std::endl;
	outFile << "         \\             / " << std::endl;
	outFile << " .--.--, / .':.   .':. \\" << std::endl;
	outFile << "/__:  /  | '::' . '::' |" << std::endl;
	outFile << "   / /   |`.   ._.   .'|" << std::endl;
	outFile << "  / /    |.'         '.|" << std::endl;
	outFile << " /___-_-,|.\\  \\   /  /.|" << std::endl;
	outFile << "      // |''\\.;   ;,/ '|" << std::endl;
	outFile << "      `==|:=         =:|" << std::endl;
	outFile << "         `.          .'" << std::endl;
	outFile << "           :-._____.-:" << std::endl;
	outFile << "          `''       `''" << std::endl;

	outFile.close();
}

const function_t PredefinedCppTasks::get_fct_from_fctName(const std::string& functionName)
{
	if (functionName == "factorials")
	{
		return PredefinedCppTasks::factorials;
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
	}  else if (functionName == "isSoftwareDeveloperAGoodJob")
	{
		return PredefinedCppTasks::isSoftwareDeveloperAGoodJob;
	} else if (functionName == "pikachu")
	{
		return PredefinedCppTasks::pikachu;
	} else
	{
		throw std::string("Unknown CPP function name ") + functionName + std::string("\n");
	}
}
