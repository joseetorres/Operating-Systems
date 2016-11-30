#include <iostream>
#include <string>
#include <map>
#include <fstream>  
#include <sstream> 
#include<vector>
#include<stack>

using namespace std;

class VirtualMachine{

	struct statusRegister
	{
		unsigned int carry : 1;
		unsigned int greater : 1;
		unsigned int equal : 1;
		unsigned int less : 1;
		unsigned int overflow : 1;
	};



private:
	statusRegister status;
	typedef void (VirtualMachine::*FP)(istringstream&);
	fstream vmProg;
	fstream outFile;
	fstream inFile;
	string line;
	bool error;
	int rd, rs, constant, carry, outNum, i, opcode;
	map<string, FP> instr;
	static const int REG_FILE_SIZE = 4;
	static const int MEM_SIZE = 256;
	vector<int> r;
	vector<int> mem;
	int pc, ir, sr, sp, base, limit, clock;
	stack<int> hole;

	int getSr();
	void runOp();
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
	VirtualMachine();
	void iFetch();
};


