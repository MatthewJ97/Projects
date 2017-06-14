#include "room.h"
#include "String.h"
#include "window.h"

#if 1
// keys used in the game
static String Up("Up");
static String Down("Down");
static String Right("Right");
static String Left("Left");
static String Use("Use");
static String Search("Search");
static String Password("Password");
static String Attack("Attack");

extern const Rect pInputLine;
extern const Rect pPHOutputLine;
extern const Rect pPCOutputLine;
extern const Rect pEHOutputLine;
extern const Rect pECOutputLine;
extern const int inputLocationX ;
extern const int inputLocationY;
extern const int outputLocationX;
extern const int outputLocationY;
extern const Rect pInputZone;
extern const Rect pOutputzone;
extern const Rect pMapZone;
extern const Rect pOutputMax;
extern const Rect pOutputText;
// START room
StartRoom::StartRoom()
{

	m_isChained = true;
	m_hasSearched = false;
	char Description[] = "You are awoken by a deafening rumbling roar, as you jerk awake you find that youre arm is secured to the wall\nSEARCH:		Take a look around the room\nUP    :You can see a door ahead\nLEFT  :You can see a door to your left ";
	m_Description.append(Description);
	m_room = START;
	m_hasEntered = true;
	m_firstTime = true;

}

RoomName StartRoom::processInput(String a_Input)
{
	RoomName room = m_room;

	String printOut("");
	a_Input.toLower(true);
	if(m_firstTime) {
		m_Description.setString("You are awoken by a deafening rumbling roar, as you jerk awake you find that youre arm is secured to the wall ");
		m_firstTime = false;

	}
	if (!m_firstTime) {
		if (!m_bossRoomOpen) {
			char Description[] = "This is the room you woke up in the floor is covered in bones and there are torches burning on the walls.\nSEARCH:		Take a look around the room\nUP    :You can see a door ahead\nLEFT  :You can see a door to your left";
			m_Description.setString(Description);
		}
		else {
			char Description[] = "This is the room you woke up in the floor is covered in bones and there are torches burning on the walls.\nSEARCH:		Take a look around the room\nUP    :You can see a door ahead\nLEFT  :You can see a door to your left \nDOWN  :You can see a door behind you";
			m_Description.setString(Description);
			if (a_Input.equalTo(Down)) {
				room = BOSS_1;
			}
		}
	}
	if (!m_isChained) {
		if (a_Input.equalTo(Up)) {
			room = ROOM_1;
		}
		if (a_Input.equalTo(Left)) {

			printOut.append("You enter a small corridor with another door at the end.");
			if (m_hasKey == false) {
				printOut.append("The Door at the other end is locked you must find the key. The corridor is empty so you head back to the other Room");

			}
			else {
				room = ROOM_9;
			}
		}
		if (a_Input.equalTo(Search)) {
			m_hasSearched = true;

			printOut.append("You Found nothing of use to you");
		}
	}
	else {
		if (a_Input.equalTo(Up)) {
			printOut.append("You start to move towards the door when you remember that your connected to the wall");
		}
		if (a_Input.equalTo(Left)) {

			printOut.append("You start to move towards the door when you remember that your connected to the wall");

		}
		if (a_Input.equalTo(Search)) {
			m_hasSearched = true;
			m_isChained = false;
			printOut.append("You notice that the chain is rusty and starting to corrode on its own. With a hard tug on the chain you are able to break it clean from the shackle");
		}
	}
	if (printOut.length()) {
		Window::ClearSection(pOutputText);
		Window::DrawLine(outputLocationX, outputLocationY, GREEN, printOut.cStr(), 60);
		Window::SetXY(inputLocationX, inputLocationY);
	}
	return room;
}
Room_1::Room_1()
{
	m_enemyAlive = true;
	char Description[] = "The manacles set into the walls of this room give you the distinct impression that it was used as a prison and torture chamber, although you can see no evidence of torture devices. One particularly large set of manacles have been broken open.\nATTACK: Attack the enemy\nBLOCK: Block the enemy's attack (1/2 damage)\nITEM:	Use an item\nDISARM:	Have a chance to dodge an enemy's attack.";
	m_Description.append(Description);
	m_hasEntered = false;
	m_room = ROOM_1;
	m_hasSearched = false;

}

