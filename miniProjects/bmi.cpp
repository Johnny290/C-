#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main()
{
	float weight, height, bmi;
	cout << "weight(kg): ";
	cin >> weight;
	cout << "height(m): ";
	cin >> height;
	bmi = weight / (height * height);
	cout << bmi;

	if (bmi < 18.5)
		cout << " Underweight" << endl;
	else if (bmi > 25)
		cout << " Overweight" << endl;	
	else 
		cout << " Normal weight" << endl;
	cout << " BMI: " << bmi;
	cin.get();
	return 0;

}
