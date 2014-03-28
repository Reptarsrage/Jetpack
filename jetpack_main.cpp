/* Justin Robb
 * 3-27-14
 * JetPack
 * Main
*/

/* The main driver program for the other parts. We have two major components,
 * UI and Doc.
 * They do have a link to each other as their member such that they can 
 * communicate.
 */

#include <stdio.h>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Shared_Image.H>

#include "jetpackUI.h"
#include "jetpackDoc.h"

JetpackUI *impUI;
JetpackDoc *impDoc;

int main(int	argc, 
		 char**	argv) 
{
	impDoc = new JetpackDoc();

	// Create the UI
	impUI = new JetpackUI();

	// Set the impDoc
	impUI->setDocument(impDoc);
	impDoc->setUI(impUI);

	Fl::visual(FL_DOUBLE|FL_INDEX);

	impUI->show();

	return Fl::run();
}