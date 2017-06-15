#include <time.h>
#include <iostream>
#include <cctype>
#include "window.h"
#include "Enemy.h"
#include "Player.h"
#include "string.h"
#include "room.h"


#pragma region Variables
static String Attack("Attack");
static String Item("Item");
static String Block("Block");
static String Disarm("Disarm");

StartRoom start;
Room_1 room1;
Room_2 room2;
Room_3 room3;
Room_4 room4;
Room_5 room5;
Room_6 room6;
Room_7 room7;
Room_8 room8;
Room_9 room9;
Room_10 room10;
Boss bossRoom;

RoomName currentRoom;

//borders
extern const Rect pInputZone{ 0, 35, 35,5 };
extern const Rect pOutputzone{ 0,40,35,20 };
extern const Rect p2Outputzone{ 34,40,62,20 };
extern const Rect pMapZone = { 0,0,35,35 };

extern const int inputLocationX = 2;
extern const int inputLocationY = 36;
extern const int outputLocationX = 35;
extern const int outputLocationY = 41;
extern const Rect pOutputText{35,41,58,10};
Rect pintro = { 35,5,60,5 };

extern const Rect pInputLine{ pInputZone.x +1, pInputZone.y + 1,32,1};
extern const Rect pOutputMax{ pOutputzone.x + 1, pOutputzone.y + 1, 32, 16 };
extern const Rect pPHOutputLine{ 2, 44, 30, 0 };
extern const Rect pEHOutputLine{ 2, 49, 30, 0 };
extern const Rect pPCOutputLine{ 1, 45, 30, 1 };
extern const Rect pECOutputLine{ 1, 50, 30, 1 };

static int width = 120;
static int height = 60;
const Rect pBorder{ 0,0,width,height };

#pragma endregion

#pragma region Draw

void drawCorridor(int a_x, int a_y) {
	Rect pLocation = { a_x-2, a_y+1, 11, 4 };
	Window::DrawBorder(pLocation, YELLOW);
}
void drawCorridor3(int a_x, int a_y) {
	Rect pLocation = { a_x +1, a_y -6, 5, 8 };
	Window::DrawBorder(pLocation, YELLOW);
}
void drawCorridor2(int a_x, int a_y) {
	Rect pLocation = { a_x+1 , a_y + 1, 16, 4 };

	Window::DrawBentCorridor(pLocation, YELLOW);
	
}

// the main routine
void drawRoom(int a_x, int a_y, bool a_hasEntered, bool a_IAmHere, bool a_hasSearched)
{
	Rect pLocation = { a_x, a_y, 7, 6 };
	Window::DrawBorder(pLocation, YELLOW);
	eColor color = a_IAmHere ? YELLOW : a_hasEntered ? GREEN : a_hasSearched ? CYAN : DARKMAGENTA;
	Window::SetTextColor(color);
	Window::DrawChar(a_x + 3, a_y + 2, a_IAmHere ? 'O' : 'X');
}

// draws the ship
void drawShip()
{
	short tx = 2;
	//top rooms
	drawCorridor(tx + 16, 22);
	drawCorridor2(tx, 2);
	drawCorridor3(tx + 24, 17);
	drawRoom(tx+16, 2, room5.ReturnEntered(), currentRoom == ROOM_5, room5.returnHasSearched());
	drawRoom(tx+8, 7, room4.ReturnEntered(), currentRoom == ROOM_4, room4.returnHasSearched());
	drawRoom(tx + 16, 7, room3.ReturnEntered(), currentRoom == ROOM_3,room3.returnHasSearched());
	drawRoom(tx + 24, 7, room2.ReturnEntered(), currentRoom == ROOM_2,room2.returnHasSearched());
	//bottom rooms
	drawRoom(tx + 8, 17, room10.ReturnEntered(), currentRoom == ROOM_10, room10.returnHasSearched());
	drawRoom(tx+24, 17, room1.ReturnEntered(), currentRoom == ROOM_1,room1.returnHasSearched());
	drawRoom(tx, 22, room6.ReturnEntered(), currentRoom == ROOM_6, room6.returnHasSearched());
	drawRoom(tx+8, 22, room9.ReturnEntered(), currentRoom == ROOM_9, room9.returnHasSearched());
	drawRoom(tx+24, 22, start.ReturnEntered(), currentRoom == START, start.returnHasSearched());
	drawRoom(tx, 27, room7.ReturnEntered(), currentRoom == ROOM_7, room7.returnHasSearched());
	drawRoom(tx+8, 27, room8.ReturnEntered(), currentRoom == ROOM_8, room8.returnHasSearched());

	if (room8.getLeverPulled() == true) {
		drawRoom(tx + 24, 27, bossRoom.ReturnEntered(), currentRoom == BOSS_1, bossRoom.returnHasSearched());
	}
}

