#include "Huffman.h"


int main()
{
	string in_file_name = { "3.bmp" };
	string arch_file_name = { "arch.txt" };
	string out_file_name = { "out.bmp" };
	huffman b(in_file_name);
	b.code_f(in_file_name, arch_file_name);
	b.decod_f(arch_file_name, out_file_name);

	return 0;

}