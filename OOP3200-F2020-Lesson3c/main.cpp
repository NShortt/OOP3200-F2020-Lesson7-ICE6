#include <iomanip>
#include <iostream>
#include <map>
#include <fstream>
#include <cstdlib>

#include <vector>

#include "GameObject.h"
#include "Vector3D.h"


static void BuildGameObjects(std::vector<GameObject*>& game_objects, const int num = 2)
{
	for (auto count = 0; count < num; ++count)
	{
		int id;
		std::cout << "Enter the gameObject's ID: ";
		std::cin >> id;
		Vector2D<float> point;
		std::cout << "Enter the gameObject's Position (x, y): ";
		std::cin >> point;
		std::cout << "\n--------------------------------------------------------------" << std::endl;
		std::cout << "You Entered " << id << " for the gameObject's ID " << std::endl;
		std::cout << "You Entered " << point << " for the gameObject's Position" << std::endl;
		std::cout << "--------------------------------------------------------------\n" << std::endl;
		auto* gameObject = new GameObject(id, point);
		game_objects.push_back(gameObject);
	}
	
}

static void CompareGameObjects(GameObject* object1, GameObject* object2)
{
	std::cout << std::fixed << std::setprecision(3);
	std::cout << "Magnitude of first gameObject is: " << object1->GetPosition().GetMagnitude() << std::endl;
	std::cout << "Magnitude of second gameObject is: " << object2->GetPosition().GetMagnitude() << std::endl;
	std::cout << "Distance between first gameObject and second gameObject is: "
		<< Vector2D<float>::Distance(object1->GetPosition(), object2->GetPosition()) << std::endl;
	std::cout << "--------------------------------------------------------------\n" << std::endl;

	std::cout << "The angle (in degrees) from the first gameObject to the second gameObject is: "
		<< Vector2D<float>::SignedAngle(object1->GetPosition(), object2->GetPosition()) << std::endl;

	std::cout << "--------------------------------------------------------------\n" << std::endl;
	std::cout << "First Game Object Details:" << std::endl;
	std::cout << object1->ToString() << std::endl;

	std::cout << "Second Game Object Details:" << std::endl;
	std::cout << object2->ToString() << std::endl;
}

void PrintGameObjects(const std::map<std::string, GameObject*>& gameObjects)
{
	std::cout << "=================================" << std::endl;
	std::cout << "Output map of Game Objects" << std::endl;
	std::cout << "=================================" << std::endl;

	// For every game object in GameObjects....loop
	for (const auto& game_object : gameObjects)
	{
		std::cout << "Key  : " << game_object.first << std::endl;
		std::cout << "---------------------------------" << std::endl;
		std::cout << game_object.second->ToString() << std::endl;
		std::cout << "---------------------------------" << std::endl;
	}

}

int main()
{
	// Map is made up of key value pairs - here a key of string and value of GameObject
	std::map<std::string, GameObject*> gameObjects;

	auto* ship = new GameObject("Ship", 0, 3.0f, 4.0f);
	auto* enemy = new GameObject("Enemy", 1, 10.0f, 20.0f);

	gameObjects[ship->GetName()] = ship;
	gameObjects[enemy->GetName()] = enemy;
	
	PrintGameObjects(gameObjects);

	auto distance = Vector2D<float>::Distance(gameObjects["Ship"]->GetPosition(), gameObjects["Enemy"]->GetPosition());

	std::cout << "Distance between " << gameObjects["Ship"]->GetName()
		<< " and " << gameObjects["Enemy"]->GetName() << "is " << std::to_string(distance) << std::endl;

	std::ofstream outfile("GameObjects.txt", std::ios::out);
	outfile << gameObjects["Ship"]->ToFile() << std::endl;
	outfile << gameObjects["Enemy"]->ToFile() << std::endl;
	outfile.close();

	std::cout << "-----------------------------------------------------------------------------------------------------------------\n";
	std::cout << " END OF OUTPUT \n";
	std::cout << "-----------------------------------------------------------------------------------------------------------------\n";

	std::cout << "-----------------------------------------------------------------------------------------------------------------\n";
	std::cout << " STARTING INPUT \n";
	std::cout << "-----------------------------------------------------------------------------------------------------------------\n";



	std::ifstream infile;
	std::string fileName = "GameObjects.txt";

	infile.open(fileName.c_str());

	while (infile.is_open())
	{
		int id = 0;
		float x, y = 0.0f;
		std::string name;

		while (!infile.fail())
		{
			infile >> id >> name;
			infile.ignore(1, ' ');
			infile.ignore(1, '(');
			infile >> x;
			infile.ignore(1, ',');
			infile.ignore(1, ' ');
			infile >> y;
			infile.ignore(1, ')');

			auto* tempObject = new GameObject(name, id, x, y);

			gameObjects[name + "1"] = tempObject;
		}
		infile.close();
	}
	
	PrintGameObjects(gameObjects);

	//std::vector<GameObject*> gameObjects;

	//int num_of_GO;
	//std::cout << "How Many Game Objects do you need?: ";
	//std::cin >> num_of_GO;
	//std::cout << "\n--------------------------------------------------------------" << std::endl;

	//BuildGameObjects(gameObjects, num_of_GO);
	//
	//
	//int index1;
	//std::cout << "What is the First Object index?: ";
	//std::cin >> index1;
	//std::cout << "\n--------------------------------------------------------------" << std::endl;
	//int index2;
	//std::cout << "What is the Second Object index?: ";
	//std::cin >> index2;
	//std::cout << "\n--------------------------------------------------------------" << std::endl;
	//
	//CompareGameObjects(gameObjects[index1], gameObjects[index2]);
	//CompareGameObjects(gameObjects[index1], gameObjects[index2]);
}

