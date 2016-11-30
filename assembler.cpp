#include "assembler.h"

bool Assembler::checkRd(int val, bool err){
	if(val < 0 || val > 3){
		cout << "ERROR: destination register is not valid" << endl;
		err = true;
		return err;
	}
	else{
		error = false;
		return err;
	}
}
bool Assembler::checkConst(int val, bool err){

	constant = constant & 255;

	if(val < -64 || val > 63){
		cout << "ERROR: const is not valid" << endl;
		err = true;
		return err;
	}
	else{
		err = false;
		return err;
	}
}
void Assembler::load(istringstream& s){
	s >> rd >> constant;
	if(checkRd(rd , error) || checkConst(constant, error)){
		return;
	}
	outNum = 0;
	outNum += (rd << 9);
	outNum += constant;
	outFile << outNum << "\n";
}
void Assembler::loadi(istringstream& s){
	s >> rd >> constant;
	i = 1;
	if (checkRd(rd, error) || checkConst(constant, error)){ return; }
	outNum = 0;
	outNum += (rd << 9);
	outNum += constant;
	outNum += (i << 8);
	outFile << outNum << "\n";
}
void Assembler::store(istringstream& s){
	s >> rd >> constant;
	if (checkRd(rd, error) || checkConst(constant, error)){ return; }
	i = 1;
	outNum = 0;
	outNum = 1;
	outNum <<= 11;
	outNum += (i << 8);
	outNum += (rd << 9);
	outNum += constant;
	outFile << outNum << "\n";
}
void Assembler::add(istringstream& s){
	s >> rd >> rs;
	if (checkRd(rd, error) || checkRd(rs, error)){ return; }
	outNum = 0;
	outNum = 2;
	outNum <<= 11;
	outNum += (rd << 9);
	outNum += (rs << 6);
	outFile << outNum << "\n";
}
void Assembler::addi(istringstream& s){
	s >> rd >> constant;
	if(checkRd(rd, error) || checkConst(constant, error))
	{
		return;
	}

	i = 1;
	outNum = 0;
	outNum = 2;
	outNum <<= 11;
	outNum += (rd << 9);
	outNum += constant;
	outNum += (i<<8);
	outFile << outNum << "\n";
}
void Assembler::addc(istringstream& s){
	s >> rd >> rs;
	if (checkRd(rd, error) || checkRd(rs, error)){ return; }
	outNum = 0;
	outNum = 3;
	outNum <<= 11;
	outNum += (rd << 9);
	outNum += (rs << 6);
	outFile << outNum << "\n";
}
void Assembler::addci(istringstream& s){
	s >> rd >> constant;
	if (checkRd(rd, error) || checkConst(constant, error)){ return; }
	i = 1;
	outNum = 0;
	outNum = 3;
	outNum <<= 11;
	outNum += (rd << 9);
	outNum += (i << 8);
	outNum += constant;
	outFile << outNum << "\n";
}
void Assembler::sub(istringstream& s){
	s >> rd >> rs;
	if (checkRd(rd, error) || checkRd(rs, error)){ return; }
	outNum = 0;
	outNum = 4;
	outNum <<= 11;
	outNum += (rd << 9);
	outNum += (rs << 6);
	outFile << outNum << "\n";
}
void Assembler::subi(istringstream& s){
	s >> rd >> constant;
	if (checkRd(rd, error) || checkConst(constant, error)){ return; }
	i = 1;
	outNum = 0;
	outNum = 4;
	outNum <<= 11;
	outNum += (rd << 9);
	outNum += (i << 8);
	outNum += constant;
	outFile << outNum << "\n";
}
void Assembler::subc(istringstream& s){
	s >> rd >> rs;
	if (checkRd(rd, error) || checkRd(rs, error)){ return; }
	outNum = 0;
	outNum = 5;
	outNum <<= 11;
	outNum += (rd << 9);
	outNum += (rs << 6);
	outFile << outNum << "\n";
}
void Assembler::subci(istringstream& s){
	s >> rd >> constant;
	if (checkRd(rd, error) || checkConst(constant, error)){ return; }
	i = 1;
	outNum = 0;
	outNum = 5;
	outNum <<= 11;
	outNum += (rd << 9);
	outNum += (i << 8);
	outNum += constant;
	outFile << outNum << "\n";
}
void Assembler::and1(istringstream& s){
	s >> rd >> rs;
	if (checkRd(rd, error) || checkRd(rs, error)){ return; }
	outNum = 0;
	outNum = 6;
	outNum <<= 11;
	outNum += (rd << 9);
	outNum += (rs << 6);
	outFile << outNum << "\n";
}
void Assembler::andi(istringstream& s){
	s >> rd >> constant;
	if (checkRd(rd, error) || checkConst(constant, error)){ return; }
	i = 1;
	outNum = 0;
	outNum = 6;
	outNum <<= 11;
	outNum += (rd << 9);
	outNum += (i << 8);
	outNum += constant;
	outFile << outNum << "\n";
}
void Assembler::xor1(istringstream& s){
	s >> rd >> rs;
	if (checkRd(rd, error) || checkRd(rs, error)){ return; }
	outNum = 0;
	outNum = 7;
	outNum <<= 11;
	outNum += (rd << 9);
	outNum += (rs << 6);
	outFile << outNum << "\n";
}
void Assembler::xori(istringstream& s){
	s >> rd >> constant;
	if (checkRd(rd, error) || checkConst(constant, error)){ return; }
	i = 1;
	outNum = 0;
	outNum = 7;
	outNum <<= 11;
	outNum += (rd << 9);
	outNum += (i << 8);
	outNum += constant;
	outFile << outNum << "\n";
}
void Assembler::compl1(istringstream& s){
	s >> rd;
	if (checkRd(rd, error)){ return; }
	outNum = 0;
	outNum = 8;
	outNum <<= 11;
	outNum += (rd << 9);
	outFile << outNum << "\n";
}
void Assembler::shl(istringstream& s){
	s >> rd;
	if (checkRd(rd, error)){ return; }
	outNum = 0;
	outNum = 9;
	outNum <<= 11;
	outNum += (rd << 9);
	outFile << outNum << "\n";
}
void Assembler::shla(istringstream& s){
	s >> rd;
	if (checkRd(rd, error)){ return; }
	outNum = 0;
	outNum = 10;
	outNum <<= 11;
	outNum += (rd << 9);
	outFile << outNum << "\n";
}
void Assembler::shr(istringstream& s){
	s >> rd;
	if (checkRd(rd, error)){ return; }
	outNum = 0;
	outNum = 11;
	outNum <<= 11;
	outNum += (rd << 9);
	outFile << outNum << "\n";
}
void Assembler::shra(istringstream& s){
	s >> rd;
	if (checkRd(rd, error)){ return; }
	outNum = 0;
	outNum = 12;
	outNum <<= 11;
	outNum += (rd << 9);
	outFile << outNum << "\n";
}
void Assembler::compr(istringstream& s){
	s >> rd >> rs;
	if (checkRd(rd, error) || checkRd(rs, error)){ return; }
	outNum = 0;
	outNum = 13;
	outNum <<= 11;
	outNum += (rd << 9);
	outNum += (rs << 6);
	outFile << outNum << "\n";
}
void Assembler::compri(istringstream& s){
	s >> rd >> constant;
	if (checkRd(rd, error) || checkConst(constant, error)){ return; }
	i = 1;
	outNum = 0;
	outNum = 13;
	outNum <<= 11;
	outNum += (rd << 9);
	outNum += (i << 8);
	outNum += constant;
	outFile << outNum << "\n";
}
void Assembler::getstat(istringstream& s){
	if (checkRd(rd, error)){ return; }
	s >> rd;
	outNum = 0;
	outNum = 14;
	outNum <<= 11;
	outNum += (rd << 9);
	outFile << outNum << "\n";
}
void Assembler::putstat(istringstream& s){
	s >> rd;
	if (checkRd(rd, error)){ return; }
	outNum = 0;
	outNum = 15;
	outNum <<= 11;
	outNum += (rd << 9);
	outFile << outNum << "\n";
}
void Assembler::jump(istringstream& s){
	s >> constant;
	if (checkConst(constant, error)){ return; }
	i = 1;
	outNum = 0;
	outNum = 16;
	outNum <<= 11;
	outNum += (i << 8);
	outNum += constant;
	outFile << outNum << "\n";
}
void Assembler::jumpl(istringstream& s){
	s >> constant;
	if (checkConst(constant, error)){ return; }
	i = 1;
	outNum = 0;
	outNum = 17;
	outNum <<= 11;
	outNum += (i << 8);
	outNum += constant;
	outFile << outNum << "\n";
}
void Assembler::jumpe(istringstream& s){
	s >> constant;
	if (checkConst(constant, error)){ return; }
	i = 1;
	outNum = 0;
	outNum = 18;
	outNum <<= 11;
	outNum += (i << 8);
	outNum += constant;
	outFile << outNum << "\n";
}
void Assembler::jumpg(istringstream& s){
	s >> constant;
	if (checkConst(constant, error)){ return; }
	i = 1;
	outNum = 0;
	outNum = 19;
	outNum <<= 11;
	outNum += (i << 8);
	outNum += constant;
	outFile << outNum << "\n";
}
void Assembler::call(istringstream& s){
	s >> constant;
	if (checkConst(constant, error)){ return; }
	i = 1;
	outNum = 0;
	outNum = 20;
	outNum <<= 11;
	outNum += (i << 8);
	outNum += (rd << 9);
	outNum += constant;
	outFile << outNum << "\n";
}
void Assembler::ret(istringstream& s){
	outNum = 0;
	outNum = 21;
	outNum <<= 11;
	outFile << outNum << "\n";
}
void Assembler::read(istringstream& s){
	s >> rd;
	if (checkRd(rd, error)){ return; }
	outNum = 0;
	outNum = 22;
	outNum <<= 11;
	outNum += (rd << 9);
	outFile << outNum << "\n";
}
void Assembler::write(istringstream& s){
	s >> rd;
	if (checkRd(rd, error)){ return; }
	outNum = 0;
	outNum = 23;
	outNum <<= 11;
	outNum += (rd << 9);
	outFile << outNum << "\n";
}
void Assembler::halt(istringstream& s){
	outNum = 0;
	outNum = 24;
	outNum <<= 11;
	outFile << outNum << "\n";
}
void Assembler::noop(istringstream& s){
	outNum = 0;
	outNum = 25;
	outNum <<= 11;
	outFile << outNum << "\n";
}


