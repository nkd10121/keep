#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*テンプレート関数*/
template<typename T>
T Add(T a, T b)
{
	return  a + b;
}

/*テンプレート関数*/
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

	////int型の動的配列
	//std::vector<int> ivec;
	////float型の動的配列
	//std::vector<float> fvec;
	////string型の動的配列
	//std::vector<string> svec;
	////Enemy型の動的配列
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

	////'o'の場所を取得
	auto idx = str.find('o');

	cout << idx << endl;					//前から探す
	cout << str.find('o', idx + 1) << endl;	//2つ目の'o'
	cout << str.rfind('o') << endl;			//後ろから探す

	str = "Hello,World";
	idx = str.find(',');
	cout << str.substr(idx + 1) << endl;					//前から探す

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

	////strの長さを取得
	//cout << str.length() << endl;
	//cout << str << endl;

	return 0;
}
