# Huffman-algorithm
Huffman algorithm on C++

Use example:
<html>
<code>
  int main() { <br>
  string in_file_name = { "3.bmp" }; // file to be encoded <br>
	string arch_file_name = { "arch.txt" }; // encoded file <br>
	string out_file_name = { "out.bmp" }; // decoded file <br> <br>
  
	huffman b(in_file_name); // initial huffman object <br> <br>
  
	b.code_f(in_file_name, arch_file_name); // encode <br>
	b.decod_f(arch_file_name, out_file_name); // decode <br> <br>
  
  return 0; <br>
  } <br>
</code>
</html>