RoomName Room_1::processInput(String a_Input)
{

	RoomName room = m_room;
	m_hasEntered = true;
	String printOut("");
	a_Input.toLower(true);
	Window::ClearSection(pOutputzone);
	Window::DrawBorder(pOutputzone, CYAN);
	Window::DrawBorder(pMapZone, CYAN);



	if (a_Input.equalTo(Up)) {
		printOut.append("You enter a small corridor with another door at the end. You continue down and enter the room on the other side");
		room = ROOM_2;
	}
	if (a_Input.equalTo(Down)) {
		room = START;
	}
	if (a_Input.equalTo(Search)) {
		m_hasSearched = true;
		printOut.append("You Found nothing of use to you");
	}

	Window::SetXY(inputLocationX, inputLocationY);;
	if (printOut.length()) {
		Window::ClearSection(pOutputText);

		Window::DrawLine(outputLocationX, outputLocationY, GREEN, printOut.cStr(), 60);
	}

	return room;
}

#endif

Room_2::Room_2()
{
	m_hasSearched = false;
	m_room = ROOM_2;
	m_hasEntered = false;
	char Description[] = " The strong, sour-sweet scent of vinegar assaults your nose as you enter this room. Sundered casks and broken bottle glass line the walls of this room. Clearly this was someone's wine cellar for a time. The shards of glass are somewhat dusty, and the spilled wine is nothing more than a sticky residue in some places. Only one small barrel remains unbroken amid the rubbish\nSEARCH:		Take a look around the room\nLEFT  :You can see a door to your left ";
	m_Description.append(Description);
}
RoomName Room_2::processInput(String a_input)
{
	RoomName room = m_room;
	m_hasEntered = true;
	String printOut("");
	a_input.toLower(true);


	if (a_input.equalTo(Left)) {
		room = ROOM_3;
	}
	if (a_input.equalTo(Down)) {
		room = ROOM_1;
	}
	if (a_input.equalTo(Search)) {
		m_hasSearched = true;
		printOut.append("You Found nothing of use to you");
	}
	if (printOut.length()) {
		Window::ClearSection(pOutputText);
		Window::DrawLine(outputLocationX, outputLocationY, GREEN, printOut.cStr(), 60);
		Window::SetXY(inputLocationX, inputLocationY);
	}

	return room;
}

Room_3::Room_3()
{

	m_room = ROOM_3;
	m_hasEntered = false;
	m_hasSearched = false;
	char Description[] = " There's a hiss as you open this door, and you smell a sour odor, like something rotten or fermented. Inside you see a small room lined with dusty shelves, crates, and barrels. It looks like someone once used this place as a larder, but it has been a long time since anyone came to retrieve food from it.\nSEARCH:		Take a look around the room\nUP    :You can see a door ahead\nLEFT  :You can see a door to your left \nRIGHT  :You can see a door to your right";
	m_Description.append(Description);

}

RoomName Room_3::processInput(String a_input)
{
	RoomName room = m_room;
	m_hasEntered = true;
	String printOut("");
	a_input.toLower(true);


	if (a_input.equalTo(Left)) {
		room = ROOM_4;
	}
	if (a_input.equalTo(Right)) {
		room = ROOM_2;
	}
	if (a_input.equalTo(Up)) {
		room = ROOM_5;
	}
	if (a_input.equalTo(Search)) {
		if (!m_hasSearched) {
			m_hasSearched = true;
			printOut.append(" You Found a helmet but it was to heavy to be useful.");
			
		}
		else {
			printOut.append("You Found nothing of use to you");
		}
	}
	if (printOut.length()) {
		Window::SetXY(inputLocationX, inputLocationY);;
		Window::ClearSection(pOutputText);
		Window::DrawLine(outputLocationX, outputLocationY, GREEN, printOut.cStr(), 60);
	}

	return room;
}

