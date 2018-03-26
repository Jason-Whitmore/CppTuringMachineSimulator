#pragma once
#include <vector>
#include "Instruction.h"
#include <iostream>
class TuringMachine {
	public:
	TuringMachine();
	~TuringMachine();
	

	Instruction findInstruction(std::string readChar);


	bool executeStep();


	//main methods for testing the string.
	bool executeMachine(std::string input);

	bool testString(std::string input, std::string expectedOutput);

	

	void expandTapeLeft();
	void expandTapeRight();

	bool isInAcceptState();

	void addInstruction(Instruction in);


	void setStates(std::vector<unsigned long long> s);
	std::vector<unsigned long long> getStates();

	void setAcceptStates(std::vector<unsigned long long> s);
	std::vector<unsigned long long> getAcceptStates();

	void setStartStates(unsigned long long s);
	unsigned long long getStartState();

	void performTestCases(std::vector<std::string> input, std::vector<bool> expectedResult);

	void printOutActiveTape();

	private:

	std::vector<Instruction> transitionTable;
	std::vector<std::string> tape;
	
	std::vector<unsigned long long> states;
	std::vector<unsigned long long> acceptStates;
	unsigned long long currentState;

	unsigned long long startState;

	unsigned long long readHeadLocation;
	unsigned long long lengthOfActiveTape;

	
};

