#include "Game.h"
#include "GameObject.h"
#include <iostream>

/*INDEX OF GAMESTATE IDS:
 * 0 = INTRO SCREEN
 * 1 = GAME SCREEN
 * 2 = VICTORY SCREEN
 * 3 = GAME OVER SCREEN
 * 4 = LEVEL SELECT
 * 5 = HIGH SCORE
 * 6 = INSTRUCTIONS SCREEN
 * DEFAULT = ERROR SCREEN*/


Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{

  //initialise all visual assets

  if (!font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "ERROR LOADING FONT";
  }

  titleText.setString("ANGRY BIRDS");
  titleText.setFont(font);
  titleText.setCharacterSize(100);
  titleText.setFillColor(red);
  titleText.setPosition(500, 80);

  levelSelectText.setString(">>LEVEL SELECT<<");
  levelSelectText.setFont(font);
  levelSelectText.setCharacterSize(50);
  levelSelectText.setFillColor(red);
  levelSelectText.setPosition(650, 500);

  instructionsText.setString("  INSTRUCTIONS");
  instructionsText.setFont(font);
  instructionsText.setCharacterSize(50);
  instructionsText.setFillColor(red);
  instructionsText.setPosition(650, 640);

  quitText.setString("  QUIT");
  quitText.setFont(font);
  quitText.setCharacterSize(50);
  quitText.setFillColor(red);
  quitText.setPosition(750, 780);

  instructionScreenText.setString( "CLICK AND DRAG BEHIND THE BIRDS TO AIM THEM\n"
                                  "AND RELEASE TO FIRE!\n\n"
                                  "YELLOW BIRDS SHOOT FORWARD WHEN YOU PRESS ENTER AS THEY FLY!\n"
                                  "BLUE BIRDS SHOOT STRAIGHT DOWN WHEN YOU PRESS ENTER!\n\n"
                                  "DEFEAT ALL THE PIGS TO WIN.\n\n"
                                  "YOU LOSE WHEN YOU RUN OUT OF BIRDS.\n\n"
                                  "GOOD LUCK!\n\n"
                                  "(PRESS SPACE TO RETURN)");
  instructionScreenText.setFont(font);
  instructionScreenText.setCharacterSize(50);
  instructionScreenText.setFillColor(red);
  instructionScreenText.setPosition(100, 150);

  scoreText.setString("SCORE: 0");
  scoreText.setFont(font);
  scoreText.setCharacterSize(50);
  scoreText.setFillColor(red);
  scoreText.setPosition(0, 0);

  gameOverText.setString("GAME OVER!\n\n"
                         "PRESS SPACE TO RESTART.\n\n"
                         "PRESS ESC TO QUIT.");
  gameOverText.setFont(font);
  gameOverText.setCharacterSize(70);
  gameOverText.setFillColor(red);
  gameOverText.setPosition(300, 300);

  victoryScreenText.setString("CONGRATULATIONS!\n\n");
  victoryScreenText.setFont(font);
  victoryScreenText.setCharacterSize(70);
  victoryScreenText.setFillColor(red);
  victoryScreenText.setPosition(300, 150);

  levelSelectScreenText.setString("LEVEL SELECTION");
  levelSelectScreenText.setFont(font);
  levelSelectScreenText.setCharacterSize(50);
  levelSelectScreenText.setFillColor(red);
  levelSelectScreenText.setPosition(650, 150);

  level1Text.setString(">>LEVEL 1<<");
  level1Text.setFont(font);
  level1Text.setCharacterSize(50);
  level1Text.setFillColor(red);
  level1Text.setPosition(650, 500);

  level2Text.setString("    LEVEL 2");
  level2Text.setFont(font);
  level2Text.setCharacterSize(50);
  level2Text.setFillColor(red);
  level2Text.setPosition(650, 640);

  level3Text.setString("    LEVEL 3");
  level3Text.setFont(font);
  level3Text.setCharacterSize(50);
  level3Text.setFillColor(red);
  level3Text.setPosition(650, 780);

  level4Text.setString("    LEVEL 4");
  level4Text.setFont(font);
  level4Text.setCharacterSize(50);
  level4Text.setFillColor(red);
  level4Text.setPosition(650, 920);

  background.initialiseSprite(backgroundTexture,  "/Users/josephkhan/Desktop/games_in_cpp/angry-birds-2020-JosephZKhan/Data/Images/backgroundField.jpg");
  background.scaleSprite(2, 2);

  marker.initialiseSprite(markerTexture, "/Users/josephkhan/Desktop/games_in_cpp/angry-birds-2020-JosephZKhan/Data/Images/marker.png");

  return true;
}