Room_4::Room_4()
{

	m_room = ROOM_4;
	m_hasEntered = false;
	m_enemyAlive = true;
	m_hasSearched = false;
	char Description[] = "You enter the room and there is an enemy quick defend yourself!!!\nATTACK: Attack the enemy\nBLOCK: Block the enemy's attack (1/2 damage)\nITEM:	Use an item\nDISARM:	Have a chance to dodge an enemy's attack.";
	m_Description.append(Description);
}

RoomName Room_4::processInput(String a_Input)
{
	RoomName room = m_room;
	m_hasEntered = true;
	String printOut("");
	a_Input.toLower(true);
	if (!m_enemyAlive) {
		if (a_Input.equalTo(Right)) {
			room = ROOM_3;
		}

		if (a_Input.equalTo(Search)) {
			if (!m_hasSearched) {
				m_hasSearched = true;
				
				printOut.append("You Found a key with a large skull on the handle");
			}
			else {
				printOut.append("You Found nothing of use to you");
			}
		}
	}
	if (printOut.length()) {
		Window::SetXY(inputLocationX, inputLocationY);;
		Window::ClearSection(pOutputText);
		Window::DrawLine(outputLocationX, outputLocationY, GREEN, printOut.cStr(), 60);
	}

	return room;
}

Room_5::Room_5()
{
	m_room = ROOM_5;
	m_hasEntered = false;
	m_hasKey = false;
	m_hasSearched = false;
	char Description[] = "This small room contains several pieces of what was once well-polished wood furniture. Eight ornate, high-backed chairs surround a long oval table, and a side table stands next to the far exit. All bear delicate carvings of various shapes. One bears carvings of skulls and bones, another is carved with shields and magic circles, and a third is carved with shapes like flames and lightning strokes.\nSEARCH:		Take a look around the room \nLEFT : You can see a door to your left \nDOWN : You can see a door behind you";
	m_Description.append(Description);
}

RoomName Room_5::processInput(String a_input)
{
	RoomName room = m_room;
	m_hasEntered = true;
	String printOut("");
	a_input.toLower(true);


	if (a_input.equalTo(Left)) {
		if (m_hasKey) {
			printOut.append(" You enter a long corridor that you follow, it reaches a 90 degree turn and you continue down until you reach a door.");
			room = ROOM_6;

		}
		else {
			printOut.append(" The door is locked you must find the key");
		}
	}
	if (a_input.equalTo(Down)) {
		room = ROOM_3;
	}
	if (a_input.equalTo(Search)) {
		if (!m_hasSearched) {
			m_hasSearched = true;
			printOut.append(" You Found a scroll of healing. How on earth is a scroll supposed to heal you?");
		}
		else {
			printOut.append("You Found nothing of use to you");
		}
	}
	if (printOut.length()) {
		Window::SetXY(inputLocationX, inputLocationY);;
		Window::ClearSection(pOutputText);
		Window::DrawLine(outputLocationX, outputLocationY, GREEN, printOut.cStr(), 60);
	}

	return room;
}

Room_6::Room_6()
{
	m_room = ROOM_6;
	m_hasEntered = false;
	char Description[] = "Rats inside the room shriek when they hear the door open, then they run in all directions from a putrid corpse lying in the center of the floor. As these creatures crowd around the edges of the room, seeking to crawl through a hole in one corner, they fight one another. The stinking corpse in the middle of the room looks human, but the damage both time and the rats have wrought are enough to make determining its race by appearance an extremely difficult task at best.\nSEARCH:		Take a look around the room\nUP    :You can see a door ahead \nDOWN  :You can see a door behind you \nRIGHT  :You can see a door to your right";
	m_Description.append(Description);
	m_hasSearched = false;

}

