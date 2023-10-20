#pragma once
class Player
{
public:
	Player();
	~Player();
	
	void Init();
	void Update();
	void Draw();

private:
	int posUp;
	int posRight;
	int posLeft;
	int posDown;


};