void Game::update(float dt)
{
  switch (gameState)
  {
      //if on intro screen:
    case 0:
      return;

      //if on game screen:
    case 1:
      //if the bird has taken aim and the mouse has been released
      if (birds[birdsListIndex].drawMarker)
      {
        if (!theMouseIsClicked)
        {
          //launch the bird
          birds[birdsListIndex].setBirdMoving(true);
        }
      }

      //iterate through all pigs in the level
      for (int count{ 0 }; count <= pigsInLevel; ++count)
      {
        // collision processing
        if (birds[birdsListIndex].getIsMoving())
        {
          if (pigs[count].collide(
                birds[birdsListIndex].getSpriteX(),
                birds[birdsListIndex].getSpriteY(),
                birds[birdsListIndex].getSpritePointer()->getGlobalBounds().width,
                birds[birdsListIndex]
                  .getSpritePointer()
                  ->getGlobalBounds()
                  .height))
          {
            // deplete a pig's health
            if (!pigs[count].getIsDead())
            {
              pigs[count].depletePigHealth();

              // kill a pig if its health reaches 0
              if (pigs[count].getPigHealth() <= 0)
              {
                pigs[count].die();
                pigsAliveInLevel -= 1;
                Game::addScore(125);

                // update the game state to victory when all pigs are dead
                if (pigsAliveInLevel <= 0)
                {
                  gameState = 2;
                }


              }

              birds[birdsListIndex].die();
            }
          }

          // update the game logic when a bird dies
          if (birds[birdsListIndex].getIsDead())
          {
            birdsAliveInLevel -= 1;
            birdsListIndex++;
          }



          // update the game state to loss when all birds are dead
          if (birdsAliveInLevel <= 0)
          {
            //std::cout << birdsAliveInLevel;
            gameState = 3;
          }
        }
      }

      //bird moving logic
      if (birds[birdsListIndex].getIsMoving())
      {
        birds[birdsListIndex].moveBird();

        //logic to convert the position calculated from the suvat equations
        //t0 the equivalent position in the birds' trajectory
        float temp1 = birds[birdsListIndex].horizontal.s + originPosX;
        float temp2 = birds[birdsListIndex].vertical.s + originPosY;
        float temp3 = (window.getSize().y - temp2);
        //float temp4 = bird's saved Y position when enter is pressed - launchPosY
        float temp4 = birds[birdsListIndex].savedYPos - originPosY;
        birds[birdsListIndex].getSpritePointer()->setPosition(temp1, temp3);
        //if bird type = 2 and enter is pressed
        //move up by temp4
        if (birds[birdsListIndex].getBirdType() == 2)
        {
          if(birds[birdsListIndex].getIsMoving() and birds[birdsListIndex].isShootingDown)
          {
            birds[birdsListIndex].getSpritePointer()->move(0, temp4);
          }
        }


        //kill bird if it goes offscreen
        if (birds[birdsListIndex].getSpritePointer()->getPosition().y >= window.getSize().y)
        {
          birds[birdsListIndex].die();
        }

        if (birds[birdsListIndex].getSpritePointer()->getPosition().x >= window.getSize().x)
        {
          birds[birdsListIndex].die();
        }
      }

      // logic to calculate the new position of the marker
      if (theMouseIsClicked)
      {
        float temp1 = originPosX - sf::Mouse::getPosition(window).x;
        float temp2 =
          originPosY - (window.getSize().y - sf::Mouse::getPosition(window).y);

        if (temp1 <= originPosX and temp2 <= originPosY)

        {
          birds[birdsListIndex].drawMarker = true;

          marker.setSpritePosition(
            sf::Mouse::getPosition(window).x - marker.getSpritePointer()->getGlobalBounds().width / 2, sf::Mouse::getPosition(window).y - marker.getSpritePointer()->getGlobalBounds().height / 2);

          //multiply the bird's initial velocity by the mouse's distance from the origin point
          birds[birdsListIndex].changeAim(
            temp1 / originPosX, temp2 / originPosY);
        }
      }
      return;

      //if on victory screen:
    case 2:
      return;

      //if on game over screen:
    case 3:
      //std::cout << "Game over!\n";
      return;

      //if on level select screen:
    case 4:
      return;

      //if on high score screen:
    case 5:
      return;

      //if on instructions screen:
    case 6:
      return;

      //otherwise, on error screen:
    default:
      std::cout << "Optional error screen!";
  }

}

