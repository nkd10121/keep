#include <iostream>
#include <vector>

using namespace std;

//�I�u�W�F�N�g�w���̎O��v�f
//�@�J�v�Z����
//�A�p��
//�B�|�����[�t�B�Y��

struct MonsterParameter
{
	int hp;
	int at;
	int def;
	void Clear()
	{
		hp = 0;
		at = 0;
		def = 0;
	}
private:
	int himitu;
};

class Animal;

class Monster
{
	friend Animal;
private:
	//�O���Ɍ��J�������Ȃ��֐�
	//Monster���g�ł����Ăяo���Ȃ��֐�
	float DistanceToPlayer()
	{
		return 3.14f;
	}
public:
	//�O���Ɍ��J�������֐�
	//Monster�̎����傪�Ăяo����֐�
	virtual void Attack() = 0;

};

class Slimu : public Monster
{
public:
	void Attack()
	{
		cout << "�n����" << endl;
	}
};

class Doragon : public Monster
{
public:
	void Attack()
	{
		cout << "�u���X" << endl;
	}
};

class zonbi : public Monster
{
public:
	void Attack()
	{
		cout << "����" << endl;
	}
};


class Animal
{
protected:
	int age_;
	Slimu slimu;
public:
	int GetAge() const
	{
		return age_;
	}
	//float GetDis()
	//{
	//	slimu.
	//}

	virtual void Attack() = 0;

};

class Dog : public Animal
{
public:
	Dog()
	{
		age_ = 2;
	}

	void Attack()
	{
		cout << "���݂�" << endl;
	};
};

class Cat : public Animal
{
public:
	Cat()
	{
		age_ = 3;
	}

	void Attack() 
	{
		cout << "�Ђ�����" << endl;
	};
};

void RepeatAttack(Animal& animal, int rep)
{
	for (int i = 0; i < rep; i++)
	{
		animal.Attack();
	}
}

class Rabbit : public Animal
{
public:
	void Attack()
	{
		cout << "��x����" << endl;
	}
};

int main()
{
	//Dog dog;
	//Cat cat;
	//Rabbit rabbit;

	//cout << "DogAge = " << dog.GetAge() << endl;
	//cout << "CatAge = " << cat.GetAge() << endl;
	//
	//RepeatAttack(dog, 3);
	//RepeatAttack(cat, 2);
	//RepeatAttack(rabbit, 2);

	//dog.Attack();
	//cat.Attack();

	std::vector<Monster*> monsters(10);
	for (int i = 0; i < 10; i++)
	{
		monsters.push_back(new Slimu());
		monsters.push_back(new Doragon());
		monsters.push_back(new zonbi());
	}

	for (auto monster : monsters)
	{
		monster->Attack();
	}

	MonsterParameter mParameter;
	mParameter.Clear();
	return 0;
}