void drawVisuals() {
	drawShip();
	Window::DrawBorder(pInputZone, CYAN);
	Window::DrawBorder(pOutputzone, CYAN);
	Window::DrawBorder(p2Outputzone, CYAN);
	Window::DrawBorder(pMapZone, CYAN);
	Window::DrawBorder(pBorder, CYAN);

}

void clearPCombat() {
	Window::ClearSection(pPCOutputLine);

}
void clearECombat() {
	Window::ClearSection(pECOutputLine);
}

void clearHealth() {
	Window::ClearSection(pPHOutputLine);
	Window::ClearSection(pEHOutputLine);
}

#pragma endregion draw functions and rect variables
void pauseTillEscapeHit() {


	while (GetKeyState(VK_SPACE) >= 0) {

	}

};

bool CombatFunction(Player *a_player, Spawn *a_enemy) {
	
	bool playerBlock = false;
	int enemyCounter = 0;
	int playerCounter = 0;
	bool playerAttacked = false;
	bool enemyAttacked = false;
	int playerAttackCounter = 1;
	int enemyAttackCounter = 1;
	String noCommand = "error no command detected";
	String startFight = "Oh no an Enemy. Press space to fight!";
	String cantDisarm = "You cant disarm a weaponless opponent";
	String playerGo = " Player's Go";
	String enemyGo = " Enemy's Go ";
	String playerDead = " Player is dead";
	String enemyDead = " Enemy is dead";
	//KEEPS COMBAT GOING TILL ONE IS DEAD
	Window::ClearSection(pOutputText);
	Window::ClearSection(pOutputMax);
	clearHealth();
	Window::SetXY(pPHOutputLine.x, pPHOutputLine.y);
	std::cout << " Player health:" << a_player->getHealth() << endl;
	Window::SetXY(pEHOutputLine.x, pEHOutputLine.y);
	std::cout << " " << a_enemy->name.cStr() << " health:" << a_enemy->getHealth() << endl;
	Window::DrawLine(outputLocationX, outputLocationY, YELLOW, startFight.cStr(), 60);
	pauseTillEscapeHit();


	Window::ClearSection(pOutputText);
	while (!a_enemy->getDeath()) {
		//TURN COUNTERS
		enemyCounter++;
		playerCounter++;
		//HEALTH UPDATE GRAPHIC TOOLS
		clearHealth();
		Window::SetXY(pPHOutputLine.x, pPHOutputLine.y);
		std::cout << " Player health:" << a_player->getHealth() << endl;
		Window::SetXY(pEHOutputLine.x, pEHOutputLine.y);
		std::cout << " " << a_enemy->name.cStr() << " health:" << a_enemy->getHealth() << endl;
		
		//PLAYER ACTION COUNTER 
		if (playerCounter == a_player->getSpeed()) {
			//GRAPHICS AND REMOVAL TOOLS
			playerAttacked = false;
			Window::SetXY(pPHOutputLine.x - 1, pPHOutputLine.y);
			Window::SetTextColor(RED);
			std::cout << "=" << endl;
			Window::SetXY(pEHOutputLine.x - 1, pEHOutputLine.y);
			Window::SetTextColor(WHITE);
			std::cout << "=" << endl;
			Window::SetTextColor(YELLOW);

			Window::DrawLine(2, 42, YELLOW, playerGo.cStr(), 60);
			//INPUT LOOP
			while (playerAttacked == false) {
				//INPUT CONTROLS AND GRAPHIC REMOVAL

				Window::SetXY(pInputLine.x, pInputLine.y);
				//while (std::cin.rdbuf()->in_avail()) cin.get();
				//cin.clear();
				//cin.ignore();

				while (_kbhit())
				{
					_getche();
				}

				char input[1024];
				Window::SetXY(pInputLine.x, pInputLine.y);
				std::cin.getline(input, 1024);
				String inputS = input;
				inputS.toLower(true);
				Window::ClearSection(pInputLine);
				clearPCombat();
				int playerDamage = a_player->getDamage();
				//LETS PLAYER ATTACK
				if (inputS.equalTo(Attack)) {
					//SET BLOCKED ATTACK
					if (a_enemy->getBlocking()) {
						int remainingHealth = a_enemy->getHealth() - playerDamage;
						a_enemy->setHealth(remainingHealth);;
						String combatOut = "The Player Attacked[*] for $ Damage";
						char pActionC[20];
						_itoa_s(playerAttackCounter, pActionC, 5, 10);
						char pDamageC[20];
						_itoa_s(playerDamage, pDamageC, 5, 10);
						combatOut.replace("*", pActionC);
						combatOut.replace("$", pDamageC);
						Window::DrawLine(pPCOutputLine.x, pPCOutputLine.y, YELLOW, combatOut.cStr(), 30);
						playerAttackCounter++;
						playerCounter = 1;
						playerAttacked = true;
						break;
					}
					//STANDARD ATTACK
					else {
						int remainingHealth = a_enemy->getHealth() - playerDamage;
						a_enemy->setHealth(remainingHealth);;
						String combatOut = "The Player Attacked[*] for $ Damage";
						char pActionC[20];
						_itoa_s(playerAttackCounter, pActionC, 5, 10);
						char pDamageC[20];
						_itoa_s(playerDamage, pDamageC, 5, 10);
						combatOut.replace("*", pActionC);
						combatOut.replace("$", pDamageC);
						Window::DrawLine(pPCOutputLine.x, pPCOutputLine.y, YELLOW, combatOut.cStr(), 30);
						playerAttackCounter++;
						playerCounter = 1;
						playerAttacked = true;
						break;


					}
				}
				//LETS PLAYER USE AN ITEM
				if (inputS.equalTo(Item)) {
					/*String combatOut = "The Player Used an Item[*]";
					char pActionC[20];
					_itoa_s(playerAttackCounter, pActionC, 5, 10);
					combatOut.replace("*", pActionC);
					Window::DrawLine(pPCOutputLine.x, pPCOutputLine.y, YELLOW, combatOut.cStr(), 30);
					playerCounter = 1;
					playerAttacked = true;
					*/
					String combatOut = "The Player has no items to use right now";
					Window::DrawLine(pPCOutputLine.x, pPCOutputLine.y, YELLOW, combatOut.cStr(), 30);
					continue;


				}
				// SET PLAYER TO BLOCK
				if (inputS.equalTo(Block)) {
					playerBlock = true;
					String combatOut = "The Player is Blocking[*]";
					char pActionC[20];
					_itoa_s(playerAttackCounter, pActionC, 5, 10);
					combatOut.replace("*", pActionC);
					Window::DrawLine(pPCOutputLine.x, pPCOutputLine.y, YELLOW, combatOut.cStr(), 30);
					playerCounter = 1;
					playerAttacked = true;
					break;
				}
				//SET PLAYER TO DISARM
				if (inputS.equalTo(Disarm)) {
					if (a_enemy->getDisarmed() == false) {
						int successChance = rand() % 100;
						if (successChance < 75 - a_player->getSpeed()) {
							String combatOut = "The Player tried to disarm and failed.";
							char pActionC[20];
							_itoa_s(playerAttackCounter, pActionC, 5, 10);
							combatOut.replace("*", pActionC);
							Window::DrawLine(pPCOutputLine.x, pPCOutputLine.y, YELLOW, combatOut.cStr(), 30);
							playerAttackCounter++;
							playerCounter = 1;
							playerAttacked = true;


						}
						if (successChance > 75 - a_player->getSpeed()) {
							String combatOut = "The Player was successful in disarming the enemy.";
							a_enemy->setDisarmed(true);
							char pActionC[20];
							_itoa_s(playerAttackCounter, pActionC, 5, 10);
							combatOut.replace("*", pActionC);
							Window::DrawLine(pPCOutputLine.x, pPCOutputLine.y, YELLOW, combatOut.cStr(), 30);
							playerAttackCounter++;
							playerCounter = 1;
							playerAttacked = true;

						}
					}
					else {
						Window::DrawLine(pPCOutputLine.x, pPCOutputLine.y, YELLOW, cantDisarm.cStr(), 30);

					}
				}
				else {
					Window::DrawLine(pPCOutputLine.x, pPCOutputLine.y, YELLOW, noCommand.cStr(), 30);
				}

			}
			// SET ENEMY TO DEAD IF KILLED
			if (a_enemy->getHealth() <= 0) {
				a_enemy->setDeath(true);
				Window::ClearSection(pOutputzone);
				Window::DrawLine(2, 42, YELLOW, enemyDead.cStr(), 60);
				Window::DrawBorder(pOutputzone, CYAN);
				Window::DrawBorder(pBorder, CYAN);

				return false;
			}
		}
		//ENEMY ACTION
		if (a_player->getHealth() >= 0) {
			//SIGNIFY THE ENEMY'S TURN THROUGH A COUNTER
			if (enemyCounter == a_enemy->getSpeed()) {
				// GRAPHICS AND REMOVAL TOOLS
				Window::DrawLine(2, 42, YELLOW, enemyGo.cStr(), 60);
				Sleep(1800);
				clearECombat();
				Window::SetXY(pPHOutputLine.x - 1, pPHOutputLine.y);
				Window::SetTextColor(WHITE);
				std::cout << "=" << endl;
				Window::SetXY(pEHOutputLine.x - 1, pEHOutputLine.y);
				Window::SetTextColor(RED);
				std::cout << "=" << endl;
				Window::SetTextColor(YELLOW);
				enemyAttacked = false;
				int enemyAttack = a_enemy->getAttack();
				if (enemyAttack != 0 && enemyAttack != -1 && enemyAttack != -2) {
					//BLOCKED ATTACK
					if (playerBlock) {
						int remainingHealth = a_player->getHealth() - (enemyAttack / 2);
						a_player->setHealth(remainingHealth);
						String combatOut = "The Enemy Attacked[*] for $ Damage";
						char eActionC[20];
						_itoa_s(enemyAttackCounter, eActionC, 5, 10);
						char eDamageC[20];
						_itoa_s(enemyAttack, eDamageC, 5, 10);
						combatOut.replace("*", eActionC);
						combatOut.replace("$", eDamageC);
						Window::DrawLine(pECOutputLine.x, pECOutputLine.y, YELLOW, combatOut.cStr(), 30);
						enemyAttackCounter++;
						enemyCounter = 1;
					}
					//STANDARD ATTACK
					else {
						int remainingHealth = a_player->getHealth() - (enemyAttack);
						a_player->setHealth(remainingHealth);
						String combatOut = "The Enemy Attacked[*] for $ Damage";
						char eActionC[20];
						_itoa_s(enemyAttackCounter, eActionC, 5, 10);
						char eDamageC[20];
						_itoa_s(enemyAttack, eDamageC, 5, 10);
						combatOut.replace("*", eActionC);
						combatOut.replace("$", eDamageC);
						Window::DrawLine(pECOutputLine.x, pECOutputLine.y, YELLOW, combatOut.cStr(), 30);
						enemyAttackCounter++;
						enemyCounter = 1;
					}

				}
				//SET ENEMY TO BLOCK
				else if (enemyAttack == 0) {
					String combatOut = "The Enemy is Blocking[*] ";
					char eActionC[20];
					_itoa_s(enemyAttackCounter, eActionC, 5, 10);
					combatOut.replace("*", eActionC);
					Window::DrawLine(pECOutputLine.x, pECOutputLine.y, YELLOW, combatOut.cStr(), 30);
					enemyAttackCounter++;
					enemyCounter = 1;

				}
				//ENEMY MISSED
				else if (enemyAttack == -1) {
					String combatOut = "The Enemy Missed[*] ";
					char eActionC[20];
					_itoa_s(enemyAttackCounter, eActionC, 5, 10);
					combatOut.replace("*", eActionC);
					Window::DrawLine(pECOutputLine.x, pECOutputLine.y, YELLOW, combatOut.cStr(), 30);
					enemyAttackCounter++;
					enemyCounter = 1;

				}
				//ENEMY TRYING TO DISARM
				else if (enemyAttack == -2) {
					int hitChance = rand() % 100;
					if (a_player->getArmed() == true) {
						if (hitChance < 75 - a_player->getSpeed()) {
							String combatOut = "The Enemy tried to disarm you[*].";
							char eActionC[20];
							_itoa_s(enemyAttackCounter, eActionC, 5, 10);
							combatOut.replace("*", eActionC);
							Window::DrawLine(pECOutputLine.x, pECOutputLine.y, YELLOW, combatOut.cStr(), 30);
							enemyAttackCounter++;
							enemyCounter = 1;
						}
						if (hitChance < 75 - a_player->getSpeed()) {
							String combatOut = "The Enemy Disarmed you[*] ";
							a_player->setArmed(false);
							char eActionC[20];
							_itoa_s(enemyAttackCounter, eActionC, 5, 10);
							combatOut.replace("*", eActionC);
							Window::DrawLine(pECOutputLine.x, pECOutputLine.y, YELLOW, combatOut.cStr(), 30);
							enemyAttackCounter++;
							enemyCounter = 1;
						}
					}
					if (a_player->getArmed() == false) {
					}
				}
			}
			//SET PLAYER DEAD IF KILLED
			if (a_player->getHealth() <= 0) {
				Window::DrawLine(2, 42, YELLOW, enemyDead.cStr(), 60);
				a_player->setDeath(true);
				return false;
			}
		}
	}
	return true;
}