void Game::render()
{
  switch (gameState)
  {
    //if on intro screen:
    case 0:
      //render assets
      window.draw(*background.getSpritePointer());
      window.draw(titleText);
      window.draw(levelSelectText);
      window.draw(instructionsText);
      window.draw(quitText);
      return;

      //if on game screen:
    case 1:
      //render assets
      window.draw(*background.getSpritePointer());
      window.draw(scoreText);

      //render birds and pigs using for loops
      for (int count{ 0 }; count <= birdsInLevel; ++count)
      {

        if (!birds[birdsInLevel - count].getIsDead())
        {
          window.draw(*birds[birdsInLevel - count].getSpritePointer());
        }

      }

      for (int count{ 0 }; count <= pigsInLevel; ++count)
      {
        if (!pigs[count].getIsDead())
        {
          window.draw(*pigs[count].getSpritePointer());
        }
      }

      //render marker if appropriate
      if(birds[birdsListIndex].drawMarker)
      {
        if (theMouseIsClicked)
        {
          window.draw(*marker.getSpritePointer());
        }
      }
      return;

      //if on victory screen:
    case 2:
      //render assets
      window.draw(*background.getSpritePointer());
      window.draw(victoryScreenText);
      return;

      //if on game over screen:
    case 3:
      //render assets
      window.draw(*background.getSpritePointer());
      window.draw(gameOverText);
      return;

      //if on level select screen:
    case 4:
      //render assets
      window.draw(*background.getSpritePointer());
      window.draw(levelSelectScreenText);
      window.draw(level1Text);
      window.draw(level2Text);
      window.draw(level3Text);
      window.draw(level4Text);
      return;

      //if on high score screen:
    case 5:
      return;

      //if on instructions screen:
    case 6:
      //render assets
      window.draw(*background.getSpritePointer());
      window.draw(instructionScreenText);
      return;

      //otherwise, on error screen:
    default:
      std::cout << "Optional error screen!";
  }


}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
  switch (gameState)
  {
    //if on intro screen:
    case 0:
      return;

      //if on game screen:
    case 1:
      //if the current bird is alive, but not yet moving
      if (!birds[birdsListIndex].getIsMoving() and !birds[birdsListIndex].getIsDead())
      {
        //if the left mouse button has been clicked
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
          theMouseIsClicked = true;
        }

        else
        {
          birds[birdsListIndex].drawMarker = false;
        }
      }
      return;

      //if on victory screen:
    case 2:
      return;

      //if on game over screen:
    case 3:
      return;

      //if on level select screen:
    case 4:
      return;

      //if on high score screen:
    case 5:
      return;

      //if on instructions screen:
    case 6:
      return;

      //otherwise, on error screen:
    default:
      std::cout << "Optional error screen!";
  }


}


void Game::mouseReleased(sf::Event event){
  switch (gameState)
  {
    case 0:
      return;

    case 1:
      theMouseIsClicked = false;
  }
}