RoomName Room_6::processInput(String a_input)
{
	RoomName room = m_room;
	m_hasEntered = true;
	String printOut("");
	a_input.toLower(true);

	if (a_input.equalTo(Up)) {
		room = ROOM_5;
	}
	if (a_input.equalTo(Right)) {
		room = ROOM_9;
	}
	if (a_input.equalTo(Down)) {
		room = ROOM_7;
	}
	if (a_input.equalTo(Search)) {
		m_hasSearched = true;
		printOut.append("You Found nothing of use to you");
	}

	if (printOut.length()) {
		Window::SetXY(inputLocationX, inputLocationY);;
		Window::ClearSection(pOutputText);
		Window::DrawLine(outputLocationX, outputLocationY, GREEN, printOut.cStr(), 60);
	}

	return room;
}

Room_7::Room_7()
{
	m_room = ROOM_7;
	m_hasEntered = false;
	m_innocentAlive = true;
	m_hasSearched = false;
	char Description[] = "Burning torches in iron sconces line the walls of this room, lighting it brilliantly. At the room's center lies a squat stone altar, its top covered in recently spilled blood. A channel in the altar funnels the blood down its side to the floor where it fills grooves in the floor that trace a pattern or symbol around the altar. As you enter the room to a scream and a woman voice beg 'Please dont hurt me'you see something run and cower at the back of the room\nSEARCH:		Take a look around the room\nUP    :You can see a door ahead \nRIGHT  :You can see a door to your right \nATTACK:	Attack the creature";
	m_Description.append(Description);
}

RoomName Room_7::processInput(String a_input)
{
	RoomName room = m_room;
	m_hasEntered = true;
	String printOut("");
	a_input.toLower(true);


	if (a_input.equalTo(Up)) {
		room = ROOM_6;
	}
	if (a_input.equalTo(Right)) {
		if (m_hasKey) {
			room = ROOM_8;
		}
		else {
			printOut.append("The door is locked you must find the key");
		}
	}
	if (a_input.equalTo(Search)) {
		if (!m_hasSearched) {
			m_hasSearched = true;
			printOut.append("You Found a scroll of immortality. Neat");
		}
		else {
			printOut.append("You Found nothing of use to you");
		}
	}
	if (a_input.equalTo(Attack)) {
		
		m_hasAttacked = true;
		return room;
	}
	if (printOut.length()) {
		Window::SetXY(inputLocationX, inputLocationY);;
		Window::ClearSection(pOutputText);
		Window::DrawLine(outputLocationX, outputLocationY, GREEN, printOut.cStr(), 60);
	}

	return room;
}

Room_8::Room_8()
{
	m_room = ROOM_8;
	m_hasEntered = false;
	m_enemyAlive = true;
	m_hasSearched = false;
	m_leverPulled = false;
	char Description[] = "You enter the room and there is an enemy!! quick defend yourself *epic music* \nATTACK: Attack the enemy\nBLOCK: Block the enemy's attack (1/2 damage)\nITEM:	Use an item\nDISARM:	Have a chance to dodge an enemy's attack.";
	m_Description.append(Description);
}

RoomName Room_8::processInput(String a_Input)
{
	RoomName room = m_room;
	m_hasEntered = true;
	String printOut("");
	a_Input.toLower(true);


	if (!m_enemyAlive) {
		if (a_Input.equalTo(Up)) {
			room = ROOM_9;
		}
		if (a_Input.equalTo(Left)) {
			room = ROOM_7;
		}

		if (a_Input.equalTo(Search)) {
			if (!m_hasSearched) {
				m_hasSearched = true;
				m_leverPulled = true;
				printOut.append("You Found a lever and pulled it. you hear the sound of stone on stone to the right");
			}
			else {
				printOut.append("You Found nothing of use to you");
			}
		}
	}
	if (printOut.length()) {
		Window::SetXY(inputLocationX, inputLocationY);;
		Window::ClearSection(pOutputText);
		Window::DrawLine(outputLocationX, outputLocationY, GREEN, printOut.cStr(), 60);
	}

	return room;
}


