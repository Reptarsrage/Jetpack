
#include "SaveMenu.h"
#include <FL/fl_ask.H>
#include <sstream>
#include "fileio.h"
#include "Level.h"

void SavingMenu::cb_sel(Fl_Widget* o, void* v) {
  Fl_Hold_Browser *fbrow = (Fl_Hold_Browser*)o;
  int index = fbrow->value();            // get index of selected item
  if ( index > 1 ) {                     // valid item?
	  std::ostringstream os;
	  os << fbrow->text(index);
	  std::string t = os.str();
	  std::string d, p;
	  for (struct Level *l : *whoami(fbrow)->level_cache) {
		  if (l->title->compare(t) == 0){
				d = *l->description;
				p = *l->passcode;
				whoami(fbrow)->setTexts(t.c_str(), d.c_str(), p.c_str());
		  }
	  }
  }
}

void SavingMenu::cb_confirm(Fl_Widget* o, void* v) {
	Fl_Hold_Browser *fbrow = whoami(o)->browser;
	int index = fbrow->value();            // get index of selected item
	string t = whoami(o)->title->value();
	string d = whoami(o)->description->value();
	string p = whoami(o)->pass->value();
	if (whoami(fbrow)->level_cache == NULL) {
		whoami(o)->m_UI->saveLevel(t, d, p);
		return;
	}


	for (struct Level *l : *whoami(fbrow)->level_cache) {
		if (l->title->compare(t) == 0){
			ostringstream os;
			os << "Do you want to overwrite the currently existing level ";
			os << t;
			os << "?";
			if (fl_ask(os.str().c_str()) == 0) { // NO
				return;
			} else { // YES
				remove_level("test.level", t);
			}
		}
	}
	if (!t.empty()) {         // valid item?
		whoami(o)->m_UI->saveLevel(t, d, p);
	} else {
		printf("Please check the input!");
	}
}

void SavingMenu::update(std::string filename) {
	if (level_cache != NULL) {
		level_cache->clear();
		level_cache = NULL;
	}
	browser->clear();
	
	level_cache = load(filename, m_UI->sprites);
	browser->add("<New Save>");
	if (level_cache != NULL)
		for (struct Level * l : *level_cache) {
			browser->add(l->title->c_str());
		}
	setTexts("Enter Title.", "Enter Description.", "Enter Password.");
}

SavingMenu::SavingMenu(float x, float y, float w, float h, const char* l, JetpackUI *ui) : Fl_Group(x,y,w,h, l) {
	user_data((void*)(this));	// record self to be used by static callback functions
	browser = new Fl_Hold_Browser(x + 50, y + 50, w *.6f, h  - 100);
	m_UI = ui;
	level_cache = NULL;
	title = new Fl_Multiline_Input(x + 60 +  w *.6f, y + 50, w*.3f, 25);
	description = new Fl_Multiline_Input(x + 60 +  w *.6f, y + 85, w*.3f, 50);
	pass = new Fl_Multiline_Input(x + 60 +  w *.6f, y + 145, w*.3f, 50);
	confirm = new Fl_Button(x + 60 +  w *.6f, y + 200, w*.3f, 50, "Save");
	confirm->callback(cb_confirm);
	update("test.level");
	browser->show();
    browser->callback(cb_sel);
	browser->select(0);
}

SavingMenu::~SavingMenu(){
	delete browser;
}

void SavingMenu::setTexts(const char * t, const char * d, const char *p) {
	title->value(t);
	description->value(d);
	pass->value(p);
}

SavingMenu* SavingMenu::whoami(Fl_Widget* o)	
{
	return ( (SavingMenu*)(o->parent()->user_data()) );
}
