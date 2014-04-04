/* Justin Robb
 * 4-3-14
 * JetPack
 * File I/O
*/

#include "fileio.h"
#include "Enums.h"


void load(string& filename,  
					float row_w, 
					float col_h, 
					int *num_rows, 
					int *num_cols,
					string **title,
					string **description,
					string **passcode,
					list<AbstractThing *> *level,
					Sprites *sprites) {
	ifstream fp_in;  // declarations of streams fp_in and fp_out
	uint32_t MAGIC_WORD = 0x0CAB005E;
	try {
		printf("Loading %s\n", filename.c_str());
		fp_in.open(filename, ios::in | ios::binary);    // open the stream
		
		uint32_t magic;
		// read magic word
		fp_in.read((char *)&magic, sizeof(uint32_t));
		assert(magic == MAGIC_WORD);

		// 16 bit length of title
		uint16_t len;
		fp_in.read((char *)&len, sizeof(uint16_t));

		// title
		char *buf = new char[len];
		fp_in.read(buf, len*sizeof(char));
		*title = new string(buf, len);
		delete[] buf;
		printf("title: %s\n", (*title)->c_str());

		// 16 bit length of description
		fp_in.read((char *)&len, sizeof(uint16_t));

		// description
		buf = new char[len];
		fp_in.read(buf, len*sizeof(char));
		*description = new string(buf, len);
		delete[] buf;
		printf("description: %s\n", (*description)->c_str());

		// 16 bit length of passcode
		fp_in.read((char *)&len, sizeof(uint16_t));

		// passcode
		buf = new char[len];
		fp_in.read(buf, len*sizeof(char));
		*passcode = new string(buf, len);
		delete[] buf;
		printf("passcode: %s\n", (*passcode)->c_str());

		// 16 bit number of columns
		fp_in.read((char *)&len, sizeof(uint16_t));
		num_cols = new int(static_cast<int>(len));

		// 16 bit number of rows
		fp_in.read((char *)&len, sizeof(uint16_t));
		num_rows = new int(static_cast<int>(len));

		// col-wise level map, with token 255(max) seperating 1 byte words.
		int row_c, col_c;
		row_c = col_c = 0;
		uint8_t code;
		int code_i;
		AbstractThing *thing;
		while (!fp_in.eof()) {
			fp_in.read((char *)&code, sizeof(uint8_t));
			while (code != 255) { // skip seperator tokens
				code_i = static_cast<int>(code);
				assert(code_i < TYPE_COUNT);
				thing = getThingFromCode(code_i, static_cast<float>(col_c),
					static_cast<float>(row_c), row_w, col_h, sprites);
				assert(thing != NULL);
				level->push_back(thing);
				fp_in.read((char *)&code, sizeof(uint8_t));
			}
			if (col_c+ 1 == *num_cols){
				col_c = 0;
				row_c++;
			} else
				col_c++;
		}
		fp_in.close();   // close the stream
		printf("Loaded!\n");
	} catch (exception& e) {
		printf("Internal error loading file %s: %s\n", filename, e.what());
	}
}

void save(string& filename, 
		  string& title, 
		  string& description, 
		  string& passcode, 
		  queue<AbstractThing *> level, 
		  int num_rows, 
		  int num_cols) {
			  
	uint32_t MAGIC_WORD = 0x0CAB005E;		  
	ofstream fp_out;
	try {
		fp_out = ofstream(filename, ios::out | ios::binary);
		assert(fp_out);

		// write magic word
		fp_out.write((char *)&MAGIC_WORD, sizeof(uint32_t));

		// 16 bit length of title
		uint16_t len = static_cast<uint16_t>(title.length());
		fp_out.write((char *) &len, sizeof(uint16_t));

		// title
		fp_out << title;

		// 16 bit length of description
		len = static_cast<uint16_t>(description.length());
		fp_out.write((char *) &len, sizeof(uint16_t));

		// description
		fp_out << description;

		// 16 bit length of passcode
		len = static_cast<uint16_t>(passcode.length());
		fp_out.write((char *) &len, sizeof(uint16_t));

		// passcode
		fp_out << passcode;

		// 16 bit number of columns
		len = static_cast<uint16_t>(num_cols);
		fp_out.write((char *) &len, sizeof(uint16_t));

		// 16 bit number of rows
		len = static_cast<uint16_t>(num_rows);
		fp_out.write((char *) &len, sizeof(uint16_t));

		// col-wise level map, with token 255(max) seperating 1 byte words.
		uint8_t code;
		while (!level.empty()) {
			while (level.front() != NULL) {
				code = static_cast<uint8_t>(level.front()->getType());
				level.pop();
				fp_out.write((char *) &code, sizeof(uint8_t));
			}
			level.pop();
			code = 255;
			fp_out.write((char *) &code, sizeof(uint8_t));
		}
		fp_out.close(); 
	} catch (exception& e) {
		printf("Internal error saving file %s: %s\n", filename, e.what());
	}
}
