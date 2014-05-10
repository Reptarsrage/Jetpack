
#include "loadMenu.h"
#include <sstream>
#include "fileio.h"
#include "Level.h"

void LoadingMenu::cb_sel(Fl_Widget* o, void* v) {
  Fl_Hold_Browser *fbrow = (Fl_Hold_Browser*)o;
  int index = fbrow->value();            // get index of selected item
  if ( index > 0 ) {                     // valid item?
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
  } else {
	  whoami(fbrow)->setTexts("Non selected.", "Non selected.", "Non selected.");
  }
}

void LoadingMenu::cb_confirm(Fl_Widget* o, void* v) {
	Fl_Hold_Browser *fbrow = whoami(o)->browser;
	int index = fbrow->value();            // get index of selected item
  if ( index > 0 ) {                     // valid item?
	  std::ostringstream os;
	  os << fbrow->text(index);
	  std::string t = os.str();
	  whoami(o)->m_UI->loadLevel(t);
  } else {
	  printf("Please select a level to load!");
  }
}

void LoadingMenu::update(std::string filename) {
	if (level_cache != NULL) {
		level_cache->clear();
		level_cache = NULL;
	}
	browser->clear();
	
	level_cache = load(filename, m_UI->sprites);

	if (level_cache != NULL)
		for (struct Level * l : *level_cache) {
			browser->add(l->title->c_str());
		}
}

LoadingMenu::LoadingMenu(float x, float y, float w, float h, const char* l, JetpackUI *ui) : Fl_Group(x,y,w,h, l) {
	user_data((void*)(this));	// record self to be used by static callback functions
	browser = new Fl_Hold_Browser(x + 50, y + 50, w *.6f, h  - 100);
	m_UI = ui;
	level_cache = NULL;
	update("test.level");
	
	browser->show();
	title = new Fl_Text_Display(x + 60 +  w *.6f, y + 50, w*.3f, 25);
	description = new Fl_Text_Display(x + 60 +  w *.6f, y + 85, w*.3f, 50);
	pass = new Fl_Text_Display(x + 60 +  w *.6f, y + 145, w*.3f, 50);
	confirm = new Fl_Button(x + 60 +  w *.6f, y + 200, w*.3f, 50, "Load");
	confirm->callback(cb_confirm);
	pass_buf = new Fl_Text_Buffer();
	tit_buf = new Fl_Text_Buffer();
	desc_buf = new Fl_Text_Buffer();
	title->buffer(tit_buf);
	description->buffer(desc_buf);
	pass->buffer(pass_buf);
	setTexts("Non Selected", "Non Selected", "Non selected.");
    browser->callback(cb_sel);
}

LoadingMenu::~LoadingMenu(){
	delete browser;
}

void LoadingMenu::setTexts(const char * title, const char * description, const char *password) {
	tit_buf->text(title);
	desc_buf->text(description);
	pass_buf->text(password);
}

LoadingMenu* LoadingMenu::whoami(Fl_Widget* o)	
{
	return ( (LoadingMenu*)(o->parent()->user_data()) );
}
