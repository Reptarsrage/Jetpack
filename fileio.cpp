/* Justin Robb
 * 4-3-14
 * JetPack
 * File I/O
*/

#include "fileio.h"
#include "Enums.h"


list<struct Level*> *load(const string& filename, Sprites *sprites) {
	ifstream fp_in;  // declarations of streams fp_in and fp_out
	uint32_t MAGIC_WORD = 0x0CAB005E;
	try {
		printf("Loading %s\n", filename.c_str());
		fp_in.open(filename, ios::in | ios::binary);    // open the stream
		if (!fp_in)
			return NULL;
		
		list<struct Level*> *levels = new list<struct Level*>();
		while (!fp_in.eof()) {
			struct Level *level = (struct Level *)malloc(sizeof(struct Level));
			uint32_t magic;
			// read magic word
			fp_in.read((char *)&magic, sizeof(uint32_t));
			if (fp_in.eof())
				break;

			assert(magic == MAGIC_WORD);

			// 16 bit length of title
			uint16_t len;
			fp_in.read((char *)&len, sizeof(uint16_t));

			// title
			char *buf = new char[len];
			fp_in.read(buf, len*sizeof(char));
			level->title = new string(buf, len);
			delete[] buf;
			printf("title: %s\n", level->title->c_str());

			// 16 bit length of description
			fp_in.read((char *)&len, sizeof(uint16_t));

			// description
			buf = new char[len];
			fp_in.read(buf, len*sizeof(char));
			level->description = new string(buf, len);
			delete[] buf;
			printf("description: %s\n", level->description->c_str());

			// 16 bit length of passcode
			fp_in.read((char *)&len, sizeof(uint16_t));

			// passcode
			buf = new char[len];
			fp_in.read(buf, len*sizeof(char));
			level->passcode = new string(buf, len);
			delete[] buf;
			printf("passcode: %s\n", level->passcode->c_str());

			// len of rbgb data (width, height)
			fp_in.read((char *)&len, sizeof(uint16_t));
			int w = static_cast<int>(len);
			fp_in.read((char *)&len, sizeof(uint16_t));
			int h = static_cast<int>(len);
			printf("rgb width: %d height: %d\n", w, h);
			level->screenshot_w = w;
			level->screenshot_h = h;

			// rgb data
			unsigned char *rgb_buf = (unsigned char *)malloc(w*h*3);
			fp_in.read((char *)rgb_buf, w*h*3);
			level->screenshot_data = rgb_buf;

			// 16 bit number of columns
			fp_in.read((char *)&len, sizeof(uint16_t));
			level->num_cols = static_cast<int>(len);

			// 16 bit number of rows
			fp_in.read((char *)&len, sizeof(uint16_t));
			level->num_rows = static_cast<int>(len);

			// col-wise level map, with token 255(max) seperating 1 byte words.
			int row_c, col_c;
			row_c = col_c = 0;
			uint8_t code;
			int code_i;
			AbstractThing *thing;
			level->data = new list<AbstractThing *>();
			while (row_c < level->num_rows) {
				fp_in.read((char *)&code, sizeof(uint8_t));
				assert(!fp_in.eof());
				while (code != 255) { // skip seperator tokens
					code_i = static_cast<int>(code);
					assert(code_i < TYPE_COUNT);
					thing = getThingFromCode(code_i, static_cast<float>(col_c),
						static_cast<float>(row_c), 1, 1, sprites);
					assert(thing != NULL);
					level->data->push_back(thing);
					fp_in.read((char *)&code, sizeof(uint8_t));
					assert(!fp_in.eof());
				}
				if (col_c+ 1 == level->num_cols){
					col_c = 0;
					row_c++;
				} else
					col_c++;
			}
			levels->push_back(level);
		}
		fp_in.close();   // close the stream
		printf("Loaded!\n");
		return levels;
	} catch (exception& e) {
		printf("Internal error loading file %s: %s\n", filename, e.what());
	}
}

