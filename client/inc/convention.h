#ifndef CPLAYER_H_
#define CPLAYER_H_

/**
 * \file convention.h
 * \brief Ce fichier sert à définir les conventions de documentation
 * \author Moi
 * \version 0.1
 */
#include <string>
#include <list>

/** \namespace player
 * 
 * espace de nommage regroupant les outils composants 
 * un lecteur audio
 */
namespace player
{
  /** \class CPlayer
   * \brief classe representant le lecteur
   *
   *  La classe gere la lecture d'une liste de morceaux
   */
  class CPlayer
  {
  private:
    std::list<string> m_listSongs; /**< Liste des morceaux*/
    std::list<string>::iterator m_currentSong; /**< Morceau courant */
                                                

  public:
    /**
     *  \brief Constructeur
     *
     *  Constructeur de la classe CPlayer
     *
     *  \param listSongs : liste initial des morceaux
     */
    CPlayer(std::list<string> listSongs);

    /**
     *  \brief Destructeur
     *
     *  Destructeur de la classe CPlayer
     */
    virtual ~CPlayer();

  public:
    /**
     *  \brief Ajout d'un morceau
     *
     *  Methode qui permet d'ajouter un morceau a liste de
     *  lecture
     *
     *  \param strSong : le morceau a ajouter
     *  \return true si morceau deja present dans la liste,
     *  false sinon
     */
    bool add(std::string strSong);

    /**
     *  \brief Morceau suivant
     *
     *  Passage au morceau suivant
     */
  
  };
};

#endif