int main()
{
	srand((unsigned int)time(NULL));


	Spawn one;
	Spawn two;
	Spawn three;
	Spawn four = 3;
	Spawn five;
	Spawn boss = 4;
	currentRoom = START;
	Player mainPlayer;

	String intro = "The memory repeats itself in your head over and over again; You're sitting down to eat in a lousy boar inn when you watch a large dirty man walk past you... THUMP, you feel a blindingly pain in the the back of your head...";

	String end1 = "You have slain the beast from behind the wall and have noticed that behind the beast is a staircase that leads to a door. Your tired, bruised and beaten self walks itself aimlessly to the top of the stairs. You open the door and are welcomed with the warmth of sunlight hitting your skin\n \t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t THE END!";

	String end2 = "You have slain the beast from behind the wall and have noticed that behind the beast is a staircase that leads to a door. You tired,bruised and beaten self walks itself aimlessly to the top of the stair. You go to reach for the handle but are thrown to the bottom of the staircase. 'Why did you do it ? you killed an innocent woman who like yourself was trapped in here.She escaped just like you.  But, unlike you, she didnt turn to unrelenting killing and violence so you butchered her like one of the creatures trapped in this horrid place. For this you will be doomed to rot in this place.' a cackling voice screamed as the door was slammed shut.\n\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t THE END!";

	Window::SetTextColor(BLACK);

	RoomName nextRoom = START;
	bool Fin = false;

	int width = 120;
	int height = 60;
	bool result = Window::Initialise(width, height, L"Adventure");

	if (result == EXIT_FAILURE)
		return EXIT_FAILURE;
	start.SetIsChained(true);
	Window::DrawBorder(pBorder, CYAN);

	Window::DrawLine(5, 5, YELLOW, intro.cStr(), 100);
	pauseTillEscapeHit();

	while (_kbhit())
	{
		_getche();
	}
	Window::ClearScreen();
	drawVisuals();
	while (Fin == false) {
		while (_kbhit())
		{
			_getche();
		}
		if (currentRoom != nextRoom) {
			system("CLS");
			currentRoom = nextRoom;
		}
		Window::ClearSection(pInputLine);
		drawVisuals();
		switch (currentRoom) {

		case START:
			while (nextRoom == currentRoom) {
			
				start.printRoom();
				Window::SetXY(pInputLine.x, pInputLine.y);
				char input[1024];
				std::cin.getline(input, 1024);
				String inputS = input;
				Window::ClearSection(pInputLine);
				Window::SetXY(pInputLine.x, pInputLine.y);
				nextRoom = start.processInput(inputS);
				//inputS.setString("");
				Window::ClearSection(pintro);

			}
			break;
		case ROOM_1:

			while (nextRoom == currentRoom) {
				if (room1.getEnemyAlive() == true) {
					room1.printRoom();
					room1.setEnemyAlive(CombatFunction(&mainPlayer, &one));
					continue;
				}
				room1.setMDescription();
				room1.printRoom();
				char input[1024];				
				Window::SetXY(pInputLine.x, pInputLine.y);
				std::cin.getline(input, 1024);
				String inputS = input;
				Window::ClearSection(pInputLine);
				Window::SetXY(pInputLine.x, pInputLine.y);
				Window::ClearSection(pInputLine);
				nextRoom = room1.processInput(inputS);
			}
			break;
		case ROOM_2: // Engine2
			room2.printRoom();
			while (nextRoom == currentRoom) {
				Window::SetXY(pInputLine.x, pInputLine.y);
				char input[1024];
				std::cin.getline(input, 1024);
				String inputS = input;
				Window::ClearSection(pInputLine);
				Window::SetXY(pInputLine.x, pInputLine.y);
				Window::ClearSection(pInputLine);
				Window::SetXY(pInputLine.x, pInputLine.y);
				nextRoom = room2.processInput(inputS);
			}
			break;
		case ROOM_3: // Power
			room3.printRoom();
			while (nextRoom == currentRoom) {
				Window::SetXY(pInputLine.x, pInputLine.y);
				char input[1024];
				std::cin.getline(input, 1024);
				String inputS = input;
				Window::ClearSection(pInputLine);
				Window::SetXY(pInputLine.x, pInputLine.y);
				Window::ClearSection(pInputLine);
				Window::SetXY(pInputLine.x, pInputLine.y);
				nextRoom = room3.processInput(inputS);
			}
			break;
		case ROOM_4:
			room4.printRoom();
			while (nextRoom == currentRoom) {
				if (room4.getEnemyAlive() == true) {
					room4.printRoom();
					room4.setEnemyAlive(CombatFunction(&mainPlayer, &two));
					continue;
				}
				room4.setMDescription();
				room4.printRoom();
				Window::SetXY(pInputLine.x, pInputLine.y);
				char input[1024];
				std::cin.getline(input, 1024);
				String inputS = input;
				Window::ClearSection(pInputLine);
				Window::SetXY(pInputLine.x, pInputLine.y);
				Window::ClearSection(pInputLine);
				Window::SetXY(pInputLine.x, pInputLine.y);
				nextRoom = room4.processInput(inputS);
				room5.setHasKey(true);
			}
			break;
		case ROOM_5:
			room5.printRoom();
			while (nextRoom == currentRoom) {
				Window::SetXY(pInputLine.x, pInputLine.y);
				char input[1024];
				std::cin.getline(input, 1024);
				String inputS = input;
				Window::ClearSection(pInputLine);
				Window::SetXY(pInputLine.x, pInputLine.y);
				Window::ClearSection(pInputLine);
				Window::SetXY(pInputLine.x, pInputLine.y);
				nextRoom = room5.processInput(inputS);
			}
			break;
		case ROOM_6:
			room6.printRoom();
			while (nextRoom == currentRoom) {
				Window::SetXY(pInputLine.x, pInputLine.y);
				char input[1024];
				std::cin.getline(input, 1024);
				String inputS = input;
				Window::ClearSection(pInputLine);
				Window::SetXY(pInputLine.x, pInputLine.y);
				Window::ClearSection(pInputLine);
				Window::SetXY(pInputLine.x, pInputLine.y);
				nextRoom = room6.processInput(inputS);
			}
			break;
		case ROOM_7:
			room7.printRoom();
			while (nextRoom == currentRoom) {
				Window::SetXY(pInputLine.x, pInputLine.y);
				char input[1024];
				std::cin.getline(input, 1024);
				String inputS = input;
				Window::ClearSection(pInputLine);
				Window::SetXY(pInputLine.x, pInputLine.y);

				if (room7.getInnocentAlive() == true) {
					if (inputS.equalTo(Attack)) {
						room7.printRoom();
						room7.setInnocentAlive(CombatFunction(&mainPlayer, &four));
						continue;
					}
				}
				nextRoom = room7.processInput(input);
				
				if (room7.getInnocentAlive() == true) {
					if (room7.getAttacked() == true) {
						room7.printRoom();
						room7.setInnocentAlive(CombatFunction(&mainPlayer, &four));
						continue;
					}
				}
			}

			break;
		case ROOM_8:
			room8.printRoom();
			while (nextRoom == currentRoom) {
				if (room8.getEnemyAlive() == true) {
					room8.printRoom();
					room8.setEnemyAlive(CombatFunction(&mainPlayer, &five));
					continue;
				}
				room8.setMDescription();
				room8.printRoom();
				Window::SetXY(pInputLine.x, pInputLine.y);
				char input[1024];
				std::cin.getline(input, 1024);
				String inputS = input;
				Window::ClearSection(pInputLine);
				Window::SetXY(pInputLine.x, pInputLine.y);
				nextRoom = room8.processInput(inputS);
				start.setbossRoomOpen(room8.getLeverPulled());
			}
			break;
		case ROOM_9:
			room9.printRoom();
			while (nextRoom == currentRoom) {
				Window::SetXY(pInputLine.x, pInputLine.y);
				char input[1024];
				std::cin.getline(input, 1024);
				String inputS = input;
				Window::ClearSection(pInputLine);
				Window::SetXY(pInputLine.x, pInputLine.y);
				nextRoom = room9.processInput(inputS);
			}
			break;
		case ROOM_10:
			room10.printRoom();
			while (nextRoom == currentRoom) {
				if (room10.getEnemyAlive() == true) {
					room10.printRoom();
					room10.setEnemyAlive(CombatFunction(&mainPlayer, &three));
					continue;
				}
				room10.setMDescription();
				room10.printRoom();
				char input[1024];
				std::cin.getline(input, 1024);
				String inputS = input;
				Window::ClearSection(pInputLine);
				Window::SetXY(pInputLine.x, pInputLine.y);
				nextRoom = room10.processInput(inputS);
				room9.setHasKey(true);
				room7.setHasKey(true);
				start.setHasKey(true);
			}
			break;
		case BOSS_1:
			bossRoom.printRoom();
			while (nextRoom == currentRoom) {
				if (bossRoom.getEnemyAlive() == true) {
					bossRoom.printRoom();
					bossRoom.setEnemyAlive(CombatFunction(&mainPlayer, &boss));
					continue;
				}
				if (bossRoom.getEnemyAlive() == false) {
					Window::ClearScreen();
					Window::DrawBorder(pBorder, CYAN);
					if (room7.getInnocentAlive()) {
						Window::DrawLine(5, 5, YELLOW, end1.cStr(), 100);
						pauseTillEscapeHit();
						Fin = true;
					}
					if (!room7.getInnocentAlive()) {
						Window::DrawLine(5, 5, YELLOW, end2.cStr(), 100);
						pauseTillEscapeHit();
						Fin = true;
					}
					break;

				}
			}
				break;
			

		}
	}
	return EXIT_SUCCESS;
}



