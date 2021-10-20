#include "Raquette.h"
#include "Enum.h"
#include <SDL.h>

Raquette::Raquette(int h, int w, int x, int y, int R, int G, int B, int A)
{
	this->hauteur = h;
	this->largeur = w;
	this->posX = x;
	this->posY = y;
	this->vraiR = R;
	this->vraiG = G;
	this->vraiB = B;
	this->vraiA = A;
	etatJoueur = joueur::none;
}

void Raquette::draw(SDL_Renderer* Renderer) const
{
	SDL_Rect Rect;
	Rect.w = largeur;
	Rect.h = hauteur;
	Rect.x = posX;
	Rect.y = posY;
	SDL_SetRenderDrawColor(Renderer, 255, 255, 255,0);
	SDL_RenderFillRect(Renderer, &Rect);
}

int Raquette::getHauteur()
{
	return hauteur;
}

int Raquette::getLargeur()
{
	return largeur;
}

int Raquette::getX()
{
	return posX;
}

int Raquette::getY()
{
	return posY;
}

joueur Raquette::getEtat()
{
	return etatJoueur;
}

void Raquette::modifPosY()
{
	switch (etatJoueur)
	{
	case joueur::up :
		posY -= 15;
		break;
	case joueur::down :
		posY += 15;
		break;
	case joueur::none:
		break;
	}
}

void Raquette::setDownY(int y)
{
	this->posY += y;
}

void Raquette::setUpY(int y)
{
	this->posY -= y;
}

void Raquette::setY(int y)
{
	this->posY = y;
}

void Raquette::setEtatJoueur(joueur etat)
{
	etatJoueur = etat;
}

void Raquette::PollEventJ1(SDL_Event& Event, joueur& fauxControlJ1)
{
	const Uint8 *keystate = SDL_GetKeyboardState(NULL);
	if (Event.type == SDL_KEYDOWN) {
		if (keystate[SDL_SCANCODE_W]) {
			fauxControlJ1 = joueur::up;
		}if (keystate[SDL_SCANCODE_S]) {
			fauxControlJ1 = joueur::down;
		}
	}
	else {
		fauxControlJ1 = joueur::none;
	}
}

void Raquette::PollEventJ2(SDL_Event& Event, joueur &fauxControlJ2)
{
	const Uint8* keystateJ2 = SDL_GetKeyboardState(NULL);
	if (Event.type == SDL_KEYDOWN) {
		if (keystateJ2[SDL_SCANCODE_UP]) {
			fauxControlJ2 = joueur::up;
		}if (keystateJ2[SDL_SCANCODE_DOWN]) {
			fauxControlJ2 = joueur::down;
		}
	}
	else {
		fauxControlJ2 = joueur::none;
	}
}
