#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>

#include "Monopoly.h"

using namespace sf;
using namespace std;

int main() {
  Monopoly game;

  // Standard Font
  Font stdFont;
  stdFont.loadFromFile("fonts/Montserrat-Black.ttf");

  // Basic window 
  RenderWindow window(VideoMode(1280, 720), L"Monopoly Game", Style::Default | Style::Titlebar);
  window.setVerticalSyncEnabled(true);

  // Title icon
  Image title_icon;
  title_icon.loadFromFile("elements/monopoly-logo.png");
  window.setIcon(551, 292, title_icon.getPixelsPtr());

  // Background
  Texture background_texture;
  background_texture.loadFromFile("elements/background.png");
  RectangleShape background_screen(Vector2f(1280.0f, 720.0f));
  background_screen.setTexture(&background_texture);

  // Start button
  Texture start_button_texture;
  start_button_texture.loadFromFile("elements/start-game.png");
  RectangleShape start_button(Vector2f(320.0f, 120.0f));
  start_button.setTexture(&start_button_texture);
  start_button.setPosition(Vector2f(470.0f, 400.0f));

  bool is_game_started = false;

  while (!is_game_started) {
    Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed)
        window.close();



      if (Mouse::isButtonPressed(Mouse::Left)) {
        Vector2f mouse_position = window.mapPixelToCoords(Mouse::getPosition(window));

        FloatRect start_button_bounds = start_button.getGlobalBounds();

        if (start_button_bounds.contains(mouse_position))
          is_game_started = true;

      }
      window.clear();

      window.draw(background_screen);
      window.draw(start_button);

      window.display();
    }
  }

  // Players count selected
  int total_players = -1;
  while (is_game_started && total_players == -1) {
    Event event;
    while (window.pollEvent(event)) {
      if (event.type == Event::Closed)
        window.close();

      // Three_players_card
      Texture three_players_card_texture;
      three_players_card_texture.loadFromFile("elements/3-player-card.png");
      RectangleShape three_players_card(Vector2f(251.0f, 272.0f));
      three_players_card.setTexture(&three_players_card_texture);
      three_players_card.setPosition(sf::Vector2f(389.0f, 200.0f));

      // Four_players_card
      Texture four_players_card_texture;
      four_players_card_texture.loadFromFile("elements/4-player-card.png");
      RectangleShape four_players_card(Vector2f(251.0f, 272.0f));
      four_players_card.setTexture(&four_players_card_texture);
      four_players_card.setPosition(sf::Vector2f(
        three_players_card.getPosition().x + 260, three_players_card.getPosition().y));

      if (Mouse::isButtonPressed(Mouse::Left)) {
        Vector2f mouse_position = window.mapPixelToCoords(Mouse::getPosition(window));

        FloatRect three_players_card_bounds = three_players_card.getGlobalBounds();
        FloatRect four_players_card_bounds = four_players_card.getGlobalBounds();

        if (three_players_card_bounds.contains(mouse_position))
          total_players = 3;

        else if (four_players_card_bounds.contains(mouse_position))
          total_players = 4;
      }
      window.clear();
      window.draw(background_screen);
      window.draw(three_players_card);
      window.draw(four_players_card);
      window.display();
    }
  }

  // Game field
  Texture game_field_texture;
  game_field_texture.loadFromFile("elements/game-field.png");
  RectangleShape game_field(Vector2f(1280.0f, 720.0f));
  game_field.setTexture(&game_field_texture);
  // ****** PRIMARY GAME LOGIC ******
  game.setTotalPlayers(total_players);

    // Files names for all the player pieces

  const char* playerPieceFileName[5] = {

      "elements/player-1.png",
      "elements/player-2.png",
      "elements/player-3.png",
      "elements/player-4.png",
      "elements/player-5.png"

  };

  // Initializing all of the pieces


  int totalPlayers = game.getTotalPlayers();
  game.initializePositions();

  sf::Texture* playerTextures = new sf::Texture[totalPlayers];
  sf::RectangleShape* playerPieces = new sf::RectangleShape[totalPlayers];

  // Setting up all of the textures

  for (int i = 0; i < totalPlayers; i++) {

    playerTextures[i].loadFromFile(playerPieceFileName[i]);
    playerPieces[i].setTexture(&playerTextures[i]);
    playerPieces[i].setSize(sf::Vector2f(20.0f, 20.0f));

    playerTextures[i].setSmooth(true);

  }


  // Dice button for Dice

  sf::Texture diceButtonTexture;
  diceButtonTexture.loadFromFile("elements/dice-button.png");
  sf::RectangleShape diceButton(sf::Vector2f(111.0f, 111.0f));
  diceButton.setPosition(750.0f, 600.0f);
  diceButton.setTexture(&diceButtonTexture);


  // Player Icons

  const char* playerIconTextureImg[5] = {
      "elements/player-icon-1.png",
      "elements/player-icon-2.png",
      "elements/player-icon-3.png",
      "elements/player-icon-4.png",
  };

  sf::Texture* playerIconTexture = new sf::Texture[totalPlayers];
  sf::RectangleShape* playerIcon = new sf::RectangleShape[totalPlayers];
  for (int i = 0; i < totalPlayers; i++) {

    playerIconTexture[i].loadFromFile(playerIconTextureImg[i]);
    playerIcon[i].setTexture(&playerIconTexture[i]);
    playerIcon[i].setPosition(720.0f + (i * 100), 20.0f);
    playerIcon[i].setSize(sf::Vector2f(120.5f, 155.0f));

  }


  // Two dices

  const char* diceTextureImg[6] =
  {
      "elements/dice-1.png",
      "elements/dice-2.png",
      "elements/dice-3.png",
      "elements/dice-4.png",
      "elements/dice-5.png",
      "elements/dice-6.png"

  };


  sf::Texture* diceTexture = new sf::Texture[2];
  diceTexture[0].loadFromFile(diceTextureImg[0]);
  diceTexture[1].loadFromFile(diceTextureImg[1]);

  sf::RectangleShape* dice = new sf::RectangleShape[2];
  for (int i = 0; i < 2; i++) {
    dice[i].setSize(sf::Vector2f(80.0f, 80.f));
    dice[i].setPosition(120.0f + (i * 75), 520.0f);
    dice[i].setTexture(&diceTexture[i]);
    diceTexture[i].setSmooth(true);
  }

  // To handle animation times
  sf::Clock clk;
  sf::Time animInt = sf::seconds(0.5f);
  sf::Time pieceMvtTime = sf::milliseconds(100);

  bool diceAnim = false;

  // To handle pieces movement delay

  int* playerPrevPos = new int[totalPlayers];
  for (int i = 0; i < totalPlayers; i++)
    playerPrevPos[i] = 0;


  // Property Cards Assets (Private)

  sf::Texture cardPanelTexture;
  cardPanelTexture.loadFromFile("elements/prop-cards.png");
  sf::RectangleShape cardPanel(sf::Vector2f(448.0f, 166.0f));
  cardPanel.setPosition(760.0f, 200.0f);
  cardPanel.setTexture(&cardPanelTexture);

  sf::Texture* navButtonTexture = new sf::Texture[2];
  navButtonTexture[0].loadFromFile("elements/float-left-btn.png");
  navButtonTexture[1].loadFromFile("elements/float-right-btn.png");

  sf::RectangleShape* navButton = new sf::RectangleShape[2];
  for (int i = 0; i < 2; i++) {

    navButton[i].setSize(sf::Vector2f(88.0f, 88.0f));
    navButton[i].setTexture(&navButtonTexture[i]);
    navButton[i].setPosition(725.0f + (i * 425.0f), 235.0f);

  }


  // Property Card Assets (Commercial)

  sf::RectangleShape commercialCardPanel(cardPanel);
  commercialCardPanel.setPosition(760.0f, 350.0f);

  sf::RectangleShape* commercialNavButton = new sf::RectangleShape[2];
  for (int i = 0; i < 2; i++) {

    commercialNavButton[i].setSize(sf::Vector2f(88.0f, 88.0f));
    commercialNavButton[i].setTexture(&navButtonTexture[i]);
    commercialNavButton[i].setPosition(725.0f + (i * 425.0f), 390.0f);

  }


  // Private Property Names to iterate through, on cards

  int privatePropertyCardScroll = 0;
  int commercialPropertyCardScroll = 0;

  const char* privatePropertyNames[20] = {

      "IQBAL TOWN A",
      "IQBAL TOWN B",
      "IQBAL TOWN C",

      "JOHAR TOWN A",
      "JOHAR TOWN B",

      "FAISAL TOWN A",
      "FAISAL TOWN B",
      "FAISAL TOWN C",

      "MODEL TOWN A",
      "MODEL TOWN B",
      "MODEL TOWN C",

      "GULBERG II A",
      "GULBERG II B",
      "GULBERG II C",

      "DHA A",
      "DHA B",
      "DHA Y",

      "BAHRIA TOWN A",
      "BAHRIA TOWN B",
      "BAHRIA TOWN C"

  };

  const char* privatePropertyPrices[20] = {

      "250", "300", "400",
      "200", "250",
      "300", "400", "400",
      "800", "850", "2000",
      "1000", "1200", "2500",
      "2000", "2000", "2500",
      "2500", "3000", "3000"

  };

  const char* privatePropertyRents[20] = {

      "60", "70", "100",
      "80", "90",
      "100", "130", "130",
      "200", "250", "500",
      "300", "350", "600",
      "500", "500", "1000",
      "800", "900", "1000"

  };

  int privatePropertySpaces[20] = {

      1, 3, 6, 8,
      9, 11, 13, 14,
      16, 18, 19, 21,
      23, 24, 26, 27,
      29, 31, 32, 34,

  };


  const char* commercialPropertyNames[8] = {

      "METRO ST.",
      "LESCO",
      "BUS ST.",
      "RAILWAY ST.",
      "WASA",
      "ORANGE TRAIN",
      "PTCL",
      "SUI"

  };

  const char* commercialPropertyPrices[8] = {

      "2000",
      "5000",
      "2000",
      "2500",
      "4000",
      "2500",
      "8000",
      "2500"

  };

  const char* commercialPropertyRents[8] = {

      "200",
      "450",
      "200",
      "350",
      "400",
      "350",
      "500",
      "350"

  };

  int commercialPropertySpaces[8] = {

      5, 12, 15, 25,
      28, 35, 37, 39

  };

  // Text for Private Properties

  sf::Font cardFont;
  cardFont.loadFromFile("fonts/Nexa-Light.otf");

  sf::Text* cardTitle = new sf::Text[3];
  for (int i = 0; i < 3; i++) {

    cardTitle[i].setFillColor(sf::Color::Black);
    cardTitle[i].setFont(cardFont);
    cardTitle[i].setCharacterSize(12);
    cardTitle[i].setString(privatePropertyNames[i]);

  }

  cardTitle[0].setPosition(785.0f, 250.0f);
  cardTitle[1].setPosition(925.0f, 250.0f);
  cardTitle[2].setPosition(1070.0f, 250.0f);


  sf::Text* cardPrice = new sf::Text[3];

  for (int i = 0; i < 3; i++) {

    cardPrice[i].setFillColor(sf::Color(26, 188, 156));
    cardPrice[i].setFont(stdFont);
    cardPrice[i].setCharacterSize(12);
    cardTitle[i].setString(privatePropertyPrices[i]);

  }

  cardPrice[0].setPosition(785.0f, cardTitle[0].getPosition().y + 20.0f);
  cardPrice[1].setPosition(925.0f, cardTitle[0].getPosition().y + 20.0f);
  cardPrice[2].setPosition(1070.0f, cardTitle[0].getPosition().y + 20.0f);


  sf::Text* cardRent = new sf::Text[3];
  for (int i = 0; i < 3; i++) {

    cardRent[i].setFillColor(sf::Color(52, 152, 219));
    cardRent[i].setFont(stdFont);
    cardRent[i].setCharacterSize(10);
    cardRent[i].setString(privatePropertyRents[i]);

  }

  cardRent[0].setPosition(785.0f, cardTitle[0].getPosition().y + 40.0f);
  cardRent[1].setPosition(925.0f, cardTitle[0].getPosition().y + 40.0f);
  cardRent[2].setPosition(1070.0f, cardTitle[0].getPosition().y + 40.0f);


  // Colors for Card Owners

  sf::Color** cardOwnerColors = new sf::Color * [6];
  cardOwnerColors[0] = new sf::Color(231, 76, 60);
  cardOwnerColors[1] = new sf::Color(39, 174, 96);
  cardOwnerColors[2] = new sf::Color(52, 152, 219);
  cardOwnerColors[3] = new sf::Color(242, 205, 20);
  cardOwnerColors[4] = new sf::Color(230, 126, 34);
  cardOwnerColors[5] = new sf::Color(52, 73, 94);

  sf::CircleShape* cardOwnerIcon = new sf::CircleShape[3];
  for (int i = 0; i < 3; i++) {

    cardOwnerIcon[i].setRadius(10.0f);
    cardOwnerIcon[i].setPosition(865.0f + (i * 145), 280.0f);
    cardOwnerIcon[i].setFillColor(cardOwnerColors[0][0]);
    cardOwnerIcon[i].setPointCount(50);

  }


  // Property Upgrade options elements

  bool showPropertyUpgradePanel = false;
  int propertySelected = 0;

  sf::Texture cardUpgradeIconTexture;
  cardUpgradeIconTexture.loadFromFile("elements/upgrade-btn.png");

  sf::RectangleShape* cardUpgradeIcon = new sf::RectangleShape[3];
  for (int i = 0; i < 3; i++) {
    cardUpgradeIcon[i].setTexture(&cardUpgradeIconTexture);
    cardUpgradeIcon[i].setSize(sf::Vector2f(13.0f, 13.0f));

  }

  cardUpgradeIcon[0].setPosition(870.0f, 315.0f);
  cardUpgradeIcon[1].setPosition(1015.0f, 315.0f);
  cardUpgradeIcon[2].setPosition(1015.0f + 143.0f, 315.0f);


  sf::Text* mortgageStatus = new sf::Text[3];
  for (int i = 0; i < 3; i++) {

    mortgageStatus[i].setString("M");
    mortgageStatus[i].setCharacterSize(14);
    mortgageStatus[i].setFont(stdFont);
    mortgageStatus[i].setFillColor(sf::Color(149, 165, 166));
    mortgageStatus[i].setPosition(825.0f + (i * 142), 285.0f);

  }



  // Property Upgrade Prompt

  sf::Texture propertyUpgradePromptTexture;
  propertyUpgradePromptTexture.loadFromFile("elements/upgrade-prompt.png");

  sf::Texture upgradePromptCloseTexture;
  upgradePromptCloseTexture.loadFromFile("elements/upgrade-prompt-close.png");

  sf::RectangleShape propertyUpgradePrompt(sf::Vector2f(1280.0f, 720.0f));
  propertyUpgradePrompt.setTexture(&propertyUpgradePromptTexture);
  propertyUpgradePrompt.setPosition(0.0f, 0.0f);

  sf::RectangleShape upgradePromptClose(sf::Vector2f(41.0f, 41.0f));
  upgradePromptClose.setTexture(&upgradePromptCloseTexture);
  upgradePromptClose.setPosition(900.0f, 200.0f);


  sf::Texture addButtonTexture;
  addButtonTexture.loadFromFile("elements/upgrade-prompt-add.png");

  sf::RectangleShape** addButton = new sf::RectangleShape * [3];
  for (int i = 0; i < 3; i++) {

    addButton[i] = new sf::RectangleShape[2];

    for (int j = 0; j < 2; j++) {

      addButton[i][j].setTexture(&addButtonTexture);
      addButton[i][j].setSize(sf::Vector2f(70.0f, 70.0f));
      addButton[i][j].setPosition(500.0f + (j * 300.0f), 220.0f + (i * 120.0f));

    }

  }

  const char* upgradePromptIconsImg[6] = {

      "elements/upgrade-prompt-house.png",
      "elements/upgrade-prompt-wifi.png",


      "elements/upgrade-prompt-shop.png",
      "elements/upgrade-prompt-elec.png",



      "elements/upgrade-prompt-hotel.png",
      "elements/upgrade-prompt-gas.png",

  };

  sf::Texture** upgradePromptIconsTexture = new sf::Texture * [3];
  for (int i = 0; i < 3; i++) {

    upgradePromptIconsTexture[i] = new sf::Texture[2];

    for (int j = 0; j < 2; j++) {

      upgradePromptIconsTexture[i][j].loadFromFile(upgradePromptIconsImg[(2 * i) + j]);
      upgradePromptIconsTexture[i][j].setSmooth(true);

    }

  }


  sf::RectangleShape** upgradePromptIcons = new sf::RectangleShape * [3];
  for (int i = 0; i < 3; i++) {

    upgradePromptIcons[i] = new sf::RectangleShape[2];

    for (int j = 0; j < 2; j++) {

      upgradePromptIcons[i][j].setTexture(&upgradePromptIconsTexture[i][j]);
      upgradePromptIcons[i][j].setSize(sf::Vector2f(80.0f, 80.0f));
      upgradePromptIcons[i][j].setPosition(400.0f + (j * 300.0f), 200.0f + (i * 120.0f));

    }

  }



  // Text for commercial properties

  sf::Text* commercialCardTitle = new sf::Text[3];
  for (int i = 0; i < 3; i++) {
    commercialCardTitle[i].setFillColor(sf::Color::Black);
    commercialCardTitle[i].setFont(cardFont);
    commercialCardTitle[i].setCharacterSize(12);
    commercialCardTitle[i].setString(commercialPropertyNames[i]);
  }

  commercialCardTitle[0].setPosition(785.0f, 400.0f);
  commercialCardTitle[1].setPosition(925.0f, 400.0f);
  commercialCardTitle[2].setPosition(1070.0f, 400.0f);


  sf::Text* commercialCardPrice = new sf::Text[3];

  for (int i = 0; i < 3; i++) {

    commercialCardPrice[i].setFillColor(sf::Color(230, 126, 34));
    commercialCardPrice[i].setFont(stdFont);
    commercialCardPrice[i].setCharacterSize(12);
    commercialCardPrice[i].setString(commercialPropertyPrices[i]);

  }

  commercialCardPrice[0].setPosition(785.0f, commercialCardTitle[0].getPosition().y + 20.0f);
  commercialCardPrice[1].setPosition(925.0f, commercialCardTitle[0].getPosition().y + 20.0f);
  commercialCardPrice[2].setPosition(1070.0f, commercialCardTitle[0].getPosition().y + 20.0f);


  sf::Text* commercialCardRent = new sf::Text[3];
  for (int i = 0; i < 3; i++) {

    commercialCardRent[i].setFillColor(sf::Color(211, 84, 0));
    commercialCardRent[i].setFont(stdFont);
    commercialCardRent[i].setCharacterSize(10);
    commercialCardRent[i].setString(commercialPropertyRents[i]);

  }

  commercialCardRent[0].setPosition(785.0f, commercialCardTitle[0].getPosition().y + 40.0f);
  commercialCardRent[1].setPosition(925.0f, commercialCardTitle[0].getPosition().y + 40.0f);
  commercialCardRent[2].setPosition(1070.0f, commercialCardTitle[0].getPosition().y + 40.0f);

  sf::CircleShape* commercialCardOwnerIcon = new sf::CircleShape[3];
  for (int i = 0; i < 3; i++) {

    commercialCardOwnerIcon[i].setRadius(10.0f);
    commercialCardOwnerIcon[i].setPosition(865.0f + (i * 145), 430.0f);
    commercialCardOwnerIcon[i].setFillColor(cardOwnerColors[0][0]);
    commercialCardOwnerIcon[i].setPointCount(50);

  }

  sf::Text* commercialMortgageStatus = new sf::Text[3];
  for (int i = 0; i < 3; i++) {

    commercialMortgageStatus[i].setString("M");
    commercialMortgageStatus[i].setCharacterSize(14);
    commercialMortgageStatus[i].setFont(stdFont);
    commercialMortgageStatus[i].setFillColor(sf::Color(149, 165, 166));
    commercialMortgageStatus[i].setPosition(825.0f + (i * 142), 437.0f);

  }

  // Player Cash Text setup


  sf::Text* playerCash = new sf::Text[totalPlayers];
  for (int i = 0; i < totalPlayers; i++) {

    playerCash[i].setFillColor(sf::Color(26, 188, 156));
    playerCash[i].setFont(stdFont);
    playerCash[i].setCharacterSize(11);

    playerCash[i].setString(to_string(game.getBoard().getPlayers()[i]->getCash()));
    playerCash[i].setPosition(735.f + (i * 100.0f), 125.0f);

  }


  // Turn Display Assets

  sf::Text turnText;
  turnText.setFont(stdFont);
  turnText.setFillColor(sf::Color::Black);
  turnText.setCharacterSize(10);
  turnText.setString("TURN");
  turnText.setPosition(141.0f, 460.0f);

  sf::Texture turnDisplayTexture;
  turnDisplayTexture.loadFromFile("elements/turn-display.png");

  sf::RectangleShape turnDisplay(sf::Vector2f(80.0f, 80.f));
  turnDisplay.setPosition(120.0f, 450.0f);
  turnDisplay.setTexture(&turnDisplayTexture);

  sf::Texture turnDisplayPieceTexture;
  turnDisplayPieceTexture.loadFromFile("elements/player-1.png");

  sf::RectangleShape turnDisplayPiece(sf::Vector2f(30.0f, 30.0f));
  turnDisplayPiece.setTexture(&turnDisplayPieceTexture);
  turnDisplayPiece.setPosition(142.0f, 480.0f);
  turnDisplayPieceTexture.setSmooth(true);



  // Card Upgrades Assets

  sf::Texture** upgradeIconTexture = new sf::Texture * [3];
  for (int i = 0; i < 3; i++)
    upgradeIconTexture[i] = new sf::Texture[2];

  const char* upgradeIconImg[6] = {

      "elements/wifi.png", "elements/wifi-en.png",
      "elements/elec.png", "elements/elec-en.png",
      "elements/gas.png", "elements/gas-en.png"

  };

  for (int i = 0; i < 3; i++) {

    for (int j = 0; j < 2; j++) {

      upgradeIconTexture[i][j].loadFromFile(upgradeIconImg[(2 * i) + j]);

    }

  }

  sf::RectangleShape** upgradeIcon = new sf::RectangleShape * [3];

  for (int i = 0; i < 3; i++) {

    upgradeIcon[i] = new sf::RectangleShape[3];

    for (int j = 0; j < 3; j++) {

      upgradeIcon[i][j].setTexture(&upgradeIconTexture[j][0]);


      upgradeIcon[i][j].setSize(sf::Vector2f(13.0f, 15.0f));

    }

  }

  for (int i = 0; i < 3; i++) {
    upgradeIcon[0][i].setPosition(785.f + (i * 20), 315.0f);
    upgradeIcon[1][i].setPosition(785.f + (i * 20) + 140, 315.0f);
    upgradeIcon[2][i].setPosition(785.f + (i * 20) + 285, 315.0f);
  }


  // Card Building Upgrade Assets
  sf::Texture* buildingIconTextures = new sf::Texture[3];

  buildingIconTextures[0].loadFromFile("elements/house.png");
  buildingIconTextures[1].loadFromFile("elements/shop.png");
  buildingIconTextures[2].loadFromFile("elements/hotel.png");

  sf::RectangleShape** buildingIcon = new sf::RectangleShape * [3];

  for (int i = 0; i < 3; i++) {

    buildingIcon[i] = new sf::RectangleShape[3];

    for (int j = 0; j < 3; j++) {

      buildingIcon[i][j].setTexture(&buildingIconTextures[j]);
      buildingIcon[i][j].setSize(sf::Vector2f(13.0f, 13.0f));

    }

  }


  for (int i = 0; i < 3; i++) {

    buildingIcon[0][i].setPosition(785.f + (i * 42), 225.0f);
    buildingIcon[1][i].setPosition(785.f + (i * 42) + 140, 225.0f);
    buildingIcon[2][i].setPosition(785.f + (i * 42) + 285, 225.0f);

  }


  // Tooltip

  bool tooltipIsVisible = false;
  int iClickedX = 0, iClickedY = 0;

  sf::Texture tooltipTexture;
  tooltipTexture.loadFromFile("elements/tooltip.png");

  sf::RectangleShape tooltip(sf::Vector2f(77.25f, 69.75f));
  tooltip.setTexture(&tooltipTexture);

  sf::Text tooltipText;
  tooltipText.setFillColor(sf::Color::White);
  tooltipText.setCharacterSize(14);
  tooltipText.setFont(stdFont);


  // Property Purchase or Rent Prompt

  sf::Texture boardPromptTexture;
  boardPromptTexture.loadFromFile("elements/property-prompt.png");
  sf::RectangleShape boardPrompt(sf::Vector2f(265.0f, 166.0f));
  boardPrompt.setTexture(&boardPromptTexture);
  boardPrompt.setPosition(240.0f, 280.0f);

  //Buttons for Prompt

  sf::Texture buyButtonTexture;
  buyButtonTexture.loadFromFile("elements/property-prompt-rent.png");

  sf::RectangleShape buyButton(sf::Vector2f(128.0f, 74.0f));
  buyButton.setTexture(&buyButtonTexture);
  buyButton.setPosition(255.0f, 360.0f);

  sf::Texture rentButtonTexture;
  rentButtonTexture.loadFromFile("elements/property-prompt-rent.png");

  sf::RectangleShape rentButton(sf::Vector2f(128.0f, 74.0f));
  rentButton.setTexture(&rentButtonTexture);
  rentButton.setPosition(365.0f, 360.0f);

  // 0 index -> propertyName
  // 1 index -> propertyPrice
  // 2 index -> propertyRent
  // 3 index -> buy
  // 4 index -> sell

  int dealChoice = -1; // 0 for purchase, 1 for rent
  bool showPurchasePrompt = false;
  int onRent = -1;

  sf::Text* promptText = new sf::Text[5];


  for (int i = 0; i < 5; i++) {

    promptText[i].setFont(cardFont);
    promptText[i].setCharacterSize(14);
    promptText[i].setFillColor(sf::Color::Black);

  }

  promptText[0].setString("IQBAL TOWN A");
  promptText[0].setPosition(265.0f, 300.0f);

  promptText[1].setString("ÖÅÍÀ: 30000");
  promptText[1].setPosition(265.0f, 320.0f);
  promptText[1].setFillColor(sf::Color(53, 73, 94));


  promptText[2].setString("ÀÐÅÍÄÀ: 10000");
  promptText[2].setPosition(380.0f, 320.0f);
  promptText[2].setFillColor(sf::Color(53, 73, 94));


  promptText[3].setString("ÊÓÏÈÒÜ");
  promptText[3].setFont(stdFont);
  promptText[3].setPosition(295.0f, 380.0f);
  promptText[3].setFillColor(sf::Color(236, 240, 241));

  promptText[4].setString("ÀÐÅÍÄÀ");
  promptText[4].setFont(stdFont);
  promptText[4].setPosition(400.0f, 380.0f);
  promptText[4].setFillColor(sf::Color(236, 240, 241));


  sf::Text gameWon;
  gameWon.setFont(stdFont);
  gameWon.setCharacterSize(50);
  gameWon.setFillColor(sf::Color::Red);
  gameWon.setPosition(200.0f, 400.0f);
  gameWon.setString("ÈÃÐÀ ÎÊÎÍ×ÅÍÀ!");
  gameWon.setOutlineColor(sf::Color::White);
  gameWon.setOutlineThickness(5);




  while (window.isOpen()) {

    int currInd = game.getBoard().getPlayerByID(game.getBoard().getPreviousTurn())->getPlayerPosition();

    sf::Event evt;
    while (window.pollEvent(evt)) {

      if (evt.type == Event::Closed)
        window.close();

      if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {


        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        sf::FloatRect diceButtonBounds = diceButton.getGlobalBounds();

        sf::FloatRect navBtnLeftBounds = navButton[0].getGlobalBounds();
        sf::FloatRect navBtnRightBounds = navButton[1].getGlobalBounds();

        sf::FloatRect commercialNavBtnLeftBounds = commercialNavButton[0].getGlobalBounds();
        sf::FloatRect commercialNavBtnRightBounds = commercialNavButton[1].getGlobalBounds();


        sf::FloatRect** buildingIconBounds = new sf::FloatRect * [3];
        for (int i = 0; i < 3; i++) {

          buildingIconBounds[i] = new sf::FloatRect[3];

          for (int j = 0; j < 3; j++) {

            buildingIconBounds[i][j] = buildingIcon[i][j].getGlobalBounds();


            if (buildingIconBounds[i][j].contains(mousePos) && !tooltipIsVisible) {

              tooltipIsVisible = true;

              iClickedX = i;
              iClickedY = j;

            }
            else if (buildingIconBounds[i][j].contains(mousePos) && tooltipIsVisible) {

              tooltipIsVisible = false;

            }



          }

        }



        for (int i = 0; i < 3; i++)
          delete[] buildingIconBounds[i];
        delete[] buildingIconBounds;


        // Property Upgrade function tracking

        sf::FloatRect* cardUpgradeIconBounds = new sf::FloatRect[3];
        for (int i = 0; i < 3; i++) {
          cardUpgradeIconBounds[i] = cardUpgradeIcon[i].getGlobalBounds();

          if (cardUpgradeIconBounds[i].contains(mousePos) && !showPropertyUpgradePanel) {

            showPropertyUpgradePanel = true;

            propertySelected = i + privatePropertyCardScroll;


          }
          else if (cardUpgradeIconBounds[i].contains(mousePos) && showPropertyUpgradePanel) {

            showPropertyUpgradePanel = false;

            propertySelected = 0;

          }

        }

        delete[] cardUpgradeIconBounds;



        // Add button functionality

        if (showPropertyUpgradePanel) {
          sf::FloatRect** addButtonBounds = new sf::FloatRect * [3];
          for (int i = 0; i < 3; i++) {

            addButtonBounds[i] = new sf::FloatRect[2];

            for (int j = 0; j < 2; j++) {

              addButtonBounds[i][j] = addButton[i][j].getGlobalBounds();


              if (addButtonBounds[i][j].contains(mousePos)) {

                int ind = privatePropertySpaces[propertySelected];

                game.getBoard().upgradeProperty(ind, i, j);


              }


            }

          }

          for (int i = 0; i < 3; i++)
            delete[] addButtonBounds[i];
          delete[] addButtonBounds;


        }




        // Upgrade Prompt Close Button

        sf::FloatRect upgradePromptCloseBounds = upgradePromptClose.getGlobalBounds();

        if (upgradePromptCloseBounds.contains(mousePos)) {

          showPropertyUpgradePanel = false;

        }



        // Mortgage Prompt

        sf::FloatRect mortgageBtnBounds[3];
        sf::FloatRect commercialMortgageBtnBounds[3];
        for (int i = 0; i < 3; i++) {

          mortgageBtnBounds[i] = mortgageStatus[i].getGlobalBounds();
          commercialMortgageBtnBounds[i] = commercialMortgageStatus[i].getGlobalBounds();

          if (mortgageBtnBounds[i].contains(mousePos)) {

            game.mortgageProperty(privatePropertySpaces[i + privatePropertyCardScroll]);

          }
          else if (commercialMortgageBtnBounds[i].contains(mousePos)) {

            game.mortgageProperty(commercialPropertySpaces[i + commercialPropertyCardScroll]);

          }


        }




        // Purchase prompt

        sf::FloatRect buyButtonBounds = buyButton.getGlobalBounds();
        sf::FloatRect rentButtonBounds = rentButton.getGlobalBounds();

        bool isValidDeal = false;

        if (buyButtonBounds.contains(mousePos) && showPurchasePrompt) {

          dealChoice = 0;
          showPurchasePrompt = false;
          isValidDeal = true;
          game.getBoard().getPlayerByID(game.getBoard().getPreviousTurn())->setIsRenting(-1);

        }
        else if (rentButtonBounds.contains(mousePos) && showPurchasePrompt) {

          dealChoice = 1;
          showPurchasePrompt = false;
          isValidDeal = true;
          game.getBoard().getPlayerByID(game.getBoard().getPreviousTurn())->setIsRenting(currInd);

        }

        if (isValidDeal) {

          game.getBoard().putsPlayerOnSpace(currInd, game.getBoard().getPreviousTurn(), window, dealChoice);

          dealChoice = -1;


        }

        if (diceButtonBounds.contains(mousePos)) {

          clk.restart();
          diceAnim = true;

          game.playDice(window, dice, diceTexture, dealChoice);

          // showPurchasePrompt = false;



        }


        if (navBtnLeftBounds.contains(mousePos)) {

          if (privatePropertyCardScroll) {

            privatePropertyCardScroll--;

          }

        }

        if (navBtnRightBounds.contains(mousePos)) {

          if (privatePropertyCardScroll < 17) {

            privatePropertyCardScroll++;

          }


        }

        if (commercialNavBtnLeftBounds.contains(mousePos)) {

          if (commercialPropertyCardScroll) {

            commercialPropertyCardScroll--;

          }

        }

        if (commercialNavBtnRightBounds.contains(mousePos)) {

          if (commercialPropertyCardScroll < 5) {

            commercialPropertyCardScroll++;

          }


        }


        int currTurnOnBoard = game.getBoard().getTurn();
        turnDisplayPieceTexture.loadFromFile(playerPieceFileName[currTurnOnBoard]);


      }

      if (evt.type == sf::Event::MouseWheelScrolled) {

        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        sf::FloatRect cardBound = cardPanel.getGlobalBounds();
        sf::FloatRect commercialCardBound = commercialCardPanel.getGlobalBounds();

        if (evt.mouseWheelScroll.delta > 0) // moving up
        {
          if (privatePropertyCardScroll && cardBound.contains(mousePos)) {

            privatePropertyCardScroll--;

          }

          if (commercialPropertyCardScroll && commercialCardBound.contains(mousePos)) {

            commercialPropertyCardScroll--;

          }

        }
        else if (evt.mouseWheelScroll.delta < 0) // moving down
        {

          if (privatePropertyCardScroll < 17 && cardBound.contains(mousePos)) {

            privatePropertyCardScroll++;

          }

          if (commercialPropertyCardScroll < 5 && commercialCardBound.contains(mousePos)) {

            commercialPropertyCardScroll++;

          }


        }

      }


    }

    window.clear();

    window.draw(background_screen);
    window.draw(game_field);
    window.draw(diceButton);
    window.draw(cardPanel);
    window.draw(commercialCardPanel);
    window.draw(turnDisplay);
    window.draw(turnText);
    window.draw(turnDisplayPiece);

    if (game.getGameWon())
      window.draw(gameWon);



    // Prints card texts

    for (int i = 0; i < 3; i++) {

      cardTitle[i].setString(privatePropertyNames[i + privatePropertyCardScroll]);
      cardPrice[i].setString(privatePropertyPrices[i + privatePropertyCardScroll]);
      cardRent[i].setString(privatePropertyRents[i + privatePropertyCardScroll]);

      commercialCardTitle[i].setString(commercialPropertyNames[i + commercialPropertyCardScroll]);
      commercialCardPrice[i].setString(commercialPropertyPrices[i + commercialPropertyCardScroll]);
      commercialCardRent[i].setString(commercialPropertyRents[i + commercialPropertyCardScroll]);

      Property* p = (Property*)game.getBoard().getCells()[privatePropertySpaces[i + privatePropertyCardScroll]];

      mortgageStatus[i].setFillColor(
        (p->getMortgaged()) ? sf::Color(231, 76, 60) : sf::Color(149, 165, 166));

      window.draw(cardTitle[i]);
      window.draw(cardPrice[i]);
      window.draw(cardRent[i]);
      window.draw(cardUpgradeIcon[i]);
      window.draw(mortgageStatus[i]);


      if (p->getOwnerID() == -1) {
        cardOwnerIcon[i].setFillColor(cardOwnerColors[5][0]);
      }
      else {

        cardOwnerIcon[i].setFillColor(cardOwnerColors[p->getOwnerID()][0]);

      }

      CommercialProperty* c = (CommercialProperty*)game.getBoard().getCells()[commercialPropertySpaces[i + commercialPropertyCardScroll]];

      if (c->getOwnerID() == -1) {
        commercialCardOwnerIcon[i].setFillColor(cardOwnerColors[5][0]);
      }
      else {

        commercialCardOwnerIcon[i].setFillColor(cardOwnerColors[c->getOwnerID()][0]);

      }


      window.draw(cardOwnerIcon[i]);
      window.draw(commercialCardOwnerIcon[i]);


      window.draw(commercialCardTitle[i]);
      window.draw(commercialCardPrice[i]);
      window.draw(commercialCardRent[i]);


      commercialMortgageStatus[i].setFillColor(
        (c->getMortgaged()) ? sf::Color(231, 76, 60) : sf::Color(149, 165, 166));


      window.draw(commercialMortgageStatus[i]);


      // enable switching based on connection
      for (int j = 0; j < 3; j++) {

        PrivateProperty* propertyCell = (PrivateProperty*)game.getBoard().getCells()[privatePropertySpaces[i + privatePropertyCardScroll]];

        upgradeIcon[i][0].setTexture(&upgradeIconTexture[j][propertyCell->getHasWifi()]);
        upgradeIcon[i][1].setTexture(&upgradeIconTexture[j][propertyCell->getHasElectricity()]);
        upgradeIcon[i][2].setTexture(&upgradeIconTexture[j][propertyCell->getHasGas()]);

        window.draw(upgradeIcon[i][j]);

        window.draw(buildingIcon[i][j]);

      }

    }


    // Prints all the player icons on the screen
    for (int i = 0; i < totalPlayers; i++) {
      window.draw(playerIcon[i]);

      if (!game.getBoard().getPlayerByID(i)->getIsBankrupt()) {
        playerCash[i].setString(to_string(game.getBoard().getPlayers()[i]->getCash()));
        playerCash[i].setFillColor(sf::Color(46, 204, 113));
      }
      else {
        playerCash[i].setString("0");
        playerCash[i].setFillColor(sf::Color(231, 76, 60));
      }

      window.draw(playerCash[i]);


    }



    // Tooltip
    if (tooltipIsVisible) {

      PrivateProperty* propertyCell = (PrivateProperty*)game.getBoard().getCells()[privatePropertySpaces[iClickedX + privatePropertyCardScroll]];

      char* count = new char[10];

      if (iClickedY == 0) {

        _itoa(propertyCell->getHouseCount(), count, 10);

      }
      else if (iClickedY == 1) {

        _itoa(propertyCell->getShopCount(), count, 10);

      }
      else if (iClickedY == 2) {

        _itoa(propertyCell->getHotelCount(), count, 10);

      }


      tooltip.setPosition(sf::Mouse::getPosition(window).x - 40.0f, sf::Mouse::getPosition(window).y - 60.0f);



      tooltipText.setPosition(sf::Mouse::getPosition(window).x - (8.0f + (2.0f * (strlen(count) > 1.0f))), sf::Mouse::getPosition(window).y - 40.0f);



      tooltipText.setString(count);
      window.draw(tooltip);
      window.draw(tooltipText);

      delete[] count;

    }


    // Prints the dices on the board

    if (clk.getElapsedTime().asMilliseconds() < animInt.asMilliseconds() && diceAnim) {

      diceTexture[0].loadFromFile(diceTextureImg[rand() % 6]);
      diceTexture[1].loadFromFile(diceTextureImg[rand() % 6]);

    }
    else {

      diceAnim = false;
      clk.restart();
      game.updateDiceTextures(diceTexture);

    }


    for (int i = 0; i < 2; i++) {
      window.draw(dice[i]);
      window.draw(navButton[i]);
      window.draw(commercialNavButton[i]);
    }

    // Prints players when the dice animation
    // is going on.

    for (int i = 0; i < totalPlayers && diceAnim; i++) {

      game.printPlayerOnCell(window, playerPieces[i],
        playerPrevPos[i], i);

    }

    // Prints all the player pieces on the board
    // after the dice has been rolled completely
    for (int i = 0; i < totalPlayers && !diceAnim; i++) {

      game.printPlayerOnCell(window, playerPieces[i],
        game.getPlayerPosition(i), i);


      playerPrevPos[i] = game.getPlayerPosition(i);

    }



    if (showPropertyUpgradePanel) {

      window.draw(propertyUpgradePrompt);
      window.draw(upgradePromptClose);

      for (int i = 0; i < 3; i++) {

        for (int j = 0; j < 2; j++) {

          window.draw(addButton[i][j]);
          window.draw(upgradePromptIcons[i][j]);

        }

      }


    }


    window.display();


  }

  delete[] playerPrevPos;
  for (int i = 0; i < 3; i++) {
    delete[] buildingIcon[i];
    delete[] upgradeIcon[i];
    delete[] upgradeIconTexture[i];
    delete[] cardOwnerColors[i];
    delete[] upgradePromptIconsTexture[i];
    delete[] upgradePromptIcons[i];
  }
  delete[] buildingIcon;
  delete[] buildingIconTextures;
  delete[] upgradeIcon;
  delete[] upgradeIconTexture;
  delete[] playerCash;
  delete[] mortgageStatus;
  delete[] cardUpgradeIcon;
  delete[] cardOwnerIcon;
  delete[] cardOwnerColors;
  delete[] cardRent;
  delete[] cardPrice;
  delete[] cardTitle;
  delete[] commercialMortgageStatus;
  delete[] commercialCardOwnerIcon;
  delete[] commercialCardRent;
  delete[] commercialCardPrice;
  delete[] commercialCardTitle;
  delete[] navButton;
  delete[] navButtonTexture;
  delete[] commercialNavButton;
  delete[] dice;
  delete[] diceTexture;
  delete[] playerIcon;
  delete[] playerIconTexture;
  delete[] playerTextures;
  delete[] playerPieces;
  delete[] upgradePromptIconsTexture;
  delete[] upgradePromptIcons;

  return 0;
}




// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <algorithm>

template <typename T>
class BST {
public:
  struct Node {
    T value;
    int count;
    Node* left;
    Node* right;
  };

private:
  Node* root;
  Node* addNode(Node* root, T value);
  int depthTree(Node* root);
  int searchNode(Node* root, T value);

public:
  BST();
  void add(T value);
  int depth();
  int search(T value);
};

template <typename T>
BST<T>::BST() : root(nullptr) {}

template <typename T>
typename BST<T>::Node* BST<T>::addNode(Node* root, T value) {
  if (root == nullptr) {
    root = new Node;
    root->value = value;
    root->count = 1;
    root->left = root->right = nullptr;
  }
  else if (root->value > value) {
    root->left = addNode(root->left, value);
  }
  else if (root->value < value) {
    root->right = addNode(root->right, value);
  }
  else {
    root->count++;
  }
  return root;
}

template <typename T>
void BST<T>::add(T value) {
  root = addNode(root, value);
}

template <typename T>
int BST<T>::depthTree(Node* root) {
  if (root == nullptr) {
    return 0;
  }
  else {
    int leftDepth = depthTree(root->left);
    int rightDepth = depthTree(root->right);
    return std::max(leftDepth, rightDepth) + 1;
  }
}

template <typename T>
int BST<T>::depth() {
  return depthTree(root) - 1;
}

template <typename T>
int BST<T>::searchNode(Node* root, T value) {
  if (root == nullptr)
    return 0;
  else if (root->value == value)
    return root->count;
  else if (root->value > value)
    return searchNode(root->left, value);
  else
    return searchNode(root->right, value);
}

template <typename T>
int BST<T>::search(T value) {
  return searchNode(root, value);
}

#endif  // INCLUDE_BST_H_