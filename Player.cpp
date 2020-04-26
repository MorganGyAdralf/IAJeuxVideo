#include "Player.h"

Player::Player(GameWorld* p_world) : currentWorld_(p_world) {
	playerPosition_ = currentWorld_->spawnPlayer();
	playerDestination_ = playerPosition_;
	playerLookingDirection_ = Direction::North;
}

Player::~Player() {

}

bool Player::attackAMeleeTarget() const {	// Fonction qui vérifie si une cible est à côté du joueur et la détruit dans ce cas
	if (currentWorld_->playerCanAdvance(playerPosition_, Direction::East).second == SquareType::Target) {
		currentWorld_->attackTarget(playerPosition_, Direction::East);
		cout << "PLAYER:: j'ai attaque a l'est" << endl;
		return true;
	}
	else if (currentWorld_->playerCanAdvance(playerPosition_, Direction::North).second == SquareType::Target) {
		currentWorld_->attackTarget(playerPosition_, Direction::North);
		cout << "PLAYER:: j'ai attaque au nord" << endl;
		return true;
	}
	else if (currentWorld_->playerCanAdvance(playerPosition_, Direction::South).second == SquareType::Target) {
		currentWorld_->attackTarget(playerPosition_, Direction::South);
		cout << "PLAYER:: j'ai attaque au sud" << endl;
		return true;
	}
	else if (currentWorld_->playerCanAdvance(playerPosition_, Direction::West).second == SquareType::Target) {
		currentWorld_->attackTarget(playerPosition_, Direction::West);
		cout << "PLAYER:: j'ai attaque a l'ouest" << endl;
		return true;
	}
	else {
		cout << "PLAYER:: pas de cible a attaquer" << endl;
		return false;
	}
}

bool Player::findClosestTarget() {	// Fonction qui tente de trouver la cible la plus proche, et la prends comme destination
	playerDestination_ = currentWorld_->findclosestTarget(playerPosition_);
	if (playerDestination_ == playerPosition_) {
		cout << "PLAYER:: pas de cible trouvee" << endl;
		return false;
	}
	cout << "PLAYER:: cible trouvee en " << playerDestination_.first << " " << playerDestination_ .second << endl;
	return true;
}

void Player::turnTowardClosestTarget() {	// Fonction qui tourne le joueur dans la direction de sa cible
	int t_xDist = playerDestination_.first - playerPosition_.first;
	int t_yDist = playerDestination_.second - playerPosition_.second;
	if (abs(t_xDist) >= abs(t_yDist)) {
		if (t_xDist > 0) {
			playerLookingDirection_ = Direction::East;
			cout << "PLAYER:: je me tourne vers l'est" << endl;
		}
		else {
			playerLookingDirection_ = Direction::West;
			cout << "PLAYER:: je me tourne vers l'ouest" << endl;
		}
	}
	else {
		if (t_yDist > 0) {
			playerLookingDirection_ = Direction::North;
			cout << "PLAYER:: je me tourne vers le nord" << endl;
		}
		else {
			playerLookingDirection_ = Direction::South;
			cout << "PLAYER:: je me tourne vers le sud" << endl;
		}
	}
}

pair<bool, SquareType> Player::canAdvance() const {	// Fonction qui vérifie si le joueur peut avancer
	return currentWorld_->playerCanAdvance(playerPosition_, playerLookingDirection_);
}

void Player::advance() {	// Fonction qui avance le joueur d'une case dans la direction vers laquelle il est tourné
	playerPosition_ = currentWorld_->advancePlayer(playerPosition_, playerLookingDirection_);
	cout << "PLAYER:: j'ai avance d'une case" << endl;
}

bool Player::turnForWall() {	// Fonction qui tourne le joueur pour qu'il évite un mur
	if (playerLookingDirection_ == Direction::East || playerLookingDirection_ == Direction::West) {
		if (currentWorld_->playerCanAdvance(playerPosition_, Direction::North).first) {
			playerLookingDirection_ = Direction::North;
			cout << "PLAYER:: je me tourne vers le nord" << endl;
		}
		else if (currentWorld_->playerCanAdvance(playerPosition_, Direction::South).first) {
			playerLookingDirection_ = Direction::South;
			cout << "PLAYER:: je me tourne vers le sud" << endl;
		}
		else {
			cout << "PLAYER:: pas moyen de contourner le mur" << endl;
			return false;
		}
	}
	else {
		if (currentWorld_->playerCanAdvance(playerPosition_, Direction::East).first) {
			playerLookingDirection_ = Direction::East;
			cout << "PLAYER:: je me tourne vers l'est" << endl;
		}
		else if (currentWorld_->playerCanAdvance(playerPosition_, Direction::West).first) {
			playerLookingDirection_ = Direction::West;
			cout << "PLAYER:: je me tourne vers l'ouest" << endl;
		}
		else {
			cout << "PLAYER:: pas moyen de contourner le mur" << endl;
			return false;
		}
	}
	return true;
}

bool Player::hasNotAttainedObjective() const {	// Fonction qui vérifie si le joueur a atteint son objectif, c'est-à-dire s'il est à la "verticale" de sa cible
	int t_distRest;
	if (playerLookingDirection_ == Direction::East || playerLookingDirection_ == Direction::West)
		t_distRest = abs(playerDestination_.first - playerPosition_.first);
	else
		t_distRest = abs(playerDestination_.second - playerPosition_.second);
	cout << "PLAYER:: distance restante a l'objectif : " << t_distRest << endl;
	return (t_distRest > 0);
}

bool Player::gameIsOn() const {	// Fonction qui regarde si le jeu continue
	return currentWorld_->gameIsOngoing();
}