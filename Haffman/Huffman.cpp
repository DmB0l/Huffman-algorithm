#include "Huffman.h"

huffman::huffman(string file_name)
{
	this->name_file = file_name;
	counter_of_symbols = 0;

	ifstream in_file(file_name, ios::binary);
	if (in_file.is_open()) {
		while (1)
		{
			char c = in_file.get();
			if (in_file.eof()) break;
				cymbol_val[c]++; // считывание информации о том, сколько раз встретился тот или иной символ
				counter_of_symbols++;
		}

		in_file.close();

		for (map<char, int>::iterator it = cymbol_val.begin(); it != cymbol_val.end(); it++) // создание списка первоночальных элементов
		{
			node* p = new node;
			p->set_symbol(it->first);
			p->set_val(it->second);
			tree.push_back(p);
		}

		while (tree.size() != 1) // создание самого дерева
		{
			tree.sort(MyCompare());

			node* l_son = tree.front();
			tree.pop_front();
			node* r_son = tree.front();
			tree.pop_front();

			node* parent = new node(l_son, r_son);
			tree.push_back(parent);
		}
		vector<bool> code;
		create_table(tree.front(), code); // создание таблицы ассоциативности кода хаффмана с символом
	}
}

huffman::~huffman()
{
	for (auto i = tree.begin(); i != tree.end(); i++)
	{
		delete[] *i;
	}
}

void huffman::create_table(node* head, vector<bool>& code) // постройка таблицы ассоциативности символов с кодом хаффмана
{
	if (head->get_left() != NULL)
	{
		code.push_back(0);
		create_table(head->get_left(), code);
	}

	if (head->get_right() != NULL)
	{
		code.push_back(1);
		create_table(head->get_right(), code);
	}

	if (head->get_right() == NULL && head->get_left() == NULL)
	{
		table[head->get_symbol()] = code;
	}

	if (code.size() != 0 && !(code.empty())) code.pop_back();

}

void huffman::code_f(string in_file_name, string out_file_name)
{
	ofstream arch_file(out_file_name, ios::binary);
	arch_file << '#';

	for (auto i = table.begin(); i != table.end(); i++)
	{
		arch_file.write((char*)&(i->first), sizeof(i->first));
		vector<bool> x = i->second;
		for (auto j = 0; j < x.size(); j++)
		{
			arch_file << x[j];
		}
		arch_file << '#';
	}
	arch_file << "CODE";

	int count = 0;
	char buf = 0;
	int count_of_code = 0;

	ifstream in_file(in_file_name, ios::binary);
	if (in_file.is_open())
	{
		while (1)
		{
			
			char c = 0;
			in_file.read((char*)&c, 1); // считывается символ из файла
			if (in_file.eof()) break;
				vector<bool> v = table[c]; // берется его двоичный код в ассоциации хаффмана

				for (int j = 0; j < v.size(); j++)
				{
					buf = buf | v[j] << (7 - count); // переписывается 8 бит из двоичного вектора(может быть меньше, тогда добирается из следующего и тд)
					count++;
					if (count == 8)
					{
						count = 0;
						arch_file.write((char*)&buf, sizeof(buf)); // когда набрали 8 бит, записываем получившийся символ в архивированный файл
						buf = 0;
					}
				}
		}
		if (buf != 0)
		{
			arch_file.write((char*)&buf, sizeof(buf)); // проверка на последний элемент
		}

		arch_file.seekp(0);
		char bad_bits = 0;
		bad_bits = 8 - count;
		arch_file.write((char*)&bad_bits, sizeof(char));
	}

	arch_file.close();
}

void huffman::decod_f(string in_file_name, string out_file_name)
{
	unordered_map<vector<bool>, char> safe_table;
	unordered_map<vector<bool>, char>::iterator it;

	ifstream F(in_file_name, ios::binary);

	if (F.is_open())
	{
		int bad_bits = 0;
		F.read((char*)&bad_bits, 1);

		while (1)
		{
			char c = 0;
			char m = 0;
			F.read((char*)&m, 1);
			if (m == 'C') {
				char tmp = m;
				auto pos = F.tellg();
				if ((m = F.get()) == 'O' && (m = F.get()) == 'D' && (m = F.get()) == 'E') break;
				F.seekg(pos);
				m = tmp;
			}

			vector<bool> cood1;
			while (c != '#')
			{
				F.read((char*)&c, 1);
				if (c != '#') cood1.push_back((int)c - '0');
			}
			safe_table.insert(pair<vector<bool>, char>(cood1, m));
		}

		ofstream out_f(out_file_name, ios::binary);
		int count = 0;
		char buf = 0;
		bool flag = 0;
		vector<bool> cood_symbol;

		F.readsome((char*)&buf, 1); // читаем закодированный символ
		while (1)
		{
			if (flag == 1 && bad_bits + count == 8) break;

			bool b = buf & (1 << (7 - count)); // переписываем его побитно
			cood_symbol.push_back(b); // записываем результат в вектор
			it = safe_table.find(cood_symbol); // ищем по дереву путь до символа


			if (it != safe_table.end()) // если нашли то записываем его в декодированный файл, обнуляем вектор
			{
				out_f.write((char*)&it->second, sizeof(it->second));
				cood_symbol.clear();
			}

			count++;
			if (count == 8) // если считали все 8 бит, то берем следующий символ из файла
			{
				count = 0;
				F.read((char*)&buf, 1);
				if (F.eof()) break;

				char tmp = buf;
				auto pos = F.tellg();
				F.read((char*)&buf, 1);
				if (F.eof())
				{
					flag = 1;
				}
				F.seekg(pos);
				buf = tmp;

			}
		}

		out_f.close();
		F.close();
	}
}