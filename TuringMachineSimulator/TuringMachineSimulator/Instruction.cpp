#include "Instruction.h"



Instruction::Instruction(unsigned long long startState, unsigned long long endState, std::string readChar, std::string writeChar, std::string movement) {
	setReadCharacter(readChar);
	setWriteCharacter(writeChar);
	setReadHeadMovement(movement);

	sState = startState;
	eState = endState;
}

Instruction::Instruction() {
	isNull = "NULL";
}


Instruction::~Instruction() {

}

std::string Instruction::getReadCharacter() {
	return readCharacter;
}

void Instruction::setReadCharacter(std::string c) {
	readCharacter = c;
}

std::string Instruction::getWriteCharacter() {
	return writeCharacter;
}

void Instruction::setWriteCharacter(std::string c) {
	writeCharacter = c;
}

std::string Instruction::getReadHeadMovement() {
	return readHeadMovement;
}

void Instruction::setReadHeadMovement(std::string m) {
	if (m != "s" || m != "l" || m != "r" || m != "S" || m != "L" || m != "R") {
		//ERROR HERE
	}

	readHeadMovement = m;
}

unsigned long long Instruction::getStartState() {
	return sState;
}

unsigned long long Instruction::getEndState() {
	return eState;
}

bool Instruction::isNullInstruction() {
	
	return !isNull.empty();
}
