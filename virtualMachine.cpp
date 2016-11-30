#include "virtualMachine.h"

VirtualMachine::VirtualMachine(){
	r = vector <int>(REG_FILE_SIZE);
	mem = vector <int>(MEM_SIZE);

	for (int i = 0; i < REG_FILE_SIZE; i++)
		r[i] = 0;
	for (int i = 0; i < MEM_SIZE; i++)
		mem[i] = 0;
}
void VirtualMachine::iFetch(){
	vmProg.open("prog.o", ios::in);
	inFile.open("data.in", ios::in);
	outFile.open("output.txt", ios::out);

	if (!vmProg.is_open()) {
		cout << "prog.o failed to open.\n";
		return;
	}
	if (!inFile.is_open()) {
		cout << "inFile failed to open.\n";
		return;
	}
	if (!outFile.is_open()) {
		cout << "outFile failed to open.\n";
		return;
	}

	base = 0;
	limit = 0;
	pc = 0;
	clock = 0;
	sp = 256;
	int j = 0;

	getline(vmProg, line);
	while (!vmProg.eof()) {
		rd = -1; rs = -1; constant = -129; error = false;

		istringstream str(line.c_str());
		str >> mem[j];
		++limit;
		j++;
		getline(vmProg, line);
	}


	while (pc < limit){
		cout << "ENTERED FETCH CYCLE" << endl;
		ir = mem[pc];
		++pc;
		opcode = ir >> 11;
		rd = ir >> 9;
		rd &= 3;
		i = ir >> 8;
		i &= 1;
		rs = ir >> 6;
		rs &= 3;
		constant = ir;
		constant &= 255;

		runOp();
	}

	outFile << clock << " clock \n";
}

int VirtualMachine::getSr(){
	sr = 0;
	sr += (status.overflow << 4);
	sr += (status.less << 3);
	sr += (status.equal << 2);
	sr += (status.greater << 1);
	sr += status.carry;
	return sr;
}

void VirtualMachine::runOp(){
	if (opcode == 0 && i == 0){ //load
		r[rd] = mem[constant];
		clock += 4;
	}
	else if (opcode == 0 && i == 1){//loadi
		r[rd] = constant;
		clock += 1;
	}
	else if (opcode == 1 && i == 1){//store
		mem[constant] = r[rd];
		clock += 4;
	}
	else if (opcode == 2 && i == 0){//add
		r[rd] += r[rs];
		clock += 1;
	}
	else if (opcode == 2 && i == 1){//addi
		r[rd] += constant;
		clock += 1;
	}
	else if (opcode == 3 && i == 0){//addc
		r[rd] += (r[rs] + carry);
		clock += 1;
	}
	else if (opcode == 3 && i == 1){//addci
		r[rd] += (constant + carry);
		clock += 1;
	}
	else if (opcode == 4 && i == 0){//sub
		r[rd] -= r[rs];
		clock += 1;
	}
	else if (opcode == 4 && i == 1){//subi
		r[rd] -= constant;
		clock += 1;
	}
	else if (opcode == 5 && i == 0){//subc
		r[rd] -= (r[rs] - carry);
		clock += 1;
	}
	else if (opcode == 5 && i == 1){//subci
		r[rd] -= (constant - carry);
		clock += 1;
	}
	else if (opcode == 6 && i == 0){//and
		r[rd] = r[rd] & r[rs];
		clock += 1;
	}
	else if (opcode == 6 && i == 1){//andi
		r[rd] = r[rd] & constant;
		clock += 1;
	}
	else if (opcode == 7 && i == 0){//xor
		r[rd] = r[rd] ^ r[rs];
		clock += 1;
	}
	else if (opcode == 7 && i == 1){//xori
		r[rd] = r[rd] ^ constant;
		clock += 1;
	}
	else if (opcode == 8 && i == 1){//compl
		r[rd] = ~r[rd];
		clock += 1;
	}
	else if (opcode == 9){//shl
		r[rd] = r[rd] << 1;
		clock += 1;
	}
	else if (opcode == 10){//shla
		;//shl arithmetic
		clock += 1;
	}
	else if (opcode == 11){//shr
		r[rd] = r[rd] >> 1;
		clock += 1;
	}
	else if (opcode == 12){//shra
		//shr arithmetic
		clock += 1;
	}
	else if (opcode == 13 && i == 0){//compr
		if (r[rd] < r[rs]){
			status.less = 1;
			status.equal = 0;
			status.greater = 0;
		}
		else if (r[rd] == r[rs]){
			status.less = 0;
			status.equal = 1;
			status.greater = 0;
		}
		else if (r[rd] == r[rs]){
			status.less = 0;
			status.equal = 0;
			status.greater = 1;
		}
		clock += 1;
	}
	else if (opcode == 13 && i == 1){//compri
		if (r[rd] < constant){
			status.less = 1;
			status.equal = 0;
			status.greater = 0;
		}
		else if (r[rd] == constant){
			status.less = 0;
			status.equal = 1;
			status.greater = 0;
		}
		else if (r[rd] == constant){
			status.less = 0;
			status.equal = 0;
			status.greater = 1;
		}
		clock += 1;
	}
	else if (opcode == 14){//getstat
		r[rd] = getSr();
		clock += 1;
	}
	else if (opcode == 15){//putstat
		status.carry = (r[rd] & 1);
		status.greater = ((r[rd] >> 1) & 1);
		status.equal = ((r[rd] >> 2) & 1);
		status.less = ((r[rd] >> 3) & 1);
		status.overflow = ((r[rd] >> 4) & 1);
		clock += 1;
	}
	else if (opcode == 16 && i == 1){//jump
		pc = constant;
		clock += 1;
	}
	else if (opcode == 17 && i == 1){//jumpl
		if (status.less == 1)
			pc = constant;

		clock += 1;
	}
	else if (opcode == 18 && i == 1){//jumpe
		if (status.equal == 1)
			pc = constant;
		clock += 1;
	}
	else if (opcode == 19 && i == 1){//jumpg
		if (status.greater == 1)
			pc = constant;
		clock += 1;
	}
	else if (opcode == 20 && i == 1){//call
		hole.push(pc);
		hole.push(r[0]);
		hole.push(r[1]);
		hole.push(r[2]);
		hole.push(r[3]);
		hole.push(status.carry);
		hole.push(status.equal);
		hole.push(status.greater);
		hole.push(status.less);
		hole.push(status.overflow);
		pc = constant;
		sp -= 6;
		clock += 4;
	}
	else if (opcode == 21){//return
		status.overflow = hole.top();
		hole.pop();
		status.less = hole.top();
		hole.pop();
		status.greater = hole.top();
		hole.pop();
		status.equal = hole.top();
		hole.pop();
		status.carry = hole.top();
		hole.pop();
		r[3] = hole.top();
		hole.pop();
		r[2] = hole.top();
		hole.pop();
		r[1] = hole.top();
		hole.pop();
		r[0] = hole.top();
		hole.pop();
		pc = hole.top();
		hole.pop();

		sp += 6;
		clock += 4;
	}
	else if (opcode == 22){//read rd
		inFile >> r[rd];
		clock += 28;
	}
	else if (opcode == 23){//write rd
		outFile << r[rd] << "\n";
		clock += 28;
	}
	else if (opcode == 24){//halt
		return;
		clock += 1;
	}
	else if (opcode == 22){ // noop
		clock += 1;
	}

}

	
