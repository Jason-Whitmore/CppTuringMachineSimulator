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

	for (unsigned long long i = 0; i < transitionTable.size(); i++) {
		if (currentState == transitionTable[i].getStartState() && readChar == transitionTable[i].getReadCharacter()) {
			return transitionTable[i];
		}
	}

	Instruction();
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
	} else if ((ins.getReadHeadMovement() == "l" || ins.getReadHeadMovement() == "L")) {
		readHeadLocation--;
	} else if (ins.getReadHeadMovement() == "r" || ins.getReadHeadMovement() == "R") {
		//move head right
		readHeadLocation++;
	} else {
		//stay
	}


}

bool TuringMachine::executeMachine(std::string input) {


	//place the string on the tape
	for (int i = 0; i < input.length(); i++) {
		tape.push_back(input.substr(i, 1));
	}

	while (executeStep()) {

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


int main() {

	TuringMachine bb = TuringMachine();

	bb.addInstruction(Instruction(0, 1,"","1","r"));
	bb.addInstruction(Instruction(0, 1, "1", "1", "l"));
	bb.addInstruction(Instruction(1, 0, "", "1", "l"));
	bb.addInstruction(Instruction(1, 2, "1", "1", "l"));


	std::vector<unsigned long long> states = std::vector<unsigned long long>();
	std::vector<unsigned long long> aStates = std::vector<unsigned long long>();

	states.push_back(0);
	states.push_back(1);
	states.push_back(2);
	
	aStates.push_back(2);

	bb.setStates(states);
	bb.setAcceptStates(aStates);

	bb.executeMachine("");
	
return 0;
}