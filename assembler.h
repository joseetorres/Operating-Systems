#include <iostream>
#include <string>
#include <map>
#include <fstream>  
#include <sstream> 

using namespace std;

class Assembler {

	typedef void (Assembler::*FP)(istringstream&);
	fstream assemblyProg;
	fstream outFile;
	string line, opcode;
	bool error;
	int rd, rs, carry, constant, outNum , i;
	map<string, FP> instr;

	void checkRd(int val);
	void checkConst(int val);
	void load(istringstream& s);
	void loadi(istringstream& s);
	void store(istringstream& s);
	void add(istringstream& s);
	void addi(istringstream& s);
	void addc(istringstream& s);
	void addci(istringstream& s);
	void sub(istringstream& s);
	void subi(istringstream& s);
	void subc(istringstream& s);
	void subci(istringstream& s);
	void and1(istringstream& s);
	void andi(istringstream& s);
	void xor1(istringstream& s);
	void xori(istringstream& s);
	void compl1(istringstream& s);
	void shl(istringstream& s);
	void shla(istringstream& s);
	void shr(istringstream& s);
	void shra(istringstream& s);
	void compr(istringstream& s);
	void compri(istringstream& s);
	void getstat(istringstream& s);
	void putstat(istringstream& s);
	void jump(istringstream& s);
	void jumpl(istringstream& s);
	void jumpe(istringstream& s);
	void jumpg(istringstream& s);
	void call(istringstream& s);
	void ret(istringstream& s);
	void read(istringstream& s);
	void write(istringstream& s);
	void halt(istringstream& s);
	void noop(istringstream& s);
	bool checkRd(int, bool);
	bool checkConst(int, bool);

public:

	Assembler();
	int assemble();
};



