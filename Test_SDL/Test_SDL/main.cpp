#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include <cstdlib>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Raquette.h"
#include "Balle.h"
#include "Enum.h"
#include "Score.h"
#include "Visuel.h"


using namespace std;

int main(int argc, char** argv)
{

    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stdout, "Échec de l'initialisation de la SDL (%s)\n", SDL_GetError());
        return -1;
    }

    if (TTF_Init() == -1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    {
        /* Création de la fenêtre */
        SDL_Window* pWindow = NULL;
        SDL_Renderer* pRenderer = NULL;

        Score scoreJoueur;

        TTF_Font* police = TTF_OpenFont("../fonts/sample.ttf", 65);

        if (police == nullptr)
        {
            fprintf(stderr, "Erreur %s\n", SDL_GetError());
            return -1;
        }

        if (SDL_CreateWindowAndRenderer(WIDTHSCREEN<unsigned int>, HEIGHTSCREEN<unsigned int>, SDL_WINDOW_SHOWN, &pWindow, &pRenderer) < 0)
        {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "[DEBUG] > %s", SDL_GetError());
            SDL_Quit();
            return EXIT_FAILURE;
        }
        SDL_SetWindowTitle(pWindow, "Pong en SDL");


        if (pWindow)
        {
            SDL_Event events;
            Raquette Joueur1(150, 20, 0, HEIGHTSCREEN<int>/2, 255, 255,255,0);
            Raquette Joueur2(150, 20, WIDTHSCREEN<int>-20, HEIGHTSCREEN<int>/2, 255, 255,255,0);
            Balle balle(WIDTHSCREEN<int> / 2, HEIGHTSCREEN<int> / 2, 10, 10);

            

            bool isOpen = true;

            while (isOpen && (!scoreJoueur.verifVictoireJ1() && !scoreJoueur.verifVictoireJ2()))

            {
                while (SDL_PollEvent(&events))
                {
                    switch (events.type) {

                    case SDL_QUIT:
                        // handling of close button
                        isOpen = false;
                        break;

                    case SDL_KEYDOWN:
                        // keyboard API for key pressed
                        switch (events.key.keysym.sym) {
                        case SDLK_z:
                            Joueur1.setEtatJoueur(joueur::up);
                            break;
                        case SDLK_s:
                            Joueur1.setEtatJoueur(joueur::down);
                            break;


                        case SDLK_UP:
                            Joueur2.setEtatJoueur(joueur::up);
                            break;
                        case SDLK_DOWN:
                            Joueur2.setEtatJoueur(joueur::down);
                            break;
                        }
                        break;
                    case SDL_KEYUP:
                        switch (events.key.keysym.sym) {
                        case SDLK_z:
                        case SDLK_s:
                            Joueur1.setEtatJoueur(joueur::none);
                            break;
                        case SDLK_UP:
                        case SDLK_DOWN:
                            Joueur2.setEtatJoueur(joueur::none);
                            break;
                        }
                        break;
                    }
                }
                Joueur1.modifPosY();
                Joueur2.modifPosY();
                

                balle.setPlusX(balle.getVX());
                balle.setPlusY(balle.getVY());
                if (balle.getX() > WIDTHSCREEN<int> - balle.getLargeur() || balle.getX() < 0) {
                    balle.setFoisVX(-1); // horiz wall hit
                }
                if (balle.getY() > HEIGHTSCREEN<int> - balle.getHauteur() || balle.getY() < 0) balle.setFoisVY(-1);// vert wall hit
                    if (balle.getX() >= Joueur1.getX() && balle.getX() <= Joueur1.getX() + Joueur1.getLargeur() && balle.getY() >= Joueur1.getY() && balle.getY() <= Joueur1.getY() + Joueur1.getHauteur()) {
                        // paddle hit
                        int CentreJoueur1 = Joueur1.getY() + (Joueur1.getHauteur() / 2);
                        int d = CentreJoueur1 - balle.getY();
                        balle.setPlusVY(d * -0.1); // here's the trick
                        balle.setFoisVX(-1);
                    }
                    if (balle.getX() >= Joueur2.getX() - 10 && balle.getX() <= Joueur2.getX() + Joueur2.getLargeur() && balle.getY() >= Joueur2.getY() && balle.getY() <= Joueur2.getY() + Joueur2.getHauteur()) {
                        // paddle hit
                        int CentreJoueur2 = Joueur2.getY() + (Joueur2.getHauteur() / 2);
                        int d2 = CentreJoueur2 - balle.getY();
                        balle.setPlusVY(d2 * -0.1); // here's the trick
                        balle.setFoisVX(-1);
                    }

                    if (balle.getX() > WIDTHSCREEN<int> -balle.getLargeur()) {
                        scoreJoueur.setScoreJ1();
                        balle.setVX(5);
                        balle.setVY(0);
                        balle.setX(WIDTHSCREEN<int> / 2);
                        balle.setY(HEIGHTSCREEN<int> / 2);
                        Joueur1.setY(HEIGHTSCREEN<int> / 2);
                        Joueur2.setY(HEIGHTSCREEN<int> / 2);
                        printf("Le joueur 1 a : %d points\n", scoreJoueur.getScoreJ1());
                    }
                    if (balle.getX() < 0) {
                        scoreJoueur.setScoreJ2();
                        balle.setVX(-5);
                        balle.setVY(0);
                        balle.setX(WIDTHSCREEN<int> / 2);
                        balle.setY(HEIGHTSCREEN<int> / 2);
                        Joueur1.setY(HEIGHTSCREEN<int> / 2);
                        Joueur2.setY(HEIGHTSCREEN<int> / 2);

                        printf("Le joueur 2 a : %d points\n", scoreJoueur.getScoreJ2());
                    }



                if (Joueur1.getY() == 0) {
                    Joueur1.setDownY(15);
                }
                if (Joueur1.getY() >= HEIGHTSCREEN<int> - Joueur1.getHauteur()) {
                    Joueur1.setUpY(15);
                }
                if (Joueur2.getY() == 0) {
                    Joueur2.setDownY(15);
                }
                if (Joueur2.getY() >= HEIGHTSCREEN<int> -Joueur2.getHauteur()) {
                    Joueur2.setUpY(15);
                }
                
                Joueur1.draw(pRenderer);
                Joueur2.draw(pRenderer);
                balle.draw(pRenderer);
                SDL_RenderPresent(pRenderer);
                SDL_SetRenderDrawColor(pRenderer, 0, 0, 0, 255);
                SDL_RenderClear(pRenderer);


                SDL_Delay(1000 / 60);
            }
        }
        else
        {
            fprintf(stderr, "Erreur de création de la fenêtre: %s\n", SDL_GetError());
        }
    }

    SDL_Quit();

    return 0;
}