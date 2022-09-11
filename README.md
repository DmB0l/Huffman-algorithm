# Huffman-algorithm
Huffman algorithm on C++

Use example:

  	int main() {
  
  	string in_file_name = { "3.bmp" }; // file to be encoded
	string arch_file_name = { "arch.txt" }; // encoded file 
	string out_file_name = { "out.bmp" }; // decoded file
  
	huffman b(in_file_name); // initial huffman object
  
	b.code_f(in_file_name, arch_file_name); // encode 
	b.decod_f(arch_file_name, out_file_name); // decode
  	return 0;
  	}
