
#include "loadMenu.h"
#include <sstream>
#include "fileio.h"

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
				whoami(fbrow)->addImage(l->screenshot_data, l->screenshot_w, l->screenshot_h);
				whoami(fbrow)->setTexts(t.c_str(), d.c_str(), p.c_str());
		  }
	  }
  } else {
	  whoami(o)->Reset();
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

void LoadingMenu::Reset() {
	if (img)
		  delete img;
	int wi = img_box->w();
	int he = img_box->h();
	unsigned char *img_d = (unsigned char *)malloc(wi*he*3);
	for (int i =0; i < wi*he*3; i++) {
		img_d[i] = static_cast<char>(m_rand());
	}
	img = new Fl_RGB_Image(img_d, wi, he);
	img_box->image(img);
	img_box->redraw();
	browser->selected(-1);
	setTexts("Non selected.", "Non selected.", "Non selected.");
}

void LoadingMenu::addImage(const unsigned char *img_data, int width, int height) {
	if (img)
		delete img;
	
	unsigned char *raw_data = (unsigned char *)malloc(width*height*3);
	memcpy(raw_data, img_data, width*height*3);
	img = new Fl_RGB_Image(Resample(raw_data, width, height, img_box->w(), img_box->h()), img_box->w(), img_box->h());
	img_box->image(img);
	img_box->redraw();
}

// Perform a basic 'pixel' enlarging resample.
unsigned char * LoadingMenu::Resample(unsigned char *buf, int width, int height, int newWidth, int newHeight)
{
    if(buf == NULL) return false;
    //
    // Get a new buuffer to interpolate into
    unsigned char* newData = new unsigned char [newWidth * newHeight * 3];

    double scaleWidth =  (double)newWidth / (double)width;
    double scaleHeight = (double)newHeight / (double)height;

    for(int cy = 0; cy < newHeight; cy++)
    {
        for(int cx = 0; cx < newWidth; cx++)
        {
            int pixel = (cy * (newWidth *3)) + (cx*3);
            int nearestMatch =  (((int)(cy / scaleHeight) * (width *3)) + ((int)(cx / scaleWidth) *3) );
                
            newData[pixel    ] =  buf[nearestMatch    ];
            newData[pixel + 1] =  buf[nearestMatch + 1];
            newData[pixel + 2] =  buf[nearestMatch + 2];
        }
    }

    delete[] buf;
    return newData;
}

void LoadingMenu::cb_cancel(Fl_Widget* o, void* v) {
	whoami(o)->Reset();
	whoami(o)->m_UI->switch_contexts(whoami(o)->m_UI->m_editor_group);
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
	browser = new Fl_Hold_Browser(x + 10, y + 10, w *.4f, h  - 20);
	m_UI = ui;
	level_cache = NULL;
	title = new Fl_Text_Display(x + 20 +  w *.4f, y + 10, w - w *.4f - 30, 25);
	description = new Fl_Text_Display(x + 20 +  w *.4f, y + 45, w - w *.4f - 30, 50);
	//pass = new Fl_Text_Display(x + 20 +  w *.4f, y + 145, w*.5f, 50);
	update("test.level");
	//pass_buf = new Fl_Text_Buffer();
	tit_buf = new Fl_Text_Buffer();
	desc_buf = new Fl_Text_Buffer();
	title->buffer(tit_buf);
	description->buffer(desc_buf);
	//pass->buffer(pass_buf);
    browser->callback(cb_sel);
	int wi, he;
	wi = w - w *.4f - 30;
	he = h  - 125 - 50;

	confirm = new Fl_Button(x + 20 +  w *.4f,  y + 115 + he, -5 + wi / 2.f, 50, "Save");
	cancel = new Fl_Button(5 + x + 20 +  w *.4f + wi / 2.f, y + 115 + he, -5 + wi / 2.f, 50, "Cancel");
	confirm->callback(cb_confirm);
	cancel->callback(cb_cancel);
	img_box = new Fl_Box(x + 20 +  w *.4f, y + 120, wi, he);
	img = NULL;
	Reset();
}

LoadingMenu::~LoadingMenu(){
	delete browser;
}

void LoadingMenu::setTexts(const char * title, const char * description, const char *password) {
	tit_buf->text(title);
	desc_buf->text(description);
	//pass_buf->text(password);
}

LoadingMenu* LoadingMenu::whoami(Fl_Widget* o)	
{
	return ( (LoadingMenu*)(o->parent()->user_data()) );
}
