#ifndef _ROOM_H_
#define _ROOM_H_
// Full version
#include "string.h"
#include "window.h"

// define the rooms for the ship
enum RoomName {
	START, ROOM_1, ROOM_2, ROOM_3, ROOM_4, ROOM_5, ROOM_6,
	ROOM_7, ROOM_8, ROOM_9, ROOM_10, BOSS_1};

class NewRoom {
public:
	NewRoom() { }
	NewRoom(String a_Description) : m_Description(a_Description) { }
	~NewRoom() { }
	void printRoom() {

		Rect roomDesc =  { 35,15,60,16  };
		Window::ClearSection(roomDesc);
		Window::DrawLine(35, 15, YELLOW, m_Description.cStr(), 60);
	};
	virtual RoomName processInput(String a_input) = 0;
	bool ReturnEntered() { return m_hasEntered; };
	bool returnHasSearched() { return m_hasSearched; }
	void setSearched(bool a_hasEntered) { m_hasEntered = a_hasEntered; }

protected:
	String m_Description;
	RoomName m_room;
	bool m_hasEntered;
	bool m_hasSearched;
};

// START room
class StartRoom : public NewRoom
{
public:
	StartRoom();
	StartRoom(String a_Description) : NewRoom(a_Description) {
		m_room = START;
		m_hasEntered = true;
	} 
	RoomName processInput(String a_input);
	void SetIsChained(bool a_chained) {
		m_isChained = a_chained;
	}
	void setbossRoomOpen(bool a_bossRoomOpen) { m_bossRoomOpen = a_bossRoomOpen; }
	void setHasKey(bool a_hasKey) { m_hasKey = a_hasKey; };


private:
	bool m_hasKey;
	bool m_isChained;
	bool m_bossRoomOpen;
	bool m_firstTime;

};


class Room_1 : public NewRoom
{
public:
	String clearedRoom;

	Room_1();
	Room_1(String a_Description) : NewRoom(a_Description) {};
	RoomName processInput(String a_input);
	bool getEnemyAlive() { return m_enemyAlive; }
	void setEnemyAlive(bool a_alive) { m_enemyAlive = a_alive; }
	void setMDescription() { m_Description.setString("The manacles set into the walls of this room give you the distinct impression that it was used as a prison and torture chamber, although you can see no evidence of torture devices. One particularly large set of manacles have been broken open.\nSEARCH:		Take a look around the room \nUP : You can see a door ahead of you \nDOWN : You can see a door behind you"); }
private:
	bool m_enemyAlive;

};

class Room_2 : public NewRoom
{
public:
	Room_2();
	Room_2(String a_Description) : NewRoom(a_Description) {};
	RoomName processInput(String a_input);
	
private:


};


class Room_3 : public NewRoom
{
public:
	Room_3();
	Room_3(String a_Description) : NewRoom(a_Description) {};
	RoomName processInput(String a_input);


private:

};


class Room_4 : public NewRoom
{
public:
	Room_4();
	Room_4(String a_Description) : NewRoom(a_Description) {};
	bool getEnemyAlive() { return m_enemyAlive; }
	void setEnemyAlive(bool a_alive) { m_enemyAlive = a_alive; }
	RoomName processInput(String a_input);
	void setMDescription() { m_Description.setString("You look around and find that the room is full of destroyed crates and boxes as if it was used as a storage room.\nSEARCH:		Take a look around the room \nRIGHT  :You can see a door to your right"); }
private:
	bool m_enemyAlive;
	bool m_hasSearched;

};

class Room_5 : public NewRoom
{
public:
	Room_5();
	Room_5(String a_Description) : NewRoom(a_Description) {};
	RoomName processInput(String a_input);
	void setHasKey(bool a_hasKey) { m_hasKey = a_hasKey; };
private:
	bool m_hasKey; 
	bool m_hasSearched;
};

class Room_6 : public NewRoom
{
public:
	Room_6();
	Room_6(String a_Description) : NewRoom(a_Description) {};
	RoomName processInput(String a_input);
private:


};

class Room_7 : public NewRoom
{
public:
	Room_7();
	Room_7(String a_Description) : NewRoom(a_Description) {};
	RoomName processInput(String a_input);
	bool getAttacked() { return m_hasAttacked; }
	bool getInnocentAlive() {return m_innocentAlive; }
	void setInnocentAlive(bool a_innocentAlive) { m_innocentAlive = a_innocentAlive; }
	void setHasKey(bool a_hasKey) { m_hasKey = a_hasKey; };
	void setMDescription() { m_Description.setString("Burning torches in iron sconces line the walls of this room, lighting it brilliantly. At the room's center lies a squat stone altar, its top covered in recently spilled blood. A channel in the altar funnels the blood down its side to the floor where it fills grooves in the floor that trace a pattern or symbol around the altar.\nSEARCH:		Take a look around the room\nUP    :You can see a door ahead \nRIGHT  :You can see a door to your right "); }
private:
	bool m_innocentAlive;
	bool m_hasAttacked;
	bool m_hasKey;
};

class Room_8 : public NewRoom
{
public:
	Room_8();
	Room_8(String a_Description) : NewRoom(a_Description) {};
	RoomName processInput(String a_input);
	bool getEnemyAlive() { return m_enemyAlive; }
	void setEnemyAlive(bool a_alive) { m_enemyAlive = a_alive; }
	void setLeverPulled(bool a_leverPulled) { m_leverPulled = a_leverPulled; }
	bool getLeverPulled() { return m_leverPulled; }
	void setMDescription() { m_Description.setString(" The scent of earthy decay assaults your nose upon peering through the open door to this room. Smashed bookcases and their sundered contents litter the floor. Paper rots in mold-spotted heaps, and shattered wood grows white fungus.\nSEARCH:		Take a look around the room \nUP : You can see a door ahead of you \nLEFT  :You can see a door to your left"); }

private:
	bool m_enemyAlive;
	bool m_leverPulled;
};

class Room_9 : public NewRoom
{
public:
	Room_9();
	Room_9(String a_Description) : NewRoom(a_Description) {};
	RoomName processInput(String a_input);
	void setHasKey(bool a_hasKey) { m_hasKey = a_hasKey; };

private:
	bool m_hasKey;


};

class Room_10 : public NewRoom
{
public:
	Room_10();
	Room_10(String a_Description) : NewRoom(a_Description) {};
	bool getEnemyAlive() { return m_enemyAlive; }
	void setEnemyAlive(bool a_alive) { m_enemyAlive = a_alive; }
	RoomName processInput(String a_input);
	void setMDescription() { m_Description.setString("This small chamber seems divided into three parts.The first has several hooks on the walls from which hang dusty robes.A half wall separates that space from the next, which has a dry basin set in the floor."); }
private:
	bool m_enemyAlive;

};

// Boss room
class Boss : public NewRoom
{
public:
	Boss();
	Boss(String a_Description) : NewRoom(a_Description) {};
	RoomName processInput(String a_input);
	bool getEnemyAlive() { return m_bossAlive; }
	void setEnemyAlive(bool a_alive) { m_bossAlive = a_alive; }
	bool getWin() { return m_bossAlive; }
	bool setKilledInnocent(bool a_killedInnocent) { m_killedInnocent = a_killedInnocent; }
private:
	bool m_win;
	bool m_killedInnocent;
	bool m_bossAlive;
};

#endif