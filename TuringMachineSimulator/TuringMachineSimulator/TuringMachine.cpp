#include "TuringMachine.h"



TuringMachine::TuringMachine() {
	transitionTable = std::vector<Instruction>();
	tape = std::vector<std::string>();
	tape.push_back("");

	states = std::vector<unsigned long long>();
	acceptStates = std::vector<unsigned long long>();

	currentState = startState;

}


TuringMachine::~TuringMachine() {
}

Instruction TuringMachine::findInstruction(std::string readChar) {
	//linear search. not pretty, but it works

	for (int i = 0; i < transitionTable.size(); i++) {
		if (currentState == transitionTable[i].getStartState() && readChar == transitionTable[i].getReadCharacter()) {
			return transitionTable[i];
		}
	}
	return Instruction();
}

bool TuringMachine::executeStep() {
	//check to see if there is a halt here
	if (findInstruction(tape[readHeadLocation]).isNullInstruction()) {
		return false;
	}

	Instruction ins = findInstruction(tape[readHeadLocation]);

	//move state
	currentState = ins.getEndState();

	//write down on the tape
	tape[readHeadLocation] = ins.getWriteCharacter();

	//moving logic
	//make room at left
	if (readHeadLocation == 0 && (ins.getReadHeadMovement() == "l" || ins.getReadHeadMovement() == "L")) {
		expandTapeLeft();
		
		//make room at the right
	} else if (readHeadLocation == tape.size() - 1 && (ins.getReadHeadMovement() == "r" || ins.getReadHeadMovement() == "R")) {
		expandTapeRight();
		readHeadLocation++;
		//move head left
	} else if (ins.getReadHeadMovement() == "l" || ins.getReadHeadMovement() == "L") {
		readHeadLocation--;
	} else if (ins.getReadHeadMovement() == "r" || ins.getReadHeadMovement() == "R") {
		//move head right
		readHeadLocation++;
	} else {
		//stay
	}
}

bool TuringMachine::executeMachine(std::string input) {
	//make sure tape is clear from previous runs of the machine
	tape.clear();
	readHeadLocation = 0;
	currentState = startState;
	//place the string on the tape

	if (input.size() == 0) {
		tape.push_back("");
	}

	for (int i = 0; i < input.length(); i++) {
		tape.push_back(input.substr(i, 1));
	}

	int numberOfSteps = 0;
	std::cout << "Input: " << input << std::endl;
	printOutActiveTape();
	while (executeStep()) {
		numberOfSteps++;
		printOutActiveTape();
	}

	return isInAcceptState();
}

bool TuringMachine::testString(std::string input, std::string expectedOutput) {
	return false;
}

void TuringMachine::expandTapeLeft() {
	std::vector<std::string> nTape = std::vector<std::string>();

	nTape.push_back("");

	for (unsigned long long i = 0; i < tape.size(); i++) {
		nTape.push_back(tape[i]);
	}

	tape = nTape;
}

void TuringMachine::expandTapeRight() {
	tape.push_back("");
}

bool TuringMachine::isInAcceptState() {
	

	for (unsigned long long i = 0; i < acceptStates.size(); i++) {
		if (acceptStates[i] == currentState) {
			return true;
		}
	}

	return false;
}

void TuringMachine::addInstruction(Instruction in) {
	transitionTable.push_back(in);

}

void TuringMachine::setStates(std::vector<unsigned long long> s) {

	states = s;
}

std::vector<unsigned long long> TuringMachine::getStates() {
	return states;
}

void TuringMachine::setAcceptStates(std::vector<unsigned long long> s) {
	acceptStates = s;
}

std::vector<unsigned long long> TuringMachine::getAcceptStates() {
	return acceptStates;
}

void TuringMachine::setStartStates(unsigned long long s) {
	startState = s;
}

unsigned long long TuringMachine::getStartState() {
	return startState;
}

void TuringMachine::performTestCases(std::vector<std::string> input, std::vector<bool> expectedResult) {
	int failures = 0;

	for (int i = 0; i < input.size(); i++) {
		if (expectedResult[i] != executeMachine(input[i])) {
			std::cout << "Failure on string: " << input[i] << ", expected return: " << expectedResult[i] << std::endl;
			failures++;
		}
	}

	std::cout << "Test cases complete: " << failures << " failures" << std::endl;
}

void TuringMachine::printOutActiveTape() {

	std::cout << "Tape Reads: " << std::endl;

	for (int i = 0; i < tape.size(); i++) {
		if (tape[i] == "") {
			std::cout << " (BLANK), ";
		} else {
			std::cout << " (" << tape[i] << "), ";
		}
	}

	std::cout << std::endl;
}


int main() {

	TuringMachine ep = TuringMachine();
						//start, end, read, write, movement
	ep.addInstruction(Instruction(0, 1,"a","X","r"));
	ep.addInstruction(Instruction(1, 1, "a", "a", "r"));
	ep.addInstruction(Instruction(1, 1, "b", "b", "r"));
	ep.addInstruction(Instruction(1, 3, "", "", "l"));
	ep.addInstruction(Instruction(1, 3, "X", "X", "l"));
	ep.addInstruction(Instruction(3, 5, "a", "X", "l"));
	ep.addInstruction(Instruction(5, 5, "a", "a", "l"));

	//bottom half

	ep.addInstruction(Instruction(0, 2, "b", "X", "r"));
	ep.addInstruction(Instruction(2, 2, "a", "a", "r"));
	ep.addInstruction(Instruction(2, 2, "b", "b", "r"));
	ep.addInstruction(Instruction(2, 4, "", "", "l"));
	ep.addInstruction(Instruction(2, 4, "X", "X", "l"));
	ep.addInstruction(Instruction(4, 5, "b", "X", "l"));
	ep.addInstruction(Instruction(5, 5, "b", "b", "l"));

	ep.addInstruction(Instruction(5, 0, "X", "X", "r"));

	ep.addInstruction(Instruction(0, 6, "X", "X", "s"));

	std::vector<unsigned long long> aStates = std::vector<unsigned long long>();

	ep.setStartStates(0);
	aStates.push_back(6);

	std::vector<std::string> testStrings = std::vector<std::string>();
	std::vector<bool> testResults = std::vector<bool>();

	testStrings.push_back("");
	testResults.push_back(false);

	testStrings.push_back("ab");
	testResults.push_back(false);

	testStrings.push_back("ba");
	testResults.push_back(false);

	testStrings.push_back("aba");
	testResults.push_back(false);

	testStrings.push_back("aabb");
	testResults.push_back(false);

	testStrings.push_back("aaabbb");
	testResults.push_back(false);

	testStrings.push_back("aabbaa");
	testResults.push_back(true);

	testStrings.push_back("abba");
	testResults.push_back(true);


	ep.setAcceptStates(aStates);

	ep.performTestCases(testStrings, testResults);
	
	return 0;
}