#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*�e���v���[�g�֐�*/
template<typename T>
T Add(T a, T b)
{
	return  a + b;
}

/*�e���v���[�g�֐�*/
template<typename T>
class Array {
private:
	T array_[10];
public:
	Array()
	{
		float start = 3.14f;
		for (T& a : array_)
		{
			a = start;
			start += 0.1f;
		}
	}

	void OutPut()
	{
		for (const T& a : array_)
		{
			cout << a << endl;
		}
	}
};

int main()
{
	constexpr int row = 3;
	constexpr int col = 4;

	//cout << Add(row, col) << endl;
	//cout << Add(3.14f, 2.71f) << endl;
	//cout << Add(string("Hallo"), string("World")) << endl;

	Array<int> iarray;
	Array<float> farray;

	//iarray.OutPut();
	//farray.OutPut();

	////int�^�̓��I�z��
	//std::vector<int> ivec;
	////float�^�̓��I�z��
	//std::vector<float> fvec;
	////string�^�̓��I�z��
	//std::vector<string> svec;
	////Enemy�^�̓��I�z��
	//std::vector<Enemy> enemies;

	//vector<int> array_ = { 1,2,3,4,5 };

	//array_ .push_back(9);
	//
	//for (auto& a : array_)
	//{
	//	cout << a << endl;
	//}

	string str = "Hello";

	str += "World";

	////'o'�̏ꏊ���擾
	auto idx = str.find('o');

	cout << idx << endl;					//�O����T��
	cout << str.find('o', idx + 1) << endl;	//2�ڂ�'o'
	cout << str.rfind('o') << endl;			//��납��T��

	str = "Hello,World";
	idx = str.find(',');
	cout << str.substr(idx + 1) << endl;					//�O����T��

	str = "Hello,World,Fukuoka";

	idx = 0;
	do
	{
		int nidx = str.find(',', idx);
		if (nidx == std::string::npos) {
			cout << str.substr(idx) << endl;
			break;
		}
		cout << str.substr(idx, nidx - idx) << endl;
		idx = nidx + 1;
	} while (idx != std::string::npos);

	////str�̒������擾
	//cout << str.length() << endl;
	//cout << str << endl;

	return 0;
}