Assembler::Assembler()
{
	instr["load"] = &Assembler::load;
	instr["loadi"] = &Assembler::loadi;
	instr["store"] = &Assembler::store;
	instr["add"] = &Assembler::add;
	instr["addi"] = &Assembler::addi;
	instr["addc"] = &Assembler::addc;
	instr["addci"] = &Assembler::addci;
	instr["sub"] = &Assembler::sub;
	instr["subi"] = &Assembler::subi;
	instr["subci"] = &Assembler::subci;
	instr["and"] = &Assembler::and1;
	instr["andi"] = &Assembler::andi;
	instr["xor"] = &Assembler::xor1;
	instr["xori"] = &Assembler::xori;
	instr["compl"] = &Assembler::compl1;
	instr["shl"] = &Assembler::shl;
	instr["shla"] = &Assembler::shla;
	instr["shr"] = &Assembler::shr;
	instr["shra"] = &Assembler::shra;
	instr["compr"] = &Assembler::compr;
	instr["compri"] = &Assembler::compri;
	instr["getstat"] = &Assembler::getstat;
	instr["putstat"] = &Assembler::putstat;
	instr["jump"] = &Assembler::jump;
	instr["jumpl"] = &Assembler::jumpl;
	instr["jumpe"] = &Assembler::jumpe;
	instr["jumpg"] = &Assembler::jumpg;
	instr["call"] = &Assembler::call;
	instr["return"] = &Assembler::ret;
	instr["read"] = &Assembler::read;
	instr["write"] = &Assembler::write;
	instr["halt"] = &Assembler::halt;
	instr["noop"] = &Assembler::noop;
}

int Assembler::assemble()
{
	assemblyProg.open("prog.s", ios::in);
	outFile.open("prog.o", ios::out);

	if (!assemblyProg.is_open()) {
		cout << "prog.s failed to open.\n";
		return 1;
	}

	getline(assemblyProg, line);
	while (!assemblyProg.eof()) {
		rd = -1; rs = -1; constant = -129; error = false; 

		istringstream str(line.c_str());
		str >> opcode;

		getline(assemblyProg, line);
		(this->*instr[opcode])(str);
	}
}