void Game::keyPressed(sf::Event event, float dt)
{
  //ensure the game window closes whenever the player presses Escape
  if (event.key.code == sf::Keyboard::Escape)
  {
    window.close();
  }
  switch (gameState)
  {
    //if on intro screen:
    case 0:

      //when the player selects a menu option with enter
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
      {
        switch (introMenuIndex)
        {
          //go to level selection screen if player selects 'LEVEL SELECT'
          case 0:
            gameState = 4;
            return;

          //go to instructions screen if player selects instructions
          case 1:
            gameState = 6;
            return;

          //close window if the player selects quit
          case 2:
            window.close();
            return;

          default:
            gameState = 1;
        }
      }

      //handle menu navigation up and down
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
      {
        introMenuIndex -= 1;
      }

      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      {
        introMenuIndex += 1;
      }

      //prevent introMenuIndex from going out of range
      if (introMenuIndex < 0)
      {
        introMenuIndex = 2;
      }

      else if (introMenuIndex > 2)
      {
        introMenuIndex = 0;
      }

      //update the menu after a player may have changed their selection
      switch (introMenuIndex)
      {
        case 0:
          levelSelectText.setString(">>LEVEL SELECT<<");
          instructionsText.setString("  INSTRUCTIONS");
          quitText.setString("  QUIT");
          return;

        case 1:
          levelSelectText.setString("  LEVEL SELECT");
          instructionsText.setString(">>INSTRUCTIONS<<");
          quitText.setString("  QUIT");
          return;

        case 2:
          levelSelectText.setString("  LEVEL SELECT");
          instructionsText.setString("  INSTRUCTIONS");
          quitText.setString(">>QUIT<<");
          return;
      }

      return;

      //if on game screen:
    case 1:

      //fire the bird if it is alive and has been aimed
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
      {
        /*if (birds[birdsListIndex].drawMarker)
        {
          birds[birdsListIndex].setBirdMoving(true);
        }*/
      }

      //activate birds' special abilities upon enter
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
      {
        if (birds[birdsListIndex].getIsMoving() and !birds[birdsListIndex].getIsDead() and birds[birdsListIndex].canShootForward)
        {
          if (birds[birdsListIndex].getBirdType() == 1)
          {
            birds[birdsListIndex].isShootingForward = true;
          }

          if (birds[birdsListIndex].getBirdType() == 2)
          {
            birds[birdsListIndex].isShootingDown = true;

            //save y position
            birds[birdsListIndex].savedYPos = birds[birdsListIndex].getSpriteY();
          }
        }
      }
      return;

      //if on victory screen:
    case 2:
      //restart game when space is pressed
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
      {
        Game::restart();
      }
      return;

      //if on game over screen:
    case 3:
      //restart game when space is pressed
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
      {
        Game::restart();
      }
      return;

      //if on level select screen:
    case 4:
      //update gamescreen to the appropriate level when enter pressed
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
      {
        gameState = 1;
        switch (levelSelectMenuIndex)
        {
          //go to level selection screen if player selects 'LEVEL SELECT'
          case 0:
            initLevel1();
            return;

            //go to instructions screen if player selects instructions
          case 1:
            levelIndex = 1;
            initLevel2();
            return;

            //close window if the player selects quit
          case 2:
            levelIndex = 2;
            initLevel3();
            return;

          case 3:
            levelIndex = 3;
            initLevel4();

          default:
            gameState = 1;

        }
      }

      //handle menu navigation up and down
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
      {
        levelSelectMenuIndex -= 1;
      }

      else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
      {
        levelSelectMenuIndex += 1;
      }

      //prevent levelSelectMenuIndex from going out of range
      if (levelSelectMenuIndex < 0)
      {
        levelSelectMenuIndex = 3;
      }

      else if (levelSelectMenuIndex > 3)
      {
        levelSelectMenuIndex = 0;
      }

      //update the menu after a player may have changed their selection
      switch (levelSelectMenuIndex)
      {
        case 0:
          level1Text.setString(">>LEVEL 1<<");
          level2Text.setString("    LEVEL 2");
          level3Text.setString("    LEVEL 3");
          level4Text.setString("    LEVEL 4");
          return;

        case 1:
          level1Text.setString("    LEVEL 1");
          level2Text.setString(">>LEVEL 2<<");
          level3Text.setString("    LEVEL 3");
          level4Text.setString("    LEVEL 4");
          return;

        case 2:
          level1Text.setString("    LEVEL 1");
          level2Text.setString("    LEVEL 2");
          level3Text.setString(">>LEVEL 3<<");
          level4Text.setString("    LEVEL 4");
          return;

        case 3:
          level1Text.setString("    LEVEL 1");
          level2Text.setString("    LEVEL 2");
          level3Text.setString("    LEVEL 3");
          level4Text.setString(">>LEVEL 4<<");
      }

      return;

      //if on high score screen:
    case 5:
      return;

      //if on instructions screen:
    case 6:
      //return to menu when the space key is pressed
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
      {
        gameState = 0;
        introMenuIndex = 0;
      }
      return;

      //otherwise, on error screen:
    default:
      std::cout << "Optional error screen!";
  }
}

void Game::addScore(int newPoints){
  //add points to score
  score += newPoints;

  //update the score string
  std::string scoreString = std::to_string(score * (birdsAliveInLevel + 1));
  scoreText.setString("SCORE: " + scoreString);
  victoryScreenText.setString("CONGRATULATIONS!\n\n"
                              "YOU BEAT LEVEL " + std::to_string(levelIndex + 1) + "\n\n"
                                                           " YOU GOT " + scoreString + " POINTS\n\n"
                                            "PRESS SPACE TO RESTART\n\n"
                                            "PRESS ESC TO QUIT");
}

