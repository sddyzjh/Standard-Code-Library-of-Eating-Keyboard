/*
 require c++11 support
*/
#include <chrono>
using namespace chrono;
int main(){
	auto start = system_clock::now();
	//do something
	auto end   = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	cout << double(duration.count()) * microseconds::period::num / microseconds::period::den << endl;
}