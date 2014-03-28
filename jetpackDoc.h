/* Justin Robb
 * 3-27-14
 * JetPack
 * Handler for everything not UI related
*/

#ifndef JetpackDoc_h
#define JetpackDoc_h

#include "jetpack_main.h"
#include "Sprites.h"

class JetpackUI;

/*
 * Keeps track of Animation, painting, and also in charge of keeping track of states.
 */
class JetpackDoc 
{
// Functions
public:
	JetpackDoc();

	/* Assign the UI to use */
	void	setUI(JetpackUI* ui);
	
	/* Begins animation counter */
	void	startAnimating();

	/* Stops animation counter */
	void	stopAnimating();

// Attributes
public:

	int				m_nWidth,		// Dimensions of original window.
					m_nHeight;

	int				m_nPaintWidth,  // Dimensions of the paint window.
					m_nPaintHeight;						

	JetpackUI*	m_pUI;				// UI to communicate with
	Sprites *sprites;				// Sprite manager (all sprites)
	bool animating;					// controller for animation callbacks
};

extern void MessageBox(char *message);

#endif