void Game::restart(){

  //reset all variables to default values
  playerRestart = false;
  levelSelectMenuIndex = 0;
  levelIndex = 0;
  gameState = 0;
  Game::addScore(-score);
  birdsListIndex = 0;
  birdsAliveInLevel = birdsInLevel + 1;
  pigsAliveInLevel = pigsInLevel + 1;
  for (int count{ 0 }; count <= birdsInLevel; ++count)
  {
    birds[count].resurrect();
    birds[count].setSpritePosition(originPosX, window.getSize().y - originPosY);
    birds[count].horizontal.t = 0;
    birds[count].horizontal.s = 0;
    birds[count].horizontal.u = 25;
    birds[count].vertical.t = 0;
    birds[count].vertical.s = 0;
    birds[count].vertical.a = -0.6;
    birds[count].vertical.u = 50;
    birds[count].setBirdMoving(false);
    birds[count].isShootingForward = false;
    birds[count].isShootingDown = false;
    birds[count].drawMarker = false;
  }

  for (int count{ 0 }; count <= pigsInLevel; ++count)
  {
    pigs[count].resurrect();
    pigs[count].setPigHealth(1);
    if (pigs[count].getPigType() == 1)
    {
      pigs[count].setPigHealth(3);
      pigs[count].initialiseSprite(pigs[count].fancyPigHealthyTexture, pigs[count].pigImageList[1]);
    }
  }

  level1Text.setString(">>LEVEL 1<<");
  level2Text.setString("    LEVEL 2");
  level3Text.setString("    LEVEL 3");
  level4Text.setString("    LEVEL 4");

}

//init function for different levels

void Game::initLevel1(){

  birdsInLevel = 5;
  pigsInLevel = 2;
  birdsAliveInLevel = birdsInLevel + 1;
  pigsAliveInLevel = pigsInLevel + 1;

  //birds are red by default

  for (int count{ 0 }; count <= maxBirds; ++count)
  {
    birds[count].setBirdType(0);
  }

  //pigs are normal by default

  for (int count{ 0 }; count <= maxPigs; ++count)
  {
    pigs[count].setPigType(0);
    pigs[count].setPigHealth(1);
  }

  //initialise bird and pig sprites

  for (int count{ 0 }; count <= maxBirds; ++count)
  {
    birds[count].initialiseSprite(birds[count].redBirdTexture, birds[count].birdImageNames[0]);

    if (birds[count].getBirdType() == 1)
    {
      birds[count].initialiseSprite(birds[count].yellowBirdTexture, birds[count].birdImageNames[1]);
    }

    birds[count].initialiseSpritePosition(originPosX, window.getSize().y - originPosY);
  }

  for (int count{ 0 }; count <= maxPigs; ++count)
  {
    pigs[count].initialiseSprite(pigs[count].normalPigTexture, pigs[count].pigImageList[0]);

    if (pigs[count].getPigType() == 1)
    {
      pigs[count].initialiseSprite(pigs[count].fancyPigHealthyTexture, pigs[count].pigImageList[1]);
    }
  }

  //set individual positions of pigs

  pigs[0].initialiseSpritePosition(1200, 500);
  pigs[1].initialiseSpritePosition(1000, 500);
  pigs[2].initialiseSpritePosition(800, 500);
}

void Game::initLevel2(){

  birdsInLevel = 6;
  pigsInLevel = 2;
  birdsAliveInLevel = birdsInLevel + 1;
  pigsAliveInLevel = pigsInLevel + 1;

  for (int count{ 0 }; count <= maxBirds; ++count)
  {
    birds[count].setBirdType(0);
  }

  for (int count{ 0 }; count <= maxPigs; ++count)
  {
    pigs[count].setPigType(0);
    pigs[count].setPigHealth(1);
  }

  birds[2].setBirdType(1);
  birds[5].setBirdType(1);



  pigs[2].setPigType(1);
  pigs[2].setPigHealth(3);

  for (int count{ 0 }; count <= maxBirds; ++count)
  {
    birds[count].initialiseSprite(birds[count].redBirdTexture, birds[count].birdImageNames[0]);

    if (birds[count].getBirdType() == 1)
    {
      birds[count].initialiseSprite(birds[count].yellowBirdTexture, birds[count].birdImageNames[1]);
    }

    birds[count].initialiseSpritePosition(originPosX, window.getSize().y - originPosY);
  }

  for (int count{ 0 }; count <= maxPigs; ++count)
  {
    pigs[count].initialiseSprite(pigs[count].normalPigTexture, pigs[count].pigImageList[0]);

    if (pigs[count].getPigType() == 1)
    {
      pigs[count].initialiseSprite(pigs[count].fancyPigHealthyTexture, pigs[count].pigImageList[1]);
    }
  }

  pigs[0].initialiseSpritePosition(1200, 1000);
  pigs[1].initialiseSpritePosition(1000, 675);
  pigs[2].initialiseSpritePosition(1200, 215);
}