void remove_level(const string& filename, const string& title) {
	ofstream fp_out;
	ifstream fp_in;
	uint32_t MAGIC_WORD = 0x0CAB005E;
	// write all levels except for the one were removing to a temp file
	try {
		fp_in.open(filename, ios::in | ios::binary);
		if (!fp_in)
			return;
		fp_out.open(".temp", ios::out | ios::binary | ios::trunc);
		assert(fp_out);
		int start = 0;
		bool found = false;
		while (!found) {
			start = fp_in.tellg();
			uint32_t magic;
			// read magic word
			fp_in.read((char *)&magic, sizeof(uint32_t));
			if (fp_in.eof())
				break;
			assert(magic == MAGIC_WORD);

			// 16 bit length of title
			uint16_t len;
			fp_in.read((char *)&len, sizeof(uint16_t));
			

			// title
			char *buf = new char[len];
			fp_in.read(buf, len*sizeof(char));
			string title_f = string(buf, len);
			
			if (title.compare(title_f) == 0) {
					found = true;
			}
			if (!found) {
				fp_out.write((char *)&MAGIC_WORD, sizeof(uint32_t));
				fp_out.write((char *)&len, sizeof(uint16_t));
				fp_out.write(buf, len*sizeof(char));
			}
			delete[] buf;

			// 16 bit length of description
			fp_in.read((char *)&len, sizeof(uint16_t));

			// description
			buf = new char[len];
			fp_in.read(buf, len*sizeof(char));
			string description = string(buf, len);
			if (!found) {
				fp_out.write((char *)&len, sizeof(uint16_t));
				fp_out.write(buf, len*sizeof(char));
			}
			delete[] buf;

			// 16 bit length of passcode
			fp_in.read((char *)&len, sizeof(uint16_t));

			// passcode
			buf = new char[len];
			fp_in.read(buf, len*sizeof(char));
			string passcode = string(buf, len);
			if (!found) {
				fp_out.write((char *)&len, sizeof(uint16_t));
				fp_out.write(buf, len*sizeof(char));
			}
			delete[] buf;

			// 16 bit width, height of rgb data
			fp_in.read((char *)&len, sizeof(uint16_t));
			int w = static_cast<int>(len);
			if (!found)
				fp_out.write((char *)&len, sizeof(uint16_t));

			fp_in.read((char *)&len, sizeof(uint16_t));
			int h = static_cast<int>(len);

			// rgb data
			unsigned char *rgb_buf = (unsigned char *)malloc(w*h*3);
			fp_in.read((char *)rgb_buf, w*h*3);
			if (!found) {
				fp_out.write((char *)&len, sizeof(uint16_t));
				fp_out.write((char *)rgb_buf, w*h*3);
			}

			// 16 bit number of columns
			fp_in.read((char *)&len, sizeof(uint16_t));
			int num_cols = static_cast<int>(len);
			if (!found) {
				fp_out.write((char *)&len, sizeof(uint16_t));
			}

			// 16 bit number of rows
			fp_in.read((char *)&len, sizeof(uint16_t));
			int num_rows = static_cast<int>(len);
			if (!found) {
				fp_out.write((char *)&len, sizeof(uint16_t));
			}

			// col-wise level map, with token 255(max) seperating 1 byte words.
			int row_c, col_c;
			row_c = col_c = 0;
			uint8_t code;
			while (row_c < num_rows) {
				fp_in.read((char *)&code, sizeof(uint8_t));
				if (!found) {
					fp_out.write((char *)&code, sizeof(uint8_t));
				}
				assert(!fp_in.eof());
				while (code != 255) { // skip seperator tokens
					fp_in.read((char *)&code, sizeof(uint8_t));
					if (!found) {
						fp_out.write((char *)&code, sizeof(uint8_t));
					}
					assert(!fp_in.eof());
				}
				if (col_c+ 1 == num_cols){
					col_c = 0;
					row_c++;
				} else
					col_c++;
			}
		}

		// fill in rest of temp file
		while (!fp_in.eof()) {
			char buf[256];
			fp_in.read(buf, 256);
			fp_out.write(buf, fp_in.gcount());
			//delete[] buf;
		}
		fp_in.close();
		fp_out.close();
		
		// duplicate temp file to actual file
		fp_in.open(".temp", ios::in | ios::binary);
		fp_out.open(filename, ios::out | ios::binary | ios::trunc);
		assert(fp_in);
		assert(fp_out);
		while (!fp_in.eof()) {
			char buf[256];
			fp_in.read(buf, 256);
			fp_out.write(buf, fp_in.gcount());
			//delete[] buf;
		}
		fp_in.close();
		fp_out.close();
		remove(".temp"); // cleanup
	} catch (exception& e) {
		printf("Internal error removing from file %s: %s\n", filename, e.what());
	}
}

void save(const string& filename, Level& level) {
			  
	uint32_t MAGIC_WORD = 0x0CAB005E;		  
	ofstream fp_out;
	try {
		// find where to write (overwite existing with same name or at end)
		fp_out.open(filename, ios::binary | ios::out | ios::app);
		assert(fp_out);
		
		// write magic word
		fp_out.write((char *)&MAGIC_WORD, sizeof(uint32_t));

		// 16 bit length of title
		uint16_t len = static_cast<uint16_t>(level.title->length());
		fp_out.write((char *) &len, sizeof(uint16_t));

		// title
		fp_out << level.title->c_str();

		// 16 bit length of description
		len = static_cast<uint16_t>(level.description->length());
		fp_out.write((char *) &len, sizeof(uint16_t));

		// description
		fp_out << level.description->c_str();

		// 16 bit length of passcode
		len = static_cast<uint16_t>(level.passcode->length());
		fp_out.write((char *) &len, sizeof(uint16_t));

		// passcode
		fp_out << level.passcode->c_str();

		// 16 bit width, height of rgb data
		uint16_t w = static_cast<uint16_t>(level.screenshot_w);
		uint16_t h = static_cast<uint16_t>(level.screenshot_h);
		printf("(save) rgb width: %d height: %d\n", w, h);

		// rgb data
		unsigned char *rgb_buf = (unsigned char *)malloc(w*h*3);
		memcpy(rgb_buf, level.screenshot_data, h*w*3);
		fp_out.write((char *)&w, sizeof(uint16_t));
		fp_out.write((char *)&h, sizeof(uint16_t));
		fp_out.write((char *)rgb_buf, w*h*3);
		delete[] rgb_buf;

		// 16 bit number of columns
		len = static_cast<uint16_t>(level.num_cols);
		fp_out.write((char *) &len, sizeof(uint16_t));

		// 16 bit number of rows
		len = static_cast<uint16_t>(level.num_rows);
		fp_out.write((char *) &len, sizeof(uint16_t));

		// col-wise level map, with token 255(max) seperating 1 byte words.
		uint8_t code;
		while (!level.data->empty()) {
			while (level.data->front() != NULL) {
				code = static_cast<uint8_t>(level.data->front()->getType());
				level.data->pop_front();
				fp_out.write((char *) &code, sizeof(uint8_t));
			}
			level.data->pop_front();
			code = 255;
			fp_out.write((char *) &code, sizeof(uint8_t));
		}
		fp_out.close(); 
	} catch (exception& e) {
		printf("Internal error saving file %s: %s\n", filename, e.what());
	}
}
