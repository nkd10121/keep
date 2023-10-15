#pragma once
#include <cmath>
//�x�N�g����֗��Ɏg�����߂̃N���X

//�w�b�_�[�t�@�C�������ڐA����΂����悤�ɂ���������
//�v���O������S���w�b�_�[�t�@�C���ɂ���
class Vec2
{
public:
	float x;
	float y;


public:
	Vec2() :
		x(0.0f),
		y(0.0f)
	{

	}

	Vec2(float posX, float posY) :
		x(posX),
		y(posY)
	{

	}
	//�P�����Z�q+ Vec2 = +Vec2
	Vec2 operator+ () const
	{
		//���g�̒l�����̂܂ܕԂ��΂���
		return *this;
	}

	//�P�����Z�q- Vec2 = -Vec2
	//�t�x�N�g�������߂�Ƃ��Ɏg��
	Vec2 operator- () const
	{
		return Vec2{ -x,-y };
	}

	//�����Z
	Vec2 operator+(Vec2 vec) const
	{
		return Vec2{ x + vec.x,y + vec.y };
	}

	//Vec2 += Vec2
	Vec2 operator+= (Vec2 vec)
	{
		x += vec.x;
		y += vec.y;
		return *this;
	}

	//�����Z
	Vec2 operator-(Vec2 vec) const
	{
		return Vec2{ x - vec.x,y - vec.y };
	}

	//Vec2 -= Vec2
	Vec2 operator-= (Vec2 vec)
	{
		x -= vec.x;
		y -= vec.y;
		return *this;
	}

	//�|���Z
	Vec2 operator* (float scale) const
	{
		return Vec2{ x * scale,y * scale };
	}

	//Vec2 *= float;
	Vec2 operator*= (float scale)
	{
		x *= scale;
		y *= scale;
		return *this;
	}

	//����Z
	Vec2 operator/ (float scale) const
	{
		return Vec2{ x / scale,y / scale };
	}

	//Vec2 /= float;
	Vec2 operator/= (float scale)
	{
		x /= scale;
		y /= scale;
		return *this;
	}


	//�x�N�g���̒�����2������߂�(�������y�����邽��)
	float sqLength() const
	{
		return x * x + y * y;
	}

	//�x�N�g���̒��������߂�
	float Length() const
	{
		return sqrtf(sqLength());
	}

	//���g�̐��K�����s��
	void normalize()
	{
		float len = Length();
		if (len > 0.0f)
		{
			x /= len;
			y /= len;
		}
		//����0�̏ꍇ�͉������Ȃ�
	}

	//���g�𐳋K�������x�N�g�����擾����
	Vec2 getNormalize() const
	{
		float len = Length();
		if (len > 0.0f)
		{
			return Vec2{ x / len, y / len };
		}
		//������0�̏ꍇ
		return Vec2{ 0.0f,0.0f };
	}
};