void Game::initLevel3(){
  birdsInLevel = 15;
  pigsInLevel = 8;
  birdsAliveInLevel = birdsInLevel + 1;
  pigsAliveInLevel = pigsInLevel + 1;

  for (int count{ 0 }; count <= maxBirds; ++count)
  {
    birds[count].setBirdType(0);
  }

  for (int count{ 0 }; count <= maxPigs; ++count)
  {
    pigs[count].setPigType(0);
    pigs[count].setPigHealth(1);
  }

  pigs[1].setPigType(1);
  pigs[1].setPigHealth(3);

  pigs[3].setPigType(1);
  pigs[3].setPigHealth(3);

  pigs[5].setPigType(1);
  pigs[5].setPigHealth(3);


  for (int count{ 0 }; count <= maxBirds; ++count)
  {
    birds[count].setBirdType(1);
    birds[count].initialiseSprite(birds[count].redBirdTexture, birds[count].birdImageNames[0]);

    if (birds[count].getBirdType() == 1)
    {
      birds[count].initialiseSprite(birds[count].yellowBirdTexture, birds[count].birdImageNames[1]);
    }

    birds[count].initialiseSpritePosition(originPosX, window.getSize().y - originPosY);
  }

  for (int count{ 0 }; count <= maxPigs; ++count)
  {
    pigs[count].initialiseSprite(pigs[count].normalPigTexture, pigs[count].pigImageList[0]);

    if (pigs[count].getPigType() == 1)
    {
      pigs[count].initialiseSprite(pigs[count].fancyPigHealthyTexture, pigs[count].pigImageList[1]);
    }
  }

  pigs[0].initialiseSpritePosition(1200, 450);
  pigs[1].initialiseSpritePosition(1200, 600);
  pigs[2].initialiseSpritePosition(1200, 750);
  pigs[3].initialiseSpritePosition(1400, 450);
  pigs[4].initialiseSpritePosition(1400, 600);
  pigs[5].initialiseSpritePosition(1400, 750);
  pigs[6].initialiseSpritePosition(1600, 450);
  pigs[7].initialiseSpritePosition(1600, 600);
  pigs[8].initialiseSpritePosition(1600, 750);
}

void Game::initLevel4(){
  birdsInLevel = 10;
  pigsInLevel = 7;
  birdsAliveInLevel = birdsInLevel + 1;
  pigsAliveInLevel = pigsInLevel + 1;

  birds[1].setBirdType(2);
  birds[2].setBirdType(2);
  birds[4].setBirdType(2);
  birds[7].setBirdType(2);

  for (int count{ 0 }; count <= maxBirds; ++count)
  {
    if (birds[count].getBirdType() == 0)
    {
      birds[count].initialiseSprite(birds[count].redBirdTexture, birds[count].birdImageNames[0]);
    }

    if (birds[count].getBirdType() == 1)
    {
      birds[count].initialiseSprite(birds[count].yellowBirdTexture, birds[count].birdImageNames[1]);
    }

    if (birds[count].getBirdType() == 2)
    {
      birds[count].initialiseSprite(birds[count].blueBirdTexture, birds[count].birdImageNames[2]);
    }

    birds[count].initialiseSpritePosition(originPosX, window.getSize().y - originPosY);
  }

  for (int count{ 0 }; count <= maxPigs; ++count)
  {
    pigs[count].setPigType(0);
    pigs[count].setPigHealth(1);

    pigs[count].initialiseSprite(pigs[count].normalPigTexture, pigs[count].pigImageList[0]);

    if (pigs[count].getPigType() == 1)
    {
      pigs[count].initialiseSprite(pigs[count].fancyPigHealthyTexture, pigs[count].pigImageList[1]);
    }
  }

  pigs[0].setSpritePosition(300, 1000);
  pigs[1].setSpritePosition(500, 1000);
  pigs[2].setSpritePosition(700, 1000);
  pigs[3].setSpritePosition(900, 1000);
  pigs[4].setSpritePosition(1100, 1000);
  pigs[5].setSpritePosition(1300, 1000);
  pigs[6].setSpritePosition(1500, 1000);
  pigs[7].setSpritePosition(1700, 1000);
}
