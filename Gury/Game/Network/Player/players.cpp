
#include "../Gury/Game/World/camera.h"
#include "../Gury/Game/Objects/part.h"

#include "../Gury/Game/Objects/mesh.h"

#include "../Gury/Game/Objects/Humanoid/humanoid.h"

#include "../Gury/Game/Serializer/serializer.h"
#include "../Gury/Game/Network/replicator.h"

#include "../Gury/Game/World/workspace.h"

#include "players.h"

using namespace RBX::Network;

RTTR_REGISTRATION
{
	rttr::registration::class_<RBX::Network::Players>("Players")
		.constructor<>()
		.property_readonly("LocalPlayer", &RBX::Network::Players::getLocalPlayer)(rttr::metadata("Serializable", false))
		.property("maxPlayers", &RBX::Network::Players::getMaxPlayers, &RBX::Network::Players::setMaxPlayers)(rttr::metadata("Type", RBX::Data))
		.property_readonly("numPlayers", &RBX::Network::Players::getNumPlayers)(rttr::metadata("Type", RBX::Data), rttr::metadata("Serializable", false))
		.method("createLocalPlayer", &RBX::Network::Players::createLocalPlayer);
}


Player* Players::createLocalPlayer(int userId)
{
	Player* player;

	if (localPlayer)
	{
		throw std::runtime_error("Local player already exists");
	}

	player = new Player();

	if (userId == 0)
		userId++;

	player->userId = userId;
	player->setName("Player");

	localPlayer = player;
	addPlayer(player);

	return localPlayer;
}

void RBX::Network::Players::setPlayerList(RBX::Gui::GuiList* _playerList)
{
	playerList = _playerList;
}

void Players::destroyPlayer(Player* plr)
{
	players.erase(std::remove(players.begin(), players.end(), plr));
	delete& plr;
}

void Players::addPlayer(Player* player)
{
	RBX::Gui::GuiLabel* lbl;

	lbl = new RBX::Gui::GuiLabel();

	lbl->textColor = Color3::wheelRandom();
	lbl->title = player->getName();
	lbl->sz = 10;

	players.push_back(player);

	playerList->visible = true;
	playerList->addChild(lbl);
}

void Players::updatePlayerList()
{
	for (unsigned int i = 0; i < players.size(); i++)
	{
		Player* p = players.at(i);
		RBX::Gui::GuiLabel* lbl = p->getGuiName();

		if (lbl && lbl->title != p->getName())
		{
			lbl->title = p->getName();
		}
	}
}

void RBX::Network::Players::onStep()
{
	if (localPlayer)
	{
		localPlayer->backpack->updateGui();
	}
}

RBX::ModelInstance* Players::findLocalCharacter()
{
	Players* players = Players::get();
	Player* player;

	player = players->localPlayer;

	if (player && (player->character))
		return player->character;

	return 0;
}

Players* RBX::Network::Players::get()
{
	return Datamodel::get()->players;
}