Room_9::Room_9()
{
	m_room = ROOM_9;
	m_hasEntered = false;
	char Description[] = "Tapestries decorate the walls of this room. Although they may once have been brilliant in hue, they now hang in graying tatters. Despite the damage of time and neglect, you can perceive once-grand images of wizards' towers, magical beasts, and symbols of spellcasting\nSEARCH:		Take a look around the room\nUP    :You can see a door ahead\nLEFT  :You can see a door to your left \nRIGHT  :You can see a door to your right";
	m_Description.append(Description);
	m_hasSearched = false;

}

RoomName Room_9::processInput(String a_input)
{
	RoomName room = m_room;
	m_hasEntered = true;
	String printOut("");
	a_input.toLower(true);


	if (a_input.equalTo(Up)) {
		room = ROOM_10;
	}
	if (a_input.equalTo(Right)) {
		if (m_hasKey) {
			room = START;
		}
		else {
			printOut.append("\nThe door is locked you must find the key");
		}
	}
	if (a_input.equalTo(Left)) {
		room = ROOM_6;
	}
	if (a_input.equalTo(Down)) {
		if (m_hasKey) {
			room = ROOM_8;
		}
		else {
			printOut.append("\nThe door is locked you must find the key");
		}
	}
	if (a_input.equalTo(Search)) {
		m_hasSearched = true;
		printOut.append("\nYou Found nothing of use to you");
		
	}
	if (printOut.length()) {
		Window::SetXY(inputLocationX, inputLocationY);;
		Window::ClearSection(pOutputText);
		Window::DrawLine(outputLocationX, outputLocationY, GREEN, printOut.cStr(), 60);
	}

	return room;
}

Room_10::Room_10()
{
	m_room = ROOM_10;
	m_hasEntered = false;
	m_enemyAlive = true;
	m_hasSearched = false;
	char Description[] = "You enter the room and there is an enemy!! quick defend yourself *epic music*\nATTACK: Attack the enemy\nBLOCK: Block the enemy's attack (1/2 damage)\nITEM:	Use an item\nDISARM:	Have a chance to dodge an enemy's attack.";
	m_Description.append(Description);
}

RoomName Room_10::processInput(String a_Input)
{
	RoomName room = m_room;
	m_hasEntered = true;
	String printOut("");
	a_Input.toLower(true);

	if (!m_enemyAlive) {
		if (a_Input.equalTo(Down)) {
			room = ROOM_9;
		}

		if (a_Input.equalTo(Search)) {
			if (!m_hasSearched) {
				m_hasSearched = true;

				printOut.append("You Found a key with a small hand as the handle");
			}
			else {
				printOut.append("You Found nothing of use to you");
			}
		}
	}
	if (printOut.length()) {
		Window::SetXY(inputLocationX, inputLocationY);;
		Window::ClearSection(pOutputText);
		Window::DrawLine(outputLocationX, outputLocationY, GREEN, printOut.cStr(), 60);
	}

	return room;
}

Boss::Boss()
{
	m_room = BOSS_1;
	m_hasEntered = false;
	m_win = false;
	char Description[] = "You open the door and before you is a dragon's hoard of treasure. Coins cover every inch of the room, and jeweled objects of precious metal jut up from the money like glittering islands in a sea of gold. OH NO a Dragon\nATTACK	:Attack the creature\nBLOCK: Block the enemy's attack (1/2 damage)\nITEM:	Use an item\nDISARM:	Have a chance to dodge an enemy's attack.";
	m_Description.append(Description);
	m_bossAlive = true;
}

RoomName Boss::processInput(String a_Input)
{
	RoomName room = m_room;
	m_hasEntered = true;
	String printOut("");
	a_Input.toLower(true);

	if (!m_bossAlive) {
		if (a_Input.equalTo(Up)) {
			room = START;
		}

		if (printOut.length()) {
			Window::SetXY(inputLocationX, inputLocationY);;
			Window::ClearSection(pOutputText);
			Window::DrawLine(outputLocationX, outputLocationY, GREEN, printOut.cStr(), 60);
		}

		return room;
	}
	return room;
}
