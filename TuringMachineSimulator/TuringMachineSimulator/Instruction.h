#pragma once
#include <string>
class Instruction {
	public:
	Instruction(unsigned long long startState, unsigned long long endState, std::string readChar, std::string writeChar, std::string movement);
	Instruction();
	~Instruction();


	std::string getReadCharacter();
	void setReadCharacter(std::string c);

	std::string getWriteCharacter();
	void setWriteCharacter(std::string c);

	std::string getReadHeadMovement();
	void setReadHeadMovement(std::string m);

	unsigned long long getStartState();
	unsigned long long getEndState();

	bool isNullInstruction();

	private:

	std::string isNull;

	std::string readCharacter;
	
	std::string writeCharacter;

	std::string readHeadMovement;

	unsigned long long sState;

	unsigned long long eState;

};

